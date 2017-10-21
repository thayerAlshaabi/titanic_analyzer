#include "menu.h"

string get_new_passenger_attr()
{
    string p_key = "";
    
    int p_class = 0,
    p_age = 0,
    p_gender = 0,
    p_survival = 0;
    
    cout << "\n------------------------"
    << "\n| Backtrack_APRS MENU: |"
    << "\n------------------------\n\n";
    
    cout << "\n -Ticket Class: "
    << "\n [1] 1st "
    << "\n [2] 2nd "
    << "\n [3] 3rd "
    << "\n [4] CREW"
    << "\n ---------------";
    cout << "\n Please Enter your Ticket class: e.g: 4";
    cout << "\n CLASS: ";
    cin >> p_class;
    
    while (cin.fail() || p_class < 1 || p_class > 4)
    {
        cout << "\n Error!: Please enter an integer between 1-4:";
        cout << "\n CLASS: ";
        
        cin.clear();
        cin.ignore(256, '\n');
        cin >> p_class;
    }
    
    cout << "\n\n -Passenger AGE: "
    << "\n [1] Adult "
    << "\n [2] Child "
    << "\n ---------------";
    cout << "\n Please Enter your age Type: e.g: 2";
    cout << "\n AGE: ";
    cin >> p_age;
    
    while (cin.fail() || p_age < 1 || p_age > 2)
    {
        cout << "\n Error!: Please enter an integer between 1-2:";
        cout << "\n AGE: ";
        
        cin.clear();
        cin.ignore(256, '\n');
        cin >> p_age;
    }
    
    cout << "\n\n -Passenger Gender: "
    << "\n [1] Female "
    << "\n [2] Male	"
    << "\n ---------------";
    cout << "\n Please Enter your gender Type: e.g: 1";
    cout << "\n GENDER: ";
    cin >> p_gender;
    
    while (cin.fail() || p_gender < 1 || p_gender > 2)
    {
        cout << "\n Error!: Please enter an integer between 1-2:";
        cout << "\n GENDER: ";
        
        cin.clear();
        cin.ignore(256, '\n');
        cin >> p_gender;
    }
    
    p_key += to_string(p_class) + to_string(p_age) + to_string(p_gender) + to_string(p_survival);
    
    cout << "\n\n p_key ::" << p_key << ":: \n\n";
    
    return p_key;
}


int prompt_main_menu()
{
    cout << "\n--------------"
    << "\n| MAIN MENU: |"
    << "\n--------------\n\n";
    
    cout << "\n [1] Display Titanic Passengers info "
    << "\n [2] Display Apriori Hash Table "
    << "\n [3] Display Association Rules Table "
    << "\n [4] Run Backtrack_APRS Algorithm "
    << "\n [0] Exit "
    << "\n --------------------------------------";
    cout << "\n Please Enter a menu number :: e.g: 4";
    cout << "\n Menu Option:: ";
    
    int option = 0;
    cin >> option;
    
    while (cin.fail() || option < 0 || option > 4)
    {
        cout << "\n Error!: Please enter an integer between (0 - 4): ";
        cout << "\n Menu Option: ";
        
        cin.clear();
        cin.ignore(256, '\n');
        cin >> option;
    }
    cout << endl;
    
    return option;
}