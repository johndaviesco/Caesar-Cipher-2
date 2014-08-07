#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* Compile:  gcc -o decode decode.c

   Program is used like this (using output from encode):

   Test file (ctext): JWRLS, XSSH PZK JH HES BJFV, UZU

   % cat ctext | decode JuliusCaesar
   map: GPFQHRSTDAUCVWXYZIEJBKLMNO - 26
   ALICE, MEET YOU AT THE PARK, BOB

 */

char upcase(char ch){
  if(islower(ch))
    ch -= 'a' - 'A';
  return ch;
}

char* fixkey(char* s){
  int i;

  for(i = 0; i < strlen(s); i++){
    if(isalpha(s[i]))
      s[i] = upcase(s[i]);
    else{
      fprintf(stderr,"Non alpha characters in the key.  Encoding aborted.\n");
      exit(-1);
    }      
  }
  return s;
}

void buildtable (char* key, char* decode){ 
  // Assumption!!!: key is already in UPPERCASE.  That's OK, because we already did that.
  // This function needs to build an array of mappings in 'decode' from encypered characters
  // to plaintext characters.

  // You are implementing a Caesar 2 Cypher as given in Class.
  // Your code here:

  //Copy key into encode and check for double ups
  int i;
  int j = 0;
  int offset;
  int start;
  char* encode = malloc(26*sizeof(char));
  for (i=0;i<strlen(key);i++){
    if(strchr(encode, key[i]) == NULL){
      encode[j] = key[i];
      j++;
    }
  }
  
  //Gets start position and loops trought the alphabet
  start = encode[strlen(encode)-1] - 'A';
  offset = start + 1;
  for(; offset != start;offset++){
    if(offset == 26){
      offset = 0;
    }
    if(strchr(encode,offset + 'A') == NULL){
      encode[j] = offset + 'A';
      j++; 
    }
  }
  for(i=0;i< strlen(encode);i++){
    decode[encode[i] - 'A'] = i + 'A';
  }
  //free the memmory
  free(encode);
}

int main(int argc, char **argv){
  // We'll be using stdin and stdout for files to encode and decode.

  // first allocate some space for our translation table.

  char* decode = (char*)malloc(sizeof(char)*26); // this changed from encode
  char ch;

  if(argc != 2){
    fprintf(stderr,"format is: '%s' key", argv[0]);
    exit(1);
  }

  // Build translation tables, and ensure key is upcased and alpha chars only.

  buildtable(fixkey(argv[1]), decode); // this changed from encode

  // write the map to stderr (so it doesn't break our pipes)

  fprintf(stderr,"map: %s - %d\n", decode, (int)strlen(decode));
  

  // the following code does the translations.  Characters are read 
  // one-by-one from stdin, translated and written to stdout.

    ch = fgetc(stdin);
    while (!feof(stdin)) {
      if(isalpha(ch))          // only decrypt alpha chars
	fputc(decode[ch-'A'], stdout);
     else 
	fputc(ch, stdout);
      ch = fgetc(stdin);      // get next char from stdin
    }
}

