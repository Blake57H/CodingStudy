# Daily Coding Problem: Problem #14 [Medium]

Good morning! Here's your coding interview problem for today.

This problem was asked by Google.

The area of a circle is defined as πr^2. Estimate π to 3 decimal places using a Monte Carlo method.

Hint: The basic equation of a circle is x^2 + y^2 = r^2.

## My solution

Reference: [Wikipedia](https://en.wikipedia.org/wiki/Monte_Carlo_method#Overview)

According to Wikipedia, given 1 as the length of square:

1. quadrant area = nSampleInsideCircle / totalSampleSize
2. rant area = 4 * quadrant area = pi * (length of square)^2 = pi
3. (4 * nSampleInsideCircle) / squareSize^2 = pi
4. pi = (4 * nSampleInsideCircle) / squareSize^2

----

O(?) time complexity and O(?) space complexity.

## Googled solution (if I actually googled it)
