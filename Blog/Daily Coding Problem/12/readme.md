# Daily Coding Problem: Problem #12 [Hard]

Good morning! Here's your coding interview problem for today.

This problem was asked by Amazon.

There exists a staircase with N steps, and you can climb up either 1 or 2 steps at a time. Given N, write a function that returns the number of unique ways you can climb the staircase. The order of the steps matters.

For example, if N is 4, then there are 5 unique ways:

- 1, 1, 1, 1
- 2, 1, 1
- 1, 2, 1
- 1, 1, 2
- 2, 2

What if, instead of being able to climb 1 or 2 steps at a time, you could climb any number from a set of positive integers X? For example, if X = {1, 3, 5}, you could climb 1, 3, or 5 steps at a time.

## My solution

Build a tree structure to record each climb. Parent node records how many steps to take this time. Child nodes will be recording how many steps to take next chimb.

If climb can reach that N step, then this climb is valid and should be returned as result. Otherwise dump the result since it is invalid.

----

## Googled solution (if I actually googled it)
