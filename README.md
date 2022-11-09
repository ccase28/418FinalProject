# Parallel Malloc Implementation

# URL
https://ccase28.github.io/418FinalProject/

# Summary

# Background
glibc's "malloc" allocator relies on mutual exclusion locks around critical procedures in order to guarantee thread safety in concurrent shared-memory applications. This exposes the malloc suite to general availability concerns as thread counts increase, particularly deadlock (in the worst case). Can we do better than this?

One often-discussed solution is to use separate mergeable arenas for each thread, which reduce contention. This still doesn't eliminate the need for locking, though. Our goal is to create a highly scalable, thread-safe, and ideally lock-free allocator that maximises availability to applications in addition to reducing data fragmentation. Constructing a lock-free allocator can be done using hardware-supported atomic instructions such as compare-and-swap, as well as thread-local caches (along the lines of Google's tcmalloc).

# Challenges

# Resources
 For this project, we primarily plan to use 
# Goals / Deliverables
### Plan to Acheive
Single global lock

### Hope to achieve
Lock free

# Schedule
