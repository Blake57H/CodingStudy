# Daily Coding Problem: Problem #25 [Hard]

Good morning! Here's your coding interview problem for today.

This problem was asked by Facebook.

Implement regular expression matching with the following special characters:

- . (period) which matches any single character
- \* (asterisk) which matches zero or more of the preceding element

That is, implement a function that takes in a string and a valid regular expression and returns whether or not the string matches the regular expression.

For example, given the regular expression "ra." and the string "ray", your function should return true. The same regular expression on the string "raymond" should return false.

Given the regular expression ".*at" and the string "chat", your function should return true. The same regular expression on the string "chats" should return false.

## My solution

My instinct: read characters one by one...

Divide expression into a sequence of period, asterisk and "other string";

Match the expression sequence against the string.

UPDATE:

Can't solve...Checked online answers.

Decided to implement a matrix.

On a second thought, what about map and set?

I can use a 2d array to record the position where regular expression and string content match. Or I use an unordered map (with vector as value).

----

O(?) time complexity and O(?) space complexity.

## Googled solution (if I actually googled it)

[python](https://github.com/ruppysuppy/Daily-Coding-Problem-Solutions/blob/master/Solutions/025.py)

This certainly gave me an idea - using a matrix(or 2d-array or whatever it is called).

I donno if the original answer is correct (because my test case failed). I'll try implementing this way anyway.
