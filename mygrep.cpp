#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void increment1();
void increment2(int, char *[]);
void increment3(int, char *[]);

int main(int argc, char *argv[])
{

    if (argc == 1)
    {
        increment1();
    }

    if (argc == 3)
    {
        increment2(argc, argv);
    }

    if (argc == 4)
    {
        increment3(argc, argv);
    }

    // Lukee argc, jos cmd- syote yli 4 (tai == 2) argumenttia pitkä, tulostetaan ohje
    if (argc > 4 || argc == 2)
    {
        cerr << "\nUsage: mygrep keyword file\n";
        cerr << "\noptional: mygrep ('options') keyword file";
        cerr << "\n-olo -> Displays line numbers and number of occurences";
        cerr << "\n-ol  -> Displays only line numbers";
        cerr << "\n-oo  -> Displays only number of occurences\n";

        return 1;
    }

    return 0;
}

void increment1()
{
    //*--------inkrementti 1----------*//

    string inString;
    string searchStr;
    int lapcount = 0;

    cout << "Give a string from which to search from: ";
    getline(cin, inString);
    cout << "Give search string:";
    getline(cin, searchStr);

    // For- luuppi, joka luuppaa syotetyn string- muuttujan sisaltaman merkkimaaran verran
    // Jos ensimmaisen merkin vastaavuus loytyy, alkaa muuttuja lapcount kaymaan lapi seuraavia tulevia merkkeja
    // Kun taysi vastaavuus loydetty, nollataan lapcount tulevien vastaavuuksien varalle
    for (int i = 0; i < inString.size(); i++)
    {
        if (inString[i] != searchStr[lapcount])
        {
            lapcount = 0;
        }

        if (inString[i] == searchStr[lapcount])
        {
            lapcount++;
        }

        if (lapcount == searchStr.size())
        {
            cout << "Key " << searchStr << " found at slot " << (i - searchStr.size() + 1) << "\n";
            lapcount = 0;
        }
    }
}

void increment2(int argc, char *argv[])
{
    //*--------inkrementti 2----------*//
    // Luodaan muuttuja jolle sijoitetaan hakusana, avataan tiedosto ja luetaan sisalto
    // Jos tiedostoa ei saada auki, palauttaa errorin
    string keyword = argv[1];
    ifstream file(argv[2]);
    if (!file)
    {
        cerr << "Error opening file\n";
    }

    // Luodaan muuttuja johon sijoitetaan tiedoston tekstirivi
    // Luupataan lopetusehdolla -> 'niin pitkaan kun tekstia loytyy'
    // Jos ohjelma loytaa vastaavuuden, tulostetaan se naytolle
    // Npos -> maksimikoko size_t:eelle -> size_t on sizeof- operaattorin palauttama tyyppi
    //- toimii siis tarkastuksena tulostukselle
    string line;
    bool notFound = true;
    while (getline(file, line))
    {
        if (line.find(keyword) != string::npos)
        {
            cout << line << endl;
            notFound = false;
        }
    }
    if (notFound)
    {
        cout << "\nRequested keyword not found in this file\n";
    }
}

void increment3(int argc, char *argv[])
{
    //*--------inkrementti 3----------*//
    // Tata kommentoin vahemman, koska kayttaa samoja evaita kuin inkrementti kaksi

    string keyword = argv[1];
    string options = argv[2];
    ifstream file(argv[3]);

    if (!file)
    {
        cerr << "Error opening file\n";
    }

    string line;
    int occurences;       // options: -oo
    int row = 1;          // options: -ol
    bool notFound = true; // Jos haettu keyword ei löydy
    while (getline(file, line))
    {
        if (line.find(keyword) != string::npos)
        {
            if (options == "-oo")
                occurences++;

            if (options == "-ol")
                cout << row << ":    " << line << endl;

            if (options == "-olo")
            {
                occurences++;
                cout << row << ":    " << line << endl;
            }

            notFound = false;
        }
        row++; // Muuttuja tallentamaan läpikäydyt rivit.
    }
    if (notFound == false && options == "-olo" || options == "-oo")
    {
        cout << "\n\nThere were total of: " << occurences << " appearances of keyword: " << keyword << endl;
    }

    if (notFound)
    {
        cout << "\nRequested keyword not found in this file\n";
    }
}