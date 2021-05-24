#include <ostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    ifstream myfile;
    ofstream output("bruteForce.txt");
    myfile.open("words.txt");
    std::string alpha;
    int i = 0;
    int k = -1;

    while (getline(myfile, alpha))
    {
        if (i % 15== 0)
        {
            output << "Y" << endl;
            k++;
            i++;
            continue;
        }
        if (alpha == "Water" || alpha == "Destruction" || alpha == "Plants" || alpha == "Animals")
        {
            continue;
        }
        output << "A " << alpha << " " << k << endl;
        i++;
    }
    myfile.close();
    output.close();
    return 0;
}