# Daily Coding Problem: Problem #31 [Easy]

Good morning! Here's your coding interview problem for today.

This problem was asked by Google.

The edit distance between two strings refers to the minimum number of character insertions, deletions, and substitutions required to change one string to the other. For example, the edit distance between “kitten” and “sitting” is three: substitute the “k” for “s”, substitute the “e” for “i”, and append a “g”.

Given two strings, compute the edit distance between them.

## My solution

I have a feeling that this is a problem that can be solved with "longest common subsequence".

1. Build a sequence tree for source string.
2. Run the longest common substring through the tree on the target string  Note down character positions.
3. Make the edit distance on the character positions.

While iterating subsequence character positions of both string at the same time, for the source string:

- Add some characters, if source string is falling behind.
- Remove some characters, if target string is falling behind.

----

I feel like I made the problem more complicated.

Update: I think my approach is incorrect. In the geeks for geeks example (AXTY --> AYZX), my approach would try to delete T and Y after X, then insert Y and Z between A and X, which is 4 steps. Python's solution only need 3 steps: replace X with Y, T with Z, and Y with X.

My approach is trying to reuse the memory of the character (if string is treated as a singly linked list of char), which is not the point of this problem.

Can't even solve an easy problem.. heh heh...  
(╯‵□′)╯︵┻━┻

48Hour time complexity and 1TB space complexity. ~JK

## Googled solution (if I actually googled it)

[python](https://github.com/ruppysuppy/Daily-Coding-Problem-Solutions/blob/master/Solutions/031.py)