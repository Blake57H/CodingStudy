#include <iostream>
#include <string.h>
#include <cassert>
#include "json/json.h"


/*
I'm trying a no library solution, but presents great difficulties. Still haven't figure out.
A library solution would be using jsoncpp.
*/

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
        std::cout << this->val << ": deleting this node \n";
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


/**
 * Serialize object with JsonCPP library
 */
static Json::Value serialize_lib(Node &node)
{
    Json::Value serialize_obj;
    Json::String val = node.get_val();
    serialize_obj["val"] = val;
    Json::Value left = node.get_left() == nullptr ? Json::nullValue : serialize_lib(*node.get_left());
    serialize_obj["left"] = left;
    Json::Value right = node.get_right() == nullptr ? Json::nullValue : serialize_lib(*node.get_right());
    serialize_obj["right"] = right;
    return serialize_obj;
}

static std::string serialize(Node &node)
{
    Json::FastWriter writer;
    std::string serialized_str = writer.write(serialize_lib(node));
    return serialized_str;
}

/**
 * Deserialize object with JsonCPP library
 */
static Node *deserialize_lib(const Json::Value &json_node)
{
    // std::cout << json_node << std::endl;
    Node *node = new Node{json_node.get("val", Json::nullValue).asString()};

    Json::Value left = json_node.get("left", Json::nullValue);
    node->set_left(left == Json::nullValue ? nullptr : deserialize_lib(left));

    Json::Value right = json_node.get("right", Json::nullValue);
    node->set_right(right == Json::nullValue ? nullptr : deserialize_lib(right));

    // std::cout << node->to_str() << std::endl;
    return node;
}


static Node *deserialize(const std::string &string)
{
    Json::Value serialized_obj;
    Json::Reader reader;
    reader.parse(string, serialized_obj);

    Node *node = deserialize_lib(serialized_obj);
    return node;
}

int main(int argc, char *argv[])
{
    // auto root_node = Node("root");
    // auto root_node = Node("root", new Node("left"));
    auto root_node = Node("root", new Node("left", new Node("left.left")), new Node("right"));

    // std::cout << "Result: " << root_node.to_str() << "\n";
    std::cout << "Result: " << serialize(root_node) << "\n"; // ("root",("left",,),("right",,))

    auto result = deserialize(serialize(root_node));
    std::cout << "Result: " << result->to_str() << "\n";
    assert(result->get_left()->get_left()->get_val() == "left.left");
    std::cout << "assertion passed" << "\n";

    return 0;
}