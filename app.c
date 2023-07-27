#include <stdio.h>
#include <stdbool.h>

#include "library/adding_funds.h"
#include "library/spending_funds.h"
#include "library/reservation.h"
#include "library/check_error.h"
#include "library/app.h"
#include "library/loading.h"
#include "library/logging.h"

int available;
int reserved;

int main(int argc, char **argv)
{
  bool exit_flag = false;
  
  while (!exit_flag)
  {
    load_data();
    printf("your available funds: %d\nyour reserved funds: %d\nwhat would you like to do?\n  [1] add funds\n  [2] spend funds\n  [3] reservations\n  [4] show log\n  [5] exit\nyour choice: ", available, reserved);
    
    
    char choice;
    scanf("%c",&choice);
    
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

void flush_input_buffer(void)
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
  
  return;
}