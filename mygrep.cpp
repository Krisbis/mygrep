#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void increment1();

int main(int argc, char *argv[])
{
    if (argc <= 1 || argc >= 3)
    {
        increment1();
        break;
    }

    if (argv[1] == "following")
    {
        ifstream file(argv[2]);
        if (!file)
        {
            cerr << "Error opening file" << endl;
            return 1;
        }
        if (file)
        {
            // getline.
        }
        
    }
}

void increment1()
{
    string inString;
    string searchStr;
    int lapcount = 0;

    cout << "Give a string from which to search for: ";
    getline(cin, inString);
    cout << "Give search string:";
    getline(cin, searchStr);

    for (int i = 0; i < inString.size(); i++)
    {

        if (inString[i] == searchStr[lapcount])
        {
            lapcount++;
        }
        if (lapcount == searchStr.size())
        {
            cout << "Key " << searchStr << " found at slot " << i << "\n";
            lapcount = 0;
        }
        else
        {
            cout << "\nKeyword not found in given string"
        }
    }
}