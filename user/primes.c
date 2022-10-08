#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {
  int rd;
  int p[2];
  int num;
  int prime;
  pipe(p);

  if (!fork()) {
    while (1) {
      rd = p[0];
      close(p[1]);
      if (read(rd, &prime, 4) == 4) {
        printf("prime %d\n", prime);
      } else {
        close(rd);
        break;
      }
      pipe(p);
      if (!fork()) continue;
      while (read(rd, &num, 4) == 4) {
        if (num % prime) write(p[1], &num, 4);
      }
      break;
    }
    close(rd);
    close(p[0]);
    exit(0);
  }

  for (int i = 2; i <= 35; ++i) {
    write(p[1], &i, 4);
  }
  close(p[0]);
  close(p[1]);
  while (wait(0) != -1);
  sleep(1);

  exit(0);
}
