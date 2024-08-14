# Daily Coding Problem: #22 [Medium]

Good morning! Here's your coding interview problem for today.

This problem was asked by Microsoft.

Given a dictionary of words and a string made up of those words (no spaces), return the original sentence in a list. If there is more than one possible reconstruction, return any of them. If there is no possible reconstruction, then return null.

For example, given the set of words 'quick', 'brown', 'the', 'fox', and the string "thequickbrownfox", you should return ['the', 'quick', 'brown', 'fox'].

Given the set of words 'bed', 'bath', 'bedbath', 'and', 'beyond', and the string "bedbathandbeyond", return either ['bed', 'bath', 'and', 'beyond] or ['bedbath', 'and', 'beyond'].

## My solution

~~I feel like this is the common substring problem and want to solve it with tree like structure.~~

~~So I'll make the tree, then iterate the string over the tree.~~

1. Make an unordered set of words.
2. Create a start and end pointer to look for sub string.
3. Match the said substring to words-set, until string exhausted.

----

~~O(?) time complexity and O(?) space complexity.~~

My solution does not considerate time or space complexity.

## Googled solution (if I actually googled it)
