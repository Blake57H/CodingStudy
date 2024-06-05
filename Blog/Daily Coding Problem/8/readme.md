# Daily Coding Problem: Problem #8 [Easy]

Good morning! Here's your coding interview problem for today.

This problem was asked by Google.

A unival tree (which stands for "universal value") is a tree where all nodes under it have the same value.

Given the root to a binary tree, count the number of unival subtrees.

For example, the following tree has 5 unival subtrees:

```txt
   0
  / \
 1   0
    / \
   1   0
  / \
 1   1
```

## My solution

1. Make a binary tree class, load the example tree. Initialize a stack, for depth search?
2. For the node at the top of the stack `x`:
3. If `x` hasn't been visited, add its child to stack and mark the node visited.
4. Else, check if it is unival subtree. If so, `univalSubtreeCount+=1`. Then pop it from stack.
5. Repeat step 2~4 until stack is empty.

the following should has 4?

```txt
   0
  / \
 1   1
    / \
   1   1
  / \
 0   1
```

----

O(n) time complexity and O(n) space complexity (because of the stack).

## Googled solution (if I actually googled it)
