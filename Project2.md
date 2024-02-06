# Part 1 

## 1.1
1. The provided code fragment utilizes the variable i in both sequential and parallel loops without clearly defining its scope. Within OpenMP, a loop's variable automatically becomes private to each thread when used in parallel execution. Nonetheless, if i is defined outside the scope of the parallel region—as suggested by the code excerpt—this may result in conflicting data access
2. The snippet immediately employs the #pragma omp parallel for construct without confirming that the a, b, and c variables are initialized and ready for use in the parallel section.

## 1.2
**False Sharing**: False sharing occurs when multiple threads on different processors modify variables that reside on the same cache line, even though they are not actually sharing any data. Cache lines are the smallest unit of memory that can be transferred between the main memory and the cache. When one thread modifies a variable, the cache line containing that variable is marked as dirty, prompting an update across all caches to maintain coherence. If another thread modifies a different variable that happens to be on the same cache line, it causes the cache line to be invalidated and reloaded, even though the two variables are unrelated.

In the case of a chunk size of 1, adjacent iterations of the loop, which are likely modifying adjacent elements of array a, are distributed across different threads. If elements of a are stored in contiguous memory locations (which is typically the case), iterations assigned to different threads will often work on elements of a that reside on the same cache line. This will result in severe performance drop.

A good strategy is to let OpenMP determine it by setting a **dynamic** value.

These are highly relevant to MPI grammar, so first do section 3 & 4.

## 1.3



## 1.4

## 1.5


## 1.6 


# Part 2

# Part 3

## 3.1 Solution

Done!

## 3.2 Solution 

Done!

## 3.3 Solution

Every processors loads and runs the binary. Therefore even without including MPI library we get 4 exections of the code. 

## 3.4 Solution

We see 12 total "Hello, World!" (when we feed in 4 ranks). The "Hello, World" before and after the MPI rin in serial on every processor so should each be output 4 times fora total of 8. And since we do not limit the output for the one in the middle it should also be output 4 times, for a total of 12.   

## 3.5 Solution

### Exercise 2.3

Check **ppbook.c**

TBD: run on hpcc

### Exercise 2.4

Check **ppbook.c**

Will output
```
Process 0 on czk123.dhcp.egr.msu.edu out of 4
Process 2 on czk123.dhcp.egr.msu.edu out of 4
Process 1 on czk123.dhcp.egr.msu.edu out of 4
Process 3 on czk123.dhcp.egr.msu.edu out of 4
```

### Exercise 2.5

Check **zerop.c**

Will output
```
Process 0 on czk123.dhcp.egr.msu.edu out of 4
```

# Part 4

## 