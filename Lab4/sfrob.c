
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int frobcmp(char const * a, char const * b);
char decode_char(const char code);
int frobWrapper(const void* a, const void* b);
void check_ptr(void* ptr);
void stdinperror();
void stdouterror();
int main() {
  //printf("%d",sizeof(int));
    char** lines =NULL;// malloc(1*sizeof(char*));
    char* word = NULL;//malloc(1*sizeof(char));
      //    check_ptr(lines);
      //check_ptr(word);
    int index_Word = 0;
    int index_Lines = 0;
    //    char prev = 'b'; //declare value that is not space
    //  int (* frobPointer)(const void *, const void*);
    //frobPointer = &frobWrapper;
    int c = getchar();
//stores values from standard input dynamically
 while ( c != EOF) {
   //   printf("Entered  loop");
   stdinperror();
   //   if (c == ' ' && prev == ' ')
   //  continue;
   if (c != ' ')
   cd{
     word = (char*)realloc(word, sizeof(char)*(index_Word + 1));
       check_ptr(word);
       word[index_Word] = c;
       index_Word++;
       // prev = c;
   }
   else if (c == ' ')
   {
     word = (char*)realloc(word, sizeof(char)*(index_Word + 1));
       word[index_Word]=c;
       lines = (char**)realloc(lines, sizeof(char*)*(index_Lines+ 1));
       check_ptr(lines);
       lines[index_Lines] = word;
       index_Lines++;
       word = NULL;
       //word = (char*)malloc(1*sizeof(char));
       //check_ptr(word);
       index_Word = 0;
       //prev = c;
   }
   c = getchar();
}
 if (index_Word > 0) {
  word = (char*)realloc(word, sizeof(char)*(index_Word + 1));
  word[index_Word] = ' ';
  lines = (char**)realloc(lines, sizeof(char*)*(index_Lines+ 1));
  check_ptr(lines);
  lines[index_Lines] = word;
  index_Lines++;
 }
 //sorts and prints input from standard output
 //printf( "%d",index_Lines);
 //printf("\n");
qsort(lines,index_Lines, sizeof(char*),frobWrapper);
//printf("%d",index_Lines);
    int i =0;
    int j = 0;
    for (; i < index_Lines; i++) {
      for (;;j++) {
	putchar(lines[i][j]);
        stdouterror();
     if(lines[i][j] == ' ')
       break;
      }
      free(lines[i]);
    }
    //Free all of my dynamically allocated memory    
    free(lines);
}
//decodes a char and decides which word to sort first, used in qsort
int frobcmp(char const * a, char const * b) {
    while (*a != ' ' && *b != ' ') {
      char check1 = *a^42; 
      char check2 = *b^42; 

        if(check1 > check2)
            return 1;
        else if (check1 < check2)
            return -1;
        a++;
        b++;
            }
    if (*a == ' ' && *b != ' ')
        return 1;
    else if (*a == ' ' && *b == ' ')
        return 0;
    else
        return -1;

    }
//checks to make sure input is working properly
void stdinperror() {
  if (ferror(stdin)) {
       fprintf(stderr, "Error, cannot read input");
  exit(1);
  }
}
//checks to make sure memory was allocated properly
void check_ptr(void * ptr) {
  if (ptr ==NULL) {
    fprintf(stderr,"Error, malloc or realloc did not allocate memory properly");
  exit(1);
  }
}
//allows us to use the qsort command
int frobWrapper(const void* a, const void* b) {
  const char* check1 = *(const char**)a;  
  const char* check2 = *(const char**)b;     
      return frobcmp(check1, check2);
}
/* gnu.org shows file is encrypted with an XOR of 0x2A need to XOR value again to revert it back to original\
 text */
inline
char decode_char(const char code) {
  return code ^ 42;
}
//checks to make sure output is working properly
void stdouterror() {
  if (ferror(stdout)) {
    fprintf(stderr, "Error, problem with output");
  exit(1);
  }
}
