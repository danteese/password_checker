void printSpecRec(int value);
void showRecomendations( int *flags );
void usage( char * program );

/**
 * [void usage Helper for bad entries]
 * @param program [$0]
 */
void
usage( char * program )
{
  printf("This program check if the password is secure.\n");
  printf("Criteria: \n");
  printf("\t 1) Check UPPERCASE and lowercase letters. \n");
  printf("\t 2) Min 8 of length.\n");
  printf("\t 3) The password have special characters.\n");
  printf("\t 4) Is not in the dictionary.\n");
  printf("Usage %s [ARGS]\n", program);
  printf("\tARGS: Your <password> within spaces.\n");
}

/**
 * [void showRecomendations Check flags and give recomendation.]
 * @param flags [Coverage tests]
 */
void
showRecomendations( int *flags ){
  int i = 0;
  int rec = 0;
  printf("\nRecomendaciones\n");
  for (i = 0; i < TEST_MAX; i++) {
    if ( flags[i] == 1 ) {
      printSpecRec(i);
      rec++;
    }
  }
  if ( rec == 0 ) {
    printSpecRec(10);
  }
}

// Data took from https://howsecureismypassword.net
/**
 * [void printSpecRec Recomendation on screen]
 * @param flag [what flag use.]
 */
void
printSpecRec(int flag)
{
  switch ( flag ) {
    case 0:
    case 1:
      printf("* Utilizar solo mayusculas y minusculas con menos de 8 caracteres podría tardar 2 min.\n");
    break;
    case 2:
      printf("* Usar dígitos podría aumentarlo hasta dos semanas.\n");
    break;
    case 3:
      printf("* Usar caracteres especiales aumenta hasta 1 mes.\n");
    break;
    case 4:
      printf("* Una contraseña con menos de 8 caracteres se puede descifrar en 10 min.\n");
    break;
    case 5:
      printf("* Si aparece en un diccionario dala por hackeada.\n");
    break;
    default:
      printf("No hay recomendación. Buena contraseña.\n");
  }
}
