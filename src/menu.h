

#include "HashTable.h"
#include "BacktrackAPRS.h"


enum MENU_OPTION
{
    EXIT					  = 0,
    DISPLAY_PASSENGERS		  = 1,
    DISPLAY_APRIORI			  = 2,
    DISPLAY_ASSOCIATION_RULES = 3,
    BACKTRACK_APRS			  = 4
};


string get_new_passenger_attr();

int prompt_main_menu();
