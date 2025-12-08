//
// Created by Rares Ionita on 07-Dec-25.
//

#include "Microbuz.h"
#include <utility>

using namespace std;

Microbuz::Microbuz(string vin, string marca, string model, int an, int kilometraj, int pret,
                   const SpecificatiiTehnice& specs, const DataOra& data, const string& observatiiTehnice,
                   int numarLocuri)
    : Vehicul(std::move(vin), std::move(marca), std::move(model), an, kilometraj, pret, specs, data, observatiiTehnice),
      numarLocuri(numarLocuri) {
}

Vehicul* Microbuz::clone() const {
    return new Microbuz(*this);
}

double Microbuz::calculPretRezerva() const {
    double pretRezerva = pretInitial;
    int vechime = 2025 - anFabricatie;

    // depreciere standard de varsta
    for(int i = 0; i < vechime; i++) {
        pretRezerva *= 0.92;
    }

    // microbuzele de 8+1 se conduc cu B deci sunt mai cautate
    if (numarLocuri <= 9) {
        pretRezerva += 500;
    }

    // scade drastic pretul de la kilometri
    if (kilometraj > 300000) {
        pretRezerva *= 0.75;
    } else if (kilometraj > 200000) {
        pretRezerva *= 0.85;
    }

    if (pretRezerva < 1000) return 1000;
    return pretRezerva;
}

void Microbuz::afisareDetalii(std::ostream& os) const {
    os << "Tip: MICROBUZ\n";
    os << "Numar Locuri: " << numarLocuri << "\n";
}

ostream& operator<<(ostream& os, const Microbuz& microbuz) {
    microbuz.afiseaza(os);
    return os;
}