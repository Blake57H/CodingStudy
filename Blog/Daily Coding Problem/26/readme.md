# Daily Coding Problem: Problem #26 [Medium]

Good morning! Here's your coding interview problem for today.

This problem was asked by Google.

Given a singly linked list and an integer k, remove the kth last element from the list. k is guaranteed to be smaller than the length of the list.

The list is very long, so making more than one pass is prohibitively expensive.

Do this in constant space and in one pass.

## My solution

I am dumb...

On the other hand, if k is guaranteed to be smaller than list's length, then I should be able to assume:

- because: k < len(List)
- k>=1
- len(List) >=2

----

O(n) time complexity and O(1) space complexity.

## Googled solution (if I actually googled it)

[here](https://www.geeksforgeeks.org/delete-nth-node-from-the-end-of-the-given-linked-list/)

I believe the link is pretty explanatory.
