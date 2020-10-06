#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUF_SIZE 1024

bool is_vowel(char c) {
  /*
   * Returns true if c is a vowel (upper or lower case), and
   * false otherwise.
   */
  if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U' ){
    return true;
  }
    return false;
}

int copy_non_vowels(int num_char, char* in_buff, char* out_buff){
  /*
   * Copy all the non-vowels from in_buf to out_buf.
   * num_chars indicates how many characters are in in_buf,
   * and this function should return the number of non-vowels that
   * that were copied over.
   */
  int index =0;
  for(int i = 0; i< num_char-1; i++){
    if( is_vowel(in_buff[i]) == false ){
      out_buff[index] = in_buff[i];
      index++;
    }
  }
  return index;
}

void disemvowel(FILE* inputFile, FILE* outputFile) {
  /*
   * Copy all the non-vowels from inputFile to outputFile.
   * Create input and output buffers, and use fread() to repeatedly read
   * in a buffer of data, copy the non-vowels to the output buffer, and
   * use fwrite to write that out.
   */
  char* inBuff = (char*)calloc(BUF_SIZE, sizeof(char));
  char* outBuff = (char*)calloc(BUF_SIZE, sizeof(char));
  int nChars = 0;
  nChars = (int)fread(inBuff, sizeof(char), BUF_SIZE, inputFile); 
  if(nChars != 0){
    int Consts = copy_non_vowels(nChars, inBuff, outBuff);
    fwrite(outBuff, sizeof(char), Consts, outputFile);
  }
  free(inBuff);
  free(outBuff);
  fclose(inputFile);
  fclose(outputFile);
}

int main(int argc, char *argv[]) {
  // You should set these to `stdin` and `stdout` by default
  // and then set them to user specified files when the user
  // provides files names as command line arguments.
  FILE *inputFile = stdin;
  FILE *outputFile = stdout;

  if (argc >= 2) {
    inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
      perror("fopen()");
      exit(1);
    }
  }

  if (argc == 3) {
    outputFile = fopen(argv[2], "w");
    if (outputFile == NULL) {
      perror("fopen()");
      exit(1);
    }
  }

  // Code that processes the command line arguments
  // and sets up inputFile and outputFile.

  disemvowel(inputFile, outputFile);
  return 0;
}
