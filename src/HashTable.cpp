#include "HashTable.h"

/********************** Start Hash Table Setup Functions ********************/
Hash_Table::Hash_Table()
{
    //cout << "CONSTRUCTED";
}


Hash_Table::~Hash_Table()
{
    //cout << "DE-CONSTRUCTED";
}


// Explanation of the hash table system:
/************************************************************************************************************
 *					 VECTOR				MAP <(KEY = string) => ( SET <intgers>)>							*
 *				-----------------		=========================================							*
 *				|	=========	|		|	--------------	--------------		|							*
 *	Level# 1	|	|  MAP	+---+----->	|	| KEY => SET |  | KEY => SET | . . .|							*
 *				|	=========	|		|	-------+------  --------------		|							*
 *				-----------------		===========|============================|							*
 *				|	=========	|				   |														*
 *	Level# 2	|	|  MAP	|	|				   |	 SET <intgers>										*
 *				|	=========	|				   +-->		-------											*
 *				|---------------|							| 2   |											*
 *		.		|				|							| 59 -+-----> index of a passenger				*
 *	Level# n	|				|							| 126 |		  in the m_all_passengers vector	*
 *				|---------------|							|  .  |											*
 *															|  n  |											*
 *															-------											*
 *																											*
 ************************************************************************************************************/
void Hash_Table::construct_hash_table()
{
    string key;
    
    map<string, set<int>> newMap;
    m_hash_tbl.push_back(newMap);
    
    for (int i = 0; i < m_all_passengers.size(); i++)	//Traverse the array of objects
    {
        for (int j = 1; j <= MAX_MEMBERS; j++)	//Cycle across all members for the object
        {
            key = create_set_key(m_all_passengers[i], j);
            
            m_hash_tbl[0][key].insert(i);	//pass the array index to the given set
        }
    }
    
    //display_hashTable();
}



// a functions that reads in a csv file
// and extract all passengers data from
// then store it into a vector of passenger objects
void Hash_Table::create_hash_tbl(string fileName)
{
    ifstream dataFile(fileName);	// open file to start reading in data
    string line = "";
    
    if (!dataFile)
    {
        cout << "Error file name " << fileName << "\n";
        return;
    }
    
    // read a line from the data file
    getline(dataFile, line);
    
    while (getline(dataFile, line))
    {
        Passenger new_passenger(line);
        m_all_passengers.push_back(new_passenger);
    }
    
    dataFile.close();
    
    construct_hash_table();	// create hash map of sets on the first level
}

/********************** End Hash Table Setup Functions ********************/


// Explanation of the ID system:
/*************************************************************************************************************
 
 ==============================================
 ID strings system, Postionals
 ==============================================
 
	-Each passenger is identified with an ID of four numeric digits
 
	-We extract each attribute value off the passenger object
	and replace it with a numeric value from our specified data types
	that were defined in the passenger object
	to formulate a meaningful representative ID for that passenger
 
	------------------------------------------------------------------
 
	- Example:	Adult, 1st Class, Male, Dead
 
	- Lets give each an ID
 
	-- Adult = 1,	Class = 1,	Male = 2,	 Surv = 2
 
	- Now we need positions to place the given members
 
	-- Class  = First Postional,	 Age  = Second Postional,
	Gender = Third Postional,	 Surv = Fourth Postional
 
	-Now combining both methods we can form an ID from this.
 
	Positonals:  |  First Postional  |  Second Postional  |  Third Postional  |  Fourth Postional  |
 
	Data Type:   |      Class        |       Age          |      Gender       |        Surv        |
 
	Given Value: |      1st Class    |      Adult         |       Male        |        Dead        |
 
	ID Value:    |        1          |        1           |         2         |          2         |
	------------------------------------------------------------------------------------------------
	Result String ID:  1122
	------------------------------------------------------------------------------------------------
 
 
	-Futher any ignored members for intersected sets are just set as zero for the given operation.
 
	Example:	Adult = 1,	Class = 3
 
	Positonals:  |  First Postional  |  Second Postional  |  Third Postional  |  Fourth Postional  |
 
	Data Type:   |      Class        |       Age          |      Gender       |        Surv        |
 
	Given Value: |      1st Class    |      Adult         |       Male        |        Dead        |
 
	ID Value:    |        3          |        1           |         0         |          0         |
	------------------------------------------------------------------------------------------------
	Result String ID:  3100
	------------------------------------------------------------------------------------------------
 
 **************************************************************************************************************/


/********************** Start Key System Functions ********************/

// Creates an ID of zeros based on the passed value.
// The passed value determines how many zeros
string Hash_Table::create_base_key_str(int amount_of_zeros)
{
    string base_key_string = "";
    
    for (int i = 0; i < amount_of_zeros; i++)
    {
        base_key_string = base_key_string + "0";//append zero to string
    }
    
    return base_key_string;
}


// Converts a key of a single member type.
string Hash_Table::create_set_key(Passenger temp, int pos_of_member)
{
    string single_member = create_base_key_str(MAX_MEMBERS);//needed to place our given ID in
    
    single_member[pos_of_member - 1] = (char)(48 + grab_member_at_pos(temp, pos_of_member));//convert value to char for string
    
    return single_member;
}


// Warning! De-Bugging code only! Needs to be changed for different process

//Converts back the key string back to it's natural attribute names for de-bugging
string Hash_Table::convert_key_to_attributes(string key)
{
    string attribute_string;
    
    if (key == "" || key == "0000" || key.size() != MAX_MEMBERS)//Error catch
    {
        return "EMPTY STRING";
    }
    for(int i = MAX_MEMBERS; i >= 1; i--)//Cycles through the positionals backwards because string appending pushes the newest strings to the front and the old strings to the back
    {
        if(CLASS_POS == i)//Compares traversal to positional var
        {
            if(key[CLASS_POS-1] == '1')//Positional needs to be subtracted by 1 to access the correct element in the key string since the positionals data types start with 1
            {
                attribute_string = "1st-Class, " + attribute_string;
            }
            else if (key[CLASS_POS-1] == '2')//ID for class 2
            {
                attribute_string = "2nd-Class, " + attribute_string;
            }
            else if (key[CLASS_POS-1] == '3')//ID for class 3
            {
                attribute_string = "3rd-Class, " + attribute_string;
            }
            else if (key[CLASS_POS-1] == '4')////ID for crew
            {
                attribute_string = "Crew-Class, " + attribute_string;
            }
        }
        
        else if(AGE_POS == i)//Get the given positional and compare
        {
            if(key[AGE_POS-1] == '1')//ID for Adult
            {
                attribute_string = "Adult, " + attribute_string;
            }
            else if (key[AGE_POS-1] == '2')//ID for Child
            {
                attribute_string = "Child, " + attribute_string;
            }
        }
        
        else if(GENDER_POS == i)//Get the given positional
        {
            if(key[GENDER_POS-1] == '1')//ID for Female
            {
                attribute_string = "Female, " + attribute_string;
            }
            else if (key[GENDER_POS-1] == '2')//ID for Male
            {
                attribute_string = "Male, " + attribute_string;
            }
            
        }
        else if (SURIVAL_POS == i)//Get the given positional
        {
            if(key[SURIVAL_POS-1] == '1')//ID for Surival
            {
                attribute_string = "Survied, " + attribute_string;
            }
            else if (key[SURIVAL_POS-1] == '2')//ID for death
            {
                attribute_string = "Dead, " + attribute_string;
            }
        }
    }
    
    return attribute_string;
}


// Based on the positional value, the given object value will pass back the corsponding member's ID
int Hash_Table::grab_member_at_pos(Passenger& temp_obj, int pos)
{
    //Checks the given positon passed and pass back
    if (pos == CLASS_POS)
    {
        return temp_obj.get_class();
    }
    else if (pos == AGE_POS)
    {
        return temp_obj.get_age();
    }
    else if (pos == GENDER_POS)
    {
        return temp_obj.get_gender();
    }
    else if (pos == SURIVAL_POS)
    {
        return temp_obj.get_survival();
    }
    else
    {
        cout << "ERROR UNKNOWN MEMBER WAS HIT!!!";//error checking
        return 0;
    }
}


// Returns true or false if the target member belongs to a master set(s).
// The master sets is either the set that has everyone who surived or died.
bool Hash_Table::is_member_of_master_set(string key)
{
    if (key[SURIVAL_POS - 1] == '0')
    {
        return false;
    }
    else
    {
        return true;
    }
    
}


/********************************************************************************************
 
	==============================================
	Combining sets process to form combinations:
	==============================================
 
      0010		  adult
	^ 0020		^ child
	= ----		= -----
      0000		  error! because the passenger can't be an adult and a child at the same time
 
	0000 => NULL_KEY :: invalid combination key
 
	---------------------------------------------
 
      0010		  adult
	^ 0100		^ female
	= ----		= -----
      0110       female-adult
 
	0110 => new combo_key :: valid combination key
 
 *******************************************************************************************/
string Hash_Table::create_combination_key(string key_1, string key_2)
{
    string new_key = create_base_key_str(key_1.size());
    
    if (key_1.size() == key_2.size()) //Ensures that the keys can be combined by being the same size
    {
        for (int i = 0; i < key_1.size(); i++)//Traverse keys since they must be the same size
        {
            if (key_1[i] == '0' && key_2[i] != '0')	//append to string if a valid value can be passed through
            {
                new_key[i] = key_2[i];
            }
            
            else if (key_2[i] == '0' && key_1[i] != '0')	//same as above
            {
                new_key[i] = key_1[i];
            }
            
            else if (key_1[i] != '0' && key_2[i] != '0')//a value has been found in both spots
            {
                if (key_1[i] == key_2[i])	//The value is the same in the positional therefore pass to the new key
                {
                    new_key[i] = key_1[i];
                }
                else //They are different therefore return empty set for error catching
                {
                    return create_base_key_str(key_1.size());
                }
            }
        }
    }
    else
    {
        cout << "AN ERROR HAS OCCUREDD WHEN CREATING NEW KEY";
    }
    
    return new_key;
}


/********************** End Key System Functions ********************/

// main apriori algorithm
void Hash_Table::apriori()
{
    double support = 0.0;
    
    //counters for each set
    int death_count = 0,
    alive_count = 0;
    
    const string NULL_KEY = create_base_key_str(MAX_MEMBERS);//set default key = 0000
    
    //Define a new map of rules for each set then push it into the rule table
    map<string, Rule> new_rule;
    m_rules_tbl.push_back(new_rule);
    
    //Iterate across the map on the zero level of the table
    for (auto map_itr = m_hash_tbl[0].cbegin(); map_itr != m_hash_tbl[0].cend(); ++map_itr)
    {
        support = map_itr->second.size() / (double)m_all_passengers.size();//find the support of the given set
        
        //Checks to see if the support meets the minmial support test and is not using the alive or dead set
        if (support > MIN_SUPPORT &&  !is_member_of_master_set(map_itr->first))
        {
            m_temp_level.push_back(map_itr->first);//Push supports that pass in the system
        }
        
        //Traverse across the set and pull all indexes
        for (auto set_itr = map_itr->second.cbegin(); set_itr != map_itr->second.cend(); set_itr++)
        {
            //Check if the passenger index inside the set belongs to a master set(s) and the increment the coresponding counter.
            if (m_hash_tbl[0]["0001"].find(*set_itr) != m_hash_tbl[0]["0001"].end())
            {
                alive_count++;
            }
            else
            {
                death_count++;
            }
            
        }	// end of set_itr loop
        
        m_rules_tbl[0][map_itr->first].support = support;//store the support
        
        //Calculate the death and alive rates
        m_rules_tbl[0][map_itr->first].alive_count = alive_count;
        m_rules_tbl[0][map_itr->first].death_count = death_count;
        
        //Calculate the alive and death confidence
        m_rules_tbl[0][map_itr->first].alive_conf = (double)(alive_count) / m_hash_tbl[0][map_itr->first].size();
        m_rules_tbl[0][map_itr->first].death_conf = (double)(death_count) / m_hash_tbl[0][map_itr->first].size();
        
        //reset counters back
        alive_count = 0;
        death_count = 0;
        
    }	// end of map_itr loop
    
    
    for (int level = 0; level < MAX_MEMBERS - 2; level++)
    {
        //Ensures that the rules table does not have an empty map.
        if(m_rules_tbl[level].size() == 0)
        {
            m_hash_tbl.pop_back();
            break;
        }
        
        //Ensures that the hash table does not have an empty map.
        //Futher, if there is only 1 set inside therefore we
        //  -have nothing to combine the set with so end.
        
        if (m_hash_tbl[level].empty() || m_temp_level.size() <= 1)
        {
            break;
        }
        
        //Create an empty rule map for the new rules in the table
        map<string, Rule> new_rule_map;
        m_rules_tbl.push_back(new_rule_map);
        
        //Create a new map for the hash table to be used
        map<string, set<int>> newMap;
        m_hash_tbl.push_back(newMap);
        
        //Traverse through m_temp_level container that has all sets that passed the previous support test.
        for (int i = 0; i < m_temp_level.size(); i++)
        {
            //Check the next string set key and if combining the two is possible.
            for (int j = i + 1; j < m_temp_level.size(); j++)
            {
                //For futher details check specs for create_combination_key function
                string new_combo_Key = create_combination_key(m_temp_level[i], m_temp_level[j]);//combine given keys
                
                //Checks to ensure an empty string is not passed
                if (new_combo_Key != NULL_KEY)
                {
                    //Traverse across one of the given sets
                    for (auto set_itr = m_hash_tbl[level][m_temp_level[i]].cbegin(); set_itr != m_hash_tbl[level][m_temp_level[i]].cend(); set_itr++)
                    {
                        //Check to see if the passed index exists the set you are comparing to.
                        if (m_hash_tbl[level][m_temp_level[j]].find(*set_itr) != m_hash_tbl[level][m_temp_level[j]].end())
                        {
                            //pass the index to the newly found set
                            m_hash_tbl[level + 1][new_combo_Key].insert(*set_itr);
                            
                            //Check if the passenger index inside the set belongs to a master set(s) and the increment the coresponding counter.
                            if (m_hash_tbl[0]["0001"].find(*set_itr) != m_hash_tbl[0]["0001"].end())
                            {
                                alive_count++;
                            }
                            else
                            {
                                death_count++;
                            }
                        }
                        
                    }	// end of set_itr loop
                    
                    //ensure that the set is not empty
                    if (alive_count != 0 || death_count != 0)
                    {
                        //Set support
                        m_rules_tbl[level + 1][new_combo_Key].support = (m_hash_tbl[level + 1][new_combo_Key].size()) / (double)m_all_passengers.size();
                        
                        
                        //Calculate the alive and death rates
                        m_rules_tbl[level + 1][new_combo_Key].alive_count = alive_count;
                        m_rules_tbl[level + 1][new_combo_Key].death_count = death_count;
                        
                        
                        //Calculate the alive and death confidences
                        m_rules_tbl[level + 1][new_combo_Key].alive_conf = (double)alive_count / m_hash_tbl[level + 1][new_combo_Key].size();
                        m_rules_tbl[level + 1][new_combo_Key].death_conf = (double)death_count / m_hash_tbl[level + 1][new_combo_Key].size();
                        
                        //reset counter
                        alive_count = 0;
                        death_count = 0;
                    }
                    
                }
                
            } // end of inner for loop
            
        } // end of outer for loop
        
        // clear out the temporary level vector
        m_temp_level.erase(m_temp_level.begin(), m_temp_level.end());//Erase last saved supported IDs
        
        
        //Travese across newly created level and decide what sets will pass to the next level.
        for (auto map_itr = m_hash_tbl[level + 1].cbegin(); map_itr != m_hash_tbl[level + 1].cend(); map_itr++)
        {
            //Find the given support
            support = map_itr->second.size() / (double)m_all_passengers.size();
            
            //Pass over IDs that surived
            if (support > MIN_SUPPORT)
            {
                m_temp_level.push_back(map_itr->first);
            }
        }
    }
    
    //display_hashTable();
}

/************************* Start Display System ***************************/
void Hash_Table::display_hashTable()
{
    double support = 0.0;
    
    for (int i = 0; i < m_hash_tbl.size(); i++)
    {
        cout << "\n\nHASH_TABLE -- level# " << i + 1 << " -- size[ " << m_hash_tbl[i].size() << " ]\n\n";
        
        for (auto map_itr = m_hash_tbl[i].cbegin(); map_itr != m_hash_tbl[i].cend(); ++map_itr)
        {
            support = map_itr->second.size() / (double)m_all_passengers.size();
            
            cout << "\t KEY: " << map_itr->first
            << "\t SIZE: " << map_itr->second.size()
            << "\t SUPPORT: " << fixed << setprecision(2) << support << "\n";
        }
    }
}


void Hash_Table::display_RulesTable()
{
    for(int level = 0; level < m_rules_tbl.size();level++)
    {
        for (auto map_itr = m_rules_tbl[level].cbegin(); map_itr != m_rules_tbl[level].cend(); ++map_itr)
        {
            cout << "\n\n______________________________________________________________";
            
            cout << "\n--------------------------------------------------\n";
            cout << " RULE KEY: \t" << (map_itr->first);
            cout << "\n TRANSLATED : \t" << convert_key_to_attributes((map_itr->first));
            cout << "\n--------------------------------------------------\n";
            
            cout << "\t DEATH Count       = " << map_itr->second.death_count << "\n"
            << "\t ALIVE Count       = " << map_itr->second.alive_count << "\n"
            << "\t------------------------------\n"
            << "\t SUPPORT          = " << fixed << setprecision(4) << map_itr->second.support << "\n"
            << "\t DEATH CONFIDENCE = " << fixed << setprecision(2) << map_itr->second.death_conf << "\n"
            << "\t ALIVE CONFIDENCE = " << fixed << setprecision(2) << map_itr->second.alive_conf << "\n";
            
            cout << "______________________________________________________________\n\n";
        }
    }
    
    
}


void Hash_Table::display_passengers_info()
{
    for (auto map_itr = m_hash_tbl[0].cbegin(); map_itr != m_hash_tbl[0].cend(); ++map_itr)
    {
        cout << "\t KEY: " << convert_key_to_attributes((map_itr->first));
        
        if (map_itr->first == "1000" || map_itr->first == "2000" ||
            map_itr->first == "3000" || map_itr->first == "4000")
        {
            cout << "\t TOTAL: " << map_itr->second.size();
        }
        else
        {
            cout << "\t\t TOTAL: " << map_itr->second.size();
        }
        
        
        cout << "\t || \t Survived: " << m_rules_tbl[0][map_itr->first].alive_count
        << "\t Died: "		<< m_rules_tbl[0][map_itr->first].death_count << "\n";
    }
}

/************************* End Display System ***************************/