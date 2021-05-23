#include "Category.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <exception>
#include "Terminal.h"
#include <chrono>
#include <cstdlib>
#include <time.h>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using namespace std;
using namespace chrono;

vector<pair<double, bool>> grandList;

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
        int i = 0;
        throw i;
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
    cout << "\t5 to Quit" << endl;
}

void printCategory(vector<category *> &fullList)
{
    for (unsigned i = 0; i < fullList.size(); i++)
    {
        cout << i << " " << fullList[i]->getCategory() << "{";
        vector<string> copyOfSet = fullList[i]->getSet();
        for (unsigned i = 0; i < copyOfSet.size(); i++)
        {
            cout << " " << copyOfSet[i];
        }
        cout << "}" << endl;
    }
}

void printCategory(vector<category *> &fullList, int k)
{

    for (unsigned i = k; i < fullList.size(); i++)
    {
        cout << i << " " << fullList[i]->getCategory() << "{";
        vector<std::pair<string, char>> copyOfSet = fullList[i]->getColorSet();
        for (unsigned i = 0; i < copyOfSet.size(); i++)
        {
            char chosenColor = copyOfSet[i].second;
            switch (chosenColor)
            {
            case 'B':
                Terminal::color_fg(false, Terminal::BLUE);

                break;
            case 'G':
                Terminal::color_fg(false, Terminal::GREEN);

                break;
            case 'U':
                Terminal::color_fg(false, Terminal::YELLOW);
                break;
            case 'C':
                Terminal::color_fg(false, Terminal::RED);

                break;
            default:
                Terminal::color_fg(false, Terminal::WHITE);
            }
            cout << " " << copyOfSet[i].first;
            Terminal::color_fg(false, Terminal::WHITE);
        }
        cout << "}" << endl;
    }
}

void removeElement(vector<string> &input, string word)
{
    for (unsigned i = 0; i < input.size(); i++)
    {
        if (input[i] == word)
        {
            input.erase(input.begin() + i);
        }
    }
}
void removeElement(vector<std::pair<string, char>> &input, string word)
{
    for (unsigned i = 0; i < input.size(); i++)
    {
        if (input[i].first == word)
        {
            input.erase(input.begin() + i);
        }
    }
}

void printVector(vector<string> input)
{

    int i = 0;
    //cout << input.size() << endl;
    while (input.size() != 0)
    {
        int getRandom = (int)(input.size() * (rand() / (RAND_MAX + 1.0)));
        cout << input[getRandom];
        for (int i = input[getRandom].length(); i < 20; i++)
        {
            cout << " ";
        }
        input.erase(input.begin() + getRandom);
        i++;
        if (i % 5 == 0)
        {
            cout << "\n";
        }
    }
    cout << endl;
}
void printVector(vector<std::pair<string, char>> input)
{

    int i = 0;
    //cout << input.size() << endl;
    while (input.size() != 0)
    {
        int getRandom = (int)(input.size() * (rand() / (RAND_MAX + 1.0)));
        char chosenColor = input[getRandom].second;
        switch (chosenColor)
        {
        case 'B':
            Terminal::color_fg(false, Terminal::BLUE);

            break;
        case 'G':
            Terminal::color_fg(false, Terminal::GREEN);

            break;
        case 'U':
            Terminal::color_fg(false, Terminal::YELLOW);
            break;
        case 'C':
            Terminal::color_fg(false, Terminal::RED);

            break;
        default:
            Terminal::color_fg(false, Terminal::WHITE);
        }

        cout << input[getRandom].first;
        for (int i = input[getRandom].first.length(); i < 20; i++)
        {
            cout << " ";
        }
        input.erase(input.begin() + getRandom);
        i++;
        if (i % 5 == 0)
        {
            cout << "\n";
        }
        Terminal::color_fg(false, Terminal::WHITE);
    }

    cout << endl;
}

void printVector(std::pair<string, char> setOfArrangements[5][5])
{
    for (int row = 0; row < 5; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            char chosenColor = setOfArrangements[row][col].second;
            switch (chosenColor)
            {
            case 'B':
                Terminal::color_fg(false, Terminal::BLUE);

                break;
            case 'G':
                Terminal::color_fg(false, Terminal::GREEN);

                break;
            case 'U':
                Terminal::color_fg(false, Terminal::YELLOW);

                break;
            case 'C':
                Terminal::color_fg(false, Terminal::RED);

                break;
            default:
                Terminal::color_fg(false, Terminal::WHITE);
                Terminal::color_fg(false, Terminal::WHITE);
            }
            cout << setOfArrangements[row][col].first;
            for (int i = setOfArrangements[row][col].first.length(); i < 20; i++)
            {
                cout << " ";
            }
            Terminal::color_fg(false, Terminal::WHITE);
        }
        cout << endl;
    }
}

bool isCorrectSet(vector<category *> correctSet, vector<category *> gameSet, int k)
{

    for (unsigned i = k; i < gameSet.size(); i++)
    {
        cout << gameSet[i]->getColorSet().size() << endl;
        if (gameSet[i]->getColorSet().size() != 5)
        {
            cout << "ERROR: User put too many or too little inputs " << endl;
            return false;
        }
    }

    //cout << "FLAG 1" << endl;

    for (unsigned bigRow = 0; bigRow < correctSet.size(); bigRow++)
    {
        cout << "bigRow " << bigRow << endl;
        for (unsigned bigCol = 0; bigCol < correctSet[bigRow]->getColorSet().size(); bigCol++)
        {
            cout << "bigRow " << bigCol << endl;

            for (unsigned smallRow = 0; smallRow < gameSet.size(); smallRow++)
            {
                for (unsigned smallCol = 0; smallCol < gameSet[bigRow]->getSet().size(); smallCol++)
                {
                    if (gameSet[smallRow]->getColorSet().at(smallCol).first == correctSet[bigRow]->getSet().at(smallRow))
                    {
                        gameSet[smallRow]->getColorSet().erase(gameSet[smallRow]->getColorSet().begin() + smallCol);
                        // cout << "erasure " << endl;
                    }
                }
            }
        }
    }

    //cout << "FLAG 2" << endl;
    for (unsigned i = 0; i < gameSet.size(); i++)
    {
        cout << "sizing " << gameSet[i]->getCategory() << gameSet[i]->getColorSet().size() << endl;
        if (gameSet[i]->getColorSet().size() != 0)
        {
            return false;
        }
    }
    return true;
}

bool isCorrectSet(vector<category *> correctSet, vector<category *> gameSet)
{

    for (unsigned i = 0; i < gameSet.size(); i++)
    {

        if (gameSet[i]->getSet().size() != 5)
        {
            cout << "ERROR: User put too many or too little inputs " << endl;
            return false;
        }
    }

    //cout << "FLAG 1" << endl;
    for (unsigned i = 0; i < correctSet.size(); i++)
    {
        // cout << "Next set " << gameSet[i]->getCategory() << endl;
        for (unsigned k = 0; k < gameSet[i]->getSet().size(); k++)
        {
            // cout << "Word " << gameSet[i]->getSet().at(k) << endl;
            for (unsigned w = 0; w < correctSet[i]->getSet().size(); w++)
            {
                if (gameSet[i]->getSet().at(k) == correctSet[i]->getSet().at(w))
                {
                    gameSet[i]->getSet().erase(gameSet[i]->getSet().begin() + k);
                    k--;
                    //  cout << "Erasure" << endl;
                    break;
                }
            }
        }
    }

    //cout << "FLAG 2" << endl;
    for (unsigned i = 0; i < gameSet.size(); i++)
    {
        //cout << "sizing " << gameSet[i]->getCategory() << gameSet[i]->getSet().size() << endl;
        if (gameSet[i]->getSet().size() != 0)
        {
            return false;
        }
    }
    return true;
}

char getColor(vector<std::pair<string, char>> &input, string word)
{
    for (unsigned i = 0; i < input.size(); i++)
    {
        if (input[i].first == word)
        {
            //cout << "Attempt value " << input[i].second << endl;
            return input[i].second;
        }
    }
    // cout << "No color " << endl;
    return 0;
}

void roundOne(vector<category *> &input)
{
    //add words
    vector<string> listOfWords;
    for (unsigned i = 0; i < input.size(); i++)
    {
        vector<string> copyOfSet = input[i]->getSet();
        //cout << "i value " << i << " size " << copyOfSet.size() << endl;
        for (int k = 0; k < 5; k++)
        {
            int getRandom = (int)(copyOfSet.size() * (rand() / (RAND_MAX + 1.0)));
            //cout << "random number " << getRandom << endl;

            listOfWords.push_back(copyOfSet[getRandom]);
            //cout<<"done push back"<<endl;
            copyOfSet.erase(copyOfSet.begin() + getRandom);

            //  cout << "round complete" << endl;
        }
    }
    vector<string> copyOfListWords = listOfWords;
    //cout << "flag 2" << endl;

    //game begins
    cout << "COMMANDS (Case Sensitive) For Round 1 - All texts are same color" << endl;
    cout << "\tTo add: 'A' <Word> <Category>" << endl;
    cout << "\tTo Remove: 'R' <Word> <Category>" << endl;
    cout << "\tTo Stop or Done Inputting: 'Q'" << endl;
    cout << "\tTo Help: 'H'" << endl;
    vector<category *> fullList;
    for (int i = 0; i < 4; i++)
    {
        fullList.push_back(new category(input[i]->getCategory()));
        cout << "\t" << (i) << " is " << input[i]->getCategory() << endl;
    }

    std::string userinput;
    cout << "CATEGORIES AND ITEMS SO FAR --------------------------------------------" << endl;
    printCategory(fullList);
    cout << "WORD BANK --------------------------------------------------------------" << endl;
    printVector(listOfWords);
    cout << "========================================================================" << endl;
    cout << "User input: ";
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
            cout << "CATEGORIES AND ITEMS SO FAR --------------------------------------------" << endl;
            printCategory(fullList);
            cout << "WORD BANK --------------------------------------------------------------" << endl;
            printVector(listOfWords);
            cout << "========================================================================" << endl;

            continue;
        }

        if (!(alpha >> word))
        {
            cout << "ERROR: Invalid Read Word" << endl;
            cout << "User input: ";

            continue;
        }
        if (!(alpha >> category))
        {
            cout << "ERROR: Bad Category Input" << endl;
            cout << "User input: ";

            continue;
        }
        if (!(category <= 3 && category >= 0))
        {
            cout << "ERROR: Invalid Category" << endl;
            cout << "User input: ";

            continue;
        }
        bool isFound = false;
        for (unsigned i = 0; i < copyOfListWords.size(); i++)
        {
            if (copyOfListWords[i] == word)
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
            if (!fullList[category]->remove(word, 1))
            {
                break;
            }
            listOfWords.push_back(word);

            break;
        case 'A':
        {
            bool isRepeat = false;
            for (unsigned i = 0; i < fullList[category]->getSet().size(); i++)
            {
                if (fullList[category]->getSet().at(i) == word)
                {
                    cout << "ERROR: Repeat word " << endl;
                    isRepeat = true;
                }
            }
            if (isRepeat)
            {
            }
            else
            {
                fullList[category]->addToSet(word);
                removeElement(listOfWords, word);
            }
        }
        break;

        default:
            cout << "BAD COMMAND" << endl;
        }
        if (listOfWords.size() == 0)
        {
            cout << "All Entries have been placed" << endl;

            break;
        }
        std::string userinput;
        cout << "CATEGORIES AND ITEMS SO FAR --------------------------------------------" << endl;
        printCategory(fullList);
        cout << "WORD BANK --------------------------------------------------------------" << endl;
        printVector(listOfWords);
        cout << "========================================================================" << endl;
        cout << "User input: ";

        userinput.clear();
    }
    auto end = high_resolution_clock::now();
    double time = duration_cast<seconds>(end - start).count();
    cout << "Completion time " << time << " seconds" << endl;
    if (isCorrectSet(input, fullList))
    {
        grandList.push_back(std::make_pair(time, true));
        cout << "Round ends with user successful attempt" << endl;
    }
    else
    {
        grandList.push_back(std::make_pair(time, false));
        cout << "Round ends with user unsuccessful attempt" << endl;
    }
    cout << "---------------------------------------------------------------" << endl;
}

void roundTwo(vector<category *> &input, vector<char> colors)
{
    //add words
    vector<std::pair<string, char>> listOfWords;
    for (unsigned i = 0; i < input.size(); i++)
    {
        vector<string> copyOfSet = input[i]->getSet();
        // cout << "i value " << i << " size " << copyOfSet.size() << endl;
        for (int k = 0; k < 5; k++)
        {
            int getRandomSetNumber = (int)(copyOfSet.size() * (rand() / (RAND_MAX + 1.0)));
            int getRandomColorNumber = (int)(colors.size() * (rand() / (RAND_MAX + 1.0)));

            //cout << "random number " << getRandomSetNumber << "\t" << getRandomColorNumber << endl;

            listOfWords.push_back(std::make_pair(copyOfSet[getRandomSetNumber], colors.at(getRandomColorNumber)));
            //cout<<"done push back"<<endl;
            copyOfSet.erase(copyOfSet.begin() + getRandomSetNumber);

            //  cout << "round complete" << endl;
        }
    }
    vector<std::pair<string, char>> copyOfListWords = listOfWords;

    //game begins
    cout << "COMMANDS (Case Sensitive) Round 2 - Random word color" << endl;
    cout << "\tTo add: 'A' <Word> <Category>" << endl;
    cout << "\tTo Remove: 'R' <Word> <Category>" << endl;
    cout << "\tTo Stop or Done Inputting: 'Q'" << endl;
    cout << "\tTo Help: 'H'" << endl;
    vector<category *> fullList;
    for (int i = 0; i < 4; i++)
    {
        fullList.push_back(new category(input[i]->getCategory()));
        cout << "\t" << (i) << " is " << input[i]->getCategory() << endl;
    }

    std::string userinput;
    cout << "CATEGORIES AND ITEMS SO FAR --------------------------------------------" << endl;
    printCategory(fullList, 0);
    cout << "WORD BANK --------------------------------------------------------------" << endl;
    printVector(listOfWords);
    cout << "========================================================================" << endl;

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
            cout << "CATEGORIES AND ITEMS SO FAR --------------------------------------------" << endl;
            printCategory(fullList, 0);
            cout << "WORD BANK --------------------------------------------------------------" << endl;
            printVector(listOfWords);
            cout << "========================================================================" << endl;

            continue;
        }
        if (!(alpha >> word))
        {
            cout << "ERROR: Invalid Read Word" << endl;
            cout << "User input: ";

            continue;
        }
        if (!(alpha >> category))
        {
            cout << "ERROR: Bad Category Input" << endl;
            cout << "User input: ";

            continue;
        }
        if (!(category <= 3 && category >= 0))
        {
            cout << "ERROR: Invalid Category" << endl;
            cout << "User input: ";

            continue;
        }
        bool isFound = false;
        for (unsigned i = 0; i < copyOfListWords.size(); i++)
        {
            if (copyOfListWords[i].first == word)
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
        {
            if (!fullList[category]->remove(word, 0))
            {
                break;
            }
            fullList[category]->remove(word, 1);
            listOfWords.push_back(std::make_pair(word, getColor(copyOfListWords, word)));
        }
        break;
        case 'A':
        {
            bool isRepeat = false;
            for (unsigned i = 0; i < fullList[category]->getSet().size(); i++)
            {
                if (fullList[category]->getSet().at(i) == word)
                {
                    cout << "ERROR: Repeat word " << endl;
                    isRepeat = true;
                }
            }
            if (isRepeat)
            {
            }
            else
            {
                fullList[category]->addToSet(word, getColor(listOfWords, word));
                fullList[category]->addToSet(word);

                removeElement(listOfWords, word);
            }
        }
        break;

        default:
            cout << "BAD COMMAND" << endl;
        }
        if (listOfWords.size() == 0)
        {
            cout << "All Entries have been placed" << endl;
            break;
        }
        std::string userinput;
        cout << "CATEGORIES AND ITEMS SO FAR --------------------------------------------" << endl;
        printCategory(fullList, 0);
        cout << "WORD BANK --------------------------------------------------------------" << endl;
        printVector(listOfWords);
        cout << "========================================================================" << endl;
        cout << "User input: ";

        userinput.clear();
    }
    auto end = high_resolution_clock::now();
    double time = duration_cast<seconds>(end - start).count();
    cout << "Completion time " << time << " seconds" << endl;
    if (isCorrectSet(input, fullList))
    {
        grandList.push_back(std::make_pair(time, true));
        cout << "Round ends with user successful attempt" << endl;
    }
    else
    {
        grandList.push_back(std::make_pair(time, false));
        cout << "Round ends with user unsuccessful attempt" << endl;
    }
    cout << "---------------------------------------------------------------" << endl;
}

void roundThree(vector<category *> &input, vector<char> colors)
{
    //add words
    vector<std::pair<string, char>> listOfWords;
    vector<char> globalSet;
    vector<char> copyoOfColors = colors;
    for (unsigned i = 0; i < input.size(); i++)
    {
        int getRandomSetNumber = 0;
        vector<string> copyOfSet = input[i]->getSet();
        //  cout << "i value " << i << " size " << copyoOfColors[i] << endl;
        // srand(time(0));
        // cout << "Colors size " << colors.size() << endl;
        int getRandomColor = (int)(colors.size() * (rand() / (RAND_MAX + 1.0)));
        //cout << "I value " << copyoOfColors[i] << "Random value " << colors[getRandomColor] << endl;
        if (colors[getRandomColor] == copyoOfColors[i] && colors.size() != 1)
        {
            i--;
            continue;
        }

        for (int k = 0; k < 5; k++)
        {

            //cout << "random number " << getRandomSetNumber << "\t" << getRandomColorNumber << endl;

            listOfWords.push_back(std::make_pair(copyOfSet[getRandomSetNumber], colors.at(getRandomColor)));
            //cout<<"done push back"<<endl;
            copyOfSet.erase(copyOfSet.begin() + getRandomSetNumber);
            getRandomSetNumber++;
            //  cout << "round complete" << endl;
        }
        globalSet.push_back(colors.at(getRandomColor));
       // cout << "Random value " << getRandomColor << endl;
        colors.erase(colors.begin() + getRandomColor);
    }
    vector<std::pair<string, char>> copyOfListWords = listOfWords;

    //game begins
    cout << "COMMANDS (Case Sensitive) Round 2 - Random word color" << endl;
    cout << "\tTo add: 'A' <Word> <Category>" << endl;
    cout << "\tTo Remove: 'R' <Word> <Category>" << endl;
    cout << "\tTo Stop or Done Inputting: 'Q'" << endl;
    cout << "\tTo Help: 'H'" << endl;
    vector<category *> fullList;
    for (int i = 0; i < 4; i++)
    {
        fullList.push_back(new category(input[i]->getCategory()));
        // cout << "\t" << (i) << " is " << input[i]->getCategory() << endl;
    }

    std::string userinput;
    cout << "CATEGORIES AND ITEMS SO FAR --------------------------------------------" << endl;
    printCategory(fullList, 0);
    cout << "WORD BANK --------------------------------------------------------------" << endl;
    printVector(listOfWords);
    cout << "========================================================================" << endl;

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
            cout << "CATEGORIES AND ITEMS SO FAR --------------------------------------------" << endl;
            printCategory(fullList, 0);
            cout << "WORD BANK --------------------------------------------------------------" << endl;
            printVector(listOfWords);
            cout << "========================================================================" << endl;

            continue;
        }

        if (!(alpha >> word))
        {
            cout << "ERROR: Invalid Read Word" << endl;
            cout << "User input: ";

            continue;
        }
        if (!(alpha >> category))
        {
            cout << "ERROR: Bad Category Input" << endl;
            cout << "User input: ";

            continue;
        }
        if (!(category <= 3 && category >= 0))
        {
            cout << "ERROR: Invalid Category" << endl;
            cout << "User input: ";

            continue;
        }
        bool isFound = false;
        for (unsigned i = 0; i < copyOfListWords.size(); i++)
        {
            if (copyOfListWords[i].first == word)
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
        {
            if (!fullList[category]->remove(word, 0))
            {
                break;
            }
            fullList[category]->remove(word, 1);
            listOfWords.push_back(std::make_pair(word, getColor(copyOfListWords, word)));
        }
        break;
        case 'A':
        {
            bool isRepeat = false;
            for (unsigned i = 0; i < fullList[category]->getSet().size(); i++)
            {
                if (fullList[category]->getSet().at(i) == word)
                {
                    cout << "ERROR: Repeat word " << endl;
                    isRepeat = true;
                }
            }
            if (isRepeat)
            {
            }
            else
            {
                fullList[category]->addToSet(word, getColor(listOfWords, word));
                fullList[category]->addToSet(word);

                removeElement(listOfWords, word);
            }
        }
        break;

        default:
            cout << "BAD COMMAND" << endl;
        }
        if (listOfWords.size() == 0)
        {
            cout << "All Entries have been placed" << endl;
            break;
        }
        std::string userinput;
        cout << "CATEGORIES AND ITEMS SO FAR --------------------------------------------" << endl;
        printCategory(fullList, 0);
        cout << "WORD BANK --------------------------------------------------------------" << endl;
        printVector(listOfWords);
        cout << "========================================================================" << endl;
        cout << "User input: ";

        userinput.clear();
    }

    auto end = high_resolution_clock::now();
    double time = duration_cast<seconds>(end - start).count();
    cout << "Completion time " << time << " seconds" << endl;
    if (isCorrectSet(input, fullList))
    {
        grandList.push_back(std::make_pair(time, true));
        cout << "Round ends with user successful attempt" << endl;
    }
    else
    {
        grandList.push_back(std::make_pair(time, false));
        cout << "Round ends with user unsuccessful attempt" << endl;
    }
    cout << "---------------------------------------------------------------" << endl;
}

void roundFour(vector<category *> &input, vector<char> colors)
{
    //add words
    vector<std::pair<string, char>> listOfWords;
    int getRandomColorNumber = 0;
    for (unsigned i = 0; i < input.size(); i++)
    {
        int getRandomSetNumber = 0;
        vector<string> copyOfSet = input[i]->getSet();
        // cout << "i value " << i << " size " << copyOfSet.size() << endl;
        for (int k = 0; k < 5; k++)
        {

            // cout << "random number " << getRandomSetNumber << "\t" << getRandomColorNumber << endl;

            listOfWords.push_back(std::make_pair(copyOfSet[getRandomSetNumber], colors.at(getRandomColorNumber)));
            //cout<<"done push back"<<endl;
            getRandomSetNumber++;
            //  cout << "round complete" << endl;
        }
        getRandomColorNumber++;
    }
    vector<std::pair<string, char>> copyOfListWords = listOfWords;

    //game begins
    cout << "COMMANDS (Case Sensitive) Round 2 - Random word color" << endl;
    cout << "\tTo add: 'A' <Word> <Category>" << endl;
    cout << "\tTo Remove: 'R' <Word> <Category>" << endl;
    cout << "\tTo Stop or Done Inputting: 'Q'" << endl;
    cout << "\tTo Help: 'H'" << endl;
    vector<category *> fullList;
    for (int i = 0; i < 4; i++)
    {
        fullList.push_back(new category(input[i]->getCategory()));
        cout << "\t" << (i) << " is " << input[i]->getCategory() << endl;
        //cout << input[i]->getColorSet().size() << endl;
    }

    std::string userinput;
    cout << "CATEGORIES AND ITEMS SO FAR --------------------------------------------" << endl;
    printCategory(fullList, 0);
    cout << "WORD BANK --------------------------------------------------------------" << endl;
    printVector(listOfWords);
    cout << "========================================================================" << endl;

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
            cout << "CATEGORIES AND ITEMS SO FAR --------------------------------------------" << endl;
            printCategory(fullList, 0);
            cout << "WORD BANK --------------------------------------------------------------" << endl;
            printVector(listOfWords);
            cout << "========================================================================" << endl;

            continue;
        }

        if (!(alpha >> word))
        {
            cout << "ERROR: Invalid Read Word" << endl;
            cout << "User input: ";

            continue;
        }
        if (!(alpha >> category))
        {
            cout << "ERROR: Bad Category Input" << endl;
            cout << "User input: ";

            continue;
        }
        if (!(category <= 3 && category >= 0))
        {
            cout << "ERROR: Invalid Category" << endl;
            cout << "User input: ";

            continue;
        }
        bool isFound = false;
        for (unsigned i = 0; i < copyOfListWords.size(); i++)
        {
            if (copyOfListWords[i].first == word)
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
        {
            if (!fullList[category]->remove(word, 0))
            {
                break;
            }
            fullList[category]->remove(word, 1);
            listOfWords.push_back(std::make_pair(word, getColor(copyOfListWords, word)));
        }
        break;
        case 'A':
        {
            bool isRepeat = false;
            for (unsigned i = 0; i < fullList[category]->getSet().size(); i++)
            {
                if (fullList[category]->getSet().at(i) == word)
                {
                    cout << "ERROR: Repeat word " << endl;
                    isRepeat = true;
                }
            }
            if (isRepeat)
            {
            }
            else
            {
                fullList[category]->addToSet(word, getColor(listOfWords, word));
                fullList[category]->addToSet(word);

                removeElement(listOfWords, word);
            }
        }
        break;

        default:
            cout << "BAD COMMAND" << endl;
        }
        if (listOfWords.size() == 0)
        {
            cout << "All Entries have been placed" << endl;
            break;
        }
        std::string userinput;
        cout << "CATEGORIES AND ITEMS SO FAR --------------------------------------------" << endl;
        printCategory(fullList, 0);
        cout << "WORD BANK --------------------------------------------------------------" << endl;
        printVector(listOfWords);
        cout << "========================================================================" << endl;
        cout << "User input: ";

        userinput.clear();
    }
    auto end = high_resolution_clock::now();
    double time = duration_cast<seconds>(end - start).count();
    cout << "Completion time " << time << " seconds" << endl;
    // cout << fullList.at(0)->getColorSet().size() << endl;
    if (isCorrectSet(input, fullList))
    {
        grandList.push_back(std::make_pair(time, true));
        cout << "Round ends with user successful attempt" << endl;
    }
    else
    {
        grandList.push_back(std::make_pair(time, false));
        cout << "Round ends with user unsuccessful attempt" << endl;
    }
    cout << "---------------------------------------------------------------" << endl;
}

void startMenu()
{
    cout << "Do you want to start? [Y/N] Case Sensitive: ";
    string roundInput;
    while (getline(cin, roundInput))
    {
        if (roundInput.empty())
        {
            continue;
        }
        if (roundInput == "Y")
        {
            break;
        }
    }
}

int main()
{
    std::cout << "MindHive Program V 1.2.0 BETA" << endl;

    vector<char> colors;
    colors.push_back('B');
    colors.push_back('C');
    colors.push_back('G');
    colors.push_back('U');

    vector<category *> workingSet;
    try
    {
        workingSet = loadSet();
    }
    catch (int l)
    {
        if (l == 0)
        {
            cout << "Program is unable to start";
            return 1;
        }
    }
 //   printRoundPrompt();
    
    vector<int> sequence;
    sequence.push_back(0);
    sequence.push_back(1);
    sequence.push_back(2);
    sequence.push_back(3);

    for (int i = 0; i < 4; i++)
    {
        int randIndex = (int)(sequence.size() * (rand() / (RAND_MAX + 1.0)));
        int getRandom = sequence.at(randIndex);
        cout << "COMMANDS (Case Sensitive) These works for all rounds" << endl;
        cout << "\tTo add: 'A' <Word> <Category>" << endl;
        cout << "\tTo Remove: 'R' <Word> <Category>" << endl;
        cout << "\tTo Stop or Done Inputting: 'Q'" << endl;
        cout << "\tTo Help: 'H'" << endl;
        switch (getRandom)
        {
        case 0:
            cout << "You're about to start ROUND 1 - Words of Same Color. ";
            startMenu();
            roundOne(workingSet);
            break;
        case 1:
            cout << "You're about to start ROUND 2 - Words of Random Different Colors. ";
            startMenu();
            roundTwo(workingSet, colors);
            break;
        case 2:
            cout << "You're about to start ROUND 3 - Words of With Wrong Color Category. ";
            startMenu();
            roundThree(workingSet, colors);
            break;
        case 3:
            cout << "You're about to start ROUND 4 - Words of Correct Color Category. ";
            startMenu();
            roundFour(workingSet, colors);
            break;
        }
        sequence.erase(sequence.begin() + randIndex);
    }
    cout << "========================================================================" << endl;

    cout << "Here are your results " << endl;
    //cout << " PLEASE SEND YOUR RESULTS TO GRACE INCLUDING EACH ROUND'S TIME AND COMPLETIONS STATUS. DO NOT ATTEMPT TO COPY THE RESULTS FROM THE TERMINAL, JUST TYPE THEM OUT IN AN EMAIL AND SEND IT. " << endl;
    for (unsigned i = 0; i < grandList.size(); i++)
    {
        cout << "ROUND " << i << ": Time\t " << grandList[i].first << " Finished Successfully? [0-> no, 1->Yes] " << grandList[i].second << endl;
    }
    cout << "Program Completion" << endl;
    /*
    string roundInput;
    while (getline(cin, roundInput))
    {
        if (roundInput.empty())
        {
            continue;
        }

        stringstream omega(roundInput);
        int userChoice;
        omega >> userChoice;
        switch (userChoice)
        {
        case 1:
            roundOne(workingSet);
            break;
        case 2:
            roundTwo(workingSet, colors);
            break;
        case 3:
            cout << "called " << endl;
            roundThree(workingSet, colors);
            break;
        case 4:
            roundFour(workingSet, colors);
            break;
        case 5:
            return 0;
            break;
        default:
            cout << "ERROR: Invalid Menu Option" << endl;
        }

        printRoundPrompt();
    }
    */
    clearMemory(workingSet);
}