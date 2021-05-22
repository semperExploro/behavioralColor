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
    bool remove(string input, int i) ;
    vector<string> &getSet();
    void setTerminalColor();
    void addToSet(string input);
    void printSet();
    void setColor(char input);
    void addToSet(string input, char color);
    vector<std::pair<string, char>> &getColorSet();
    char getColor();
private:
    string categoryName;
    char color;
    vector<string> set;
    vector<std::pair<string, char>> colorSet;
};

#endif