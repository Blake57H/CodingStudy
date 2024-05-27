# Daily Coding Problem: Problem #? [Easy]

Good morning! Here's your coding interview problem for today.

This problem was asked by Google.

An XOR linked list is a more memory efficient doubly linked list. Instead of each node holding `next` and `prev` fields, it holds a field named `both`, which is an XOR of the next node and the previous node. Implement an XOR linked list; it has an `add(element)` which adds the element to the end, and a `get(index)` which returns the node at index.

If using a language that has no pointers (such as Python), you can assume you have access to `get_pointer` and `dereference_pointer` functions that converts between nodes and memory addresses.

## My solution

I'll try this with C++, which has pointer.

First I checked the definition of [XOR Linked List](https://www.geeksforgeeks.org/xor-linked-list-a-memory-efficient-doubly-linked-list-set-1/).

This question basically asks me to implement a XOR Linked List, which is a good exercise?

There shouldn't be any problem as long as I follow the rules in the above link.

----

One thing I learnt after some knowledge digging, is that `std::unique_ptr` is preferred to a regular pointer, as it will do the free memory stuff automatically. 