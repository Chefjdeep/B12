// insecure_demo.c
// WARNING: This code is intentionally insecure for learning purposes

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void unsafe_buffer() {
    char buffer[8];
    printf("Enter your name: ");
    gets(buffer);  // ❌ dangerous: buffer overflow
    printf("Hello %s\n", buffer);
}

void command_execution() {
    char cmd[64];
    printf("Enter a command (demo only): ");
    scanf("%63s", cmd);

    // ❌ dangerous: command injection risk
    system(cmd);
}

int main() {
    int choice;

    printf("1. Unsafe buffer demo\n");
    printf("2. Command execution demo\n");
    printf("Choose: ");
    scanf("%d", &choice);

    if (choice == 1) {
        unsafe_buffer();
    } else if (choice == 2) {
        command_execution();
    } else {
        printf("Invalid choice\n");
    }

    return 0;
}
