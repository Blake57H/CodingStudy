#include <iostream>
#include <string.h>
#include <vector>
#include <cassert>

class Node
{
public:
    Node(std::string val, Node *left, Node *right)
    {
        this->val = val;
        this->left = left;
        this->right = right;
    }
    Node(std::string val, Node *left) : Node(val, left, nullptr) {}
    Node(std::string val) : Node(val, nullptr, nullptr) {}
    ~Node()
    {
        // std::cout << this->val << ": deleting left node \n";
        delete this->left;
        this->left = nullptr;
        // std::cout << this->val << ": deleting right node \n";
        delete this->right;
        this->right = nullptr;
    }
    std::string to_str()
    {
        return "Node(" + this->val + ", " + (this->left == nullptr ? "null" : this->left->to_str()) + ", " + (this->right == nullptr ? "null" : this->right->to_str()) + ")";
    }
    std::string get_val()
    {
        return this->val;
    }
    Node *get_left()
    {
        return this->left;
    }
    Node *get_right()
    {
        return this->right;
    }
    void set_left(Node *left)
    {
        this->left = left;
    }
    void set_right(Node *right)
    {
        this->right = right;
    }

private:
    std::string val;
    Node *left = nullptr;
    Node *right = nullptr;
};


enum class ReadState
{
    RootNode,
    NodeVal,
    LeftNode,
    RightNode
};

std::string print_read_state(const ReadState &state)
{
    switch (state)
    {
    case ReadState::RootNode:
        return "ReadState::RootNode";
    case ReadState::NodeVal:
        return "ReadState::NodeVal";
    case ReadState::LeftNode:
        return "ReadState::LeftNode";
    case ReadState::RightNode:
        return "ReadState::RightNode";

    default:
        return "Invalid state";
    }
}

void display_error(const char reading_subject[])
{
}

static void print_stack(std::vector<ReadState> state_stack, std::vector<std::string> val_stack, std::vector<Node *> node_stack)
{
    for (auto subject : state_stack)
    {
        std::cout << print_read_state(subject) << " ";
    }
    std::cout << std::endl;
    for (auto subject : val_stack)
    {
        std::cout << subject << " ";
    }
    std::cout << std::endl;
    for (auto subject : node_stack)
    {
        std::cout << (subject == nullptr ? "null" : subject->to_str()) << " ";
    }
    std::cout << std::endl;
}

static Node *deserialize_no_lib(const std::string &node_str)
{
    int l_ptr = 0, r_ptr = 0, str_len = node_str.length();
    std::vector<ReadState> state_stack; // the last one is what to expect when reading the next chunk of data
    std::vector<std::string> val_stack;
    std::vector<Node *> node_stack;
    while (l_ptr < str_len)
    {
        // std::cout << l_ptr << ' ' << str_len << '\n';
        print_stack(state_stack, val_stack, node_stack);
        // build a node if state stack has right node at the end
        r_ptr = node_str.find(',');
        if (r_ptr == std::string::npos)
            r_ptr = str_len;
        switch (node_str[l_ptr])
        {
        case '(':
            if (state_stack.size() == 0)
                state_stack.push_back(ReadState::RootNode);
            else if (state_stack.back() == ReadState::NodeVal)
                state_stack.push_back(ReadState::LeftNode);
            else if (state_stack.back() == ReadState::LeftNode)
                state_stack.push_back(ReadState::RightNode);
            else
            {
                std::cout << "unexpected state while reading '(':" << print_read_state(state_stack.back()) << '\n';
                exit(-1);
            }
            l_ptr += 1;
            break;
        case '"':
            state_stack.push_back(ReadState::NodeVal);
            r_ptr = node_str.find('"', l_ptr + 1);
            assert(r_ptr != std::string::npos);
            // std::cout << node_str.substr(l_ptr+1, r_ptr-l_ptr-1) << std::endl;
            val_stack.push_back(node_str.substr(l_ptr + 1, r_ptr - l_ptr - 1));
            // l_ptr = r_ptr==std::string::npos ? str_len : r_ptr;
            l_ptr = r_ptr + 1;
            break;
        case ')':
            assert(state_stack.size() > 0);
            // string reading completed
            if (state_stack.back() == ReadState::RootNode)
            {
                l_ptr += 1;
                continue;
                // continue;
            }
            if (state_stack.back() == ReadState::LeftNode)
            {
                node_stack.push_back(nullptr);
                l_ptr += 1;
                continue;
            }
            assert(state_stack.back() == ReadState::RightNode);
            node_stack.push_back(nullptr);
            // collapsing nodes (like a depth search)
            while (state_stack.size() >= 3 && state_stack.back() == ReadState::RightNode)
            {
                if (ReadState::RightNode != state_stack.back())
                {
                    std::cout << "expected RightNode, got " << print_read_state(state_stack.back()) << '\n';
                    exit(-1);
                }
                Node *r_node = node_stack.back();
                node_stack.pop_back();
                state_stack.pop_back();
                // std::cout << "r node: " << (r_node == nullptr ? "null" : r_node->to_str()) << std::endl;
                if (ReadState::LeftNode != state_stack.back())
                {
                    std::cout << "expected LeftNode, got " << print_read_state(state_stack.back()) << '\n';
                    exit(-1);
                }
                Node *l_node = node_stack.back();
                node_stack.pop_back();
                state_stack.pop_back();
                // std::cout << "l node: " << (l_node == nullptr ? "null" : l_node->to_str()) << std::endl;
                if (ReadState::NodeVal != state_stack.back())
                {
                    std::cout << "expected NodeVal, got " << print_read_state(state_stack.back()) << '\n';
                    exit(-1);
                }
                std::string node_val = val_stack.back();
                val_stack.pop_back();
                // std::cout << node_val << std::endl;
                state_stack.pop_back();
                node_stack.push_back(new Node(node_val, l_node, r_node));
                // std::cout << node_stack.back()->to_str() << std::endl;
            }
            if (state_stack.back() == ReadState::LeftNode)
            {
                state_stack.push_back(ReadState::RightNode);
            }

            l_ptr += 1;
            break;
        case ' ':
            l_ptr += 1;
            break;
        default:
            std::cout << "Uncaught case: '" << node_str[l_ptr] << "'\n";
            l_ptr += 1;
            break;
        }
    }
    // Node *deserialized_node = new Node("root");
    // return deserialized_node;
    assert(state_stack.size() == 1 && state_stack.back() == ReadState::RootNode);
    return node_stack.back();
}
