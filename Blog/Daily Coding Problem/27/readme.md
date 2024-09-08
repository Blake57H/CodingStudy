# Daily Coding Problem: Problem #27 [Easy]

Good morning! Here's your coding interview problem for today.

This problem was asked by Facebook.

Given a string of round, curly, and square open and closing brackets, return whether the brackets are balanced (well-formed).

For example, given the string "([])[]({})", you should return true.

Given the string "([)]" or "((()", you should return false.

## My solution

Instinct: use stack.

For each character in a string, push opening brackets into stack and match closing bracket to the opening bracket from stack.

Should be easy.

----

O(n) time complexity and O(n) space complexity.

## Googled solution (if I actually googled it)
