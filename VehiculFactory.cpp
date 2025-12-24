//
// Created by Rares Ionita on 24-Dec-25.
//

#include "VehiculFactory.h"
// Nu e nevoie sa includem Derivate.h aici daca e inclus in .h,
// dar pentru claritate si siguranta ca avem constructorii vizibili:
#include "Derivate.h"
#include "Microbuz.h"

std::unique_ptr<Vehicul> VehiculFactory::creeazaAutoturism(
    const std::string& vin, const std::string& marca, const std::string& model,
    int an, int km, int pret, const SpecificatiiTehnice& spec,
    const DataOra& data, const std::string& obs, bool eCoupe) {

    return std::make_unique<Autoturism>(vin, marca, model, an, km, pret, spec, data, obs, eCoupe);
}

std::unique_ptr<Vehicul> VehiculFactory::creeazaAutoutilitara(
    const std::string& vin, const std::string& marca, const std::string& model,
    int an, int km, int pret, const SpecificatiiTehnice& spec,
    const DataOra& data, const std::string& obs, double masaMaxima) {

    return std::make_unique<Autoutilitara>(vin, marca, model, an, km, pret, spec, data, obs, masaMaxima);
}

std::unique_ptr<Vehicul> VehiculFactory::creeazaMotocicleta(
    const std::string& vin, const std::string& marca, const std::string& model,
    int an, int km, int pret, const SpecificatiiTehnice& spec,
    const DataOra& data, const std::string& obs, TipMotocicleta tip) {

    return std::make_unique<Motocicleta>(vin, marca, model, an, km, pret, spec, data, obs, tip);
}


std::unique_ptr<Vehicul> VehiculFactory::creeazaMicrobuz(
    const std::string& vin, const std::string& marca, const std::string& model,
    int an, int km, int pret, const SpecificatiiTehnice& spec,
    const DataOra& data, const std::string& obs, int numarLocuri) {

    return std::make_unique<Microbuz>(vin, marca, model, an, km, pret, spec, data, obs, numarLocuri);
}
