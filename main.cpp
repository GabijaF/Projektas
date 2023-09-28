#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

struct Studentas {
    string vardas;
    string pavarde;
    vector<int> tarpiniai_rezultatai;
    int egzamino_rezultatas;
};

double GalutinisBalasVidurkis(const vector<int>& tarpiniai, int egzaminas) {
    if (tarpiniai.empty() || egzaminas > 10) {
        return -1.0; // Galutinis balas yra '-' jei nėra tarpinių rezultatų arba egzaminas > 10
    }

    double tarpiniu_vidurkis = 0.0;
    for (int rezultatas : tarpiniai) {
        tarpiniu_vidurkis += rezultatas;
    }
    tarpiniu_vidurkis /= tarpiniai.size();

    return 0.4 * tarpiniu_vidurkis + 0.6 * egzaminas;
}

double GalutinisBalasMediana(const vector<int>& tarpiniai, int egzaminas) {
    if (tarpiniai.empty() || egzaminas > 10) {
        return -1.0; // Galutinis balas yra '-' jei nėra tarpinių rezultatų arba egzaminas > 10
    }

    vector<int> tarpiniai_kopija = tarpiniai;
    sort(tarpiniai_kopija.begin(), tarpiniai_kopija.end());

    if (tarpiniai_kopija.size() % 2 == 0) {
        int vidurinio_indeksas1 = tarpiniai_kopija.size() / 2 - 1;
        int vidurinio_indeksas2 = tarpiniai_kopija.size() / 2;
        double mediana = (tarpiniai_kopija[vidurinio_indeksas1] + tarpiniai_kopija[vidurinio_indeksas2]) / 2.0;
        return 0.4 * mediana + 0.6 * egzaminas;
    } else {
        int vidurinio_indeksas = tarpiniai_kopija.size() / 2;
        double mediana = tarpiniai_kopija[vidurinio_indeksas];
        return 0.4 * mediana + 0.6 * egzaminas;
    }
}

void SpausdintiLentele(const vector<Studentas>& studentai, bool naudotiMediana) {
    if (naudotiMediana) {
        cout << left << setw(20) << "Vardas" << setw(20) << "Pavardė" << setw(15) << "Galutinis (Med.)" << endl;
        cout << "--------------------------------------------------------" << endl;
    } else {
        cout << left << setw(20) << "Vardas" << setw(20) << "Pavardė" << setw(15) << "Galutinis (Vid.)" << endl;
        cout << "-----------------------------------------------------------" << endl;
    }

    for (const Studentas& studentas : studentai) {
        double galutinis;
        if (naudotiMediana) {
            galutinis = GalutinisBalasMediana(studentas.tarpiniai_rezultatai, studentas.egzamino_rezultatas);
        } else {
            galutinis = GalutinisBalasVidurkis(studentas.tarpiniai_rezultatai, studentas.egzamino_rezultatas);
        }

        if (galutinis == -1.0) {
            cout << left << setw(20) << studentas.vardas << setw(20) << studentas.pavarde << setw(15) << "-" << endl;
        } else {
            cout << left << setw(20) << studentas.vardas << setw(20) << studentas.pavarde << setw(15) << fixed << setprecision(2) << galutinis << endl;
        }
    }
}

void NuskaitytiIsFailo(vector<Studentas>& studentai) {
    ifstream failas("kursiokai.txt"); 
    

    if (!failas) {
        cout << "Klaida: Nepavyko atidaryti failo." << endl;
        return;
    }

    studentai.clear(); 

    string eilute;
    while (getline(failas, eilute)) {
        Studentas studentas;
        size_t vardo_pozicija = eilute.find_first_of(" ");
        studentas.vardas = eilute.substr(0, vardo_pozicija);
        studentas.pavarde = eilute.substr(vardo_pozicija + 1);
        studentai.push_back(studentas);
    }

    failas.close();
}

int main() {
    vector<Studentas> studentai;

    srand(time(NULL)); // Nustatome atsitiktinio generavimo sėklą pagal laiką

    while (true) {
        Studentas studentas;
        cout << "Įveskite studento vardą (ENTER, jei norite baigti): ";
        getline(cin, studentas.vardas);

        if (studentas.vardas.empty()) {
            break;
        }

        cout << "Įveskite studento pavardę: ";
        getline(cin, studentas.pavarde);

        cout << "Generuoti atsitiktinius namų darbų rezultatus? (y/n): ";
        char generuoti_atstiktinius;
        cin >> generuoti_atstiktinius;
        cin.ignore();

        if (generuoti_atstiktinius == 'y' || generuoti_atstiktinius == 'Y') {
            int nd_sk = rand() % 11; // Sugeneruoti atsitiktinį namų darbų skaičių nuo 0 iki 10
            for (int i = 0; i < nd_sk; i++) {
                int pazymys = rand() % 11; // Sugeneruoti atsitiktinį balą nuo 0 iki 10
                studentas.tarpiniai_rezultatai.push_back(pazymys);
            }
        } else {
            cout << "Įveskite studento namų darbų rezultatus (baigti įvedimą su ENTER):" << endl;
            string eilute;
            while (true) {
                getline(cin, eilute);
                if (eilute.empty()) {
                    break;
                }
                int nd_rezultatas = stoi(eilute);
                studentas.tarpiniai_rezultatai.push_back(nd_rezultatas);
            }
        }

        cout << "Generuoti atsitiktinį egzamino balą? (y/n): ";
        char generuoti_egzamina;
        cin >> generuoti_egzamina;
        cin.ignore();

        if (generuoti_egzamina == 'y' || generuoti_egzamina == 'Y') {
            studentas.egzamino_rezultatas = rand() % 11; // Sugeneruoti atsitiktinį egzamino balą nuo 0 iki 10
        } else {
            cout << "Įveskite studento egzamino rezultatą: ";
            cin >> studentas.egzamino_rezultatas;
            cin.ignore();
        }

        studentai.push_back(studentas);
    }

    cout << "Pasirinkite balo skaičiavimo būdą:" << endl;
    cout << "1. Vidurkis" << endl;
    cout << "2. Mediana" << endl;
    int pasirinkimas;
    cin >> pasirinkimas;

    bool naudotiMediana = (pasirinkimas == 2);

    SpausdintiLentele(studentai, naudotiMediana);

    return 0;
}
