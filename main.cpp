#include "Category.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <exception>
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
            cout << "Attempt value " << input[i].second << endl;
            return input[i].second;
        }
    }
    cout << "No color " << endl;
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
    cout << "Your input: ";

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
            cout << "Your input: ";

            continue;
        }
        if (listOfWords.size() == 0)
        {
            cout << "All Entries have been placed" << endl;
            break;
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
        std::string userinput;
        cout << "CATEGORIES AND ITEMS SO FAR --------------------------------------------" << endl;
        printCategory(fullList);
        cout << "WORD BANK --------------------------------------------------------------" << endl;
        printVector(listOfWords);
        cout << "========================================================================" << endl;
        cout << "Your input: ";

        userinput.clear();
    }
    auto end = high_resolution_clock::now();

    if (isCorrectSet(input, fullList))
    {
        cout << "Program ends with user successful attempt" << endl;
    }
    else
    {
        cout << "Program ends with user unsuccessful attempt" << endl;
    }
    cout << "Completion time " << duration_cast<seconds>(end - start).count() << " seconds" << endl;
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
    cout << "Your input: ";

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
            cout << "Your input: ";

            continue;
        }
        if (listOfWords.size() == 0)
        {
            cout << "All Entries have been placed" << endl;
            break;
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
                removeElement(listOfWords, word);
            }
        }
        break;

        default:
            cout << "BAD COMMAND" << endl;
        }
        std::string userinput;
        cout << "CATEGORIES AND ITEMS SO FAR --------------------------------------------" << endl;
        printCategory(fullList, 0);
        cout << "WORD BANK --------------------------------------------------------------" << endl;
        printVector(listOfWords);
        cout << "========================================================================" << endl;
        cout << "Your input: ";

        userinput.clear();
    }
    auto end = high_resolution_clock::now();

    if (isCorrectSet(input, fullList))
    {
        cout << "Program ends with user successful attempt" << endl;
    }
    else
    {
        cout << "Program ends with user unsuccessful attempt" << endl;
    }
    cout << "Completion time " << duration_cast<seconds>(end - start).count() << " seconds" << endl;
    cout << "END OF ROUND -----------------------------------------------------------" << endl;
}

void roundThree(vector<category *> &input, vector<char> colors)
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
    int i = 0;
    std::pair<string, char> setOfArrangements[5][5];
    for (int row = 0; row < 5; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            setOfArrangements[row][col] = std::make_pair(listOfWords[i].first, listOfWords[i].second);
            i++;
        }
    }
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
    printVector(setOfArrangements);
    cout << "========================================================================" << endl;
    cout << "Your input: ";

    auto start = high_resolution_clock::now();
    cout << "Your input: ";

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
            printVector(setOfArrangements);
            cout << "========================================================================" << endl;
            cout << "Your input: ";

            continue;
        }
        if (listOfWords.size() == 0)
        {
            cout << "All Entries have been placed" << endl;
            break;
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
            //cout << "hello there" << endl;
            for (int row = 0; row < 4; row++)
            {
                for (int col = 0; col < 5; col++)
                {
                    cout << "COLOR VALUE " << getColor(copyOfListWords, word) << endl;
                    if (setOfArrangements[row][col].first == " " && getColor(copyOfListWords, word) == colors.at(row))
                    {
                        //u          cout << "Intervnetion " << endl;
                        setOfArrangements[row][col] = std::make_pair(word, colors.at(row));
                        break;
                    }
                }
            }
            listOfWords.push_back(std::make_pair(word, getColor(copyOfListWords, word)));
        }
        break;
        case 'A':
        {
            bool isRepeat = false;
            for (unsigned i = 0; i < fullList[category]->getColorSet().size(); i++)
            {
                if (fullList[category]->getColorSet().at(i).first == word)
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
                for (int row = 0; row < 5; row++)
                {
                    for (int col = 0; col < 5; col++)
                    {
                        if (setOfArrangements[row][col].first == word)
                        {
                            setOfArrangements[row][col].first = " ";
                        }
                    }
                }
                fullList[category]->addToSet(word, getColor(listOfWords, word));
                removeElement(listOfWords, word);
            }
        }
        break;

        default:
            cout << "BAD COMMAND" << endl;
        }
        std::string userinput;
        cout << "CATEGORIES AND ITEMS SO FAR --------------------------------------------" << endl;
        printCategory(fullList, 0);
        cout << "WORD BANK --------------------------------------------------------------" << endl;
        printVector(setOfArrangements);
        cout << "========================================================================" << endl;
        cout << "Your input: ";

        userinput.clear();
    }
    auto end = high_resolution_clock::now();

    if (isCorrectSet(input, fullList))
    {
        cout << "Program ends with user successful attempt" << endl;
    }
    else
    {
        cout << "Program ends with user unsuccessful attempt" << endl;
    }
    cout << "Completion time " << duration_cast<seconds>(end - start).count() << " seconds" << endl;
    cout << "END OF ROUND -----------------------------------------------------------" << endl;
}

int main()
{
    std::cout << "MindHive Program V 1.1.0 BETA" << endl;

    vector<char> colors;
    colors.push_back('G');
    colors.push_back('Y');
    colors.push_back('M');
    colors.push_back('c');

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

    printRoundPrompt();
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
            roundThree(workingSet, colors);
            break;
        case 4:
            break;
        case 5:
            return 0;
            break;
        default:
            cout << "ERROR: Invalid Menu Option" << endl;
        }
        printRoundPrompt();
    }

    clearMemory(workingSet);
}