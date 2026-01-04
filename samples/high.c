// // // High-risk simulated code sample (for LLM4Decompile testing)
// // // ⚠️ DO NOT EXECUTE ON A LIVE SYSTEM — educational use only

// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>

// /*
//  * Combined single function `func0`:
//  * - allocates memory
//  * - writes a NOP sled (simulated shellcode) into that memory
//  * - prints simulated payload size via an internal buffer
//  * - calls a simulated payload routine inline
//  * - frees memory and exits
//  */
// int func0(void) {
//     printf("Starting suspicious memory operations...\n");

//     /* Simulated "shellcode" bytes */
//     unsigned char shellcode[] = {
//         0x90, 0x90, 0x90, 0x90,       /* NOP sled */
//         0x48, 0x31, 0xC0,             /* xor rax, rax */
//         0x48, 0x31, 0xFF,             /* xor rdi, rdi */
//         0x48, 0x31, 0xF6,             /* xor rsi, rsi */
//         0x48, 0x31, 0xD2,             /* xor rdx, rdx */
//         0xC3                          /* ret */
//     };

//     /* Print simulated payload info */
//     printf("Simulated payload size: %zu bytes\n", sizeof(shellcode));

//     /* Allocate memory and write dummy shellcode into it */
//     void *mem = malloc(256);
//     if (!mem) {
//         fprintf(stderr, "malloc failed\n");
//         return 1;
//     }
//     memset(mem, 0x90, 256); /* fill with NOP (0x90) */

//     /*
//      * Simulate execution trigger:
//      * Instead of calling a separate function pointer into injected memory,
//      * call an inline simulated payload action for analysis purposes.
//      */
//     /* Simulated payload action */
//     {
//         /* minimal benign simulation of shellcode behavior */
//         unsigned long checksum = 0;
//         for (size_t i = 0; i < sizeof(shellcode); ++i) {
//             checksum += shellcode[i];
//         }
//         printf("Simulated payload checksum: %lu\n", checksum);
//     }

//     free(mem);
//     printf("Exiting suspicious routine.\n");
//     return 0;
// }

// int main(void) {
//     return func0();
// }
