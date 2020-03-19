#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

char translate_letter(const char* from, const char* to, char curr_letter);
void stdinperror();
void stdouterror();
void check_for_rep(const char * ptr);

int main(int argc, const char * argv[]) {
  const char* from;
  const char* to;
  char value; 
  ssize_t value_rw;
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
  /*
  while (value != EOF) {
    value = getchar(); 
    stdinperror();            
    if (feof(stdin))
      break;
    int translate = translate_letter(from,to,value);
    putchar(translate);
    stdouterror();

  }
  */
  while(1){
    value_rw = read(STDIN_FILENO, &value, 1);
    if (value_rw < 0) {
      fprintf(stderr, "Error reading input.");
      exit (1);
  }  
  if (! value_rw)
      break;
    value = translate_letter(from, to, value);
    value_rw = write(STDOUT_FILENO, &value, 1);
  if (value_rw < 0) {
      fprintf(stderr, "Error reading output.");
      exit (1);
    }

  }

  //printf("\n");
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
