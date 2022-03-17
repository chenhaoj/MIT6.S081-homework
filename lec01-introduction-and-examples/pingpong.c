#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    int parent_fd[2], child_fd[2];
    pipe(parent_fd);
    pipe(child_fd);
    char buf;
    // 注意！fd[1]一端只能进行写操作，fd[0]一端只能进行读操作
    // 同时，pipe管道是半双工，一次只能使用一端，另一端需要close掉
    if(fork() == 0) {
        close(parent_fd[1]); // 关闭管道parent_fd[1]，因为子进程要读取管道parent_fd[0]
        close(child_fd[0]); // 关闭管道child_fd[0]，因为子进程要写管道child_fd[1]
        if(read(parent_fd[0], &buf, 1)) {
            printf("%d: received ping\n", getpid());
            write(child_fd[1], &buf, 1);
            close(child_fd[1]);
        }
    } else {
        close(parent_fd[0]); // 关闭管道parent_fd[0]，因为父进程要写管道parent_fd[1]
        close(child_fd[1]); // 关闭管道child_fd[1]，因为父进程要读取管道child_fd[0];
        write(parent_fd[1], &buf, 1);
        if(read(child_fd[0], &buf, 1)) {
            printf("%d: received pong\n", getpid());
            close(parent_fd[1]);
        }
    }
    exit(0);
}