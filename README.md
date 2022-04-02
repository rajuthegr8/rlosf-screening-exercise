# rlosf-screening-exercise

This repository contains the screening exercise for the RLOS Fest 2022 for the project 

'Introduce Feature Engineering Language in VowpalWabbit'

## Part 1

Given an “expression” language, supporting queries consisting of variables, values (float literals,) and operators (logical and relational)

Implement a function eval(std::string expr, std::map<std::string, float> vars) to evaluate the expression

### Setup
 
part1.cpp contains the necessary function eval() and the table of variables and their values is defined in the main function.

input.txt contains the expressions to be evaluated and the results are stored in the output.txt

#### Note:
1.) Make sure there is a new line character added to the last line in input.txt or else the shell script not take the last line as the input

2.) The shell script assumes both input.txt and output.txt are present and input.txt has the vaild expression

### Usage

```bash
chmod +777 run.sh
./run.sh
```

The output will be stored in output.txt after running the script.

## Part 2

Given a “database” with rows consisting of a set of key-value pairs Implement a function 

DataTable select(std::string query, const DataTable& table) 

that, given a query in the “expression” language above and a DataTable, returns the rows that match the query.

### Setup
 
part1.cpp contains the necessary function select() and a sample "Database" is defined in the main function.

input.txt contains the expressions to be evaluated and the results are stored in the output.txt

#### Note:
1.) Make sure there is a new line character added to the last line in input.txt or else the shell script not take the last line as the input

2.) The shell script assumes both input.txt and output.txt are present and input.txt has the vaild expression

### Usage

```bash
chmod +777 run2.sh
./run2.sh
```
## Part 3
What kinds of optimizations could you make to your implementation of the select() function above? Describe them, but do not implement.

### Optimization 1

ASSUMPTION: The Database is very large compared to the number of variables present in the query.

1.) Declare an ```unordered_set<string> var ```
  
2.) Iterate throught the query and add variable names to the hashset ```var```
 
3.) Iterate throught '''var''' and Database table and add rows to another Database which will contain all the matches
  
Iterating throught a large database will the most expensive operation of the function select() this optimization would ensure no duplicate variables are present


  











