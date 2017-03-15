#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* Compile:  gcc -o encode encode.c

   Program is used like this:

   Test file (ptext): alice, meet you at the park, bob

   % cat ptext | encode JuliusCaesar
   map: JULISCAERTVWXYZBDFGHKMNOPQ - 26
   JWRLS, XSSH PZK JH HES BJFV, UZU

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

void buildtable (char* key, char* encode){
  
  // Assumption!!!: key is already in UPPERCASE.  That's OK, because we already did that.
  // This function needs to build an array of mappings in 'encode' from plaintext characters
  // to encypered characters.

  // You are implementing a Caesar 2 Cypher as given in Class.
  // Your code here:
  
  //Copy key into encode and check for double ups
  int i;
  int j = 0;
  int offset;
  int start;
  for (i=0;i<strlen(key);i++){
    if(strchr(encode, key[i]) == NULL){
      encode[j] = key[i];
      j++;
    }
  }
  
  //Gets start position and loops trought the alpha
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
  

}

int main(int argc, char **argv){
  // We'll be using stdin and stdout for files to encode and decode.

  // first allocate some space for our translation table.

  char* encode = (char*)calloc(27, sizeof(char));
  char ch;

  if(argc != 2){
    printf("format is: '%s' key", argv[0]);
    exit(1);
  }

  // Build translation tables, and ensure key is upcased and alpha chars only.

  buildtable(fixkey(argv[1]), encode);

  // write the map to stderr (so it doesn't break our pipes)

  fprintf(stderr,"key: %s - %d\n", encode, (int) strlen(encode));

  // the following code does the translations.  Characters are read 
  // one-by-one from stdin, translated and written to stdout.

  ch = fgetc(stdin);
  while (!feof(stdin)) {
    if(isalpha(ch)){        // only encrypt alpha chars
      ch = upcase(ch);      // make it uppercase
      fputc(encode[ch-'A'], stdout);
    }else 
      fputc(ch, stdout);
    ch = fgetc(stdin);      // get next char from stdin
  }
}
  
