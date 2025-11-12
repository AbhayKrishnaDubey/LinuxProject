#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>
#include <string.h>

#ifndef MY_SYSCALL_NR
#define MY_SYSCALL_NR 333
#endif

int main() {
    char buf[128];
    long ret = syscall(MY_SYSCALL_NR, buf, sizeof(buf));
    if (ret < 0) {
        printf("syscall returned error: %ld (errno=%d)\n", ret, errno);
        return 1;
    }
    printf("Returned %ld bytes: %s", ret, buf);
    return 0;
}
