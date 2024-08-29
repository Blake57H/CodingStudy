#include <iostream>
#include <memory>
#include <queue>

class Node
{
    bool locked = false;

public:
    std::shared_ptr<Node> left, right;
    std::weak_ptr<Node> parent;

    static bool check_all_ancestors_unlocked(const Node &curr_node)
    {
        std::weak_ptr<Node> node = curr_node.parent;
        while (auto p = node.lock())
        {
            if (p->locked)
                return false;
            node = p->parent;
        }
        return true;
    }

    static bool check_all_descendants_unlocked_recursive(const Node &curr_node)
    {
        bool result = true;
        if (auto p = curr_node.left)
        {
            if (p->locked)
                return false;
            else
                result = check_all_descendants_unlocked_recursive(*p);
        }
        if (!result)
            return result; // return false if a locked node exists in left branch, skip right branch checking
        if (auto p = curr_node.right)
        {
            if (p->locked)
                return false;
            else
                return check_all_descendants_unlocked_recursive(*p);
        }
        return result;
    }

    bool is_locked() { return locked; }
    bool lock()
    {
        // check if it can be locked;
        // if ancestor is locked, return false
        if (!check_all_ancestors_unlocked(*this))
            return false;
        // check if descendants is locked
        if (!check_all_descendants_unlocked_recursive(*this))
            return false;
        locked = true;
        return true;
    }
    bool unlock()
    {
        // check if it can be unlocked;
        // if ancestor is locked, return false
        if (!check_all_ancestors_unlocked(*this))
            return false;
        // check if descendants is locked
        if (!check_all_descendants_unlocked_recursive(*this))
            return false;
        locked = false;
        return true;
    }

    Node(const std::shared_ptr<Node> &parent)
    {
        this->parent = parent;
    };
    Node(const Node &node) = delete;
};

int solve()
{
    std::shared_ptr<Node> root = std::make_shared<Node>(nullptr);
    std::queue<std::pair<std::shared_ptr<Node>, int>> queue; // for planting a binary tree
    queue.push(std::make_pair(root, 3));                     // 3 means 3 more layer
    while (!queue.empty())
    {
        std::pair<std::shared_ptr<Node>, int> node = queue.front();
        std::shared_ptr<Node> left = std::make_shared<Node>(node.first), right = std::make_shared<Node>(node.first);
        node.first->left = left;
        node.first->right = right;
        if (node.second > 0)
        {
            // while layer > 0, keep planting
            queue.push(std::make_pair(left, node.second - 1));
            queue.push(std::make_pair(right, node.second - 1));
        }
        queue.pop();
        // Node()
    }

    std::cout << std::boolalpha << "Locking root: " << root->lock() << ". Expect true." << std::endl;               // true
    std::cout << std::boolalpha << "Locking root->left: " << root->left->lock() << ". Expect false." << std::endl;  // false
    std::cout << std::boolalpha << "Unlocking root: " << root->unlock() << ". Expect true." << std::endl;           // true
    std::cout << std::boolalpha << "Locking root->right: " << root->right->lock() << ". Expect true." << std::endl; // true
    // more test here
    return 0;
}

int main(int argc, char *argv[])
{
    auto result = solve();
    std::cout << "Result: " << result << "\n";
    return 0;
}