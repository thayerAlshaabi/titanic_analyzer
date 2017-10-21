
#include "Passenger.h"

// Default Constructor
Passenger::Passenger()
{
    //cout << "CONSTRUCTED";
}


// Destructor
Passenger::~Passenger()
{
    //cout << "DE-CONSTRUCTED";
}


// Copy Constructor
Passenger::Passenger(string line)
{
    /*
     # each line has four data types Identifiers separated by comma
     - This function setup a Passenger object by taking a string line
     and initializing all four attributes for that object
     with the given data in csv file
     */
    
    stringstream strstr(line);
    string word;
    
    
    // -- (line) e.g: ClassIdentifier,AgeIdentifier,GenderIdentifier,SurvivalIdentifier
    for(int i = 0; i < 4; i++)
    {
        getline(strstr, word, ',');	// look for the special delimiter(',')
        
        // checking data and initializing members with the proper attributes values
        if(i == 0)
        {
            this->set_class(check_class(word));
        }
        else if (i == 1)
        {
            this->set_gender(check_gender(word));
        }
        else if (i == 2)
        {
            this->set_age(check_age(word));
        }
        else if (i == 3)
        {
            this->set_survival(check_survival(word));
        }
        
    }
    
    //print_obj_attributes();
}



// Print out the given attributes
void Passenger:: print_obj_attributes()
{
    cout << "\n******************************\n";
    
    cout << "Passenger:\n";
    cout << "----------\n";
    cout << "CLASS    ->  " << m_class    << "\n";
    cout << "GENDER   ->  " << m_gender   << "\n";
    cout << "AGE      ->  " << m_age      << "\n";
    cout << "SURVIVAL ->  " << m_survival << "\n";
    
    cout << "\n******************************\n";
}


/****************** Start System Checking functions Definition *****************/

// check the class data and return the proper attribute value
CLASS_TYPE Passenger::check_class(string word)
{
    if (word == "Crew")
    {
        return CREW;
    }
    else if (word == "1st")
    {
        return FIRST_CLASS;
    }
    else if (word == "2nd")
    {
        return SECOND_CLASS;
    }
    else if (word == "3rd")
    {
        return THIRD_CLASS;
    }
    else
    {
        return UNDIF_CLASS;
    }
}


// check the gender data and return the proper attribute value
GENDER_TYPE Passenger::check_gender(string word)
{
    if (word == "Male")
    {
        return MALE;
    }
    else if (word == "Female")
    {
        return FEMALE;
    }
    else
    {
        return UNDIF;
    }
}


// check the age data and return the proper attribute value
AGE_TYPE Passenger::check_age(string word)
{
    if (word == "Child")
    {
        return CHILD;
    }
    else if (word == "Adult")
    {
        return ADULT;
    }
    else
    {
        return UNDIF_AGE;
    }
}


// check the surivival data and return the proper attribute value
SURVIVAL_TYPE Passenger::check_survival(string survived)
{
    if (survived == "Yes")
    {
        return SURVIVED;
    }
    else if (survived == "No")
    {
        return DEAD;
    }
    else
    {
        cout << "ERROR THERE WAS AN ERROR IN SURIVAL CHECK!!!\n";
        return UNCERTIAN;
    }
}

/****************** End System Checking functions Definition *****************/


/****************** Start Setters Definitions *****************/

void Passenger::set_survival(SURVIVAL_TYPE pass)
{
    m_survival = pass;
}

void Passenger::set_class(CLASS_TYPE pass)
{
    m_class = pass;
}

void Passenger::set_age(AGE_TYPE pass)
{
    m_age = pass;
}

void Passenger::set_gender(GENDER_TYPE pass)
{
    m_gender = pass;
}

/****************** End Setters Definitions *****************/


/****************** End Getters Definitions *****************/

SURVIVAL_TYPE Passenger::get_survival()
{
    return m_survival;
}

CLASS_TYPE Passenger::get_class()
{
    return m_class;
}

AGE_TYPE Passenger::get_age()
{
    return m_age;
}

GENDER_TYPE Passenger::get_gender()
{
    return m_gender;
}

/****************** End Getters Definitions *****************/