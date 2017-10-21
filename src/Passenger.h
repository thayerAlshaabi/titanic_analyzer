#ifndef PASSENGER_H
#define PASSENGER_H

#include <iostream>
#include <string>
#include <sstream>

using namespace std;



/*******************************************************
 - defining four enumeration data types	to handle four
 different attributes for the Passenger class
 
 ************** Start Data Types Definitions ************/

enum CLASS_TYPE
{
    UNDIF_CLASS	 = -1,
    FIRST_CLASS  = 1,
    SECOND_CLASS = 2,
    THIRD_CLASS  = 3,
    CREW		 = 4
};


enum GENDER_TYPE
{
    UNDIF  = -1,
    FEMALE = 1,
    MALE   = 2,
};


enum AGE_TYPE
{
    UNDIF_AGE = -1,
    ADULT	  = 1,
    CHILD	  = 2
};


enum SURVIVAL_TYPE
{
    UNCERTIAN = -1,
    SURVIVED  = 1,
    DEAD	  = 2
};

/************** End Data Types Definitions ************/



/************** Start Passenger Class Definition ************/
class Passenger
{
private:
    
    /************** Private Members ************/
    
    CLASS_TYPE m_class;
    AGE_TYPE m_age;
    GENDER_TYPE m_gender;
    SURVIVAL_TYPE m_survival;
    
    /*******************************************/
    
    
    /************** Private Functions ******************
     // system checking functions tp populate data
     // into the passenger attributes
     ****************************************************/
    
    CLASS_TYPE check_class(string);
    GENDER_TYPE check_gender(string);
    AGE_TYPE check_age(string);
    SURVIVAL_TYPE check_survival(string);
    
    /*********************************************/
    
    
public:
    
    Passenger();		// Default Constructor
    Passenger(string);	// Copy Constructor
    ~Passenger();		// Destructor
    
    //Print out all atribute ID formats
    void print_obj_attributes();
    
    /****************** Setters *****************/
    
    void set_class(CLASS_TYPE);
    void set_age(AGE_TYPE);
    void set_gender(GENDER_TYPE);
    void set_survival(SURVIVAL_TYPE);
    
    /*********************************************/
    
    
    /****************** Getters ******************/
    
    CLASS_TYPE get_class();
    AGE_TYPE get_age();
    GENDER_TYPE get_gender();
    SURVIVAL_TYPE get_survival();
    
    /*********************************************/
    
};

/************** End Passenger Class Definition ************/

#endif