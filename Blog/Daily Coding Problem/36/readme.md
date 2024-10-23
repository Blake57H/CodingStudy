# Daily Coding Problem: Problem #36 [Medium]

Good morning! Here's your coding interview problem for today.

This problem was asked by Dropbox.

Given the root to a binary search tree, find the second largest node in the tree.

## My solution

1. Go all the way right to fine the largest node.
2. If the largest node doesn't have a left branch, then its parent would be the second largest node.
3. Otherwise, find the largest node in its left branch, which should be the largest.

----

O(?) time complexity and O(?) space complexity.

## Googled solution (if I actually googled it)
