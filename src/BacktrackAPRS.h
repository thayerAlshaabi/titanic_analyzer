#ifndef BACKTRACK_APRS_H
#define BACKTRACK_APRS_H

#include "Passenger.h"
#include "HashTable.h"

using namespace std;

/************** Start Backtrack_APRS class Definition **************/

class Backtrack_APRS
{
private:
    const double NULL_CONF = -1.1;
    
    
    // Key System functions
    /*************************************/
    void check_hash_map_at_level_for_key(int,string,bool&,vector<string>&);//Checks to see if a given key at a set level exist
    
    void create_permission_string_and_fix_key(string&, string&);//A key of ones and zeros is created to mark out areas where a numeric occured or a '/' = 'NULL'
    string create_base_key_str(int);//Creates a key of zeros
    void fix_comb_string(string, const string&,int,bool&,vector<string>&);//Takes a string of ones and zeros (known as the permission string) to fix a string cointaining '/'
    
    void key_combinations_hash_set(string, string,int,bool&,vector<string>&);//Starts off the combinations of the string
    void combinationUtil(const string&, string&, const string&,int,const int&,int,const int&,bool&,vector<string>&);//Recursive function for creating the string combinations
    /*************************************/
    void make_changes_to_given_key(vector<string>&,vector<string>&,string&,int&,map<string,unsigned int>&);
    set<int> get_intersection_set(vector<string>&, map<string,unsigned int>&);
    
public:
    Hash_Table HashTable;
    
    Backtrack_APRS();// Default Constructor
    Backtrack_APRS(double);//Copy Constructor
    
    ~Backtrack_APRS();// Decstructor
    
    void BT_APRS(string);//Starts the back track process with a given set key
    
};

/************** END Backtrack_APRS class Definition **************/

#endif