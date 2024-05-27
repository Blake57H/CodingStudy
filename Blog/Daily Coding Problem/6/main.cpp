#include <iostream>

// why not doing the old school way as well? 
class RegularLinkedList
{
    class RegularNode
    {
    public:
        int val;
        RegularNode *prev, *next;
        RegularNode(const int &val)
        {
            this->val = val;
            this->next = NULL;
            this->prev = NULL;
        }

        /**
         * Bad practice, I only think of removing the whole list instead of an element.
         */
        ~RegularNode()
        {
            if (this->prev != NULL)
            {
                std::cout << "Removing prevNode of nodeVAL=" << this->val << "\n";
                this->prev->next = NULL;
                delete this->prev;
            }
            if (this->next != NULL)
            {
                std::cout << "Removing nextNode of nodeVAL=" << this->val << "\n";
                this->next->prev = NULL;
                delete this->next;
            }
            std::cout << "Removing currNode of nodeVAL=" << this->val << "\n";
        }
    };

private:
    RegularNode *startNode = nullptr;

public:
    ~RegularLinkedList()
    {
        delete startNode;
    }

    void add(const int &val)
    {
        // std::cout << "Adding value (" << val << ") to regular list\n";
        if (startNode == nullptr)
        {
            startNode = new RegularNode(val);
            // std::cout << "value (" << val << ") added to regular list\n";
            return;
        }
        RegularNode *node = startNode;
        while (node->next != NULL)
        {
            node = node->next;
        }
        node->next = new RegularNode(val);
        node->next->prev = node;
        // std::cout << "value (" << val << ") added to regular list\n";
    }

    int get(const unsigned int &index)
    {
        if (startNode == NULL)
            return INT_MIN;
        RegularNode *node_at_index = startNode;
        for (unsigned int i = 0; i < index; i++)
        {
            if (node_at_index == nullptr)
            {
                std::cout << "index out of range\n";
                exit(-1);
            }
            node_at_index = node_at_index->next;
        }
        return node_at_index->val;
    }
    void print_list()
    {
        std::cout << "Regular list: \t";
        RegularNode *current = this->startNode;
        while (current != NULL)
        {
            std::cout << current->val << " <-> ";
            current = current->next;
        }
        std::cout << "EOF\n";
    }
};

//////////////////////////////////////

class XORNode
{
private:
    int val;
    XORNode *both = NULL;

public:
    XORNode(const int &val)
    {
        this->val = val;
    }

    void set_both_field(XORNode *both)
    {
        this->both = both;
    }
    XORNode *get_both_field()
    {
        return this->both;
    }
    int get_val()
    {
        return this->val;
    }
};

class XORLinkedList
{
private:
    XORNode *startNode = nullptr;

public:
    ~XORLinkedList()
    {
        XORNode *prev = NULL, *current = this->startNode;
        XORNode *next = XORLinkedList::calculateAddr(prev, current->get_both_field());
        while (current != NULL)
        {
            prev = current; // only the address value is needed to iterate the list;

            std::cout << "Deleting xor node value(" << current->get_val() << ")\n";
            delete current;

            current = next;
            if (current == NULL)
                break;
            next = XORLinkedList::calculateAddr(prev, current->get_both_field());
        }

        // todo: should I reset all the local pointers or compiler will do it for me?
    }

    static XORNode *calculateAddr(XORNode *prev, XORNode *next)
    {
        return (XORNode *)((size_t)prev ^ (size_t)next);
    }

    void add(XORNode *element)
    {
        if (this->startNode == nullptr)
        {
            this->startNode = element;
            return;
        }
        // startNode's prev is NULL, "both" is a address that can be calculated by (prevAddr ^ nextAddr).
        // Therefore nextAddr = (prevAddr ^ "Both") = (NULL ^ get_both_field())
        XORNode *prev = NULL, *current = this->startNode, *next = XORLinkedList::calculateAddr(prev, current->get_both_field());
        while (next != NULL)
        {
            prev = current;
            current = next;
            next = XORLinkedList::calculateAddr(prev, current->get_both_field());
        }
        current->set_both_field(XORLinkedList::calculateAddr(prev, element));
        element->set_both_field(XORLinkedList::calculateAddr(current, NULL));
        // std::cout << "value (" << element->get_val() << ") added to xor list\n";
    }
    XORNode *get(const unsigned int &index)
    {
        if (this->startNode == nullptr)
            return nullptr;
        XORNode *prev = NULL, *current = this->startNode;
        XORNode *next = XORLinkedList::calculateAddr(prev, current->get_both_field());
        for (unsigned int i = 0; i < index; i++)
        {
            prev = current;
            current = next;
            if (current == nullptr)
            {
                std::cout << "index out of range\n";
                exit(-1);
            }
            next = XORLinkedList::calculateAddr(prev, current->get_both_field());
        }
        return current;
    }

    // I wanna see what's in the list
    void print_list()
    {
        std::cout << "XOR list: \t";
        XORNode *prev = NULL, *current = this->startNode;
        XORNode *next = XORLinkedList::calculateAddr(prev, current->get_both_field());
        while (current != NULL)
        {
            std::cout << current->get_val() << " <-> ";
            prev = current;
            current = next;
            if (current == NULL)
                break;
            next = XORLinkedList::calculateAddr(prev, current->get_both_field());
        }
        // std::cout << XORLinkedList::calculateAddr(prev, current->get_both_field());
        std::cout << "EOF\n";
    }
};

int main(int argc, char *argv[])
{
    // XORNode *node = new XORNode(10);
    // auto result = node;
    // std::cout << "Result: " << result << ", " << sizeof(node) << " " << sizeof(size_t) << "\n";
    // std::cout << "Result: " << (nullptr == NULL) << "\n";

    int test_data[] = {1, 2, 3, 4, 5, 0, 9, 8, 7, 6};
    XORLinkedList xor_list;
    RegularLinkedList regular_list;
    for (int i : test_data)
    {
        // std::cout << i;
        xor_list.add(new XORNode(i));
        regular_list.add(i);
    }
    regular_list.print_list();
    xor_list.print_list();

    unsigned int at_index = 9;
    std::cout << "at index " << at_index << ": " << regular_list.get(at_index) << ", " << xor_list.get(at_index)->get_val() << std::endl;

    return 0;
}