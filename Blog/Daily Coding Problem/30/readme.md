# Daily Coding Problem: Problem #30 [Medium]

Good morning! Here's your coding interview problem for today.

This problem was asked by Facebook.

You are given an array of non-negative integers that represents a two-dimensional elevation map where each element is unit-width wall and the integer is the height. Suppose it will rain and all spots between two walls get filled up.

Compute how many units of water remain trapped on the map in O(N) time and O(1) space.

For example, given the input [2, 1, 2], we can hold 1 unit of water in the middle.

Given the input [3, 0, 1, 3, 0, 5], we can hold 3 units in the first index, 2 in the second, and 3 in the fourth index (we cannot hold 5 since it would run off to the left), so we can trap 8 units of water.

## My solution

I spent quite some time to understand what the problem is. I couldn't understand what "unit-width wall" is, until I started treating it as "floor".

>> "given the input [2, 1, 2], we can hold 1 unit of water in the middle"

Imagine a map, where there's 3 trunks of floor. The floor's height is 2 units on the left, 1 unit on the middle, and 2 on the right. Therefore 1 unit of water will be trapped in this map.

![Image of map (2,1,2)](30-1.png)

>> Given the input [3, 0, 1, 3, 0, 5], we can hold 3 units in the first index, 2 in the second, and 3 in the fourth index (we cannot hold 5 since it would run off to the left), so we can trap 8 units of water.

I drew a map of this example.

![Image of map (3, 0, 1, 3, 0, 5)](30-2.png)

And to solve this problem I imagine I need the program to know where the curve is going. Begin from the first floor, is the floor height going up or going down?

Update 1: I think I only need the position of the top of the hills (the place where floors on its left and right are lower).

----

Array is iterated (at most) 2 times.

O(n) time complexity and O(1) space complexity.

## Googled solution (if I actually googled it)
