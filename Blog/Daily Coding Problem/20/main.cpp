#include <iostream>
#include <unordered_set>
#include <memory>

struct Node
{
    int val;
    std::shared_ptr<Node> next = nullptr;

    Node(const int &val)
    {
        this->val = val;
    }
};

// O(M+N) time and O(M) space
int solve(std::shared_ptr<Node> &listA, std::shared_ptr<Node> &listB)
{
    std::unordered_set<size_t> memoryAddresses;
    for (std::shared_ptr<Node> item = listA; item != nullptr; item = item->next)
        memoryAddresses.emplace((size_t) & (*item));
    for (std::shared_ptr<Node> item = listB; item != nullptr; item = item->next)
        if (memoryAddresses.find((size_t) & (*item)) != memoryAddresses.end())
        {
            std::cout << "Value: " << item->val << "; Address: " << &(*item) << std::endl;
            std::cout << "Value: " << item->val << "; Address: " << item << std::endl;
            std::cout << "Value: " << item->val << "; Address: " << &item << std::endl; // incorrect
            return item->val;
        }
    return 0;
}

int solveAlt(std::shared_ptr<Node> &listA, std::shared_ptr<Node> &listB)
{
    int aLength = 0, bLength = 0;

    // calculate the length of a and b
    for (std::shared_ptr<Node> i = listA; i != nullptr; aLength++, i = i->next);
    for (std::shared_ptr<Node> i = listB; i != nullptr; bLength++, i = i->next);

    int diff = aLength - bLength;
    std::shared_ptr<Node> &shorterListPtr = diff < 0 ? listA : listB;
    std::shared_ptr<Node> &longerListPtr = diff >= 0 ? listA : listB;
    int &shorterListLength = diff < 0 ? aLength : bLength;

    for(int i = 0; i < abs(diff); i++)
        longerListPtr = longerListPtr->next;
    
    for(int i = 0; i < shorterListLength; i++)
    {
        if(shorterListPtr == longerListPtr)
        {
            std::cout << "Value: " << shorterListPtr->val << "; Address: " << shorterListPtr << std::endl;
            return shorterListPtr->val;
        }
        shorterListPtr = shorterListPtr->next;
        longerListPtr = longerListPtr->next;
    }
    return 0;
    
}

int main(int argc, char *argv[])
{
    std::shared_ptr<Node> listA{std::make_shared<Node>(3)}, listB(std::make_shared<Node>(99));
    std::shared_ptr<Node> iA = listA, iB = listB, temp;

    iA->next = std::make_shared<Node>(7);
    iA = iA->next;
    iB->next = std::make_shared<Node>(1);
    iB = iB->next;
    temp = std::make_shared<Node>(80);
    iA->next = temp;
    iB->next = temp;
    iA = iA->next;
    iB = iB->next;
    temp = std::make_shared<Node>(10);
    iA->next = temp;
    iB->next = temp;
    iA = iA->next;
    iB = iB->next;

    // auto result = solve(listA, listB);
    auto result = solveAlt(listA, listB);
    std::cout << "Result: " << result << "\n";
    return 0;
}