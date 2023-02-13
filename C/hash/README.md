## `Hash Set using open addressing with quadratic probing by alternating signs`  test result:

### with `USE_HT` off:

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

### with `USE_HT` on:

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