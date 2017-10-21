#include "menu.h"
#include "HashTable.h"
#include "BacktrackAPRS.h"

using namespace std;


/************************ The Main Function ************************/
int main()
{
    const double MIN_SUPPORT = .75;
    
    Backtrack_APRS BAPRS(MIN_SUPPORT);
    
    int option = 1;
    do
    {
        option = prompt_main_menu();
        
        switch (option)
        {
            case DISPLAY_PASSENGERS:
            {
                BAPRS.HashTable.display_passengers_info();
                break;
            }
                
            case DISPLAY_APRIORI:
            {
                BAPRS.HashTable.display_hashTable();
                break;
            }
                
            case DISPLAY_ASSOCIATION_RULES:
            {
                BAPRS.HashTable.display_RulesTable();
                break;
            }
                
            case BACKTRACK_APRS:
            {
                BAPRS.BT_APRS(get_new_passenger_attr());
                break;
            }
        }
        
    }
    while (option != EXIT);

    return 0;
}

