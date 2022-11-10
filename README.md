# Parallel Malloc Implementation

# URL
https://ccase28.github.io/418FinalProject/

# Summary
We plan to create a highly scalable, thread-safe, and ideally lock-free allocator that maximises availability to applications in addition to reducing data fragmentation. To do so, we will utilize separate, mergeable arenas for each thread. 

# Background
glibc's "malloc" allocator relies on mutual exclusion locks around critical procedures in order to guarantee thread safety in concurrent shared-memory applications. This exposes the malloc suite to general availability concerns as thread counts increase, particularly deadlock (in the worst case). Can we do better than this?

One often-discussed solution is to use separate mergeable arenas for each thread, which reduce contention. This still doesn't eliminate the need for locking, though. Our goal is to create a highly scalable, thread-safe, and ideally lock-free allocator that maximises availability to applications in addition to reducing data fragmentation. Constructing a lock-free allocator can be done using hardware-supported atomic instructions such as compare-and-swap, as well as thread-local caches (along the lines of Google's tcmalloc).

# Challenges
We believe that the greatest challenge in this project will be building a thread-safe allocator that does not use traditional synchronization primitives. The chunk of memory, or "heap", that we need to keep track of actually constitutes the underlying data structure, so keeping track of global state is extra tricky.

# Resources
 For this project, we primarily plan to use the PSC machines to test our implentation. We also plan to use the GHC machines for testing in order to conserve resources. As a starting point, we will be using Makoto's 213 implentation of Malloc Lab. We'll need to make further optimizations to this code, as well as entirely rewriting support routines that instantiate and manage different heaps. 
 
 [1] Google, _tcmalloc overview_. https://google.github.io/tcmalloc/overview.html.
 
 [2] Maged M. Michael. _Scalable Lock-Free Dynamic Memory Allocation_. 
 
# Goals / Deliverables
### Plan to Acheive
An single-heap, thread-safe allocator with a single global lock. 

We will extend this implementation to work with multiple arenas, and experiment with (1) multiple arenas that are each statically assigned to a single thread, still managed by mutexes, and (2) a shared pool of arenas that are dynamically claimed as needed by a thread using a bounded-buffer switch.

All three implementations will be run tested by various multithreaded programs, each with different access patterns, to analyze speedup (or slowdown, as the case may be).

### Hope to achieve
If we have time, our stretch goal is to implement a completely lock free version of Malloc. 

# Schedule
We elected to go with the earlier project presentation slot. Because of this, our schedule must be expedited. 
