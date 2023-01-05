#include <stdlib.h>
#include <stdio.h>

int main() {
    int password;

    puts("***********************************");
    puts("* \t     -Level00 -\t\t  *");
    puts("***********************************");
    printf("Password:");
    scanf("%d", &password);
    if (password == 5276)
    {
        puts("\nAuthenticated!");
        system("/bin/sh");
    }
    else {
        puts("\nInvalid Password!");
    }
    return (0);
}