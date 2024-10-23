#include <iostream>
#include <random>
#include <memory>

const uint32_t SEED = 2;
std::mt19937 generator;

struct Node
{
    const int val;
    std::shared_ptr<Node> left = nullptr, right = nullptr;

    Node(int val) : val(val) {};
};

int solve(std::shared_ptr<Node> root)
{
    // go all the way right
    std::shared_ptr<Node> front = root, back = root;
    while (front->right != nullptr)
        front = front->right;
    // largest node found. if it doesn't have a left branch, its parent would be the second largest node
    if(front->left == nullptr)
    {
        while(back->right != front)
            back = back->right;
        return back->val;
    }
    // find the largest node in its left branch
    front = front->left;
    while (front->right != nullptr)
        front = front->right;
    return front->val;
}

std::shared_ptr<Node> generate_tree(int min, int max)
{
    if (min >= max)
        return nullptr;

    std::uniform_int_distribution<int> dist(min, max);
    int curr_val = dist(generator);
    std::shared_ptr<Node> node(std::make_shared<Node>(curr_val));
    node->left = generate_tree(min, curr_val - 1);
    node->right = generate_tree(curr_val + 1, max);
    return node;
}

void print_tree(std::shared_ptr<Node> &node, size_t level, int top)
{
    if (node == nullptr)
    {
        std::cout << "nullptr\n";
        return;
    }
    // for (size_t i = 0; i < level; i++)
    //     std::cout << "│";
    std::cout << "val=" << node->val << '\n';
    for (size_t i = 0; i < level; i++)
        std::cout << "│";
    std::cout << "├";
    print_tree(node->right, level + 1, 1);
    // std::cout << '\n';
    for (size_t i = 0; i < level; i++)
        std::cout << "│";
    std::cout << "└";
    print_tree(node->left, level + 1, top == -1 ? 0 : top == 1);
    // std::cout << '\n';
}

int main(int argc, char *argv[])
{
    generator.seed(SEED);
    std::shared_ptr<Node> root_node = generate_tree(0, 10);
    // print_tree(root_node, 0, -1);
    std::cout << "Result: " << solve(root_node) << "\n";
    return 0;
}