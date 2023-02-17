#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

struct optionsStruct
{
    bool occurence = false;  // Number of occurences
    bool lineNumber = false; // Linenumbers
    bool reverse = false;    // deletion of the keyword containing line
    bool insens = false;     // case insensitiveness
};

void increment1();
int increment2(int, char *[]);
int increment3_4(int, char *[], optionsStruct);
void optionsCheck(string, optionsStruct &);

int main(int argc, char *argv[])
{
    optionsStruct method{false, false, false, false};

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
        increment3_4(argc, argv, method);
    }

    // Lukee argc, jos cmd- syote yli 4 (tai == 2) argumenttia pitkä, tulostetaan ohje
    if (argc > 4 || argc == 2)
    {
        cerr << "\nUsage: mygrep keyword file\n";
        cerr << "\noptional: mygrep ('options') keyword file";
        cerr << "\n-ol  -> Displays only line numbers";
        cerr << "\n-oo  -> Displays only number of occurences";
        cerr << "\n-oi  -> Displays only number of occurences (case-insensitive)";
        cerr << "\n-or  -> Displays every line that doesn't include the keyword";
    }
    return 0;
}

void increment1()
{
    //*--------inkrementti 1----------*//

    string inString;
    string searchStr;
    int lapcount = 0;
    bool found = false;

    cout << "Give a string from which to search from: ";
    getline(cin, inString);
    cout << "Give search string: ";
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
            found = true;
        }
    }
    if (!found)
    {
        cout << "search key: " << searchStr << " not found in: " << inString;
    }
    
}

int increment2(int argc, char *argv[])
{
    //*--------inkrementti 2----------*//
    // Luodaan muuttuja jolle sijoitetaan hakusana, avataan tiedosto ja luetaan sisalto
    // Jos tiedostoa ei saada auki syystä tai toisesta, palauttaa errorin
    string keyword = argv[1];
    ifstream file(argv[2]);
    if (!file)
    {
        cerr << "Error opening file\n";
        return -1;
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
        cout << "\nRequested keyword not found in this file 1\n";
    }
    return 0;
}

void optionsCheck(string option, optionsStruct &method)
{

    // Tama aliohjelma passaa increment3_4 aliohjelmalle tiedon millä metodeilla (options -o) kayttaja haluaa tulosteen
    // Sijoittaa siis structiin referenssillä totuusarvon, josta incement3_4 aliohjelma tarkastaa mitä tulostetta halutaan
    for (int i = 2; i < option.size(); i++)
    {
        if (option[i] == 'l')
        {
            method.lineNumber = true;
        }
        else if (option[i] == 'o')
        {
            method.occurence = true;
        }
        else if (option[i] == 'i')
        {
            method.insens = true;
        }

        else if (option[i] == 'r')
        {
            method.reverse = true;
        }
    }
}

int increment3_4(int argc, char *argv[], optionsStruct method)
{
    //*--------inkrementti 3----------*//
    //*--------inkrementti 4----------*//
    // Tata kommentoin vahemman, koska kayttaa samoja evaita kuin inkrementti kaksi
    // Tahan aliohjelmaan on myös sisallytetty viimeinen inkrementti
    // Viimeistä inkrementtia koskevat patkat ovat merkittynä ohjelman arviointia helpottamiseksi

    string option = argv[1];
    string keyword = argv[2];
    ifstream file(argv[3]);

    if (!file)
    {
        cerr << "Error opening file\n";
        return -1;
    }

    string line;
    int occurences = 0;   // options: -oo
    int row = 0;          // options: -ol
    bool notFound = true; // Jos haettu keyword ei löydy

    optionsCheck(option, method);

    while (getline(file, line))
    {
        row++; // Muuttuja tallentamaan läpikäydyt rivit.

        // ↓↓-inkrementti4 -- case insenitiveness if chosen--↓↓
        /*______________________________________________________*/
        if (method.insens)
        {
            transform(line.begin(), line.end(), line.begin(), ::tolower);
            transform(keyword.begin(), keyword.end(), keyword.begin(), ::tolower);
        }

        // ↓↓-inkrementti4 -- reverse if chosen--↓↓
        /*______________________________________________________*/
        if (method.reverse)
        {
            if (line.find(keyword) != string::npos)
            {
                notFound = false;
                occurences++;
                continue;
            }
            method.lineNumber ? cout << row << ":   " : cout << "";
            cout << line << endl;
        }

        // ↓↓-inkrementti3&4 -- normal flow of options-↓↓
        /*______________________________________________________*/
        if (line.find(keyword) != string::npos && !method.reverse)
        {
            // options: line numbers
            method.lineNumber ? cout << row << ":   " : cout << "";

            cout << line << endl;

            occurences++;
            notFound = false;
        }
    }

    // Tulostetaan tulos luupin ulkopuolella vaihtoehdoille joissa occurence valittuna
    if (!notFound && method.occurence)
    {
        cout << "\n\nThere were total of: " << occurences << " appearances of keyword: " << keyword << endl;
    }

    // Jos vastaavuuksia ei loydy, niin yksiselitteisesti notFound = true
    // Tarkistaa boolean muuttujan, ja luettujen rivien maaran
    // Jos luetut rivit > 1, tiedetaan että ohjelma pääsi käsiksi tiedostoon ja luki-
    //  sen sisallon loytamatta vastaavuuksia
    if (notFound == true && row > 1)
    {
        cout << "\nRequested keyword not found in this file\n";
    }
    return 0;
}