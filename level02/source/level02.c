#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

int main(int ac, char **av)
{
    char username[100]; /* rbp-0x70 */
    bzero(&username, 12);
    char password[48]; /* rbp-0xa0 */
    bzero(&password, 5);
    char entry_password[112]; /* rbp-0x110 */
    bzero(&entry_password, 12);

    FILE *file; /* rbp-0x8 */
    int password_size; /* rbp-0xc */

    file = fopen("/home/users/level03/.pass", "r");
    if (file == 0) {
        fwrite("ERROR: failed to open password file\n", 1, 36, stderr);
        exit(1);
    }
    password_size = fread(&password, 1, 41, file);
    password[strcspn(password, "\n")] = 0;
    if (password_size != 41) {
        fwrite("ERROR: failed to read password file\n", 1, 36, stderr);
        fwrite("ERROR: failed to read password file\n", 1, 36, stderr);
        exit(1);
       
    }
    fclose(file);
    puts("===== [ Secure Access System v1.0 ] =====");
    puts("/***************************************\\");
    puts("| You must login to access this system. |");
    puts("\\**************************************/");
    printf("--[ Username: ");
    fgets(&username, 100, stdin);
    username[strcspn(&username, "\n")] = 0;
    printf("--[ password: ");
    fgets(&entry_password, 100, stdin);
    entry_password[strcspn(entry_password, "\n")] = 0;
    puts("*****************************************");
    if (strncmp(password, entry_password, 41) == 0) {
        printf("Greetings, %s!\n", username);
        system("/bin/sh");
        return 0;
    }
    printf(username);
    puts(" does not have access!");
    exit(1);
    return 0;
}