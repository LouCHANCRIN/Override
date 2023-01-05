#include <stdio.h>

int main(void) {
    int i = 0;
    char buf[100];
    fgets(&buf, 100, stdin);
    while (i < strlen(buf)) {
        if (buf[i] > 64) {
            if (buf[i] < 90) {
                buf[i] = buf[i] ^ 32
            }
        }
        i++;
    }
    printf(buf);
    exit(0);
}