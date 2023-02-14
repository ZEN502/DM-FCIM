#include <iostream>
#include <string>
#include <iomanip>
//#include <stdlib.h>

#define ERROR_RETURN -2

using std::cout;
using std::cin;
using std::endl;
using std::string;


namespace trash{

enum class TYPE_GRAPH{
    AM_GRAPH = 1,
    IM_GRAPH = 2,
    IL_GRAPH = 3
};

enum class AM_GRAPH{
    FROM = -1,
    VOID = 0,
    TO = 1,
    CYCLE = 2,
};

enum class IM_GRAPH{
    VOID = 0,
    ARC = 1,
    CYCLE = 2,
    LINE = -999

};

bool is_int(const string& magic)
{
    size_t i = 0;
    while(magic[i])
    {
        if(!(magic[i] >= '0' && magic[i] <= '9' || magic[i] == ' ' || magic[i] == '-'))
            return false;
        ++i;
    }
    return true;
}

bool is_int_unsigned(const string& magic)
{
    size_t i = 0;
    while(magic[i])
    {
        if(!(magic[i] >= '0' && magic[i] <= '9' || magic[i] == ' '))
            return false;
        ++i;
    }
    return true;
}

int str_to_int(string& magic)
{
    size_t i = 0;
    bool is_positive = true;
    long long result = 0;
    while(magic[i] == ' ') i++;
    if(magic[i] == '-')
    {
        ++i;
        while(magic[i] != ' ' && magic[i])
        {
            result *= 10;
            result -= (int)magic[i] - (int)'0';
            ++i;
        }
    }
    else 
        while(magic[i] != ' ' && magic[i])
        {
            result *= 10;
            result += (int)magic[i] - (int)'0';
            ++i;
        }
    magic.erase(magic.cbegin(), magic.cbegin() + i);
    return (int)result;
}

int cin_number(unsigned int start, unsigned int end)
{
    if(end < start)
        return -1;
    string a;
    int result;
    do{
        try{
            getline(cin, a);
            result = std::stoi(a);
        }catch(std::exception e)
        {
            continue;
        }
        if(result >= start && result  <= end)
            return result;
        
    }while(1);
}

int cin_number(int start, int end, const char* baseQuestion)
{
    if(end < start)
        return -1;
    string a;
    int result;
    do{
        try{
            cout << endl << baseQuestion;
            getline(cin, a);
            result = std::stoi(a);
        }catch(std::exception e)
        {
            continue;
        }
        if(result >= start && result  <= end)
            return result;
        
    }while(1);
    
}

int cin_number(int start, int end, const char* baseQuestion, const char* wrongAnswerMessage)
{
    if(end < start)
        return -1;
    string a;
    int result;
    do{
        try{
            cout << endl << baseQuestion;
            getline(cin, a);
            result = std::stoi(a);
        }catch(std::exception e)
        {
            cout << endl << wrongAnswerMessage;
            continue;
        }
        if(result >= start && result  <= end)
            return result;
        
    }while(1);
}

    namespace text{

        void spam()
        {
            cout << "1. Adjacency Matrix \n"    //Матрица инцидентности
                 << "2. Identify Matrix \n"      //Матрица смежности
                 << "3. Identify List \n"        //Список смежности
                << endl;
        }
    }

}