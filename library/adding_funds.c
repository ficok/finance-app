#include <stdio.h>
#include <string.h>

#include "app.h"
#include "adding_funds.h"
#include "error_codes.h"
#include "logging.h"
#include "loading.h"

extern int add_funds()
{
  int added;
  printf("how much are you adding: ");
  scanf("%d",&added); getchar();
  printf("currently available: %d\n", available+added);
  
  FILE *available_file = fopen("account_data/available", "w");
  if (available_file == NULL)
  {
    fprintf(stderr, "unable to open available file\n");
    return CANT_OPEN_FILE;
  }
  fprintf(available_file, "%d", available+added);
  fclose(available_file);
  
  char message[1024];
  sprintf(message, "added,%d,available,%d", added, available+added);
  write_log(message);

  load_data();

  return OK;
}