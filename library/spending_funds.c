#include <stdio.h>
#include <string.h>

#include "app.h"
#include "spending_funds.h"
#include "error_codes.h"
#include "logging.h"
#include "loading.h"

extern int spend_funds()
{
  int spent;
  printf("how much are you spending: ");
  scanf("%d",&spent); getchar();
  
  FILE *available_file = fopen("account_data/available", "w");
  if(available_file == NULL)
  {
    fprintf(stderr, "unable to open available file.\n");
    return CANT_OPEN_FILE;
  }
  
  fprintf(available_file, "%d", available-spent);
  fclose(available_file);
  
  char message[1024];
  sprintf(message, "spent,%d,available,%d", spent, available-spent);
  write_log(message);
  
  load_data();
  
  return OK;
}