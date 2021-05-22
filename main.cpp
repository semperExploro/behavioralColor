#include "Category.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Terminal.h"
#include <chrono>
#include <cstdlib>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using namespace std;

using namespace chrono;

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
    cout << "\t100 to Quit" << endl;
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
    cout << "FLAG 1" << endl;
    for (unsigned i = 0; i < correctSet.size(); i++)
    {
        for (unsigned k = 0; k < gameSet[i]->getSet().size(); k++)
        {
            for (unsigned w = 0; w < correctSet[i]->getSet().size(); w++)
            {
                if (gameSet[i]->getSet().at(k) == correctSet[i]->getSet().at(w))
                {
                    gameSet[i]->getSet().erase(gameSet[i]->getSet().begin() + k);
                    cout << "Sizing " << gameSet[i]->getSet().size();
                    cout << "Erasure" << endl;
                }
            }
        }
    }

    cout << "FLAG 2" << endl;
    for (unsigned i = 0; i < gameSet.size(); i++)
    {
        cout << "sizing " << gameSet[i]->getSet().size() << endl;
        if (gameSet[i]->getSet().size() != 0)
        {
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
        //cout << "i value " << i << " size " << copyOfSet.size() << endl;
        for (int k = 0; k < 1; k++)
        {
            int getRandom = (int)(copyOfSet.size() * (rand() / (RAND_MAX + 1.0)));
            //cout << "random number " << getRandom << endl;

            listOfWords.push_back(copyOfSet[getRandom]);
            //cout<<"done push back"<<endl;
            copyOfSet.erase(copyOfSet.begin() + getRandom);
            //  cout << "round complete" << endl;
        }
    }

    //cout << "flag 2" << endl;

    //game begins
    cout << "COMMANDS" << endl;
    cout << "\tTo add: 'A' <Word> <Category>" << endl;
    cout << "\tTo Remove: 'R' <Word> <Category>" << endl;
    cout << "\tTo Stop or Done Inputting: Q" << endl;
    cout << "\tTo Help: H" << endl;
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

    auto start = high_resolution_clock::now();

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
            cout << "ERROR: Invalid command read" << endl;
        }
        if (command == 'Q')
        {
            cout << "Quitting" << endl;
            break;
        }
        if (command == 'H')
        {
            cout << "COMMANDS" << endl;
            cout << "\tTo add: 'A' <Word> <Category>" << endl;
            cout << "\tTo Remove: 'R' <Word> <Category>" << endl;
            cout << "\tTo Stop or Done Inputting: Q" << endl;
            cout << "\tTo Help: H" << endl;
            cout << "CATEGORIES AND ITEMS SO FAR ---------------------" << endl;
            printCategory(fullList);
            cout << "REMAINING WORDS ---------------------------------" << endl;
            cout << delta.str();
            cout << "=================================================" << endl;
            continue;
        }
        if (!(alpha >> word))
        {
            cout << "ERROR: Invalid Read Word" << endl;
            continue;
        }
        if (!(alpha >> category))
        {
            cout << "ERROR: Bad Category Input" << endl;
            continue;
        }
        if (!(category <= 3 && category >= 0))
        {
            cout << "ERROR: Invalid Category" << endl;
            continue;
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
            cout << "INVALID WORD: does not match any words in Remaining words list" << endl;
            continue;
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
            cout << "BAD COMMAND" << endl;
        }
        std::string userinput;
        cout << "CATEGORIES AND ITEMS SO FAR ---------------------" << endl;
        printCategory(fullList);
        cout << "REMAINING WORDS ---------------------------------" << endl;
        cout << delta.str();
        cout << "=================================================" << endl;
        userinput.clear();
    }
    auto end = high_resolution_clock::now();

    if (isCorrectSet(input, fullList))
    {
        cout << "Program ends with user successful attempt" << endl;
    }
    else
    {
        cout << "Program ends with user insuccessful attempt" << endl;
    }
    cout << "Completion time " << duration_cast<seconds>(end - start).count() << endl;
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
        case 100:
            return 0;
            break;
        default:
            cout << "ERROR: Invalid Menu Option" << endl;
        }
        printRoundPrompt();
    }

    clearMemory(workingSet);
}