#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char a_user_name[256];

int verify_user_name() {
    puts("verifying username....\n");
    return (strncmp(a_user_name, "dat_wil", 7));
}

int verify_user_pass(char *password) {
    puts("verifying username....\n");
    return (strncmp(password, "admin", 5));
}

int main() {
    char password[80];
    int ret = 0;

    puts("********* ADMIN LOGIN PROMPT *********");
    printf("Enter Username: ");
    fgets(a_user_name, 256, stdin);
    if (verify_user_name() != 0) {
        puts("nope, incorrect username...\n");
        return (1);
    }
    puts("Enter Password: ");
    fgets(password, 100, stdin);
    ret = verify_user_pass(password);
    if (ret == 0 || ret != 0) {
        puts("nope, incorrect password...\n");
        return (1);
    }
    return (0);
}