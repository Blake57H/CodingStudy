# Daily Coding Problem: Problem #35 [Hard]

Good morning! Here's your coding interview problem for today.

This problem was asked by Google.

Given an array of strictly the characters 'R', 'G', and 'B', segregate the values of the array so that all the Rs come first, the Gs come second, and the Bs come last. You can only swap elements of the array.

Do this in linear time and in-place.

For example, given the array ['G', 'B', 'R', 'R', 'B', 'R', 'G'], it should become ['R', 'R', 'R', 'G', 'G', 'B', 'B'].

## My solution

My first impression would be:

1. Initialize a front pointer and a back pointer. Both of them would be pointing the first element.
2. Back pointer start moving, and find the first occurrence of not 'R' character.
3. Front pointer would then find the first occurrence of 'R' character beyond back pointer. If found then swap the value which front and back is pointing at.
4. Go back to step 2 until 'R' cannot be found in step 3. That way 'R' should be sorted.
5. Go back to step 1, except this time, both pointer would point at back pointer's next element, and sort character 'G'.
6. When 'G' is sorted, 'B' should also be sorted.

----

O(n) time complexity and O(1) space complexity.

## Googled solution (if I actually googled it)
