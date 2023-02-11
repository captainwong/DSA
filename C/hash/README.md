test result:

with `USE_HT` off:

```
Inserting: 5000000 items in 4183 ms
Linear access of existing elements: 5000000 items in 1798 ms
Linear access of existing elements (2nd round): 5000000 items in 1755 ms
Random access of existing elements: 5000000 items in 1334 ms
```

with `USE_HT` on:

```
Inserting: 5000000 items in 3521 ms
Linear access of existing elements: 5000000 items in 1601 ms
Linear access of existing elements (2nd round): 5000000 items in 1608 ms
Random access of existing elements: 5000000 items in 1374 ms
```

compare to `redis`, my code is a little bit slow...

```
Inserting: 5000000 items in 3395 ms
Linear access of existing elements: 5000000 items in 1603 ms
Linear access of existing elements (2nd round): 5000000 items in 1606 ms
Random access of existing elements: 5000000 items in 1503 ms
Accessing random keys: 5000000 items in 560 ms
Accessing missing: 5000000 items in 1232 ms
Removing and adding: 5000000 items in 2940 ms
```