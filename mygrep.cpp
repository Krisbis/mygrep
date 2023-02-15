#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

void increment1();
int increment2(int, char *[]);
int increment3_4(int, char *[]);

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
        increment3_4(argc, argv);
    }

    // Lukee argc, jos cmd- syote yli 4 (tai == 2) argumenttia pitkä, tulostetaan ohje
    if (argc > 4 || argc == 2)
    {
        cerr << "\nUsage: mygrep keyword file\n";
        cerr << "\noptional: mygrep ('options') keyword file";
        cerr << "\n-olo -> Displays line numbers and number of occurences";
        cerr << "\n-ol  -> Displays only line numbers";
        cerr << "\n-oo  -> Displays only number of occurences\n";
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
        }
    }
}

int increment2(int argc, char *argv[])
{
    //*--------inkrementti 2----------*//
    // Luodaan muuttuja jolle sijoitetaan hakusana, avataan tiedosto ja luetaan sisalto
    // Jos tiedostoa ei saada auki, palauttaa errorin
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
        cout << "\nRequested keyword not found in this file\n";
    }
    return 0;
}

int increment3_4(int argc, char *argv[])
{
    //*--------inkrementti 3----------*//
    //*--------inkrementti 4----------*//
    // Tata kommentoin vahemman, koska kayttaa samoja evaita kuin inkrementti kaksi
    // Tahan aliohjelmaan on myös sisallytetty viimeinen inkrementti
    // Viimeistä inkrementtia koskevat patkat ovat merkittynä ohjelman arviointia helpottamiseksi

    string keyword = argv[1];
    string options = argv[2];
    ifstream file(argv[3]);

    if (!file)
    {
        cerr << "Error opening file\n";
        return 1;
    }

    string line;
    int occurences;       // options: -oo
    int row = 1;          // options: -ol
    bool notFound = true; // Jos haettu keyword ei löydy

    while (getline(file, line))
    {
        // ↓↓-inkrementti4 -- case insenitiveness if chosen--↓↓
        //______________________________________________________//
        if (options == "-oi" || options == "-olori" || options == "oloi")
        {
            string lineLower = line;
            transform(lineLower.begin(), lineLower.end(), lineLower.begin(), ::tolower);
            string keywordLower = keyword;
            transform(keywordLower.begin(), keywordLower.end(), keywordLower.begin(), ::tolower);

            if (lineLower.find(keywordLower) != string::npos)
            {
                if (options == "-oi")
                    cout << lineLower << endl;

                if (options == "-olori")
                {
                    cout << row << ":   " << lineLower << endl;
                }
                if (options == "-oloi")
                {
                    occurences++;
                    cout << row << ":    " << lineLower << endl;
                }
                notFound = false;
            }
        }

        // ↓↓-inkrementti3 -- normal flow of options-↓↓
        //______________________________________________________//
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

    // Tulostetaan tulos luupin ulkopuolella -olo ja -oo vaihtoehdoille
    if (notFound == false && options == "-olo" || options == "-oo")
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
