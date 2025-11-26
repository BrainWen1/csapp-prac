#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define MAX_HEAP (20 * (1 << 20)) /* 20 MB */

/* Private global variables */
static char *mem_heap = NULL;     /* Points to first byte of heap */
static char *mem_brk = NULL;      /* Points to last byte of heap plus 1 */
static char *mem_max_addr = NULL; /* Max legal heap addr plus 1 */

/* mem_init -- Initialize the memory system model */
void mem_init(void) {
	if (mem_heap != NULL) {
		mem_brk = mem_heap;
		return;
	}

	mem_heap = (char *)malloc(MAX_HEAP);
	if (mem_heap == NULL) {
		fprintf(stderr, "ERROR: mem_init failed. Unable to allocate heap...\n");
		exit(1);
	}
	mem_brk = mem_heap;
	mem_max_addr = mem_heap + MAX_HEAP;
}

void mem_deinit(void) {
	if (mem_heap != NULL) {
		free(mem_heap);
	}
	mem_heap = NULL;
	mem_brk = NULL;
	mem_max_addr = NULL;
}

void mem_reset_brk(void) {
	if (mem_heap == NULL) {
		return;
	}
	mem_brk = mem_heap;
}

/* mem_sbrk -- Simple model of the sbrk function. Extends the heap */
/* by incr bytes and returns the start address of the new area. In */
/* this model, the heap cannot be shrunk. */
void *mem_sbrk(int incr) {
	if (mem_heap == NULL) {
		mem_init();
	}
	char *old_brk = mem_brk;

	if ((incr < 0) || ((mem_brk + incr) > mem_max_addr)) {
		errno = ENOMEM;
		fprintf(stderr, "ERROR: mem_sbrk failed. Ran out of memory...\n");
		return (void *)(-1);
	}

	mem_brk += incr;
	return (void *)old_brk;
}

void *mem_heap_lo(void) {
	return (void *)mem_heap;
}

void *mem_heap_hi(void) {
	return (void *)(mem_brk ? mem_brk - 1 : NULL);
}

size_t mem_heapsize(void) {
	return (size_t)(mem_heap && mem_brk ? (mem_brk - mem_heap) : 0);
}

size_t mem_pagesize(void) {
	long pgsize = sysconf(_SC_PAGESIZE);
	if (pgsize <= 0) {
		return 0;
	}
	return (size_t)pgsize;
}
