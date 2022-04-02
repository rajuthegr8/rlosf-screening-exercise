#include<iostream>
#include<string>
#include<stack>
#include<map>
#include<sstream>
#include<vector>
#include<set>
using namespace std;

struct DataRow
{
  std::map<std::string, float> Fields;
};

typedef std::vector<DataRow> DataTable;
DataTable select(std::string query, const DataTable& table);


int main(int argc, char const *argv[])
{

    map<string,float>vars;
    DataTable table;
    DataRow temp;

    //generating a sample "Database"
    vars.insert({"sepal_length",4.9});
    temp.Fields = vars;
    table.push_back(temp);
    vars.insert({"sepal_width",3.0});
    temp.Fields = vars;
    table.push_back(temp);
    vars.insert({"petal_length",1.4});
    temp.Fields = vars;
    table.push_back(temp);
    vars.insert({"petal_width",0.2});
    temp.Fields = vars;
    table.push_back(temp);

    
    
    string s,t;
    for (int i = 1; i < argc; i++)
    {
        s = s + argv[i] + " ";
    }
    for (auto c:s)
    {
        if(c=='(' || c==')')
        {
            t=t+" "+c+" ";
        }
        else
        {
            t=t+c;
        }
    }
    
    DataTable match  = select(t,table);
    for(auto row:match)
    {
        for(auto kv:row.Fields)
        {
            cout<<kv.first<<"-"<<kv.second<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    return 0;
}

DataTable select(std::string query, const DataTable& table)
{
    stringstream expression(query);
    string token;
    DataTable match;
    set<int>match_index;

    while(expression>>token)
    {
        if(token=="" || token==" ")
        continue;

        for(int i = 0;i<table.size();i++)
        {
            auto row = table[i];
            if(row.Fields.find(token)!=row.Fields.end())
            {
                match_index.insert(i);
            }
        } 
    }

    for(int id:match_index)
    {
        match.push_back(table[id]);
    }
    return match;
}

