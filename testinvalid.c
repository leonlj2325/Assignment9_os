#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
  int pid;

  printf(1, "Invalid memory access test\n");

  pid = fork();

  if(pid < 0){
    printf(1, "fork failed\n");
    exit();
  }

  if(pid == 0){
    char *p = sbrk(0);
    printf(1, "Child accessing invalid address...\n");
    p[4096] = 1;
    printf(1, "ERROR: child survived invalid access\n");
    exit();
  }

  wait();
  printf(1, "Parent survived child fault\n");
  exit();
}
