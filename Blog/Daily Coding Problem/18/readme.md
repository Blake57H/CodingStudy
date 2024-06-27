# Daily Coding Problem: Problem #18 [Hard]

Good morning! Here's your coding interview problem for today.

This problem was asked by Google.

Given an array of integers and a number k, where 1 <= k <= length of the array, compute the maximum values of each subarray of length k.

For example, given array = [10, 5, 2, 7, 8, 7] and k = 3, we should get: [10, 7, 8, 8], since:

- 10 = max(10, 5, 2)
- 7 = max(5, 2, 7)
- 8 = max(2, 7, 8)
- 8 = max(7, 8, 7)

Do this in O(n) time and O(k) space. You can modify the input array in-place and you do not need to store the results. You can simply print them out as you compute them.

## My solution

I don't think the build-in max function can be trusted. I can't be sure it costs O(n) time.

For k >= 3, I divided each sub-array into 3 parts. 

- sub-array[0] is PART1, also the position where max value is stored.
- sub-array[1] is PART2.
- sub-array[2:] (from 3rd to the last element) is PART3, there an unseen value should be compared.

```bash
 >< PART1, 10
        >!!!< PART3, [2, 7]
[10, 5, 2, 7, 8, 7]
 > 1st  <
     > 2nd <
    >< PART2, 5
```

For each sub-array, I mark the 

----

O(?) time complexity and O(?) space complexity.

## Googled solution (if I actually googled it)

[https://github.com/ruppysuppy/Daily-Coding-Problem-Solutions/blob/master/Solutions/018.py](https://github.com/ruppysuppy/Daily-Coding-Problem-Solutions/blob/master/Solutions/018.py)

It appeared to be making use of the O(k) space to keep track of the last k maximum values of each sub array (last 1, then last 2, then ... until last k).

However time complexity seemed to be O(n*k). <-- False

`while(dq)` should be treated as O(1) time
