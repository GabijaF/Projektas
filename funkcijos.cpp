#include "funkcijos.h"
#include "vidurkis.h"
#include "mediana.h"

double skaiciuotiGalutiniBala(const Studentas& studentas, bool naudotiVidurki) {
    double NdBalas = skaiciuotiVidurki(studentas.Nd);
    double galutinisBalas = (0.4 * NdBalas + 0.6 * studentas.egz);
    if (naudotiVidurki) {
        return galutinisBalas;
    } else {
        double mediana = skaiciuotiMediana(studentas.Nd);
        return (0.4 * mediana + 0.6 * studentas.egz);
    }
}


