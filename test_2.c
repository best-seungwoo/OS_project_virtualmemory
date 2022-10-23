#include "types.h"
#include "stat.h"
#include "user.h"
#include "mmu.h"

int
main(int argc, char *argv[])
{
  int* ptr_array[10];
  int size_array[10] = {600, 5, 100, 5, 1300, 5, 300, 5, 800, 5};
  int size_array2[5] = {200, 900, 300, 100, 700};
  int size_array3[5] = {500, 200, 300, 200, 400};
  int i;

  // Malloc ten times
  printf(1, "----------------malloc 10 times-----------------\n");
  for(i = 0; i < 10; i++){
    ptr_array[i] = (int*)malloc(size_array[i] * 8 - 8);
    //just to avoid warning
    ptr_array[i][0] = 0;
  }
  print_free_list();

  // Free five times
  printf(1, "-----------------free 5 times-------------------\n");
  for(i = 0; i < 5; i++){
    free(ptr_array[2 * i]);
  }
  print_free_list();

  // Show results when using first fit strategy (default)
  printf(1, "------------------first fit---------------------\n");
  for(i = 0; i < 5; i++){
    printf(1, "malloc(%d)\n", size_array2[i])    ;
    malloc(size_array2[i] * 8 - 8);
  }
  print_free_list();

  //init_freep();
  printf(1, "-------------------best fit---------------------\n");
  for(i = 0; i < 5; i++){
    printf(1, "malloc_bf(%d)\n", size_array3[i])    ;
    malloc_bf(size_array3[i] * 8 - 8);
  }
  print_free_list();

  exit();
}
