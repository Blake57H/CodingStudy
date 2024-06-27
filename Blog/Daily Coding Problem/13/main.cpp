#include <iostream>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>

struct Node
{
    char character;
    std::unordered_map<char, std::shared_ptr<Node>> nextNodes;

    Node(char c)
    {
        this->character = c;
    }
};

void buildTree(std::string_view s, std::shared_ptr<Node> &treeNode, bool isRootNode)
{
    if (s.length() == 0)
        return;
    if (treeNode->nextNodes.find(s[0]) == treeNode->nextNodes.end())
    {
        treeNode->nextNodes[s[0]] = std::make_shared<Node>(s[0]);
    }

    // adding remaining char as child node
    // e.g. a->b->c->b->a
    buildTree(s.substr(1, s.length() - 1), treeNode->nextNodes[s[0]], false);

    // adding substring to root
    // abcba(a->b->c->b->a), bcba(b->c->b->a), cba(...), ba(..),
    if (isRootNode)
        buildTree(s.substr(1, s.length() - 1), treeNode, true);
}

std::unordered_set<std::string> solveTree(const size_t &k, std::shared_ptr<Node> &treeNode, std::string_view substring)
{
    // std::cout  << (treeNode->character) << ": " << '"' << substring << '"' << std::endl;

    std::unordered_set<char> uniqueChars{substring.begin(), substring.end()};
    // for (auto item : uniqueChars)
    // {
    //     std::cout << '"' << item << "\", ";
    // }
    // std::cout << std::endl;
    
    if (uniqueChars.size() == k && uniqueChars.find(treeNode->character) == uniqueChars.end())
        return std::unordered_set{std::string{substring}};

    std::string currString{substring};
    if (treeNode->character != 0)
        currString.push_back(treeNode->character); // do not add root node character

    // std::cout  << (treeNode->character) << ": " << '"' << currString << '"' << std::endl;

    std::unordered_set<std::string> result{currString};
    size_t currentMaxSubstringLength = currString.length();
    for (auto &childNode : treeNode->nextNodes)
    { //      ^ avoid copy
        for (std::string_view childResult : solveTree(k, childNode.second, currString))
        { //      ^ avoid copy
            if (childResult.size() < currentMaxSubstringLength)
                continue; // ignore short substring
            if (childResult.size() > currentMaxSubstringLength)
            { // if longer substring is found, clear all short substring from previous result
                result.clear();
                currentMaxSubstringLength = childResult.size();
            }
            result.emplace(std::string{childResult});
            
            // std::cout << (treeNode->character == 0 ? 0 : treeNode->character) << ": " << result.back() << std::endl;
        }
    }
    return result;
}

// there might be more than 1 answer? Say s="abcbd" and k=3 (expects "abcb" and bcbd).
std::unordered_set<std::string> solve(const int &k, std::string_view s)
{ // ^^^^^^^^^^^^^ using set to remove  duplicate results
    std::shared_ptr<Node> root = std::make_shared<Node>(0);
    buildTree(s, root, true);
    std::unordered_set<std::string> result;
    for (std::string_view solveResult : solveTree(k, root, ""))
    { //      ^^^^^^^^^^^ for whatever reason, string doesn't work, string& doesn't, string_view does
        // std::cout  << '"' << solveResult << '"' << std::endl;
        result.emplace(std::string{solveResult});    // if use auto, solveResult gets deleted after each loop; using string_view can force a data copy
    }
    return result;
}

int main(int argc, char *argv[])
{
    int k = 2;
    std::string_view s = "abcba";

    auto result = solve(k, s);
    std::cout << "Result: ";
    for (std::string_view item : result)
        std::cout << '"' << item << "\", ";
    std::cout << std::endl;

    std::cout << "Result: ";
    for (std::string_view item : solve(3, "abcbd"))
        std::cout << '"' << item << "\", ";
    std::cout << std::endl;
    
    std::cout << "Result: ";
    for (std::string_view item : solve(4, "abcbd"))
        std::cout << '"' << item << "\", ";
    std::cout << std::endl;

    std::cout << "Result: ";
    for (std::string_view item : solve(2, "abcdb"))
        std::cout << '"' << item << "\", ";
    std::cout << std::endl;
    return 0;
}