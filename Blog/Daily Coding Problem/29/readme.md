# Daily Coding Problem: Problem #29 [Easy]

Good morning! Here's your coding interview problem for today.

This problem was asked by Amazon.

Run-length encoding is a fast and simple method of encoding strings. The basic idea is to represent repeated successive characters as a single count and character. For example, the string "AAAABBBCCDAA" would be encoded as "4A3B2C1D2A".

Implement run-length encoding and decoding. You can assume the string to be encoded have no digits and consists solely of alphabetic characters. You can assume the string to be decoded is valid.

## My solution

My instinct tells me to do it like a queue.

Iterate the string from beginning to the end.

For each character in the string, count the character so that a digit can be recorded to "encode".

As for the decode part, read a number then a alphabet.

----

Expect O(n) time complexity and O(n) space complexity.

Space complexity due to string buffer during encoding and decoding.

## Googled solution (if I actually googled it)
