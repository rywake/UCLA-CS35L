#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int frobcmp(char const * a, char const * b);
int decode_char(const char * code);

int main() {
printf(0x2A);
 char arr** = malloc(10);
 while ( (char c = getchar()) != EOF) {
   putchar(c);
 }
}
/* gnu.org shows file is encrypted with an XOR of 0x2A need to XOR value again to revert it back to original text */
char decode_char(const char* code) {
  return (code ^ 0x2A);
}


