# Daily Coding Problem: Problem #42 [Hard]

Good morning! Here's your coding interview problem for today.

This problem was asked by Google.

Given a list of integers S and a target number k, write a function that returns a subset of S that adds up to k. If such a subset cannot be made, then return null.

Integers can appear more than once in the list. You may assume all numbers in the list are positive.

For example, given S = [12, 1, 61, 5, 9, 2] and k = 24, return [12, 9, 2, 1] since it sums up to 24.

## My solution

My initial thought would be:

1. Make a hash-map of array S as S', to keep track of how many a number is available.
2. Select the first number from S' as j, then do "k-j", save the result as l, available j in S' minus 1;
3. Repeat step 2 with l as the next k, until k=0. Else remove j from S';
4. If S' exhausted before k=0, then there is no result;

----

O(?) time complexity and O(?) space complexity.

## Googled solution (if I actually googled it)
