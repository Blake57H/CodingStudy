# Daily Coding Problem: Problem #21 [Easy]

Good morning! Here's your coding interview problem for today.

This problem was asked by Snapchat.

Given an array of time intervals (start, end) for classroom lectures (possibly overlapping), find the minimum number of rooms required.

For example, given [(30, 75), (0, 50), (60, 150)], you should return 2.

## My solution

1. Sort the list
2. Create a list-like thing (to simulate the schedule)
3. Record the max concurrent lectures (how many lectures will happen at the same time)
4. Return the result

Alternatively...

1. I create some race tracks (schedule for lectures).
2. I line up the race cars (sorting lectures in chronological order)
3. Overlapping lectures gets its own classroom
4. Count the max classrooms needed

I don't think will perform with time-efficiency.

----

O(?) time complexity and O(?) space complexity.

## Googled solution (if I actually googled it)
