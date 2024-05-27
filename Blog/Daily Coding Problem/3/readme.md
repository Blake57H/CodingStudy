# Daily Coding Problem: Problem #3 [Medium]

Good morning! Here's your coding interview problem for today.

This problem was asked by Google.

Given the root to a binary tree, implement serialize(root), which serializes the tree into a string, and deserialize(s), which deserializes the string back into the tree.

For example, given the following Node class

```python
class Node:
    def __init__(self, val, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
```

The following test should pass:

```python
node = Node('root', Node('left', Node('left.left')), Node('right'))
assert deserialize(serialize(node)).left.left.val == 'left.left'
```

## My solution

String serialization using JsonCPP library. (kinda cheating because my serialization/deserialization function relies on another serialization/deserialization function)

I tried writing my own, independent function but it failed miserably.

----

O(1)? time complexity and O(1)? space complexity.

## Googled solution (if I actually googled it)

## Side notes

### building a static library

```bash
g++ -c -Wall main.cpp  // "-c": stops before running linker; "-Wall": prints a lot of debug message; This generates "main.o" library file.
g++ -o main main.o -static  // compiling "main.o" into "main" executable (or name it "main.exe").
```

### Passing pointer vs passing object

I have a class:

```cpp
class Node
{
public:
    Node(const char val[]);
    Node(const char val[], Node *left);
    Node(const char val[], Node *left, Node *right);
    ~Node();
    std::string to_str();
private:
    std::string val;
    Node *left = nullptr;
    Node *right = nullptr;
};
```

This constructor will work fine (complete instantly):

```cpp
Node::Node(const char val[], Node *left, Node *right)
{
    this->val = val;
    this->left = left;
    this->right = right;
}

// initialize
auto root_node = Node("root", new Node("left"), new Node("right"));
```

This will cause what looks like a memory leak (pauses for a sec before quitting):
(Program stuck at a suspended state and cannot be terminated)

```cpp
/*
public:
    Node(const char val[], Node left, Node right);
 */
Node::Node(const char val[], Node left, Node right)
{
    this->val = val;
    this->left = &left;
    this->right = &right;
}

// initialize
auto root_node = Node("root", Node("left"), Node("right"));
```

## credit

JsonCPP repository: [https://github.com/open-source-parsers/jsoncpp/releases/tag/1.9.5](https://github.com/open-source-parsers/jsoncpp/releases/tag/1.9.5)
