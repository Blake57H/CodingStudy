# Daily Coding Problem: Problem #13 [Hard]

Good morning! Here's your coding interview problem for today.

This problem was asked by Amazon.

Given an integer k and a string s, find the length of the longest substring that contains at most k distinct characters.

For example, given s = "abcba" and k = 2, the longest substring with k distinct characters is "bcb".

## My solution

Time to implement the "most comment substring" algorithm I googled a few weeks back.

A that time I have a lot of  duplicated torrent files and wanted to removed them based on filename and size.

1. Build a tree object containing all possible substring.
2. Then query the substring with max distinct characters of 2 (the check at line 48)
3. Print all possible results.

----

I learnt that I probably should use string_view for parameter and string for return value. This way I should be able to avoid data copy while passing parameter, and avoid variable life cycle issue while reading returned data.

## Googled solution (if I actually googled it)
