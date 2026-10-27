#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
  char *p;
  int i;

  printf(1, "Lazy allocation test\n");

  p = sbrk(32 * 4096);
  if(p == (char*)-1){
    printf(1, "sbrk failed\n");
    exit();
  }

  printf(1, "Faults before access: %d\n", getfaults());

  for(i = 0; i < 5; i++)
    p[i * 4096] = 1;

  printf(1, "Faults after access: %d\n", getfaults());

  exit();
}
