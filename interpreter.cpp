#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
 
void translate(std::vector <std::string>& linee);
void declare(std::vector <std::string>& linee);
void read(std::ifstream& file);
void output(std::vector <std::string>& linee);
void operation(std::vector <std::string>& linee);
void condition(std::vector<std::string>& linee);
bool do_condition(std::vector<std::string>& vec); 
int int_operators(std::string sym, std::string a, std::string b);
double double_operators(std::string sym, std::string a, std::string b);
std::string sym_operators(std::string a, std::string b);
bool logic_operators(std::string sym, std::string a, std::string b);
std::vector <std::string> tokens;
std::vector<std::string> vec;
struct var
{
  std::string name;
  std::string type;
  void* value;
};
 
std::vector <var> vars;
 
void translate(std::vector <std::string>& linee)
{
    if(linee[0] == "round" || linee[0] == "comma" || linee[0] == "sym" || linee[0] == "logic")
    {
        declare(linee);
    }
    else if(linee[0] == "show")
    {
        output(linee);
    }
    else if(linee[0] == "cond")
    {
        condition(linee);
    }
    else
    {
        for(int j = 0;j < vars.size();j++)
        {
                if(linee[0] == vars[j].name)
                {
                   operation(linee);
                }
        }
    }
}
 
void read(std::ifstream& file)
{
    std::string tmp;
    while(!file.eof())
    {
        std::string line;
        getline(file,line);
        for(int i = 0;i < line.length();++i)
        {
            if(line[i] != ' ' && line[i] != ';')
            {
                tmp = tmp + line[i];
            }
            else
            {
                tokens.push_back(tmp);
                tmp = "";
                if(line[i] == ';')
                {
                    translate(tokens);
                    tokens.erase(tokens.begin(),tokens.end());
                }
            }
        }
    }
}
 
void declare(std::vector <std::string> &linee)
{
    if(linee[0] == "round")
    {
        int i = 0;
        var p;
        p.type = linee[i];
        ++i;
        p.name = linee[i];
        ++i;
        if(linee[i] == "=")
        {
            ++i;
            p.value = static_cast <void*> (new int);
            *(static_cast <int*> (p.value))=stoi(linee[i]);
        }
        vars.push_back(p);
    }
 
    if(linee[0] == "comma")
    {
        int i = 0;
        var p;
        p.type = linee[i];
        ++i;
        p.name = linee[i];
         ++i;
        if(linee[i] == "=")
        {
            ++i;
            p.value=static_cast<void*>(new double);
            *(static_cast<double*>(p.value))=stod(linee[i]);
        }
        vars.push_back(p);
    }
 
    if(linee[0] == "sym")
    {
        int i = 0;
        var p;
        p.type = linee[i];
        ++i;
        p.name = linee[i];
        ++i;
        if(linee[i] == "=")
        {
            ++i;
            p.value = static_cast<void*>(new std::string);
            *(static_cast<std::string*>(p.value)) = (linee[i].substr(1,(linee[i].length()-2)));
        }
        vars.push_back(p);
    }
 
    if(linee[0] == "logic")
    {
        int i = 0;
        var p;
        p.type = linee[i];
        ++i;
        p.name = linee[i];
        ++i;
        if(linee[i] == "=")
        {
            ++i;
            if(linee[i] == "true")
            {
                p.value = static_cast <void*> (new bool);
                *(static_cast <bool*>(p.value)) = true;
            }
            else
            {
                p.value = static_cast <void*>(new bool);
                *(static_cast <bool*>(p.value)) = false;
            }
        }
        vars.push_back(p);
    }
}
 
void output(std::vector <std::string>& linee)
{
    for(int i = 0; i < linee.size(); ++i)
    {
        if(linee[i] == ";")
        {
            break;
        }
 
        if(linee[i] == "<<")
        {
            ++i;
        }
        
        for(int j = 0; j < vars.size(); ++j)
        {
            if(linee[i] == vars[j].name)
            {
                if(vars[j].type == "round")
                {
                    std::cout << *(static_cast <int*> (vars[j].value)) << std::endl;
                }
                else if(vars[j].type == "comma")
                {
                    std::cout << *(static_cast <double*> (vars[j].value)) << std::endl;
                }
                else if(vars[j].type == "sym")
                {
                    std::cout << *(static_cast <std::string*> (vars[j].value)) << std::endl;;
                }
                else if(vars[j].type == "logic")
                {
                    std::cout << *(static_cast <bool*> (vars[j].value)) << std::endl;
                }
                break;
            }
        }
    }
}
 
int int_operators(std::string sym, std::string a, std::string b) 
{
    if(sym == "+") 
    {
        for(int i = 0; i < vars.size(); ++i) 
        {
            for(int j = 0; j < vars.size(); ++j) 
            {
                if(vars[i].name == a && vars[j].name == b) 
                {
                    int x = *(static_cast<int*> (vars[i].value));
                    int y = *(static_cast<int*> (vars[j].value));
                    return x + y;
                }
            }
        }
    }
    if(sym == "-") 
    {
        for(int i = 0; i < vars.size(); ++i) 
        {
            for(int j = 0; j < vars.size(); ++j) 
            {
                if(vars[i].name == a && vars[j].name == b) 
                {
                    int x = *(static_cast<int*> (vars[i].value));
                    int y = *(static_cast<int*> (vars[j].value));
                    return x - y;
                }
            }
        }
    }
    if(sym == "*") 
    {
        for(int i = 0; i < vars.size(); ++i) 
        {
            for(int j = 0; j < vars.size(); ++j) 
            {
                if(vars[i].name == a && vars[j].name == b) 
                {
                    int x = *(static_cast<int*> (vars[i].value));
                    int y = *(static_cast<int*> (vars[j].value));
                    return x * y;
                }
            }
        }   
    }
    if(sym == "/") 
    {
        for(int i = 0; i < vars.size(); ++i) 
        {
            for(int j = 0; j < vars.size(); ++j) 
            {
                if(vars[i].name == a && vars[j].name == b) 
                {
                    int x = *(static_cast<int*> (vars[i].value));
                    int y = *(static_cast<int*> (vars[j].value));
                    return x / y;
                }
            }    
        }
    }
    if(sym == "%") 
    {
        for(int i = 0; i < vars.size(); ++i) 
        {
            for(int j = 0; j < vars.size(); ++j) 
            {
                if(vars[i].name == a && vars[j].name == b) 
                {
                    int x = *(static_cast<int*> (vars[i].value));
                    int y = *(static_cast<int*> (vars[j].value));
                    return x % y;
                }
            }    
        }
    }
}

double double_operators(std::string sym, std::string a, std::string b) 
{
    if(sym == "+") 
    {
        for(int i = 0; i < vars.size(); ++i)
        {
            for(int j = 0; j < vars.size(); ++j) 
            {
                if(vars[i].name == a && vars[j].name == b) 
                {
                    double x = *(static_cast<double*> (vars[i].value));
                    double y = *(static_cast<double*> (vars[j].value));
                    return x + y;
                }
            }    
        }
    }
    if(sym == "-") 
    {
        for(int i = 0; i < vars.size(); ++i) 
        {
            for(int j = 0; j < vars.size(); ++j) 
            {
                if(vars[i].name == a && vars[j].name == b) 
                {
                    double x = *(static_cast<double*> (vars[i].value));
                    double y = *(static_cast<double*> (vars[j].value));
                    return x - y;
                }
            }    
        }
    }
    if(sym == "*")
    {
        for(int i = 0; i < vars.size(); ++i) 
        {
            for(int j = 0; j < vars.size(); ++j)
            {
                if(vars[i].name == a && vars[j].name == b) 
                {
                    double x = *(static_cast<double*> (vars[i].value));
                    double y = *(static_cast<double*> (vars[j].value));
                    return x * y;
                }
            }
        }
    }
    if(sym =="/")
    {
        for(int i = 0; i < vars.size(); ++i) 
        {
            for(int j = 0; j < vars.size(); ++j) 
            {
                if(vars[i].name == a && vars[j].name == b) 
                {
                    double x = *(static_cast<double*> (vars[i].value));
                    double y = *(static_cast<double*> (vars[j].value));
                    return x / y;
                }
            }
        }
    }
}

std::string sym_operators(std::string a, std::string b)
{
    for (int i = 0; i < vars.size(); ++i)
    {
        for (int j = 0; j < vars.size(); ++j)
        {
            if (vars[i].name == a && vars[j].name == b)
            {
                std::string x = *(static_cast<std::string*> (vars[i].value));
                std::string y = *(static_cast<std::string*> (vars[j].value));
                return x + y;
            }
        }
    }
}

bool logic_operators(std::string sym, std::string a, std::string b)
{
    if(sym == "&&") 
    {
        for(int i = 0; i < vars.size(); ++i) 
        {
            for(int j = 0; j < vars.size(); ++j) 
            {
                if(vars[i].name == a && vars[j].name == b) 
                {
                    bool x = *(static_cast<bool*> (vars[i].value));
                    bool y = *(static_cast<bool*> (vars[j].value));
                    return x && y;
                }
            }
        }
    }
    else if(sym == "||") 
    {
        for(int i = 0; i < vars.size(); ++i) 
        {
            for(int j = 0; j < vars.size(); ++j) 
            {
                if((vars[i].name == a && vars[j].name == b)) 
                {
                    bool x = *(static_cast<bool*> (vars[i].value));
                    bool y = *(static_cast<bool*> (vars[j].value));
                    return x || y;
                }
            }
        }
    }
    else if(sym == "<") 
    {
        for(int i = 0; i < vars.size(); ++i) 
        {
            for (int j = 0; j < vars.size(); ++j) 
            {
                if((vars[i].name == a && vars[j].name == b) && (vars[i].type == "round")) 
                {
                    int x = *(static_cast<int*> (vars[i].value));
                    int y = *(static_cast<int*> (vars[j].value));
                    return x < y;
                }
                else if((vars[i].name == a && vars[j].name == b) && (vars[i].type == "comma"))
                {
                    double x = *(static_cast<double*> (vars[i].value));
                    double y = *(static_cast<double*> (vars[j].value));
                    return x < y;
                }
            }
        }
    }
    else if(sym == ">") 
    {
        for(int i = 0; i < vars.size(); ++i) 
        {
            for(int j = 0; j < vars.size(); ++j) 
            {
                if((vars[i].name == a && vars[j].name == b) && (vars[i].type == "round")) 
                {
                    int x = *(static_cast<int*> (vars[i].value));
                    int y = *(static_cast<int*> (vars[j].value));
                    return x > y;
                }
                else if((vars[i].name == a && vars[j].name == b) && (vars[i].type == "comma"))
                {
                    double x = *(static_cast<double*> (vars[i].value));
                    double y = *(static_cast<double*> (vars[j].value));
                    return x > y;
                }
            }
        }
    }
    else if(sym == "==") 
    {
        for(int i = 0; i < vars.size(); ++i) 
        {
            for(int j = 0; j < vars.size(); ++j) 
            {
                if ((vars[i].name == a && vars[j].name == b) && (vars[i].type == "round"))
                {
                    int x = *(static_cast<int*> (vars[i].value));
                    int y = *(static_cast<int*> (vars[j].value));
                    return x == y;
                }
                else if ((vars[i].name == a && vars[j].name == b) && (vars[i].type == "comma"))
                {
                    double x = *(static_cast<double*> (vars[i].value));
                    double y = *(static_cast<double*> (vars[j].value));
                    return x == y;
                }
                else if ((vars[i].name == a && vars[j].name == b) && (vars[i].type == "sym")) 
                {
                    std::string x = *(static_cast<std::string*> (vars[i].value));
                    std::string y = *(static_cast<std::string*> (vars[j].value));
                    return x == y;
                }
                else if ((vars[i].name == a && vars[j].name == b) && (vars[i].type == "logic")) 
                {
                    bool x = *(static_cast<bool*> (vars[i].value));
                    bool y = *(static_cast<bool*> (vars[j].value));
                    return x == y;
                }
            }
        }
    }
    else if(sym == "!=") 
    {
        for(int i = 0; i < vars.size(); ++i) 
        {
            for(int j = 0; j < vars.size(); ++j) 
            {
                if ((vars[i].name == a && vars[j].name == b) && (vars[i].type == "round"))
                {
                    int x = *(static_cast<int*> (vars[i].value));
                    int y = *(static_cast<int*> (vars[j].value));
                    return x != y;
                }
                else if ((vars[i].name == a && vars[j].name == b) && (vars[i].type == "comma"))
                {
                    double x = *(static_cast<double*> (vars[i].value));
                    double y = *(static_cast<double*> (vars[j].value));
                    return x != y;
                }
                else if ((vars[i].name == a && vars[j].name == b) && (vars[i].type == "sym")) 
                {
                    std::string x = *(static_cast<std::string*> (vars[i].value));
                    std::string y = *(static_cast<std::string*> (vars[j].value));
                    return x != y;
                }
                else if ((vars[i].name == a && vars[j].name == b) && (vars[i].type == "logic")) 
                {
                    bool x = *(static_cast<bool*> (vars[i].value));
                    bool y = *(static_cast<bool*> (vars[j].value));
                    return x != y;
                }
            }
        }
    }
}

void operation(std::vector <std::string>& linee) 
{
    for(int i = 0; i < vars.size(); ++i) 
    {
        if(vars[i].name == linee[0]) 
        {
            if(vars[i].type == "round") 
            {
                if(linee[3] == "+" || linee[3] == "-" || linee[3] == "*" || linee[3] == "/") 
                {
                    *(static_cast<int*> (vars[i].value)) = int_operators(linee[3], linee[2], linee[4]);
                }
            }
            else if(vars[i].type == "comma") 
            {
                if(linee[3] == "+" || linee[3] == "-" || linee[3] == "*" || linee[3] == "/")
                {
                    *(static_cast<double*> (vars[i].value)) = double_operators(linee[3], linee[2], linee[4]);
                }
            }
            else if(vars[i].type == "sym") 
            {
                if(linee[3] == "+") 
                {
                    *(static_cast<std::string*> (vars[i].value)) = sym_operators(linee[2], linee[4]);
                }
            }
            else if(vars[i].type == "logic") 
            {
                if(linee[2] == "!") 
                {
                    for(int j = 0; j < vars.size(); ++j) 
                    {
                        if (vars[j].name == linee[3]) 
                        {
                            *(static_cast<bool*> (vars[i].value)) = !(*(static_cast<bool*> (vars[j].value)));
                            std::cout << *(static_cast<bool*> (vars[i].value));
                        }
                    }
                }
                else if(linee[3] == "&&" || linee[3] == "||" || linee[3]== ">" || linee[3]== "<" || linee[3] == "==" || linee[3] == "!=")
                {
                    *(static_cast <bool*> (vars[i].value)) = logic_operators(linee[3], linee[2], linee[4]);
                }
            }
        }
    }
}

void condition(std::vector<std::string>& linee) 
{
    int i = 1;
    while(linee[i] != ")") 
    {
        if(linee[i] == "(") 
        {
            ++i;
        }
        vec.push_back(linee[i]);
        ++i;
    }
    do_condition(vec);
}

bool do_condition(std::vector<std::string>& vec) 
{
    bool ret = false;
    if(vec.size() == 1) 
    {
        for(int i = 0; i < vars.size(); ++i) 
        {
            if(vars[i].name == vec[0] && vars[i].type == "logic") 
            {
                if(*(static_cast<bool*>(vars[i].value)) == true) 
                {
                    return true;
                }
                else 
                {
                    return false;
                }
            }
        }
    }
    else if(vec.size() == 3) 
    {
        ret = logic_operators(vec[1], vec[0], vec[2]);
        if(ret == true) 
        {
            return true;
        }
        else 
        {
            return false;
        }
    }
}

int main()
{
    std::ifstream file;
    std::string word;
    file.open("as.txt");
        if(file.is_open())
        read(file);
        else
        {
        std::cout << "Failed to open the text file"<<std::endl;
        }
        file.close();
        std::cout << vars[0].name << "=" << *(static_cast<int*>(vars[0].value)) << std::endl;
        std::cout << vars[1].name<< "=" << *(static_cast<double*>(vars[1].value)) << std::endl;
        std::cout << vars[2].name<< "=" << *(static_cast<std::string*>(vars[2].value)) << std::endl;
        std::cout << vars[3].name<< "=" << *(static_cast<bool*>(vars[3].value)) << std::endl;
}