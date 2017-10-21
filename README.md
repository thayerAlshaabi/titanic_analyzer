# TITANIC ANALYZER 

In this project we are going to use data structures and algorithms to find out some truth behind Titanic's tragic case. After the famous ship sunk people have gathered some information from witnesses about what happened on those last minutes. The Titanic movie shows some details about who got into boats and how different people reacted to saving their life vs helping others in a sinking ship. Some sources even suggested that richer people who had higher-class tickets had better chance of survival. However, witness stories sometimes can be biased, so we are going to use factual data to find out for ourselves who got saved and if there were any factors that went into that like ticket class or age.


## Building & Running
Open your terminal/Command-Line and follow the instructions below:
#### &emsp;&emsp; 1. Move your current working directory to (titanic_analyzer/src)
#### &emsp;&emsp; 2. To build the project on your machine: ` make `
#### &emsp;&emsp; 3. To run the program: ` .\titanic_analyzer `
#### Additionally, you could type in this command to remove any files from the previous build of the program: ` make clean `


## Dataset
For this project you will be using a real dataset that was gathered on titanic and contains information on every passenger on the ship. The dataset includes their ticket class, age, sex and whether or not they survived (see ` titanic.csv `).



## Data Structures and Algorithms
1.	Apriori: association mining algorithm
2. BacktrackAPRS custum-designed prediction algorithm

 
## Implementation
The source code is very well-documented explaining in detail every process individually, and how it contributes to the overall structure of the project.

#### Initialization process & Apriori Algorithm:
 - Input Passengers' Data
 - Setup first level of sets using a single passenger's attribute 
 - Run minimum support test
 - Setup the second level of sets using only the sets that passed the min-support test.
 - Run the minimum support test again and apply the same method till no set passes the test anymore

![figure1](https://github.com/thaer275/titanic_analyzer/blob/master/figure1.png)

---

#### Results of Apriori Algorithm:
The results of the Apriori algorithm are saved to a customized structure that was designed specifically for the purpose and scope of this project.

![figure2](https://github.com/thaer275/titanic_analyzer/blob/master/figure2.png)

---

#### BacktrackAPRS Algorithm:
 - Ask user for passenger info
 - Check rules' table for a corresponding rule
 - Present rule result to the user 
 - If no rule was found: collect all possible sets that could help to make a prediction from the rules table.
 - Use available statistical data to provide a meaningful prediction for the new user.

![figure3](https://github.com/thaer275/titanic_analyzer/blob/master/figure3.png)



## License
Licensed under the MIT License.
