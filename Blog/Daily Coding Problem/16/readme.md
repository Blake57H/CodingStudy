# Daily Coding Problem: Problem #16 [Easy]

Good morning! Here's your coding interview problem for today.

This problem was asked by Twitter.

You run an e-commerce website and want to record the last `N` `order` ids in a log. Implement a data structure to accomplish this, with the following API:

    record(order_id): adds the order_id to the log
    get_last(i): gets the ith last element from the log. i is guaranteed to be smaller than or equal to N.

You should be as efficient with time and space as possible.

## My solution

1. Setup a vector to save order information.
2. Make use of vector's `end()` iterator.
3. Step 2 translates into `return std::vector{orders.end()-i, orders.end()}`
4. return the result from step 3.

----

## Googled solution (if I actually googled it)
