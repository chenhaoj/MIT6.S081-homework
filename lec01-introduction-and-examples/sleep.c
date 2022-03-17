#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    // if(argc != 2) {
    //     fprintf(2, "error! you are supposed to type an argument");
    //     exit(1);
    // }
    if(!argv) {
        printf("error");
        exit(1);
    }
    sleep(atoi(argv[1]));
    exit(0);
}