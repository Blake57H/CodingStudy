#include <iostream>
#include <vector>
#include <memory>

class BinaryTreeNode
{
public: // not a good practice, but for the sake of ease of use in solving the problem...
    std::shared_ptr<BinaryTreeNode> left = nullptr, right = nullptr;
    int val;
    bool isVisited = false;
    bool isUnivalSubtree = false;

    BinaryTreeNode(int val, std::shared_ptr<BinaryTreeNode> left, std::shared_ptr<BinaryTreeNode> right)
    {
        this->val = val;
        this->left = left;
        this->right = right;
    }
    BinaryTreeNode(int val) : BinaryTreeNode(val, nullptr, nullptr) {}
    BinaryTreeNode(BinaryTreeNode &node) = delete;
};

bool isNodeBranchUniVal(std::shared_ptr<BinaryTreeNode> node)
{   // if all childs is, either empty, or its's val match parent's, then this node branch is unival subtree
    bool leftIsUnivalSubtree, rightIsUnivalSubtree;
    leftIsUnivalSubtree = node->left == nullptr || (node->left->val == node->val && node->left->isUnivalSubtree);
    rightIsUnivalSubtree = node->right == nullptr || (node->right->val == node->val && node->right->isUnivalSubtree);
    return leftIsUnivalSubtree && rightIsUnivalSubtree;
}

int solve(std::shared_ptr<BinaryTreeNode> &node)
{
    int univalSubtreeCount = 0;
    std::vector<std::shared_ptr<BinaryTreeNode>> processStack;
    processStack.emplace_back(node);
    std::shared_ptr<BinaryTreeNode> currNode;
    while (!processStack.empty())
    {
        currNode = processStack.back();
        if (!currNode->isVisited)
        {   // if node hasn't been visited, it's child has not been added to the stack. Adding...
            if (currNode->right != nullptr)
                processStack.emplace_back(currNode->right);
            if (currNode->left != nullptr)
                processStack.emplace_back(currNode->left);
            currNode->isVisited = true;
            continue;
        }

        // if node has been visited, then check for its child for unival subtree.
        // because I'm using depth search, isNodeBranchUniVal() will not nest calling itself.
        currNode->isUnivalSubtree = isNodeBranchUniVal(currNode);
        if(currNode->isUnivalSubtree)
            univalSubtreeCount += 1;
        processStack.pop_back();
    }

    return univalSubtreeCount;
}

int main(int argc, char *argv[])
{
    std::shared_ptr<BinaryTreeNode> rootNode = std::make_shared<BinaryTreeNode>(0);
    rootNode->left = std::make_shared<BinaryTreeNode>(1);
    rootNode->right = std::make_shared<BinaryTreeNode>(1);
    rootNode->right->left = std::make_shared<BinaryTreeNode>(1);
    rootNode->right->right = std::make_shared<BinaryTreeNode>(1);
    rootNode->right->left->left = std::make_shared<BinaryTreeNode>(0);
    rootNode->right->left->right = std::make_shared<BinaryTreeNode>(1);

    auto result = solve(rootNode);
    std::cout << "Result: " << result << "\n";
    return 0;
}