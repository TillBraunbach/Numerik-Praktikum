#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Variablen
bool Entwicklerversion;
double Pr, A, B, C;
string Pfad;
string configDatei = "Config.txt";

void leseConfig(string dateiName){
    // Config öffnen
    ifstream datei(dateiName);

    // Prüfe ob die Config geöffnet werden kann, wenn nicht --> Fehlermeldung
    if (!datei) {
        cerr << "Fehler: " << dateiName << " konnte nicht geoeffnet werden." << endl;
        exit(1); // abbruch der funktion
    }

    // jede Zeile einlesen und ausgaben im Terminal 
    string zeile;
    while(getline(datei, zeile)){

        //Kommentare und leere Zeilen ignorieren, checken was die ersten zwei Zeichen einer Zeile sind, wenn dort // steht wird die Zeile ignoriert
        if (zeile.empty() || zeile.substr(0, 2) == "//") {
            continue;
        }

        int pos = zeile.find('='); // position des = finden
        string name = zeile.substr(0, pos - 1); // was vor dem = steht
        string wert = zeile.substr(pos + 2); // was nach dem = steht
        
        // Wert der passenden Variable zuordnen
        if (name == "Pfad") {
            Pfad = wert;
        }
        else if (name == "Entwicklerversion") {
            Entwicklerversion = (wert == "True");   // true, wenn in der Config "True" steht
        }
        else if (name == "Pr") {
            Pr = stod(wert);                        // Text zu Zahl durch stod
        }
        else if (name == "A") {
            A = stod(wert);
        }
        else if (name == "B") {
            B = stod(wert);
        }
        else if (name == "C") {
            C = stod(wert);
        }
        else {
            cerr << "Warnung: unbekannter Eintrag in Config: " << name << "\n";
        }
    }
}
void configAusgabe(){ //Funktion die die globelen Variabelen ausgibt die in der Config gespeichert waren zum testen
    cout << "Pfad: " << Pfad << endl;
    cout << "Entwicklerversion: " << Entwicklerversion << endl;
    cout << "Pr: " << Pr << endl;
    cout << "A: " << A << endl;
    cout << "B: " << B << endl;
    cout << "C: " << C << endl;
}
int main() {
    leseConfig(configDatei);
    configAusgabe();
    return 0; 
}