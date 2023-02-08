#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
    string inputString;
    string inputSearch;
    int lapcount = 0;

    cout << "Give a string from which to search for: ";
    getline(cin, inputString);
    cout << "Give search string:";
    getline(cin, inputSearch);

    for (int i = 0; i < inputString.size(); i++)
    {
      
        if (inputString[i] == inputSearch[lapcount])
        {
            lapcount++;
        }
        if (lapcount == inputSearch.size())
        {
            cout << "Found at round " << i;
            break;
        }

    }

}