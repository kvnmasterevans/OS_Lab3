#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(void)
{
  char *stack = malloc(8192);
  int *result = malloc(sizeof(int));
  *result = 0;


  if(stack == 0) {
    printf("Stack allocation failed\n");
    exit(1);
  }

  int pid = clone(stack + 4096);

  if(pid < 0) {
    printf("clone failed\n");
    exit(1);
  }

  if(pid == 0) {
    printf("Child: clone returned 0\n");
    *result = 42;
    exit(0);
  }

  printf("Parent: clone returned PID %d\n", pid);

  int child_pid = wait(0);
  printf("Shared memory result: %d\n", *result);
  printf("Parent: wait returned PID %d\n", child_pid);

  free(stack);
  exit(0);
}
