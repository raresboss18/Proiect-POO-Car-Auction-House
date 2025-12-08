//
// Created by Rares Ionita on 07-Dec-25.
//

#ifndef PROIECT_POO_MICROBUZ_H
#define PROIECT_POO_MICROBUZ_H

#include "Vehicul.h"

class Microbuz : public Vehicul {
private:
    int numarLocuri;

protected:
    void afisareDetalii(std::ostream& os) const override;

public:
    Microbuz(std::string vin, std::string marca, std::string model, int an, int kilometraj, int pret,
             const SpecificatiiTehnice& specs, const DataOra& data, const std::string& observatiiTehnice,
             int numarLocuri);

    [[nodiscard]] double calculPretRezerva() const override;

    [[nodiscard]] Vehicul* clone() const override;

    friend std::ostream& operator<<(std::ostream& os, const Microbuz& microbuz);
};

#endif //PROIECT_POO_MICROBUZ_H