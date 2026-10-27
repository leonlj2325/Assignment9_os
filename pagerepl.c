#include "types.h"
#include "stat.h"
#include "user.h"

#define NREF 20
#define MAX_FRAMES 5

int refs[NREF] = {
  7, 0, 1, 2, 0, 3, 0, 4, 2, 3,
  0, 3, 2, 1, 2, 0, 1, 7, 0, 1
};

int
fifo(int n)
{
  int frames[MAX_FRAMES];
  int count = 0;
  int next = 0;
  int faults = 0;
  int i, j, hit;

  for(i = 0; i < MAX_FRAMES; i++)
    frames[i] = -1;

  for(i = 0; i < NREF; i++){
    hit = 0;

    for(j = 0; j < n; j++){
      if(frames[j] == refs[i]){
        hit = 1;
        break;
      }
    }

    if(hit)
      continue;

    faults++;

    if(count < n){
      frames[count] = refs[i];
      count++;
    } else {
      frames[next] = refs[i];
      next = (next + 1) % n;
    }
  }

  return faults;
}

int
lru(int n)
{
  int frames[MAX_FRAMES];
  int last_used[MAX_FRAMES];
  int count = 0;
  int faults = 0;
  int i, j, hit, victim;

  for(i = 0; i < MAX_FRAMES; i++){
    frames[i] = -1;
    last_used[i] = -1;
  }

  for(i = 0; i < NREF; i++){
    hit = 0;

    for(j = 0; j < n; j++){
      if(frames[j] == refs[i]){
        hit = 1;
        last_used[j] = i;
        break;
      }
    }

    if(hit)
      continue;

    faults++;

    if(count < n){
      frames[count] = refs[i];
      last_used[count] = i;
      count++;
    } else {
      victim = 0;

      for(j = 1; j < n; j++){
        if(last_used[j] < last_used[victim])
          victim = j;
      }

      frames[victim] = refs[i];
      last_used[victim] = i;
    }
  }

  return faults;
}

int
main(void)
{
  int n, ff, lf;
  int fifo_hits, lru_hits;

  printf(1, "Page Replacement Simulation\n");
  printf(1, "Total page accesses: %d\n\n", NREF);
  printf(1, "Frames  FIFO Faults  FIFO Hit%%  LRU Faults  LRU Hit%%\n");

  for(n = 3; n <= 5; n++){
    ff = fifo(n);
    lf = lru(n);

    fifo_hits = (NREF - ff) * 100 / NREF;
    lru_hits = (NREF - lf) * 100 / NREF;

    printf(1, "  %d        %d          %d%%         %d          %d%%\n",
           n, ff, fifo_hits, lf, lru_hits);
  }

  exit();
}
