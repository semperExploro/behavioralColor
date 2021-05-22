#include "Category.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Terminal.h"
#include <ctime>
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
    if (!myfile.good())
    {
        cout << "File is missing. Did you include the file 'words.txt' in the same folder as the mindHive.exe?" << endl;
    }
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

std::stringstream printVector(vector<string> input)
{
    std::stringstream alpha;
    int i = 0;
    //cout << input.size() << endl;
    while (input.size() != 0)
    {
        int getRandom = (int)(input.size() * (rand() / (RAND_MAX + 1.0)));
        alpha << input[getRandom] << "\t";
        input.erase(input.begin() + getRandom);
        i++;
        if (i % 5 == 0)
        {
            alpha << endl;
        }
    }
    return alpha;
}

bool isCorrectSet(vector<category *> correctSet, vector<category *> gameSet)
{
    for (unsigned i = 0; i < correctSet.size(); i++)
    {
        for (unsigned k = 0; k < gameSet[i]->getSet().size(); k++)
        {
            for (unsigned w = 0; w < correctSet[i]->getSet().size(); w++)
            {
                if (gameSet[i]->getSet().at(i) == correctSet[i]->getSet().at(w))
                {
                    gameSet[i]->getSet().erase(gameSet[i]->getSet().begin() + k);
                }
            }
        }
    }
    for (unsigned i = 0; i < correctSet.size(); i++)
    {
        if (correctSet[i]->getSet().size() != 0)
        {
            cout << "User defined set is wrong " << endl;
            return false;
        }
    }
    return true;
}

void roundOne(vector<category *> &input)
{
    //add words
    vector<string> listOfWords;
    for (unsigned i = 0; i < input.size(); i++)
    {
        vector<string> copyOfSet = input[i]->getSet();
        // cout<<"i value "<<i<<" size "<<copyOfSet.size()<<endl;
        for (int k = 0; k < 5; k++)
        {
            int getRandom = (int)(copyOfSet.size() * (rand() / (RAND_MAX + 1.0)));
            //  cout<<"random number "<<getRandom<<endl;

            listOfWords.push_back(copyOfSet[getRandom]);
            //cout<<"done push back"<<endl;
            copyOfSet.erase(copyOfSet.begin() + getRandom);
            // cout<<"round complete"<<endl;
        }
    }

    //cout << "flag 2" << endl;

    //game begins
    cout << "COMMANDS" << endl;
    cout << "\tTo add: 'A' <Word> <Category>" << endl;
    cout << "\tTo Remove: 'R' <Word> <Category>" << endl;
    cout << "\tTo Stop: Q" << endl;
    vector<category *> fullList;
    for (int i = 0; i < 4; i++)
    {
        fullList.push_back(new category(input[i]->getCategory()));
        cout << "\t" << (i) << " is " << input[i]->getCategory() << endl;
    }
    std::stringstream delta = printVector(listOfWords);

    std::string userinput;
    cout << "CATEGORIES AND ITEMS SO FAR ---------------------" << endl;
    printCategory(fullList);
    cout << "REMAINING WORDS ---------------------------------" << endl;
    cout << delta.str();
    cout << "=================================================" << endl;

    std::clock_t start;
    double duration;
    start = std::clock();

    while (getline(std::cin, userinput))
    {
        if (userinput.empty())
        {
            continue;
        }
        std::stringstream alpha(userinput);
        char command;
        string word;
        int category;
        if (!(alpha >> command))
        {
            cout << "Error: Invalid command read" << endl;
        }
        if (command == 'Q')
        {
            cout << "Quitting" << endl;
            break;
        }

        if (!(alpha >> word))
        {
            cout << "Error: Invalid read word" << endl;
        }
        if (!(alpha >> category))
        {
            cout << "Error: Bad number input" << endl;
        }
        if (!(category <= 3 && category >= 0))
        {
            cout << "number is out of bounds" << endl;
        }
        bool isFound = false;
        for (unsigned i = 0; i < listOfWords.size(); i++)
        {
            if (listOfWords[i] == word)
            {
                isFound = true;
            }
        }
        if (!isFound)
        {
            cout << "Invalid word, does not match any words in Remaining words list" << endl;
        }
        switch (command)
        {
        case 'R':
            fullList[category]->remove(word);
            break;
        case 'A':
            fullList[category]->addToSet(word);
            break;
        default:
            cout << "Bad command" << endl;
        }
        std::string userinput;
        cout << "CATEGORIES AND ITEMS SO FAR ---------------------" << endl;
        printCategory(fullList);
        cout << "REMAINING WORDS ---------------------------------" << endl;
        cout << delta.str();
        cout << "=================================================" << endl;
        userinput.clear();
    }
    duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;

    if (isCorrectSet(input, fullList))
    {
        cout << "Program ends with user successful attempt" << endl;
    }
    else
    {
        cout << "Program ends with user insuccessful attempt" << endl;
    }
    cout << "Duration " << duration << endl;
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