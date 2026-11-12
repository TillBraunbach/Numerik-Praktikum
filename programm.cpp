#include <iostream>
#include <fstream> // zum einlesen der config
#include <string>
#include <filesystem> // um den ordner zu durchsuchen etc
#include <vector>
#include <algorithm> // für sort() um den vektor der ordnernamen zu sortieren

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

        int pos = zeile.find('='); // position des = finden und in pos speichern
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
            Pr = stod(wert);                        // Text zu Zahl durch stod(sting to double)
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
            cerr << "Warnung: unbekannter Eintrag in Config: " << name << endl; //error wenn irgendwas in der Config steht was da nicht hingehört
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
void leseZeitordner(string ordnerPfad){
    vector<string> ordnerliste; // vector mit dem namen ordnerliste und dem datentype string 
    for (filesystem::directory_entry eintrag : filesystem::directory_iterator(ordnerPfad)){ //Nimmt jeden eintrag aus dem ordner einer nach dem anderen und nennt ihn eintrag
        string name = eintrag.path().filename().string(); //.path() nimmt den Pfad des Eintrags, .filename() nimmt nur den Name am ende des Pfads, .string() wandelt den Namen in ein string um der
        if(!isdigit(name[0])){ // checkt ob die erste stelle eine Zahl ist wenn nicht wird der eintraf übersprungen
            continue;
        }
        ordnerliste.push_back(name); //hängt den eintrag am ende der ordnerliste an 
    }
    sort(ordnerliste.begin(), ordnerliste.end()); // sortiert die ordnerliste
    if(Entwicklerversion){ // checkt on die Entwicklerversion aktiviert ist 
        for (int i = 0; i < ordnerliste.size(); i++){ // geht alle einträge des vectors ordnerliste durch
        cout << ordnerliste[i] << endl; // gibt jeden eintrag im terminal aus 
        }
    }
}
int main() {
    leseConfig(configDatei);
    configAusgabe();
    leseZeitordner(Pfad);
    return 0; 
}