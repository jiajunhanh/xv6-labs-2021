#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[]) {
  int p[2];
  pipe(p);

  int pid = fork();
  if (pid == 0) {
    char byte;
    pid = getpid();
    read(p[0], &byte, 1);
    printf("%d: received ping\n", pid);
    write(p[1], &byte, 1);
  } else {
    char byte = 0;
    pid = getpid();
    write(p[1], &byte, 1);
    read(p[0], &byte, 1);
    printf("%d: received pong\n", pid);
  }

  close(p[0]);
  close(p[1]);
  exit(0);
}
