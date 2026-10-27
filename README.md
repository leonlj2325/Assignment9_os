# Operating Systems — Assignment 9

# Roll No. 2403MC04

# Name - Leon Joel

## Question 1: Printing the Page Table

Implemented the `vmprint()` system call to display the page table of the calling process. It prints the virtual address, physical address, and flags for each valid user page, along with the total number of user pages and page-table pages. Kernel mappings are excluded.

**Result:** The test showed 3 user pages before calling `sbrk(4 * 4096)` and 7 afterwards. The increase of four pages matches the expected result.

## Question 2: Lazy Allocation and Page Faults

Modified `sys_sbrk()` so that positive requests reserve virtual address space without immediately allocating physical memory. Updated `deallocuvm()` and `copyuvm()` to handle pages that have not been allocated yet.

Added page-fault handling in `trap.c`. When a valid user address below the process size is accessed for the first time, the handler allocates a zeroed page and maps it. A page fault outside the process's allocated address space causes the process to be killed. Added a per-process fault counter and the `getfaults()` system call.

**Results:**
- Reserved 32 pages and accessed five distinct pages.
- The fault counter increased from 2 to 7, meaning five additional page faults were handled.
- An invalid memory access terminated the child process while the parent continued running.

## Question 3: FIFO and LRU Page Replacement

Implemented `pagerepl.c` to simulate FIFO and LRU page replacement using the reference string:

`7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1`

The algorithms were tested with 3, 4, and 5 frames.

| Frames | FIFO Faults | FIFO Hit Ratio | LRU Faults | LRU Hit Ratio |
|---:|---:|---:|---:|---:|
| 3 | 15 | 25% | 12 | 40% |
| 4 | 10 | 50% | 8 | 60% |
| 5 | 9 | 55% | 7 | 65% |

**Result:** With three frames, FIFO produced 15 page faults and LRU produced 12, matching the expected values. Both algorithms produced fewer faults when more frames were available for this reference string.


**Note:** The test program filenames differ slightly from those specified in the assignment. `testvm.c` and `testlazy.c` are used in place of `pttest.c` and `faulttest.c`, respectively. Their functionality remains the same.
