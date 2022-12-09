#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int porownaj(string slowo1, string slowo2);

int main() {

    ifstream odczyt("dane_cezara_3.txt");
    ofstream zapis("wyniki_cezara_3.txt");

    if (!odczyt || !zapis) {
        cerr << "Blad systemu plikow" << endl;
        return 1;
    }

    while (!odczyt.eof()) {
        string slowo1;
        string slowo2;
        string linia;
        getline(odczyt, linia);

        if (linia.find(" ") == string::npos) {
            zapis << linia << " BLEDNY KOD - brak spacji" << endl;
        }
        else if (linia.find(" ") >= linia.length() - 1) {                    // ostatnia (pusta) linijka w pliku tekstowym
            zapis << linia << " BLEDNY KOD - spacja na koncu" << endl;       // "dane_cezara_3.txt" musi zostac usunieta,
        }                                                                    // aby instrukcja warunkowa dzialala poprawnie
        else {
            slowo1 = linia.substr(0, linia.find(" "));
            slowo2 = linia.substr(linia.find(" ") + 1, linia.length());

            if (slowo1.length() != slowo2.length()) {
                zapis << linia << " Rozna dlugosc slow" << endl;
            }
            else if (2 > slowo1.length()) {
                zapis << linia << " Za krotkie slowo" << endl;
            }
            else {
                if (porownaj(slowo1, slowo2) != 0) {
                    zapis << slowo1 << " " << slowo2 << endl;
                }
            }
        }
    }

    odczyt.close();
    zapis.close();

    return 0;
}

int porownaj(string slowo1, string slowo2) {     // funkcja zwraca 0, kiedy sa rowne oraz k, kiedy sa rozne
    char* tmp1 = (char*)slowo1.c_str();
    char* tmp2 = (char*)slowo2.c_str();
    int k = 0;
    int ret = 0;

    if ((tmp1[0] - tmp2[0]) > 0) {
        k = 26 - (tmp1[0] - tmp2[0]);
    }
    else {
        k = tmp2[0] - tmp1[0];
    }

    for (int i = 1; i < slowo1.length(); i++) {
        int kt = 0;

        if ((tmp1[i] - tmp2[i]) > 0) {
            kt = 26 - (tmp1[i] - tmp2[i]);
        }
        else {
            kt = tmp2[i] - tmp1[i];
        }

        if (kt != k) {
            ret = k;
            break;
        }
    }

    return ret;
}