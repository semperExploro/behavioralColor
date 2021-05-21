#include "Category.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Terminal.h"
#include <cstdlib>

using std::cout;
using std::endl;
using std::string;
using std::vector;

vector<category *> loadSet()
{
    vector<char> colors;
    colors.push_back('G');
    colors.push_back('Y');
    colors.push_back('M');
    colors.push_back('C');

    //load categories
    std::ifstream myfile;
    vector<category *> set;
    myfile.open("words.txt");
    for (unsigned i = 0; i < 4; i++)
    {
        string line;
        getline(myfile, line);
        category *newCategory = new category(line);
        newCategory->setColor(colors[i]);
        set.push_back(newCategory);
    }

    //load words
    string line;
    int thisSetName;

    while (getline(myfile, line))
    {
        bool isName = false;
        for (unsigned i = 0; i < set.size(); i++)
        {
            if (set[i]->getCategory() == line)
            {
                thisSetName = i;
                isName = true;
                continue;
            }
        }
        if (!isName)
        {
            set[thisSetName]->addToSet(line);
        }
    }
    return set;
}

void clearMemory(vector<category *> &input)
{
    for (int i = 0; i < 4; i++)
    {
        delete input[i];
    }
}

void printRoundPrompt()
{
    std::cout << "Please choose which round to play by typing in a number" << endl;
    cout << "\t1 for Round 1" << endl;
    cout << "\t2 for Round 2" << endl;
    cout << "\t3 for Round 3" << endl;
    cout << "\t4 for Round 4" << endl;
}

void printCategory(vector<category *> &fullList)
{
    for (unsigned i = 0; i < fullList.size(); i++)
    {
        cout << fullList[i]->getCategory() << "{";
        vector<string> copyOfSet = fullList[i]->getSet();
        for (unsigned i = 0; i < copyOfSet.size(); i++)
        {
            cout << " " << copyOfSet[i];
        }
        cout << "}" << endl;
    }
}

void printVector(vector<string> input)
{
    int i = 0;
    cout<<input.size()<<endl;
    while (input.size() != 0)
    {
        int getRandom = (int)(rand() * input.size());
        cout << input[getRandom] << "  ";
        input.erase(input.begin() + getRandom);
        i++;
        if (i % 5 == 0)
        {
            cout << endl;
        }
    }
}

void roundOne(vector<category *> &input)
{
    cout << "flag 1" << endl;
    //add words
    vector<string> listOfWords;
    for (unsigned i = 0;i< input.size(); i++)
    {
        vector<string> copyOfSet = input[i]->getSet();
       // cout<<"i value "<<i<<" size "<<copyOfSet.size()<<endl;
        for (int k= 0; k < 5; k++)
        {
            int getRandom = (int)(copyOfSet.size() * (rand() / (RAND_MAX + 1.0)));
          //  cout<<"random number "<<getRandom<<endl;
            
            listOfWords.push_back(copyOfSet[getRandom]);
            //cout<<"done push back"<<endl;
            copyOfSet.erase(copyOfSet.begin() + getRandom);
           // cout<<"round complete"<<endl;
        }
    }

    cout << "flag 2" << endl;

    //game begins
    cout << "DIRECTIONS type the word and the the category" << endl;
    cout << "\t for example Car 1 (given that 1 is transportation category)" << endl;
    vector<category *> fullList;
    for (int i = 0; i < 4; i++)
    {
        fullList.push_back(new category(input[i]->getCategory()));
        cout << "\t" << (i) << " is " << input[i]->getCategory() << endl;
    }
    std::string userinput;
    cout << "Categories and items so far" << endl;
    printCategory(fullList);
    cout << "Remaining words" << endl;
    printVector(listOfWords);
    while (std::cin >> userinput)
    {
        std::stringstream alpha(userinput);
        string word;
        int category;
        alpha >> word;
        alpha >> category;

        fullList[category]->addToSet(word);

        cout << "Categories and items so far" << endl;
        printCategory(fullList);
        cout << "Remaining words" << endl;
        printVector(listOfWords);
        userinput.clear();
    }

    printVector(listOfWords);
}

int main()
{
    vector<category *> workingSet = loadSet();

    printRoundPrompt();
    int roundInput;
    while (std::cin >> roundInput)
    {
        switch (roundInput)
        {
        case 1:
            roundOne(workingSet);
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        }
        printRoundPrompt();
    }

    clearMemory(workingSet);
}