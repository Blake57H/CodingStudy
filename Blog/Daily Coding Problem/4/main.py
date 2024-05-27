import random
import time
from typing import Any

# solution from https://stackoverflow.com/a/62525133

# very clever, using the value of array index as the result...

def lowestMissingStrictlyPositiveInteger(arr):
    """ Return the lowest missing strictly 
    positive integer from the array arr. 
    Warning: In order to achieve this in linear time and
    constant space, arr is modified in-place.
    
    Uses separatePositiveIntegers() to isolate all
    strictly positive integers, and marks their occurrence
    with markIndicesOfObservedPositiveIntegers(). This 
    function then scans the modified array for the 'marks'
    and returns the first unmarked value. """
    m = separatePositiveIntegers(arr)
    print(arr, m)
    markIndicesOfObservedPositiveIntegers(arr, m)
    print(arr, m)
    for i in range(m): #O(m)
        if arr[i]>0:
            # this index hasn't been marked by
            # markIndexOfObservedPositiveIntegers(), 
            # therefore the integer i+1 is missing.
            return i+1
    return m+1

def separatePositiveIntegers(arr):
    """ Modify input array in place, so that 
    strictly positive integers are
    all at the start of the array, 
    and negative integers are
    all at the end of the array. 
    
    Return the index of the first negative 
    integer in the updated array (or len(arr)
    if all values are positive). """
    i1, i2 = 0, len(arr)-1
    while (i2 > i1): #O(n)
        
        if arr[i2]<=0:
            # move to the first strictly positive value
            # starting from the end of the array.
            i2 -= 1
            continue
        
        if arr[i1]>0:
            # move to the first negative value
            # from the start of the array.
            i1 += 1
            continue
        
        # swap negative value at i1 with the first
        # strictly positive value starting from the
        # end of the array (i.e., at position i2).
        tmp = arr[i2]
        arr[i2] = arr[i1]
        arr[i1] = tmp
    
    return i1 if arr[i1]<=0 else i1+1

def markIndicesOfObservedPositiveIntegers(arr, m):
    """ Take an array arr of integer values, 
    where indices [0,m-1] are all strictly positive
    and indices >= m are all negative
    (see separatePositiveIntegers() method).
    
    Mark the occurrence of a strictly positive integer
    k<=m by assigning a negative sign to the value in 
    the array at index k-1 (modify in place)."""
    for i in range(m): #O(m)
        # all values at indices [0,m-1] are strictly positive 
        # to start with, but may have been  modified in-place 
        # (switched to negative sign) in this loop. 
        # Therefore, read the untampered value as abs(arr[i]).
        untampered_val=abs(arr[i])
        # We can safely ignore any untampered value strictly superior to m
        # because it guarantees a gap in the integer sequence at a lower value 
        # (since arr only has m strictly positive integers).
        if untampered_val<=m:
            # mark the integer as "seen" by
            # changing the sign of the value at
            # index untampered_val-1 to negative.
            arr[untampered_val-1] = -abs(arr[untampered_val-1])


if __name__ == '__main__':
    s = time.perf_counter()
    # test 1
    arr = [4, 2, 1, 1]
    assert lowestMissingStrictlyPositiveInteger(arr) == 3

    # test 2
    arr = [2, 0, 1]
    assert lowestMissingStrictlyPositiveInteger(arr) == 3

    # test 3
    arr = [1, 1, 1]
    assert lowestMissingStrictlyPositiveInteger(arr) == 2
    e = time.perf_counter()
    print(f"time consumed: {e-s:.6f} seconds")
