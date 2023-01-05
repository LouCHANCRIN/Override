#include <stdio.h> 

int main(int argc, char **argv) {
    
    int password;

    srand(time(0));
    puts("***********************************");
    puts("*\t\tlevel03\t\t**");
    puts("***********************************");
    printf("Password:");
    scanf("%d", &password);
    test(password, 322424845);
    return 0;
}

void decrypt(int password) {
    char buf[17] = "Q}|u`sfg~sf{}|a3";
    int len = strlen(buf);
    int i = 0;
    while (i < len) {
        buf[i] = buf[i] ^ password;
        i++;
    }
    if (strncmp(buf, "Congratulations!", 17) == 0)
        system("/bin/sh");
    else 
        puts("\nInvalid Password");
    return;
}

void test(int password, int nb) {
    nb = nb - password;
    if (nb <= 21)
        decrypt(nb);
    decrypt(rand());
    return;
}