# Daily Coding Problem: Problem #11 [Medium]

Good morning! Here's your coding interview problem for today.

This problem was asked by Twitter.

Implement an autocomplete system. That is, given a query string `s` and a set of all possible query strings, return all strings in the set that have s as a prefix.

For example, given the query string `de` and the set of strings `[dog, deer, deal]`, return `[deer, deal]`.

Hint: Try preprocessing the dictionary into a more efficient data structure to speed up queries.

## My solution

Make a tree that stores individual characters (and their following characters)?

The tree node should contain a map that stores the following character map, a `char`/`string` that represents current character.

This approach doesn't look memory efficient.

I suck at logic thinking... I started to get angry with myself...

## Googled solution (if I actually googled it)

Looks like my tree is a [Trie](https://www.geeksforgeeks.org/introduction-to-trie-data-structure-and-algorithm-tutorials/).

[https://github.com/ruppysuppy/Daily-Coding-Problem-Solutions/blob/master/Solutions/011.py](https://github.com/ruppysuppy/Daily-Coding-Problem-Solutions/blob/master/Solutions/011.py)

The solution uses a build-in/library structure object. While I wrote the structure myself...
