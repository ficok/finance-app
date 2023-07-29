#include <stdio.h>
#include <stdbool.h>

#include "utilities.h"
#include "reservation.h"
#include "error_codes.h"
#include "app.h"
#include "logging.h"

int reserve()
{
  flush_input_buffer();

  printf("what would you like to do:\n  [1] create a new reservation\n  [2] update a reservation\n  [3] check a reservation\n  [4] show reservation logs\n  [5] go back\nyour choice: ");

  char choice;
  scanf("%c",&choice);
  printf("%s", DIVIDER);
  switch(choice)
  {
    case '1':
      new_reservation();
      printf("%s",DIVIDER);
      break;
    case '2':
      update_reservation();
      printf("%s",DIVIDER);
      break;
    case '3':
      check_reservation();
      printf("%s",DIVIDER);
      break;
    case '4':
      print_reservation_log();
      printf("%s",DIVIDER);
      break;
    case '5':
      printf("going back.\n");
      printf("%s", DIVIDER);
      break;
    default:
      printf("invalid option.\n");
      printf("%s",DIVIDER);
      break;
  }
  
  flush_input_buffer();
  
  return OK;
}