#include <iostream>
#include <format>
#include <exception>

struct StackNode
{
    int val;
    StackNode *const prev;  // I discovered constant pointer so that the address that pointer is pointing at will not change.

    StackNode(int val, StackNode *prev) : val(val), prev(prev) {};
    ~StackNode()
    {
        using namespace std;
        // cout << format("Deleting (val={}, prev={})\n", this->val, &(this->prev));
        cout << "Deleting "<< this << "(val=" << this->val << ", prev=" << this->prev << ")" << endl;
    }
};

struct MaxValNode
{
    StackNode *const node;
    MaxValNode *const prev;

    MaxValNode(StackNode *node, MaxValNode *prev) : node(node), prev(prev) {};
};

class Stack
{
private:
    StackNode *stack_top = nullptr; // the stack itself
    MaxValNode *max_val = nullptr;  // keep track of the largest value, so that "max()" runs at constant time.

public:
    ~Stack()
    {
        StackNode *next_s = stack_top;
        while (stack_top != nullptr)
        {
            next_s = stack_top->prev;
            delete stack_top;
            stack_top = next_s;
        }

        MaxValNode *next_m = max_val;
        while (max_val != nullptr)
        {
            next_m = max_val->prev;
            delete max_val;
            max_val = next_m;
        }
    };

    void push(int val) noexcept
    {
        stack_top = new StackNode(val, stack_top);
        if (max_val == nullptr || max_val->node->val < val)
            max_val = new MaxValNode(stack_top, max_val);
    }

    const int pop()
    {
        if (stack_top == nullptr)
            throw std::runtime_error("error when popping value");

        if (max_val->node == stack_top)
        {
            MaxValNode *prev = max_val->prev;
            delete max_val;
            max_val = prev;
        }

        StackNode *node = stack_top->prev;
        int val = stack_top->val;
        delete stack_top;
        stack_top = node;
        return val;
    }

    const int max()
    {
        if (max_val == nullptr)
            throw std::runtime_error("error when reading max value");

        return max_val->node->val;
    }
};

void print(const int val)
{
    using namespace std;
    cout << val << endl;
}

void print(const std::exception &e)
{
    using namespace std;
    cout << e.what() << endl;
}

void try_pop(Stack *const s)
{
    try
    {
        print(s->pop());
    }
    catch (std::exception &e)
    {
        print(e);
    }
}

void try_max(Stack *const s)
{
    try
    {
        print(s->max());
    }
    catch (std::exception &e)
    {
        print(e);
    }
}

int main(int argc, char *argv[])
{
    Stack stack;

    try_pop(&stack);
    stack.push(1);
    print(stack.max());
    stack.push(100);
    print(stack.max());
    stack.push(10);
    print(stack.max());
    print(stack.pop());
    print(stack.pop());
    print(stack.pop());
    try_pop(&stack);
    stack.push(0);
    return 0;
}