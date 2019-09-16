# Programming Assignment Four - Operating Systems

Generated multiple paging schemes to optimize the performance of the memory access in a number of predefined programs. Specifically, designed an LRU paging implementation and predictive paging implementation.  

## File Descriptions

* **pager-lru.c** - *LRU Paging Implementation* - A local version of the "least recently used" swapping strategy.

* **pager-predict.c** - *Predictive Paging Implementation* - A paging strategy that relies heavily on the program knowledge given. Pages in pages only when they are needed and pages them out only when they are not needed by any programs. Does not include any swapping out of pages when memory is full.   

* **Makefile** - Builds both the pager-predict and pager-lru programs (as well as the given pager-basic file). Can either make one specific file (basic, lru, or predict) or "make all" recreates all generated files.


## Instructions for Building and Running
* Navigate to the directory in which the pager-lru.c and pager-predict.c functions are located.
* Compile pager-predict using the command: **make test-predict**
* Run pager-predict using the command: **./test-predict**
* Compile pager-lru using the command: **make test-lru**
* Run pager-lru using the command: **./test-lru**

### Emily Millican - Emily.Millican@Colorado.Edu
