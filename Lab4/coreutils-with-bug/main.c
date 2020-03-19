

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int frobcmp(char const * a, char const * b);
char decode_char(const char code);

int main() {
    char c;
    char** lines = malloc(1*sizeof(char*));
    char* word = malloc(1*sizeof(char)); //decide if i want to keep this
    int index_Word = 0;
    int index_Lines = 0;
    
 while ( (c = getchar()) != EOF) {
   if (c != ' ')
   {
       word = realloc(word, sizeof(char)*(index_Word + 2));
       //printf(c);
       word[index_Word] = c;
       index_Word++;
   }
   else if (c == ' ')
   {
       word[index_Lines]=c;
       lines = realloc(lines, sizeof(char*)*(index_Lines+ 2));
       lines[index_Lines] = word;
       index_Lines++;
       if (word != NULL)
       free(word);
       word = malloc(1*sizeof(char));
       index_Word = 0;
   }
    
 }
}

int frobcmp(char const * a, char const * b) {
    int indexOfChar = 0;
    while (*a != ' ' && *b != ' ') {
        if(decode_char(*a) > decode_char(*b))
            return 1;
        else if (decode_char(*a) < decode_char(*b))
            return -1;
        a++;
        b++;
            }
    if (*a == ' ' || *b == ' ')
        return 0;
    
    return 0;
    }
/* gnu.org shows file is encrypted with an XOR of 0x2A need to XOR value again to revert it back to original\
 text */
inline
char decode_char(const char code) {
  return code ^ 42;
}

