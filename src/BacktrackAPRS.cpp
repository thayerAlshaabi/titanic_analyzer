#include "BacktrackAPRS.h"


/********************** Start Backtrack_APRS Setup ********************/

Backtrack_APRS::Backtrack_APRS()
{
    //cout << "CONSTRUCTED";
}

Backtrack_APRS::Backtrack_APRS(double min_support)
{
    //The following it setup the HashTable
    
    HashTable.set_support(min_support);
    
    HashTable.create_hash_tbl("titanic.csv");
    
    HashTable.apriori();
}


Backtrack_APRS::~Backtrack_APRS()
{
    //cout << "DESTRUCTED";
}

/********************** End Backtrack_APRS Setup ********************/



/********************** Start Key System Functions ********************/
/*
 Creates a string that contains ones and zeros to define where NULL spots were found in the given key string. (/  = 0       Everything else = 1). 
 
 Futher the function, deletes the '/' inside the given key string so that combination system does not use it in it's combination forming.
 */
void Backtrack_APRS::create_permission_string_and_fix_key(string& key_string, string& permission_string)
{
    int undif_found_count = 0;
    
    for (int i = 0; i < key_string.size(); i++)
    {
        if (key_string[i] == '/')
        {
            undif_found_count++;
            key_string.erase(key_string.begin() + i);
            permission_string = permission_string + "0";
            i--;
        }
        else
        {
            permission_string = permission_string + "1";
        }
    }
}

//Create a string of zeros on the amount of zeros
string Backtrack_APRS::create_base_key_str(int amount_of_zeros)
{
    string base_key_string = "";
    for (int i = 0; i < amount_of_zeros; i++)
    {
        base_key_string = base_key_string + "0";
    }
    
    return base_key_string;
}


//Recursive start for making the string combinations
void Backtrack_APRS::key_combinations_hash_set(string key_string, string permission_string, int size_comb,bool& set_found,vector<string>& temp_sets)
{
    create_permission_string_and_fix_key(key_string, permission_string);
    
    //Give com_string the base format key
    string comb_string = create_base_key_str(key_string.size());
    
    
    if (0 < size_comb && size_comb <= key_string.size())
    {
        //Create all combinations with the given size_comb and the given string
        combinationUtil(key_string, comb_string, permission_string, 0, key_string.size() - 1, 0, size_comb,set_found,temp_sets);
    }
}


//Compares the combination string to a permission string. The permission string is representive of what elements in the newly formed comb_string are needed and what areas had been delimited by getting getting rid of NULL ('/') characters inside.
void Backtrack_APRS::fix_comb_string(string comb_string, const string& permission_string,int level,bool& set_found,vector<string>& temp_sets)
{
    
    for (int i = 0; i < permission_string.size(); i++)
    {
        if (permission_string[i] == '0')
        {
            comb_string.insert(i, "0");
        }
    }
    
    check_hash_map_at_level_for_key(level,comb_string,set_found,temp_sets);
}


//Gets combinations of the given amount by size_comb to formulate a combination string and then passes that given string combination to a check for the given hash map
void Backtrack_APRS::combinationUtil(const string& key_string, string& comb_string, const string& permission_string, int start_indexer, const int& end, int index, const int& size_comb,bool& set_found,vector<string>& temp_sets)
{
    // Current combination is ready to be checked by the hash map
    if (index == size_comb)
    {
        if (key_string.size() != permission_string.size())
        {
            fix_comb_string(comb_string, permission_string,size_comb,set_found,temp_sets);
        }
        else
        {
            check_hash_map_at_level_for_key(size_comb,comb_string,set_found,temp_sets);
        }
        return;
    }
    
    // (end-i+1 >= r-index) makes sure that including one element
    for (int i = start_indexer; i <= end && end - i + 1 >= size_comb - index; i++)
    {
        comb_string[i] = key_string[i];
        combinationUtil(key_string, comb_string, permission_string, i + 1, end, index + 1, size_comb,set_found,temp_sets);
        comb_string[i] = '0';//last recursive put the 'i' at the last index hit
    }
}


void Backtrack_APRS::check_hash_map_at_level_for_key(int level, string key_to_check,bool& set_found,vector<string>& temp_sets)
{
    //Checks the given hash table to see if it exist on the table on the given level.
    auto map_itr = HashTable.m_rules_tbl[level - 1].find(key_to_check);
    
    if (map_itr != HashTable.m_rules_tbl[level - 1].end())
    {
        //A set was found
        set_found = true;
        
        //If level occured on highest level therefore terminate the sequnce.
        if(level == key_to_check.size() - 1)
        {
            //Print out the given output for highest level found.
            cout << "\nKEY = " << key_to_check << "\n";
            cout << "-----------------------------\n";
            cout << "ALIVE CONF  = " << HashTable.m_rules_tbl[level - 1][key_to_check].alive_conf << "\n";
            cout << "DEATH CONF  = " << HashTable.m_rules_tbl[level - 1][key_to_check].death_conf << "\n";
            cout << "ALIVE COUNT = " << HashTable.m_rules_tbl[level - 1][key_to_check].alive_count << "\n";
            cout << "DEATH COUNT = " << HashTable.m_rules_tbl[level - 1][key_to_check].death_count << "\n";
            cout << "SET SIZE    = " << HashTable.m_rules_tbl[level - 1][key_to_check].alive_count
            + HashTable.m_rules_tbl[level - 1][key_to_check].death_count << "\n";
            return;
        }
        
        //Push the given set ID to a temp vector
        temp_sets.push_back(key_to_check);
    }
}

/********************** End Key System Functions ********************/


/********************** Start Backtrack_APRS System Functions ************************/

// A function to inersect multiple sets and return the intersection set
set<int> Backtrack_APRS::get_intersection_set(vector<string>& sets_keys, map<string,unsigned int>& set_level_map)
{
    //Creates an empty set
    set<int> intersection_set;
    
    //Error catch if an vector of nothing is sent
    if(sets_keys.size() == 0)
    {
        return intersection_set;
    }
    
    //Counts every found intersection
    int found_count = 0;
    
    //Uses the first element as the map itr and access the other sets accordingly.
    for(auto map_itr = HashTable.m_hash_tbl[(set_level_map[sets_keys[0]])][sets_keys[0]].cbegin(); map_itr != HashTable.m_hash_tbl[(set_level_map[sets_keys[0]])][sets_keys[0]].cend(); map_itr++)
    {
        //Reset counter
        found_count = 0;
        
        //Iterate across the array of strings.
        for(int i = 0; i < sets_keys.size(); i++)
        {
            if(HashTable.m_hash_tbl[(set_level_map[sets_keys[i]])][sets_keys[i]].find(*map_itr) != HashTable.m_hash_tbl[(set_level_map[sets_keys[i]])][sets_keys[i]].cend())
            {
                //
                found_count++;
            }
        }
        
        //If all given sets had the this given index inside then append it to the given set
        if(found_count == sets_keys.size())
        {
            intersection_set.insert(*map_itr);
        }
    }
    
    return intersection_set;//Return the given set
}


void Backtrack_APRS::make_changes_to_given_key(vector<string>& temp_sets,vector<string>& sets_to_combine,string& givenKey,int& level,map<string,unsigned int>& set_level_map)
{
    //For this code I refer to '/' as NULL
    
    //Counters
    int numeric_count = 0,
        null_count = 0;
    
    //Iterate through the temp array of strings
    for(int i = 0; i < temp_sets.size() && null_count != givenKey.size();i++)
    {
        //Reset given values
        null_count = 0;
        numeric_count = 0;
        
        for(int k = 0; k < givenKey.size(); k++)
        {
            if(temp_sets[i][k] != '0')
            {
                //Set given character to NULL
                givenKey[k] = '/';
                
                //Iterate count for every numeric found
                numeric_count++;
            }
            
            if(givenKey[k] == '/')
            {
                //Counts the given '/' inside of it
                null_count++;
            }
        }
        
        if(numeric_count > 0)
        {
            //Sets the level in which the given set must lie in
            set_level_map[temp_sets[i]] = numeric_count - 1;
            
            //All needed sets are pushed into the given array
            sets_to_combine.push_back(temp_sets[i]);
            
            //The given key must be filled with '/' therefore terminate both loops
            if(null_count == givenKey.size())
            {
                break;
            }
        }
    }
    if (null_count > 0)
    {
        //Push to the new level to search for the needed sets
        level = (givenKey.size() + 1) - null_count;
    }
    
    //Clear out temp array of leved sets
    temp_sets.clear();
}


// the main Backtrack APriori Rule Set Algorithm
void Backtrack_APRS::BT_APRS(string givenKey)
{
    //Creates a backup of the requested ID string
    const string givenKey_backup = givenKey;
    
    //Creates a temporary list of sets upon each valid level found
    vector<string> temp_sets;
    
    //Uses a list of all sets that are needed to find the given set.
    vector<string> sets_to_combine;
    
    //Checks if any set is found
    bool set_found = false;
    
    //Nullify out the targeted member
    givenKey[3] = '/';
    
    const unsigned int level_of_rules = HashTable.m_rules_tbl.size();
    
    //Permission string is used to have '/' return back to zeros on the givenKey
    string permission_string;
    
    //Used to store the levels in which all the sets exist on.
    map<string,unsigned int> set_level_map;
    
    //Starts at the level with the most member combinations
    for(int level = level_of_rules; level >= 1; level--)
    {
        //Start creating combination with the given string
        key_combinations_hash_set(givenKey,permission_string,level,set_found,temp_sets);
        
        //Checks to see if the given level is at the point where we can just grab a given rule
        if (level == givenKey.size() - 1)
        {
            if(set_found == true)
            {
                return;//output already occured for highest level terminate program
            }
            else
            {
                continue;//start next loop cycle
            }
        }
        
        if(temp_sets.size() != 0)
        {
            //Converts parts of the given key to '/' so the system can
            make_changes_to_given_key(temp_sets,sets_to_combine,givenKey,level,set_level_map);
        }
        
    }
    
    //Creates an empty rule
    Rule p_rule;
    
    //Creates an empty set.
    set<int> new_set;
    
    double alive_average_conf = 0,death_average_conf = 0;
    
    //Find the intersection of the following sets
    new_set = get_intersection_set(sets_to_combine,set_level_map);
    
    //Empty set is created therefore average out confidence and end
    if(new_set.size() == 0 || givenKey != "////")
    {
        //Add up all confidence levels for both alive and dead averages.
        for(int i = 0; i < sets_to_combine.size();i++)
        {
            alive_average_conf = alive_average_conf + HashTable.m_rules_tbl[(set_level_map[sets_to_combine[i]])][sets_to_combine[i]].alive_conf;
            death_average_conf = death_average_conf + HashTable.m_rules_tbl[(set_level_map[sets_to_combine[i]])][sets_to_combine[i]].death_conf;
        }
        
        //Average out the confidences
        death_average_conf = death_average_conf/sets_to_combine.size();
        alive_average_conf = alive_average_conf/sets_to_combine.size();
        
        cout << "\nKEY = " << givenKey_backup << "\n"
        << "\n******************************************\n"
        << "\n Backtrack_APRS (Predictions): \n"
        << "------------------------\n"
        << "\t ALIVE CONF  = " << alive_average_conf << "\n"
        << "\t DEATH CONF  = " << death_average_conf << "\n"
        << "\n******************************************\n";
    }
    else
    {
        //Traverse across the numerator_intersect_set and check if the passenger survived or died
        // then increament the coresponding counter accordingly
        for (auto set_itr = new_set.cbegin(); set_itr != new_set.cend(); set_itr++)
        {
            //Check if the passenger index inside the set belongs to a master set(s) and the increment the coresponding counter.
            if (HashTable.m_hash_tbl[0]["0001"].find(*set_itr) != HashTable.m_hash_tbl[0]["0001"].end())
            {
                p_rule.alive_count++;//iterate alive count
            }
            else
            {
                p_rule.death_count++;//iterate death count
            }
            
        }	// end of set_itr loop
        
        //Solve for conf
        p_rule.alive_conf = (double) p_rule.alive_count /new_set.size();
        p_rule.death_conf = (double) p_rule.death_count/new_set.size();
        
        cout << "\n******************************************\n"
        << "\n Backtrack_APRS (result): \n"
        << "------------------------\n"
        << "\t ALIVE CONF  = " << p_rule.alive_conf  << "\n"
        << "\t DEATH CONF  = " << p_rule.death_conf << "\n"
        << "\n******************************************\n";
    }
    
}

/********************** End Backtrack_APRS System Functions *************************/
