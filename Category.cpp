#include "Category.h"
#include <string>
#include <vector>
#include <iostream>
#include "Terminal.h"

using std::string;
using std::vector;

category::category(std::string input)
{
    this->categoryName = input;
}

string category::getCategory()
{
    return this->categoryName;
}

void category::setColor(char input)
{
    this->color = input;
}

char category::getColor()
{
    return this->color;
}
void category::addToSet(string input)
{
    this->set.push_back(input);
}

void category::setTerminalColor()
{
    char chosenColor = this->getColor();
    switch (chosenColor)
    {
    case 'G':
        Terminal::color_fg(false, Terminal::GREEN);

        break;
    case 'Y':
        Terminal::color_fg(false, Terminal::YELLOW);

        break;
    case 'M':
        Terminal::color_fg(false, Terminal::MAGENTA);

        break;
    case 'C':
        Terminal::color_fg(false, Terminal::CYAN);

        break;
    default:
        Terminal::color_fg(false, Terminal::WHITE);
    }
}

category::~category(){
    
}

void category::printSet()
{
    std::cout << "Full List for " << this->getCategory() << std::endl;
    this->setTerminalColor();
    for (unsigned i = 0; i < this->set.size(); i++)
    {
        std::cout << this->set[i] << std::endl;
    }
    Terminal::set_default();
}

vector<string> category::getSet()
{
    return this->set;
}