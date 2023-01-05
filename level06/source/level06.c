#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ptrace.h>

int auth (char *login, unsigned int serial) {
    login[strcspn(login, "\n")] = 0;
    size_t len = strnlen(login, 32)
    if (len > 5) {
        if (ptrace(0, 0, 1, 0) == -1) {
            puts("\033[32m.---------------------------.");
            puts("\033[31m| !! TAMPERING DETECTED !!  |");
            puts("\033[32m'---------------------------'");
        } else {
            int key = (login[3] ^ 0x1337) + 0x5eeded;
            for (int k = 0; k < len && login[k] > 31; k++) {
                int a = login[k] ^ key;
                int b = 0x88233b2b * a / 0x100000000;
                int c = a - ((((a - b) >> 1) + b) >> 10) * 0x539 + key;
                key = c;
            }
            if (key == serial)
                return 0;
        }
    }
    return 1;
}

int main () {
    char login[32];
    puts("***********************************");
    puts("*\t\tlevel6\t\t  *");
    puts("***********************************");
    printf("-> Enter Login: ");
    fgets(login, 32, stdin);
    puts("***********************************");
    puts("***** NEW ACCOUNT DETECTED ********");
    puts("***********************************");
    printf("-> Enter Serial: ");
    unsigned int serial;
    scanf("%u", &serial);
    int retcode;
    if ((retcode = auth(login, serial)) == 0) {
        puts("Authenticated!");
        system("/bin/sh");
    }
    return retcode;
}