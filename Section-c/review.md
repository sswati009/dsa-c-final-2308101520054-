## C1 Defect Report

| No | Line | Defect                           | Consequence                                                           |
|----|------|----------------------------------|-----------------------------------------------------------------------|
| 1  | 4    |`prev` is not initialized to NULL |Assigning`curr->next = prev` uses a junk pointer and causes a segfault | 
| 2 | 7     | Loop condition stops early at `curr->next != NULL` | Misses reversing the last node of the list |
| 3 | 12 | Function returns `head` instead of `prev` | Returns the original head node (which is now the tail) instead of the new head |

Corrected function: SectionC/C1_reverse.c
Complexity: Time O(n), Space O(1)

---

## C2 Optimisation

* **Current Time Complexity:** O(n^2) because of the nested for loops checking every pair of indices.
* **Why it fails at scale (n=1,000,000):** With 1 million elements, running O(n^2) takes around 10^12 operations, causing a Time Limit Exceeded (TLE) error.
* **Validity Condition:** The sliding window works because all array elements are strictly positive integers, meaning the running sum always increases when moving right and decreases when shrinking from the left.
