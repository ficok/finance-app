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
  load_data();
  while (!exit_flag)
  {
    printf("available money: %d\nreserved money: %d\nnumber of reservations: %d\n\nwhat would you like to do?\n  [1] add money\n  [2] spend money\n  [3] reservations\n  [4] show transaction log\n  [5] exit\nyour choice: ", available, reserved, num_of_reservations);
    
    char choice;
    scanf("%c",&choice); getchar();
    switch(choice)
    {
      case '1':
        printf("- add money\n%s", DIVIDER);
        add_funds();
        printf("%s", DIVIDER);
        break;
      case '2':
        printf("- spend money\n%s", DIVIDER);
        spend_funds();
        printf("%s", DIVIDER);
        break;
      case '3':
        printf("- reservations\n%s", DIVIDER);
        reserve();
        printf("%s", DIVIDER);
        break;
      case '4':
        printf("- show transaction log\n%s", DIVIDER);
        print_log();
        printf("%s", DIVIDER);
        break;
      case '5':
        printf("- exit\n");
        exit_flag = true;
        break;
      default:
        printf("invalid option\n");
        printf("%s", DIVIDER);
        break;
    }
  }
}