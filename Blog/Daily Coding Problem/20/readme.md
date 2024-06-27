# Daily Coding Problem: Problem #20 [Easy]

Good morning! Here's your coding interview problem for today.

This problem was asked by Google.

Given two singly linked lists that intersect at some point, find the intersecting node. The lists are non-cyclical.

For example, given A = 3 -> 7 -> 8 -> 10 and B = 99 -> 1 -> 8 -> 10, return the node with value 8.

In this example, assume nodes with the same value are the exact same node objects.

Do this in O(M + N) time (where M and N are the lengths of the lists) and constant space.

## My solution

I can think of a not constant space solution...

1. Put one of the list's item memory addresses into a set.
2. Iterate the other list. If a memory address hit the set, return the value inside that address.

----

O(M+N) time complexity and O(M) space complexity.

## Googled solution (if I actually googled it)

[Java](https://github.com/mrishab/Daily-Coding-Problems/blob/master/src/Problem20.java)
[Python](https://github.com/ruppysuppy/Daily-Coding-Problem-Solutions/blob/master/Solutions/020.py)

I can understand the Java answer.

So since they have common tail, if their length is not the same, I can trim the longer one from the front down to the size of the shorter one.

Then iterate them one by one and at some point they will show the same value because from that point the list intersects.

O(M+N+max(M,N)) time complexity and O(1) space complexity.
