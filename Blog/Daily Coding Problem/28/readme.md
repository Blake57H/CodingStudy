# Daily Coding Problem: Problem #28 [Medium]

Good morning! Here's your coding interview problem for today.

This problem was asked by Palantir.

Write an algorithm to justify text. Given a sequence of words and an integer line length k, return a list of strings which represents each line, fully justified.

More specifically, you should have as many words as possible in each line. There should be at least one space between each word. Pad extra spaces when necessary so that each line has exactly length k. Spaces should be distributed as equally as possible, with the extra spaces, if any, distributed starting from the left.

If you can only fit one word on a line, then you should pad the right-hand side with spaces.

Each word is guaranteed not to be longer than k.

For example, given the list of words ["the", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog"] and k = 16, you should return the following:

```text
["the  quick brown", # 1 extra space on the left
"fox  jumps  over", # 2 extra spaces distributed evenly
"the   lazy   dog"] # 4 extra spaces distributed evenly
```

## My solution

First impression would be using queue. Read words from a list, calculate the length of each word, and decide how many space I need to insert.

Distribute space equally makes this problem easier, since I don't need to distribute space according to word length.

----

O(?) time complexity and O(?) space complexity.

## Googled solution (if I actually googled it)
