#include <stdio.h>
#include <stdbool.h>

#include "library/utilities.h"
#include "library/adding_funds.h"
#include "library/spending_funds.h"
#include "library/reservation.h"
#include "library/check_error.h"
#include "library/app.h"
#include "library/loading.h"
#include "library/logging.h"

int available;
int reserved;
int num_of_reservations;

int main()
{
  bool exit_flag = false;
  
  while (!exit_flag)
  {
    /**
     * to lessen the footprint of this function, rework everything such that
     * it is called only:
     * 1. when program starts
     * 2. after any changes are made
     *    - new reservation
     *    - update reservation
     *    - delete reservation
    */  load_data();
    printf("your available funds: %d\nyour reserved funds: %d\nwhat would you like to do?\n  [1] add funds\n  [2] spend funds\n  [3] reservations\n  [4] show log\n  [5] exit\nyour choice: ", available, reserved);
    
    
    char choice;
    scanf("%c",&choice);
    printf("%s", DIVIDER);
    switch(choice)
    {
      case '1':
        add_funds();
        printf("%s", DIVIDER);
        break;
      case '2':
        spend_funds();
        printf("%s", DIVIDER);
        break;
      case '3':
        reserve();
        printf("%s", DIVIDER);
        break;
      case '4':
        print_log();
        printf("%s", DIVIDER);
        break;
      case '5':
        exit_flag = true;
        break;
      default:
        printf("invalid option\n");
        printf("%s", DIVIDER);
        break;
    }
    flush_input_buffer();
  }
}