//
// Created by Rares Ionita on 01-Dec-25.
//

#include "SpecificatiiTehnice.h"

using namespace std;

SpecificatiiTehnice::SpecificatiiTehnice(int capacitateCilindrica, int putere, TipCombustibil combustibil, TipCutie cutie, Tractiune tractiune) :
    capacitateCilindrica(capacitateCilindrica), putere(putere), combustibil(combustibil), cutie(cutie), tractiune(tractiune) {}

string SpecificatiiTehnice::combustibilToString() const {
    switch (combustibil) {
        case BENZINA: return "Benzina";
        case DIESEL: return "Diesel";
        case ELECTRIC: return "Electric";
        case HIBRID: return "Hibrid";
        case GPL: return "GPL";
        default: return "";
    }
}

string SpecificatiiTehnice::cutieToString() const {
    switch (cutie) {
        case MANUALA: return "Manuala";
        case AUTOMATA: return "Automata";
        default: return "";
    }
}

string SpecificatiiTehnice::tractiuneToString() const {
    switch (tractiune) {
        case FATA: return "Fata";
        case SPATE: return "Spate";
        case INTEGRALA: return "Integrala";
        default: return "";
    }
}

ostream& operator<<(ostream& os, const SpecificatiiTehnice& spec) {
    os << "Capacitate: " << spec.capacitateCilindrica << "cmc\n";
    os << "Putere: " << spec.putere << " CP\n";
    os << "Combustibil: " << spec.combustibilToString() << "\n";
    os << "Cutie de viteze: " << spec.cutieToString() << "\n";
    os << "Tractiune: " << spec.tractiuneToString() << "\n";
    return os;
}