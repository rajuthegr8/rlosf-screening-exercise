#include<iostream>
#include<string>
#include<stack>
#include<map>
#include<sstream>
using namespace std;

struct data
{
    bool type;
    bool x;
    float y;
};

void eval(std::string expr, std::map<std::string, float> vars);

int type(const string &a,const std::map<std::string, float> &vars);
int precedence(string a);
int operate(data a,data b,string op,const string &expr,stack<data>&values);


int main(int argc, char const *argv[])
{

    map<string,float>vars;
    vars.insert({"sepal_length",4.9});
    vars.insert({"sepal_width",3.0});
    vars.insert({"petal_length",1.4});
    vars.insert({"petal_width",0.2});
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
    
    eval(t,vars);
    
    return 0;
}
void eval(std::string expr, std::map<std::string, float> vars)
{
    
    stack<data> values;
    stack<string> operators;

    stringstream expression(expr);
    string token;float val;
    string op;
    data a,b;
    int st;
    while(expression>>token)
    {
        data d;
        if(token=="" || token==" ")
        continue;
        int ty = type(token,vars);
        if(ty==4)
        {
            val = stof(token);
            d.type = true;
            d.y = val;
            values.push(d);
        }
        else if(ty==1)
        {
            val = vars[token];
            d.type = true;
            d.y = val;
            values.push(d);   
        }
        else if(ty==2)
        {
            if(token=="(")
            {
                operators.push("(");
            }
            else
            {
                while(operators.top()!="(")
                {
                    
                    b=values.top();values.pop();
                    a=values.top();values.pop();
                    op = operators.top();operators.pop();
                    st = operate(a,b,op,expr,values);
                    if(st==-1)return ;
                }
                operators.pop();   
            }
        }
        else 
        {
            
            while(!operators.empty() )
            {
                if(precedence(operators.top())<precedence(token))break;
                b=values.top();
                values.pop();
                a=values.top();
                values.pop();
                op = operators.top();operators.pop();
                st = operate(a,b,op,expr,values);
                if(st==-1)return ;
            }
            operators.push(token);
        }
        
    }
    while(!operators.empty())
    {
        b=values.top();values.pop();
        a=values.top();values.pop();
        op = operators.top();operators.pop();
        st = operate(a,b,op,expr,values);
        if(st==-1)return ;
    }
    if(values.top().type)
    {
        cout<<values.top().y;
    }
    else
    {
        if(values.top().x)cout<<"true";
        else cout<<"false";
    }
}

int type(const string &a,const std::map<std::string, float> &vars)
{
    if(vars.find(a)!=vars.end())
    return 1;
    
    if(a==")" || a=="(")
    return 2;
    if(a=="<" || a==">" || a=="==" || a=="!=" || a=="&&" || a=="||")
    return 3;
    return 4;
}

int precedence(string a)
{
    if(a==">" || a=="<")return 4;
    if(a=="!=" || a=="==")return 3;
    if(a=="||")return 2;
    if(a=="&&")return 1;
    return 0;
}

int operate(data a,data b,string op,const string &expr,stack<data>&values)
{
    data d;//temporary variable to push value into the stack
    if(a.type^b.type)//checking if the 2 data types are the same or not
    {
        cout<<"Error in expression: '";
        cout<<expr;
        cout<<": cannot apply operator ";
        cout<<op;
        cout<<" to expressions of types ";
        if(a.type)
        cout<<"(float, boolean)";
        else
        cout<<"(boolean, float)";
        return -1;
    }
    if(a.type)//if operands are float
    {
        if(op=="||" || op=="&&")
        {
            cout<<"Error in expression: '";
            cout<<expr;
            cout<<": cannot apply operator ";
            cout<<op;
            cout<<" to expressions of types ";
            cout<<"(float, float)";
            return -1;
        }
        if(op=="<")
        {
            d.type=false;
            d.x = a.y < b.y;
            values.push(d);
        }
        else if(op==">")
        {
            d.type=false;
            d.x = (a.y > b.y);
            values.push(d);
        }
        else if(op=="==")
        {
            d.type=false;
            d.x = a.y == b.y;
            values.push(d);
        }
        else if(op=="!=")
        {
            d.type=false;
            d.x = a.y != b.y;
            values.push(d);
        }
    }
    else//if operands are boolean
    {
        if(op=="<" || op==">")
        {
            cout<<"Error in expression: '";
            cout<<expr;
            cout<<": cannot apply operator ";
            cout<<op;
            cout<<" to expressions of types ";
            cout<<"(boolean, boolean)";
            return -1;
        }
        if(op=="==")
        {
            d.type=false;
            d.x = (a.x == b.x);
            values.push(d);
        }
        else if(op=="!=")
        {
            d.type=false;
            d.x = a.x != b.x;
            values.push(d);
        }
        else if(op=="&&")
        {
            d.type=false;
            d.x = a.x && b.x;
            values.push(d);
        }
        else if(op=="||")
        {
            d.type=false;
            d.x = a.x || b.x;
            values.push(d);
        }
    }
    return 1;
}