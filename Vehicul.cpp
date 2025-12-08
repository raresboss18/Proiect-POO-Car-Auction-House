//
// Created by Rares Ionita on 01-Dec-25.
//

#include "Vehicul.h"
#include "Exceptii.h"
#include <cstring>
#include <utility>

using namespace std;

Vehicul::Vehicul(string vin, string marca, string model, int anFabricatie, int kilometraj, int pretInitial, const SpecificatiiTehnice& specificatiiTehnice, const DataOra& dataOra, const string& observatiiTehnice) :
    vin(std::move(vin)), marca(std::move(marca)), model(std::move(model)), anFabricatie(anFabricatie), kilometraj(kilometraj), pretInitial(pretInitial), specificatiiTehnice(specificatiiTehnice), dataOra(dataOra) {
    if (pretInitial < 0) {
        throw PretInvalidException(pretInitial);
    }
    this->observatiiTehnice = new char[observatiiTehnice.length() + 1];
    strcpy(this->observatiiTehnice, observatiiTehnice.c_str());
}

Vehicul::~Vehicul() {
    delete[] observatiiTehnice;
    observatiiTehnice = nullptr;
}

Vehicul::Vehicul(Vehicul&& other) noexcept :
    vin(std::move(other.vin)), marca(std::move(other.marca)), model(std::move(other.model)), anFabricatie(other.anFabricatie), kilometraj(other.kilometraj), pretInitial(other.pretInitial), specificatiiTehnice(other.specificatiiTehnice), dataOra(other.dataOra) {

    this->observatiiTehnice = other.observatiiTehnice;
    other.observatiiTehnice = nullptr;
}

Vehicul& Vehicul::operator=(Vehicul&& other) noexcept {
    if (this != &other) {
        this->vin = std::move(other.vin);
        this->marca = std::move(other.marca);
        this->model = std::move(other.model);
        this->dataOra = other.dataOra;
        this->specificatiiTehnice = other.specificatiiTehnice;

        this->anFabricatie = other.anFabricatie;
        this->kilometraj = other.kilometraj;
        this->pretInitial = other.pretInitial;

        delete[] this->observatiiTehnice;
        this->observatiiTehnice = other.observatiiTehnice;
        other.observatiiTehnice = nullptr;
    }
    return *this;
}

Vehicul::Vehicul(const Vehicul& other) :
    vin(other.vin), marca(other.marca), model(other.model), anFabricatie(other.anFabricatie), kilometraj(other.kilometraj), pretInitial(other.pretInitial), specificatiiTehnice(other.specificatiiTehnice), dataOra(other.dataOra) {

    this->observatiiTehnice = new char[strlen(other.observatiiTehnice) + 1];
    strcpy(this->observatiiTehnice, other.observatiiTehnice);
}

Vehicul& Vehicul::operator=(const Vehicul& other) {
    if (this != &other) {
        this->vin = other.vin;
        this->marca = other.marca;
        this->model = other.model;
        this->anFabricatie = other.anFabricatie;
        this->kilometraj = other.kilometraj;
        this->pretInitial = other.pretInitial;
        this->specificatiiTehnice = other.specificatiiTehnice;
        this->dataOra = other.dataOra;

        delete[] this->observatiiTehnice;
        if (other.observatiiTehnice != nullptr) {
            this->observatiiTehnice = new char[strlen(other.observatiiTehnice) + 1];
            strcpy(this->observatiiTehnice, other.observatiiTehnice);
        } else {
            this->observatiiTehnice = nullptr;
        }
    }
    return *this;
}

/*
double Vehicul::calculPretRezerva() const {
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

    return pretRezerva;
}
*/
void Vehicul::afiseaza(std::ostream& os) const {
    os << "VIN: " << vin << "\n";
    os << "Marca: " << marca << "\n";
    os << "Model: " << model << "\n";
    os << "An fabricatie: " << anFabricatie << "\n";
    os << "Kilometraj: " << kilometraj << "\n";
    os << "Specificatii: " << specificatiiTehnice << "\n";
    os << "Primul pret: " << calculPretRezerva() << "\n";
    os << "Data listarii: " << dataOra << "\n";

    afisareDetalii(os);
    os << "\n";

    if (observatiiTehnice != nullptr)
        os << "Observatii: " << observatiiTehnice << "\n\n\n";
}

ostream& operator<<(ostream& os, const Vehicul& vehicul) {
    vehicul.afiseaza(os);
    return os;
}

const string& Vehicul::getVIN() const {
    return vin;
}