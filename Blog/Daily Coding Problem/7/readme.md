# Daily Coding Problem: Problem #7 [Medium]

Good morning! Here's your coding interview problem for today.

This problem was asked by Facebook.

Given the mapping a = 1, b = 2, ... z = 26, and an encoded message, count the number of ways it can be decoded.

For example, the message '111' would give 3, since it could be decoded as 'aaa', 'ka', and 'ak'.

You can assume that the messages are decodable. For example, '001' is not allowed.

## My solution

1. Setup a tree-like structure for possible ways to decode a message. Root node defined as "$R".
2. Setup a queue to decode the message. A queue data includes:
    - Current node object, with possible child node, in child_node.
    - Current position of the encoded string.
3. Process the child node. Find its possible child, add them to its child map.  Remove if all child node shown undecodable (defined as "$X").
4. *That should be all?
5. Display the possible decodes. Result will be the number of leaf nodes (defined as "$E").

----

A daily question takes me 3 days to solve... Am I really up for this career?
