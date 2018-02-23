#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
#include "lib.h" // Constants definitions for test
#include "helpers.h" // Print functions

/**
 * @author: Dante Bazaldua
 * @date: 22-feb-2018
 * @brief: Check whether secure is the password and bring recommendations.
 */

extern void usage( char * program );
extern void showRecomendations( int *flags );

/**
 * [int compileRegex Regex compiler]
 * @param  r          [Type of regex <struct>]
 * @param  regex_text [Regex String]
 * @return            [Status of compiler]
 */
static int
compileRegex( regex_t *r, const char *regex_text )
{
  int status = regcomp(r, regex_text, REG_EXTENDED|REG_NEWLINE);
  if ( status != 0 )
  {
    char error_message[MAX_ERROR_MSG];
    regerror(status, r, error_message, MAX_ERROR_MSG);
    printf("Error en compilacion '%s':%s\n",
          regex_text, error_message);
    return 1;
  }
  return 0;
}

/**
 * [int matchRegex Execute de regex match]
 * @param  r     [struct of the compiled regex]
 * @param  match [Text to compare]
 * @return       [If there was or not matches]
 */
static int
matchRegex( regex_t *r, const char *match )
{
  const char *p = match;
  const int nmatches = 10;
  regmatch_t m[nmatches];
  while (1)
  {
    int nomatch = regexec( r, p, nmatches, m, 0);
    if (nomatch)
    {
      return nomatch;
    }
    else{
      return 0;
    }
  }
}

/**
 * [int testEachREGEX test each regex string]
 * @param passwd [String to compare]
 * @param regex  [Regex to compile and execute]
 * @return       [0 for match, else for no match]
 */
int
testEachREGEX( const char * passwd, const char * regex )
{
  regex_t r;
  int match;
  compileRegex(& r, regex);
  match = matchRegex(& r, passwd);
  // printf("--> %d\n", match);
  regfree(& r);
  return match;
}


/**
 * [int haveSpecial Check if the word has special characters]
 * @param passwd [description]
 * @return       [int occurrence of special characters.]
 */
int
haveSpecial( const char * passwd )
{
  int size = strlen(passwd);
  int i = 0;
  int count = 0;
  for (i = 0; i < size; i++) {
    if ( isalnum(passwd[i]) == 0 )
    {
      count++;
    }
  }
  return count;
}


// Original idea took from: https://stackoverflow.com/questions/3501338/c-read-file-line-by-line
/**
 * [int findInDictionary Finds in dictionary for string occurrence]
 * @param passwd [description]
 * @return 0 for coincidence
 * @return -1 for cannot open the FILE
 * @return -2 for no coincidence
 */
int
findInDictionary( const char * passwd )
{
  FILE *fp;
  char * line = NULL;
  size_t len = 0;
  ssize_t read;
  int count = 0;
  int coincidence = -1;

  fp = fopen(DICTIONARY, "r");
    if (fp == NULL)
      return -1;

  while ((read = getline(&line, &len, fp)) != -1)
  {
    line[read - 1] = '\0';
    if ( strcmp(passwd, line) == 0)
    {
      coincidence = 0;
    }
  }

  if (coincidence == 0){
    // printf("Encontré coincidencia: %s", passwd);
    return 0;
  }

  fclose(fp);
  if (line)
      free(line);
  return -2;
}

/**
 * [void showResults Print the results in screen]
 * @param flags  [Test coverage]
 * @param passwd [The password to check]
 */
void
showResults(int *flags, const char * passwd)
{
  int i = 0;
  int count = 0;
  char *status;
  const char *meanregex[TEST_MAX] = {
    "UPPERCASE",
    "lowercase",
    "digits",
    "special c",
    "min c > 8",
    "No App in dict"
  };
  printf("Password coverage: %s\n\n", passwd);
  printf("%15s | %s\n", "Test", "Status" );
  for (i = 0; i < TEST_MAX; i++) {
    // printf("%s: ", "Test ", meanregex[i], ":" );
    if ( flags[i] == 0 )
    {
      status = "OK";
      count++;
    }
    else
    {
      status = "FAILED";
      if (i == TEST_MAX-1) {
        status = "APPEARS";
      }
    }
    printf("%15s | [%s]\n", meanregex[i], status );
  }
}

/**
 * [void showPercentage Simple progressbar for the security percentage]
 * @param flags  [Test coverage]
 * @param passwd [The password to check]
 */
void
showPercentage( int *flags, const char * passwd )
{
  int i = 0;
  int count = 0;
  const char *per = "************************";
  for (i = 0; i < TEST_MAX; i++) {
    if ( flags[i] == 0 ){
      count++;
    }
    else{
      if ( i == TEST_MAX-1)
        count--;
    }
  }
  printf("\n* La aparición en el diccionario reduce puntos.\n");
  printf("El porcentaje de seguridad es: \n");
  printf("[%.*s]", count * 4, per);
  printf(" %d/%d (%2.2f%c Segura)\n", count, TEST_MAX, (count/1.0)/(TEST_MAX/1.0)*100, 37 );
}


int
main(int argc, char **argv)
{
  char * passwd;
  int i = 0;
  int flags[TEST_MAX] = {1,1,1,1,1,0};
  const char *regex[TEST_REGEX] = {
    "([A-Z])",
    "([a-z])",
    "([0-9])"
  };

  if ( argc != 2 ) {
    printf("Bad arguments\n");
    usage( argv[0] );
    return 0;
  }

  passwd = argv[1];
  for (i = 0; i < TEST_REGEX; i++) {
    flags[i] = testEachREGEX( passwd, regex[i] );
  }

  if ( haveSpecial( passwd ) != 0 )
    flags[3] = 0;

  if ( strlen( passwd) >= 8 )
    flags[4] = 0;

  if ( findInDictionary( passwd ) == 0 )
    flags[5] = 1;

  showResults( flags, passwd );
  showPercentage( flags, passwd );
  showRecomendations(flags);

}
