# Daily Coding Problem: Problem #41 [Medium]

Good morning! Here's your coding interview problem for today.

This problem was asked by Facebook.

Given an unordered list of flights taken by someone, each represented as (origin, destination) pairs, and a starting airport, compute the person's itinerary. If no such itinerary exists, return null. If there are multiple possible itineraries, return the lexicographically smallest one. All flights must be used in the itinerary.

For example, given the list of flights [('SFO', 'HKO'), ('YYZ', 'SFO'), ('YUL', 'YYZ'), ('HKO', 'ORD')] and starting airport 'YUL', you should return the list ['YUL', 'YYZ', 'SFO', 'HKO', 'ORD'].

Given the list of flights [('SFO', 'COM'), ('COM', 'YYZ')] and starting airport 'COM', you should return null.

Given the list of flights [('A', 'B'), ('A', 'C'), ('B', 'C'), ('C', 'A')] and starting airport 'A', you should return the list ['A', 'B', 'C', 'A', 'C'] even though ['A', 'C', 'A', 'B', 'C'] is also a valid itinerary. However, the first one is lexicographically smaller.

## My solution

1. Make a map to store airport pairs. (So that I could read data in lexicographical order).
2. Using current starting point to find the key-value pair in map.
3. If such key exists, recursively find the next pair using the value as key.
4. End the recursive finding if final iteration's map is empty.
5. Return "null" if final iteration's map is not empty and no next valid destination.

----

O(?) time complexity and O(?) space complexity.

## Googled solution (if I actually googled it)
