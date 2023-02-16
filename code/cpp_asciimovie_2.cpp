#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <vector>

using namespace std;

int main()
{
    ///////////////////////////////////////////////
    // Teil 1: Bilder aus Datei extrahieren

    // Dateiname einlesen
    string filename;
    cout << "Bitte Filmdatei angeben : ";
    cin >> filename;

    // Datei zum Lesen öffnen
    ifstream movie_data(filename);
    if (!movie_data.is_open())
    {
        cout << "Fehler beim Öffnen!" << endl;
        exit(1); // Programm mit Fehlercode beenden
    }

    // Datenstrukturen für Filmdaten
    string title;                  // Titel des Films
    string line;                   // eine Zeile
    vector<string> image;          // ein Bild
    vector<vector<string>> images; // eine Bilderserie

    // Filmdaten zeilenweise auslesen
    while (getline(movie_data, line))
    {
        // Titel extrahieren
        if (line[0] == '@') // Markierung für Titel
        {
            title = line.substr(1, line.size() - 1);
        }
        
        // Aktuelle Zeile in Bild speichern
        if (line[0] == '\"') // Markierung für Bilder
        {
            image.push_back(line);
        }

        // Fertiges Bild in Serie speichern
        if (line[0] == ' ' && image.size() > 0)
        {
            images.push_back(image); // Bild in Liste
            image.clear();           // Bild löschen
        }
    }
    movie_data.close();

    ///////////////////////////////////////////////
    // Teil 2:  Film-Statistiken ausgeben
    cout << "Filmtitel = " << title << endl;
    cout << "Anz. Bilder = " << images.size() << endl;
    int symbols{0}, lines{0};
    for (int i = 0; i < images.size(); i++)
    {
        // Anzahl Zeilen
        if (images[i].size() > lines)
        {
            lines = images[i].size(); // Maximum
        }

        // Anzahl Zeichen
        for (int j = 0; j < images[i].size(); j++)
        {
            symbols += images[i][j].size();
        }
    }
    cout << "Anzahl Zeilen / Bild = " << lines << endl;
    cout << "Anzahl Zeichen = " << symbols << endl;

    return 0;
}