#ifndef HASH_TABLE_H
#define HASH_TABLE_H


#include "Passenger.h"
#include <iomanip>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;


/**********************************************************
 - defining a (Rule) struct to record all rules resulting
	while running the apriori algorithm
 
 ************** Start Rule Struct Definition **************/

struct Rule
{
    int death_count = 0,
    alive_count = 0;
    
    double  alive_conf = 0.0,
    death_conf = 0.0,
    support	   = 0.0;
};

/************** End Rule Struct Definition **************/


/************** Start Hash_Table class Definition **************/
class Hash_Table
{
private:
    /****************************** Private Members ***************************************/
    //Maxium attributes of the given passenger object
    const int MAX_MEMBERS = 4;
    
    // minimum support given for a set to pass apriori test
    double MIN_SUPPORT = 0.0;
    
    // A temporary holder of keys for sets that passes minimum support at each level
    vector<string> m_temp_level;
    
    /**************************************************************************************/
    
    void construct_hash_table();	//Create sets for the first level
    
    /************************************** Key System Handlers *************************************************/
    
    // Helper data type for the ID system
    enum ID_POSTIONS
    {
        CLASS_POS = 1,
        AGE_POS = 2,
        GENDER_POS = 3,
        SURIVAL_POS = 4
    };
    
    string create_base_key_str(int);				// Creates string key of zeros
    string create_set_key(Passenger, int);			// Create string key with the given member
    string create_combination_key(string, string);	// Create a key string with two combined two string keys
    string convert_key_to_attributes(string);		// Converts key back to given attributes
    int grab_member_at_pos(Passenger&, int);		// Returns back the given ID based on the given positional
    bool is_member_of_master_set(string);			// Checks to see if targted ID member is hit
    
    /***********************************************************************************************************/
    
    
public:
    /****************************** Public Members ***************************************/
    
    // Array of all Passengers in the data file
    vector<Passenger> m_all_passengers;
    
    // A hash table handler that would be changed dynamically
    // along with the apriori algorithm operations
    vector< map< string, set< int > > > m_hash_tbl;
    
    // a holder of the recorded rules after running the apriori algorithm
    vector< map < string, Rule > > m_rules_tbl;
    
    /**************************************************************************************/
    
    Hash_Table();					// Default Constructor
    ~Hash_Table();					// Destructor
    
    void create_hash_tbl(string);
    void apriori(); // Main Aprior Algorithm
    
    void set_support(double s = 0.0){MIN_SUPPORT = s;}
    
    /*****************************************/
    void display_passengers_info();
    void display_hashTable();
    void display_RulesTable();
    /*****************************************/
    
    
    
    
};
/************** END Hash_Table class Definition **************/

#endif