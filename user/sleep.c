#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    if(argc != 2){
        fprintf(2, "usage: sleep ticks\n");
        exit(1);
    }

    for (char* p = argv[1]; *p != 0; ++p) {
        if (*p < '0' || '9' < *p) {
            fprintf(2, "sleep: only support integer\n");
            exit(1);
        }
    }

    int n = atoi(argv[1]);
    sleep(n);

    exit(0);
}
