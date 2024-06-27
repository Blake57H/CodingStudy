# Daily Coding Problem: Problem #15 [Medium]

Good morning! Here's your coding interview problem for today.

This problem was asked by Facebook.

Given a stream of elements too large to store in memory, pick a random element from the stream with uniform probability.

## My solution

Use random number to pick an item. It will work

However I can't proof the "uniform probability" this way...

----

I have another brain wave...

If I use a binary `std::uniform_int_distribution` (0 and 1) to decide whether the element is used or not when iterating the stream (since elements are too large to fit into memory), in my mind for each element whether it is picked or not should be 50 50. This should be a "uniform probability" (or I thought so).

## Googled solution (if I actually googled it)

In python, the build-in `random.sample` can be used. Check [here](https://stackoverflow.com/questions/74622881/pick-elements-from-the-list-randomly-in-uniform-distribution-without-replacement).

In C++... [here](https://stackoverflow.com/questions/69873685/how-to-randomly-pick-element-from-an-array-with-different-probabilities-in-c).

More reference:

- [https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution](https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution)
