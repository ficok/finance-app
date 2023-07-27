#include <stdio.h>
#include <stdbool.h>

#include "reservation.h"
#include "error_codes.h"
#include "app.h"
#include "logging.h"

int reserve()
{
  bool exit_flag = false;
  
  while (!exit_flag)
  {
    printf("what would you like to do:\n  [1] create a new reservation\n  [2] update a reservation\n  [3] show reservation logs\n  [4] go back\nyour choice: ");
  
    char choice;
    scanf("%d",&choice);
    
    switch(choice)
    {
      case '1':
        new_reservation();
        printf(DIVIDER);
        break;
      case '2':
        update_reservation();
        printf(DIVIDER);
        break;
      case '3':
        check_reservation();
        printf(DIVIDER);
        break;
      case '4':
        print_reservation_logs();
        printf(DIVIDER);
        break;
      case '5':
        exit_flag = true;
        break;
      default:
        printf("invalid option.\n");
        printf(DIVIDER);
        break;
    }
    
    flush_input_buffer();
  }
  
  return OK;
}