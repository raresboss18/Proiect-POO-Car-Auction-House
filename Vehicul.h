//
// Created by Rares Ionita on 01-Dec-25.
//

#ifndef PROIECT_POO_VEHICUL_H
#define PROIECT_POO_VEHICUL_H

#include <iostream>
#include <string>
#include "DataOra.h"
#include "SpecificatiiTehnice.h"

class Vehicul {
protected:
    std::string vin;
    std::string marca;
    std::string model;
    int anFabricatie;
    int kilometraj;
    int pretInitial;
    char* observatiiTehnice;

    SpecificatiiTehnice specificatiiTehnice;
    DataOra dataOra;

    virtual void afisareDetalii(std::ostream& os) const = 0;

public:
    Vehicul(std::string vin, std::string marca, std::string model, int anFabricatie, int kilometraj, int pretInitial, const SpecificatiiTehnice& specificatiiTehnice, const DataOra& dataOra, const std::string& observatiiTehnice);

    virtual ~Vehicul();

    Vehicul(Vehicul&& other) noexcept;
    Vehicul& operator=(Vehicul&& other) noexcept;

    Vehicul(const Vehicul& other);
    Vehicul& operator=(const Vehicul& other);

    bool operator==(const Vehicul& other) const;

    [[nodiscard]] virtual double calculPretRezerva() const = 0;

    [[nodiscard]] virtual Vehicul* clone() const = 0;

    void afiseaza(std::ostream& os) const;

    friend std::ostream& operator<<(std::ostream& os, const Vehicul& vehicul);

    [[nodiscard]] const std::string& getVIN() const;
};

#endif //PROIECT_POO_VEHICUL_H