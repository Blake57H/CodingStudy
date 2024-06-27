#include <iostream>
#include <map>
#include <memory>
#include <vector>

class Node
{
public:
    std::string m_currChar;
    bool m_thisIsAWord = false;
    std::map<std::string, std::shared_ptr<Node>> m_childNodes;

    static void addChildString(std::shared_ptr<Node> node, std::string newString)
    {
        std::string currChar = newString.substr(0, 1);
        auto childNodeFinder = node->m_childNodes.find(currChar);
        std::shared_ptr<Node> childNode;
        if (childNodeFinder == node->m_childNodes.end())
        {
            childNode = std::make_shared<Node>();
            childNode->m_currChar = currChar;
            node->m_childNodes[currChar] = childNode;
        }
        else
            childNode = childNodeFinder->second;

        if (newString.size() == 1)
        {
            childNode->m_thisIsAWord = true;    // "Word" marker regardless children count.
            return;
        }
        Node::addChildString(childNode, newString.substr(1, newString.size() - 1));
    }

    // appending child's char with child's childrens'
    static std::vector<std::string> queryString(std::shared_ptr<Node> node, std::string queryString)
    {
        // std::cout << "'" << queryString << "'" << std::endl;
        std::vector<std::string> result;

        // if query string exhausted:
        if (queryString.size() == 0)
        {
            // if child's children is empty
            // e.g. query "dog" in [dog, deer, deal]
            if (node->m_childNodes.size() == 0)
            {
                // std::cout << "'" << node->m_currChar << "'" << std::endl;
                result.push_back("");
                goto return_result;
            }

            // if this is a word, treat it like it has no children so that it would back track to a word.
            // but still need to look into its childrens.
            if (node->m_thisIsAWord){
                result.push_back("");
            }

            // has childe, append child's char along with its childrens' char
            for (auto childNodeFinder : node->m_childNodes)
            {
                // std::cout << "'" << childNodeFinder.second->m_currChar << "', " << childNodeFinder.second->m_childNodes.size() << std::endl;
                for (std::string childString : Node::queryString(childNodeFinder.second, ""))
                    result.push_back(std::string{childNodeFinder.second->m_currChar}.append(childString));
            }
            goto return_result;
        }

        // query string not exhausted, check for next child and return its result.
        if (auto childNodeFinder = node->m_childNodes.find(queryString.substr(0, 1)); childNodeFinder != node->m_childNodes.end())
        {
            for (std::string substr : Node::queryString(childNodeFinder->second, queryString.substr(1, queryString.size() - 1)))
                result.push_back(std::string{childNodeFinder->second->m_currChar}.append(substr));
            goto return_result;
        }

    return_result:
        // for (std::string item : result)
        //     std::cout << item << std::endl;
        return result;
    }
};

void solve(std::shared_ptr<Node> node, std::string query)
{
    std::vector<std::string> results = Node::queryString(node, query);
    if (results.size() == 0)
        std::cout << "No Result!";
    for (std::string result : results)
    {
        std::cout << result << ", ";
    }
}

int main(int argc, char *argv[])
{
    // auto result = solve();
    // std::cout << "Result: " << result << "\n";
    std::shared_ptr<Node> root = std::make_shared<Node>();
    Node::addChildString(root, "done");
    Node::addChildString(root, "dog");
    Node::addChildString(root, "deer");
    Node::addChildString(root, "deal");
    Node::addChildString(root, "do"); // I will need a marker to indicate that "this is a word" despite it has childrens
    solve(root, "do");
    return 0;
}