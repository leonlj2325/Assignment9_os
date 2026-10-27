#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
  printf(1, "Before sbrk:\n");
  vmprint();

  sbrk(4 * 4096);

  printf(1, "After sbrk:\n");
  vmprint();

  exit();
}
