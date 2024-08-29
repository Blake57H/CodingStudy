# Daily Coding Problem: Problem #24 [Medium]

Good morning! Here's your coding interview problem for today.

This problem was asked by Google.

Implement locking in a binary tree. A binary tree node can be locked or unlocked only if all of its descendants or ancestors are not locked.

Design a binary tree node class with the following methods:

- `is_locked`, which returns whether the node is locked
- `lock`, which attempts to lock the node. If it cannot be locked, then it should return false. Otherwise, it should lock it and return true.
- `unlock`, which unlocks the node. If it cannot be unlocked, then it should return false. Otherwise, it should unlock it and return true.

You may augment the node to add parent pointers or any other property you would like. You may assume the class is used in a single-threaded program, so there is no need for actual locks or mutexes. Each method should run in O(h), where h is the height of the tree.

## My solution

Not sure if I can think of a O(h) solution since higher the tree there are more nodes.My descendant checking function seems running in O(2^h) time.

----

O(?) time complexity and O(?) space complexity.

## Googled solution (if I actually googled it)

[https://github.com/ruppysuppy/Daily-Coding-Problem-Solutions/blob/master/Solutions/024.py](https://github.com/ruppysuppy/Daily-Coding-Problem-Solutions/blob/master/Solutions/024.py)