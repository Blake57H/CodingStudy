#include <iostream>
#include <memory>
#include <vector>
#include <format>

struct Node
{
    int data;
    std::shared_ptr<Node> next;

    Node(int data) : data(data) {};
    ~Node(){
        // uncommon to see smart pointer will deleting itself
        // std::cout << std::format("Deleting value {}\n", data);
    }
};

void solve(std::shared_ptr<Node> &linked_list_head, const int &k)
{
    std::shared_ptr<Node> ptr_fast = linked_list_head, ptr_slow = linked_list_head;
    size_t count = 0; // for printing out index

    // the "k+1" here is to make ptr_slow pointing at the Node before the k-1_th node, and delete the k_th node
    for (int i = 0; i < k + 1; i++)
    {
        ptr_fast = ptr_fast->next;
    }
    while (ptr_fast != nullptr)
    {
        ptr_fast = ptr_fast->next;
        ptr_slow = ptr_slow->next;
        count++;
    }
    std::cout << std::format("Removing item at index {}: value={}\n", count + 1, ptr_slow->next->data);
    ptr_slow->next = ptr_slow->next->next;
    // since it is a smart pointer, when there's no reference, pointer should delete itself.
}

void print_linked_list(const std::shared_ptr<Node> &linked_list_head, std::string_view prefix)
{
    std::shared_ptr<Node> curr = linked_list_head;
    size_t counter = 0;
    std::cout << std::format("{}({}: {})", prefix, counter, curr->data);
    curr = curr->next;
    counter++;
    while (curr != nullptr)
    {
        std::cout << std::format(" --> ({}: {})", counter, curr->data);
        curr = curr->next;
        counter++;
    }
    std::cout << std::endl;
}

int main(int argc, char *argv[])
{
    std::shared_ptr<Node> head = std::make_shared<Node>(-1), j = head;
    for (int i = 0; i < 5; i++, j = j->next)
        j->next = std::make_shared<Node>(i);
    print_linked_list(head, "Before: ");
    solve(head, 2);
    print_linked_list(head, "After: ");
    return 0;
}