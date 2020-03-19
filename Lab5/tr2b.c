#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

char translate_letter(const char* from, const char* to, char curr_letter);
void stdinperror();
void stdouterror();
void check_for_rep(const char * ptr);

int main(int argc, const char * argv[]) {
  const char* from;
  const char* to;
  int value; 
  from = argv[1];
  to = argv[2];
  check_for_rep(from);
  if (strlen(from) != strlen(to)) {
      fprintf(stderr, "Error, arguments are not of the same length");
  }

  if (argc != 3) {
    fprintf(stderr, "Error, wrong number of arguments were inputted");
    exit(1);
  }

  while (value != EOF) {
    value = getchar(); 
    stdinperror();            
    if (feof(stdin))
      break;
    int translate = translate_letter(from,to,value);
    putchar(translate);
    stdouterror();
  }
  //  printf("\n");
  return 0;

}


char translate_letter(const char* from, const char* to, char curr_letter) {
  int k = 0;
  for (; k < strlen(from); k++)
    if (from[k] == curr_letter) {
      char translate = to[k];
      return translate;
    }     
  return curr_letter;
}

void stdouterror() {
  if (ferror(stdout)) {
    fprintf(stderr, "Error, problem with output");
    exit(1);
  }
}

void stdinperror() {
  if (ferror(stdin)) {
    fprintf(stderr, "Error, cannot read input");
    exit(1);
  }
}

void check_for_rep(const char * ptr) {
  int i;
  int j;
  for (i=0; i < strlen(ptr); i++) {
    for (j=i+1; j < strlen(ptr); j++) {
      if (ptr[i] == ptr[j]) {
	fprintf(stderr, "Error, duplicate characters.");
	exit(1);
      }
    }
  }
}
