#include "types.h"
#include "stat.h"
#include "user.h"
#include "mmu.h"

int
main(int argc, char *argv[])
{
  // Get valid page count of parent
  int parent_count = get_valid_page_count();

  // Child 1
  if(fork() == 0) {
    // Create variables on heap
    int* heap_var_child1 = (int *)malloc(PGSIZE * 100 - 8);

    // Just to avoid warning
    heap_var_child1[0] = 0;

    // Get valid page count of child1 after allocating
    int child1_count = get_valid_page_count();
    printf(1, "Child1\n");
    printf(1, "Output: %d (after malloc)\n", child1_count - parent_count);

    // Deallocate the heap memory
    ufree(heap_var_child1);

    // Get valid page count of child1 after freeing
    int child1_count_free = get_valid_page_count();
    printf(1, "Output: %d (after free)\n", child1_count_free - parent_count);
    if(child1_count - child1_count_free == 100) printf(1, "You are right!\n");
    else printf(1, "You are wrong..\n");

    exit();
  }

  // Child 2
  else if(fork() == 0) {
    sleep(5);

    // Create variables on heap
    int* heap_var_child2 = (int *)malloc(PGSIZE * 10000 - 8);

    // Just to avoid warning
    heap_var_child2[0] = 0;

    // Get valid page count of child2 after allocating
    int child2_count = get_valid_page_count();
    printf(1, "Child2\n");
    printf(1, "Output: %d (after malloc)\n", child2_count - parent_count);

    // Deallocate the heap memory
    ufree(heap_var_child2);

    // Get valid page count of child2 after freeing
    int child2_count_free = get_valid_page_count();
    printf(1, "Output: %d (after free)\n", child2_count_free - parent_count);
    if(child2_count - child2_count_free == 10000) printf(1, "You are right!\n");
    else printf(1, "You are wrong..\n");

    exit();
  }
  // Parent: wait for children
  else {
    wait();
    wait();
  }
  exit();
}
