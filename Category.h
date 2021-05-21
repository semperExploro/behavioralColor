#ifndef CATEGORY_H
#define CATEGORY_H
#include <string>
#include <vector>

using std::string;
using std::vector;

class category
{



public:
    ~category();
    category(std::string categoryName);
    string getCategory();
    char getColor();
    vector<string> getSet();
    void setTerminalColor();
    void addToSet(string input);
    void printSet();
    void setColor(char input);

private:
    string categoryName;
    char color;
    vector<string> set;
    
};

#endif 