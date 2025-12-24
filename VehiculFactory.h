//
// Created by Rares Ionita on 24-Dec-25.
//

#ifndef PROIECT_POO_VEHICULFACTORY_H
#define PROIECT_POO_VEHICULFACTORY_H

#include <memory>
#include <string>
#include "Vehicul.h"
#include "SpecificatiiTehnice.h"
#include "DataOra.h"
#include "Derivate.h" // Necesar pentru enum TipMotocicleta

class VehiculFactory {
public:
    static std::unique_ptr<Vehicul> creeazaAutoturism(
        const std::string& vin, const std::string& marca, const std::string& model,
        int an, int km, int pret, const SpecificatiiTehnice& spec,
        const DataOra& data, const std::string& obs, bool eCoupe
    );

    static std::unique_ptr<Vehicul> creeazaAutoutilitara(
        const std::string& vin, const std::string& marca, const std::string& model,
        int an, int km, int pret, const SpecificatiiTehnice& spec,
        const DataOra& data, const std::string& obs, double masaMaxima
    );

    static std::unique_ptr<Vehicul> creeazaMotocicleta(
        const std::string& vin, const std::string& marca, const std::string& model,
        int an, int km, int pret, const SpecificatiiTehnice& spec,
        const DataOra& data, const std::string& obs, TipMotocicleta tip
    );

    static std::unique_ptr<Vehicul> creeazaMicrobuz(
        const std::string& vin, const std::string& marca, const std::string& model,
        int an, int km, int pret, const SpecificatiiTehnice& spec,
        const DataOra& data, const std::string& obs, int numarLocuri
    );
};

#endif //PROIECT_POO_VEHICULFACTORY_H