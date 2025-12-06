//
// Created by Rares Ionita on 01-Dec-25.
//

#include "Derivate.h"
#include <utility>

using namespace std;

Autoturism::Autoturism(string vin, string marca, string model, int an, int kilometraj, int pret,
                       const SpecificatiiTehnice& specs, const DataOra& data, const string& observatiiTehnice, bool eCoupe)
    : Vehicul(std::move(vin), std::move(marca), std::move(model), an, kilometraj, pret, specs, data, observatiiTehnice), eCoupe(eCoupe) {
}

Vehicul* Autoturism::clone() const {
    return new Autoturism(*this);
}

double Autoturism::calculPretRezerva() const {
    double pretRezerva = pretInitial * 1.0;
    int vechime = 2025 - anFabricatie;
    if (vechime > 0)
        for (int i = 0; i < vechime; i++)
            pretRezerva = pretRezerva * 0.9;

    if (kilometraj > 150000)
        pretRezerva = pretRezerva * 0.9;
    if (kilometraj > 250000)
        pretRezerva = pretRezerva * 0.9;
    if (kilometraj > 350000)
        pretRezerva = pretRezerva * 0.9;

    //daca e coupe e mai scumpa
    if (eCoupe == true) {
        pretRezerva += 400;
    }
    // dace e mai mic de 500 mai bine o dau la fier vechi
    if (pretRezerva < 500) return 500;
    return pretRezerva;
}

void Autoturism::afisareDetalii(std::ostream& os) const {
    os << "Tip: AUTOTURISM\n";
    if (eCoupe) {
        os << "Coupe";
    }
}

ostream& operator<<(ostream& os, const Autoturism& autoturism) {
    autoturism.afiseaza(os);
    return os;
}

Autoutilitara::Autoutilitara(string vin, string marca, string model, int an, int kilometraj, int pret,
                     const SpecificatiiTehnice& specs, const DataOra& data, const string& observatiiTehnice, double masaMaxima)
    : Vehicul(std::move(vin), std::move(marca), std::move(model), an, kilometraj, pret, specs, data, observatiiTehnice), masaMaximaAdmisa(masaMaxima) {
}

Vehicul* Autoutilitara::clone() const {
    return new Autoutilitara(*this);
}

double Autoutilitara::calculPretRezerva() const {
    double pretRezerva = pretInitial * 1.0;
    int vechime = 2025 - anFabricatie;
    if (vechime > 0)
        for (int i = 0; i < vechime; i++)
            pretRezerva = pretRezerva * 0.8;

    if (kilometraj > 150000)
        pretRezerva = pretRezerva * 0.95;
    if (kilometraj > 250000)
        pretRezerva = pretRezerva * 0.95;
    if (kilometraj > 350000)
        pretRezerva = pretRezerva * 0.95;

    //daca are masa admisa > 3.5  e mai scumpa
    if (masaMaximaAdmisa > 3.5) {
        pretRezerva = pretRezerva + pretRezerva*0.3 ;
    }
    // dace e mai mic de 500 mai bine o dau la fier vechi
    if (pretRezerva < 500) return 500;
    return pretRezerva;
}

void Autoutilitara::afisareDetalii(std::ostream& os) const {
    os << "Tip: AUTOUTILITARA\n";
    os << "Masa Maxima Admisa: " << masaMaximaAdmisa << " tone\n";
}

ostream& operator<<(ostream& os, const Autoutilitara& autoutilitara) {
    autoutilitara.afiseaza(os);
    return os;
}

Motocicleta::Motocicleta(string vin, string marca, string model, int an, int kilometraj, int pret,
                         const SpecificatiiTehnice& specs, const DataOra& data, const string& observatiiTehnice, TipMotocicleta tip)
    : Vehicul(std::move(vin), std::move(marca), std::move(model), an, kilometraj, pret, specs, data, observatiiTehnice), tip(tip) {
}

Vehicul* Motocicleta::clone() const {
    return new Motocicleta(*this);
}

string Motocicleta::tipToString() const {
    switch (tip) {
        case CRUISER: return "Cruiser";
        case SPORT: return "Sport";
        case TOURING: return "Touring";
        case ENDURO: return "Enduro";
        case NAKED: return "Naked";
        default: return "Unknown";
    }
}

double Motocicleta::calculPretRezerva() const {
    double pretRezerva = pretInitial;
    int vechime = 2025 - anFabricatie;

    // nu sunt la fel de folosite ca masina se depreciaza mai greu
    for(int i = 0; i < vechime; i++) {
        pretRezerva *= 0.94;
    }

    if (tip == CRUISER || tip == TOURING) {
        pretRezerva = pretRezerva + pretRezerva * 0.2; // e mai scumpa
    } else if (tip == SPORT) {
        pretRezerva *= 0.95; // astea la mana a2a sunt probabil abuzate
    }

    if (kilometraj > 60000) {
        pretRezerva *= 0.75;
    } else if (kilometraj > 30000) {
        pretRezerva *= 0.90;
    }

    if (pretRezerva < 500) return 500;
    return pretRezerva;
}

void Motocicleta::afisareDetalii(std::ostream& os) const {
    os << "Tip: MOTOCICLETA\n";
    os << "Categorie: " << tipToString() << "\n";
}

ostream& operator<<(ostream& os, const Motocicleta& motocicleta) {
    motocicleta.afiseaza(os);
    return os;
}