#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>

int frobcmp(char const * a, char const * b);
char decode_char(const char code);
int frobWrapper(const void* a, const void* b);
void check_ptr(void* ptr);
void stdinperror();
void stdouterror();
typedef enum {true,false} bool;
bool toupper_istrue = false;


int main(int argc, char* argv[]){
  //checks if everything needs to be upper-cased.
  if (argc > 2) {
    fprintf(stderr, "Error, wrong number of inputs.");
    exit(1);
     }
  else if (argc == 2) {
    if (strcmp(argv[1], "-f") ==0)
    {
      toupper_istrue = true;
    }
    else {

      fprintf(stderr, "Error, incorrect optional argument.");
      exit(1);
    }
  }

  //initializations
  char * inp = NULL;
  char ** lines = NULL;
  int (*frobPointer)(const void*, const void*);
  frobPointer = &frobWrapper;
  struct stat buffer; //part of the unist library to check status of the buffer.
  int value_rw;
  int size_of_input;
  ssize_t check;
  int index_of_lines = 0;
  int is_not_end = 0;
  int index_word =0;
  char * word = NULL;
  char c;
  fstat(0, &buffer);
 

  //  printf("%d", buffer.st_size);
  if (S_ISREG(buffer.st_mode))
    {
      //  printf("Entered buffer");
      size_of_input = (size_t)buffer.st_size; 


         if (size_of_input < 0) {
              fprintf(stderr, "Error reading input");
              exit(1);
            }

       inp = realloc(inp,sizeof(char)*size_of_input);
       check_ptr(inp);
       check = read(0, inp, size_of_input);
       
       is_not_end = read(0,&c, 1);
       if (is_not_end)
	 {
	   while (is_not_end)
	     {
	       inp = realloc(inp, sizeof(char)*size_of_input+1);
	       inp[size_of_input] = c;
	       is_not_end = read(0,&c,1);
               size_of_input++;
	     }
	 }

       int a;                                                                                            
       char *ptr = inp;
       lines = realloc(lines,sizeof(char*)*index_of_lines+1);
       check_ptr(lines);
       lines[0] = inp;
       index_of_lines++;                                                                                  

       for(a =0; a < size_of_input; a++)
       {  
         if (*ptr == ' ' && a != size_of_input-1)
           {                                                                                           
               lines = realloc(lines,sizeof(char*)*index_of_lines+1);
               check_ptr(lines);
               lines[index_of_lines] = ptr+1;   
               index_of_lines++;
           } 
	 ptr++;
       }

      }

 is_not_end = read(0, &c, 1);
  
 if (is_not_end)
    {
      while (is_not_end ==1)
    {
         if (c != ' ')
       	{
	  word = realloc(word, sizeof(char)*index_word + 1);
	  check_ptr(word);
	  word[index_word] = c;
	  index_word++;
	  is_not_end = read(0,&c,1);
	}
      else if (c == ' ')
	{
	  word = (char*)realloc(word, sizeof(char)*index_word + 1);
	  check_ptr(word);
	  word[index_word]=c;
	  lines = (char**)realloc(lines, sizeof(char*)*index_of_lines+ 1);
	  check_ptr(lines);
	  lines[index_of_lines] = word;
	  index_of_lines++;
	  word = NULL;
	  index_word = 0;
	  is_not_end = read(0,&c,1);

	}
    }

  if (index_word > 0) 
  {
    word = (char*)realloc(word, sizeof(char)*index_word + 1);
    word[index_word] = ' ';
    lines = (char**)realloc(lines, sizeof(char*)*index_of_lines+ 1);
    check_ptr(lines);
    lines[index_of_lines] = word;
    word = NULL;
    index_of_lines++;
  }  

}
  else
    {

      if (inp[size_of_input-1] != ' ')
	{
	  inp = (char*)realloc(inp,sizeof(char)*size_of_input+1);
	  inp[size_of_input] = ' ';
	  size_of_input++;
	}
    }


 qsort(lines, index_of_lines, sizeof(char*), frobPointer);



   size_t i;
   size_t j;
   for(i = 0; i < index_of_lines; i++)
   {
    long size_of_word = 0;
    for( j = 0; ;j++)
   	{
   	  size_of_word++;
   	  if(lines[i][j] == ' ')
   	      break;
   	}
    if (write(1,lines[i], size_of_word) == 0)
   	{
   	  fprintf(stderr, "Error, problem printing to stdout.");
  	  exit(1);
   	}
   }

  int x =0;
 
  if (inp != NULL)
  free(inp);
 
  //  for (; x < index_of_lines; x++)
  //  free(lines[x]);
  free(lines);
}


int frobcmp(char const * a, char const * b) {
  while (*a != ' ' && *b != ' ') {
    if( decode_char(*a) > decode_char(*b))
      return 1;
    else if ( decode_char(*a) < decode_char(*b))
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
  return frobcmp(*((const char**)a), *((const char**)b));
}
/* gnu.org shows file is encrypted with an XOR of 0x2A need to XOR value again to revert it back to original\
   text */
inline
char decode_char(const char code) {
  char ret_value = code;
  if (toupper_istrue == true)
    {
      return toupper((unsigned char)(ret_value^42));
    }
  return ret_value^42;
}
//checks to make sure output is working properly                                                              
void stdouterror() {
  if (ferror(stdout)) {
    fprintf(stderr, "Error, problem with output");
    exit(1);
  }
}
