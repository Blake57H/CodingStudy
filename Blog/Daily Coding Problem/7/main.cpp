#include <iostream>
#include <string>
#include <vector>        // generic list
#include <unordered_map> // hash map
#include <memory>        // shared_ptr

// use tree structure to trace number of ways to decode
class Node
{

private:
    std::string encoded_char; // unevaluated string, can be anything.
    char decoded_char = '$';  // a~z, '>' for root node, '<' for leaf node, '#' for deads, '$' for unevaluated.
    int char_pos = -1;
    std::vector<std::shared_ptr<Node>> child_nodes;

public:
    ~Node()
    {
        // std::cout << "deleting node " << this->encoded_char << " at " << &(*this) << std::endl;
    }
    Node(std::string encoded_char, const int char_pos)
    {
        this->char_pos = char_pos;
        this->encoded_char = encoded_char;
        // no char validation at this point.
        // node should be evaluated after creation.
    }
    // Node(const int &char_pos) : Node("anything", char_pos){}

    void addChildNode(const std::shared_ptr<Node> &child)
    {
        // char child_decoded_char = ;
        this->child_nodes.emplace_back(child);
    }

    int getCharPos()
    {
        return this->char_pos;
    }

    std::string getEncodedChar()
    {
        return this->encoded_char;
    }

    char getDecodedChar()
    {
        return this->decoded_char;
    }

    void setDecodeChar(const char &decodedChar)
    {
        this->decoded_char = decodedChar;
    }

    std::vector<std::shared_ptr<Node>> getChildNodes()
    {
        return this->child_nodes;
    }
};

// for dead nodes (decode impossible), return empty vector.
std::vector<std::string> concatChildChar(std::shared_ptr<Node> node)
{
    std::vector<std::string> concatResult;
    if (node->getDecodedChar() == '#')
    {   // expect '#' for dead leaf node, indicating message undecodable. Return empty list/vector.
        goto return_now;
    }

    // reaching here means message is decodable at this point;
    // expect size=0 for leaf nodes (not dead)
    if(node->getChildNodes().size() == 0){
        concatResult.push_back(std::string{node->getDecodedChar()});
        goto return_now;
    }
    
    for (std::shared_ptr<Node> child : node->getChildNodes())
    {   // for non-leaf nodes, iterate its child for their possible decodes.
        for (std::string possibleDecode : concatChildChar(child))
        {   // add possible decodes to result. for undecodable strings, empty vector will be returned, and this code will not reach (expect)
            possibleDecode.insert(possibleDecode.begin(), node->getDecodedChar());
            concatResult.push_back(possibleDecode);
        }
    }

return_now:
    return concatResult;
}

int solve(const std::string &message)
{
    // std::cout << (int)'a' << (char)96 << " " << (int)'1' << std::endl; // 'a'=97, '1'=48
    std::vector<std::shared_ptr<Node>> nodeProcessQueue;
    std::shared_ptr<Node> rootNode = std::make_shared<Node>(Node("R", -1));
    rootNode->setDecodeChar('>');
    nodeProcessQueue.emplace_back(rootNode);

    std::shared_ptr<Node> child1, child2;

    while (!nodeProcessQueue.empty())
    {
        std::shared_ptr<Node> currentNode = nodeProcessQueue.front();
        int childStartPos = currentNode->getCharPos() + currentNode->getEncodedChar().size();

        if (currentNode->getDecodedChar() == '$')
        { // '$' means unevaluated.
            int char_int = std::stoi(currentNode->getEncodedChar());
            if (char_int < 1 || char_int > 26)
            { // not a valid number, it is a dead node.
                currentNode->setDecodeChar('#');
                goto pop_item;
            }

            // is a valid number, decode string and add its possible child to queue
            currentNode->setDecodeChar((char)(char_int) + 96);
        }

        // find its possible child
        if (message.size() - childStartPos == 0)
        { // leaf node is its only child, current pos is '/0', or EOF.
            std::shared_ptr<Node> child = std::make_shared<Node>(Node("L", childStartPos));
            child->setDecodeChar('<');
            currentNode->addChildNode(child);
            goto pop_item;
        }
        if (message.size() - childStartPos >= 2)
        {
            currentNode->addChildNode(std::make_shared<Node>(Node(message.substr(childStartPos, 2), childStartPos)));
            nodeProcessQueue.push_back(currentNode->getChildNodes().back());
        }
        currentNode->addChildNode(std::make_shared<Node>(Node(message.substr(childStartPos, 1), childStartPos)));
        nodeProcessQueue.push_back(currentNode->getChildNodes().back());
    pop_item:
        nodeProcessQueue.erase(nodeProcessQueue.begin());
    }

    std::vector<std::string> possibleDecodes = concatChildChar(rootNode);

    std::cout << "Possible decodes: \n";
    for(std::string result : possibleDecodes){
        std::cout << "\t" << result.substr(1, result.size()-2) << std::endl;
    }

    return possibleDecodes.size();
}

int main(int argc, char *argv[])
{
    // std::string str = "111";
    std::string str = "110";    // expect only 1 result
    auto result = solve(str);
    std::cout << "Result: " << result << "\n";
    return 0;
}