## `Hash Set using open addressing with quadratic probing by alternating signs`  test result:

### with `USE_EXPONETIAL_EXPANDING` off:

```
Inserting: 5000000 items in 3942 ms
Linear access of existing elements: 5000000 items in 1754 ms
Linear access of existing elements (2nd round): 5000000 items in 1734 ms
Random access of existing elements: 5000000 items in 1318 ms
Accessing random keys: 5000000 items in 351 ms
Accessing missing: 5000000 items in 1587 ms
Removing and adding: 5000000 items in 5538 ms
Linear access of existing elements: 5000000 items in 3033 ms
```

### with `USE_EXPONETIAL_EXPANDING` on:

```
Inserting: 5000000 items in 3474 ms
Linear access of existing elements: 5000000 items in 1592 ms
Linear access of existing elements (2nd round): 5000000 items in 1559 ms
Random access of existing elements: 5000000 items in 1304 ms
Accessing random keys: 5000000 items in 383 ms
Accessing missing: 5000000 items in 1230 ms
Removing and adding: 5000000 items in 4779 ms
Linear access of existing elements: 5000000 items in 2510 ms
```

### compare to `redis`:

```
Inserting: 5000000 items in 3329 ms
Linear access of existing elements: 5000000 items in 1635 ms
Linear access of existing elements (2nd round): 5000000 items in 1622 ms
Random access of existing elements: 5000000 items in 1586 ms
Accessing random keys: 5000000 items in 522 ms
Accessing missing: 5000000 items in 1253 ms
Removing and adding: 5000000 items in 2999 ms
Linear access of existing elements: 5000000 items in 1643 ms
```

my code is using about 30% more memory when removing entries, because it have to malloc a new `entry_t` and 
set the `state` to `ENTRY_STATE_DELETED` to keep the `search chain` not broken.

and is much slower!

shit...

## `Hash set using seperate chaining` test result:

```
Inserting: 5000000 items in 3200 ms
Linear access of existing elements: 5000000 items in 1989 ms
Linear access of existing elements (2nd round): 5000000 items in 1360 ms
Random access of existing elements: 5000000 items in 1087 ms
Accessing random keys: 5000000 items in 519 ms
Accessing missing: 5000000 items in 891 ms
Removing and adding: 5000000 items in 3009 ms
Linear access of existing elements: 5000000 items in 1391 ms

Hash table 0 stats (main hash table):
 table size: 8388608
 number of elements: 5000000
 different slots: 3767701
 max chain length: 8
 avg chain length(counted): 1.33
 avg chain length(computed): 1.33
 Chain length distribution:
   0: 4620907 (55.09%)
   1: 2756794 (32.86%)
   2: 820641 (9.78%)
   3: 162704 (1.94%)
   4: 24336 (0.29%)
   5: 2919 (0.03%)
   6: 280 (0.00%)
   7: 23 (0.00%)
   8: 4 (0.00%)
```