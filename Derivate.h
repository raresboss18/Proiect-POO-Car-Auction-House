//
// Created by Rares Ionita on 01-Dec-25.
//

#ifndef PROIECT_POO_DERIVATE_H
#define PROIECT_POO_DERIVATE_H

#include "Vehicul.h"

class Autoturism : public Vehicul {
private:
    bool eCoupe;

protected:
    void afisareDetalii(std::ostream& os) const override;

public:
    Autoturism(std::string vin, std::string marca, std::string model, int an, int kilometraj, int pret,
               const SpecificatiiTehnice& specs, const DataOra& data, const std::string& observatiiTehnice, bool eCoupe);

    [[nodiscard]] double calculPretRezerva() const override;
    [[nodiscard]] Vehicul* clone() const override;

    friend std::ostream& operator<<(std::ostream& os, const Autoturism& autoturism);
};

class Autoutilitara : public Vehicul {
private:
    double masaMaximaAdmisa;

protected:
    void afisareDetalii(std::ostream& os) const override;

public:
    Autoutilitara(std::string vin, std::string marca, std::string model, int an, int kilometraj, int pret,
              const SpecificatiiTehnice& specs, const DataOra& data, const std::string& observatiiTehnice, double masaMaxima);

    [[nodiscard]] double calculPretRezerva() const override;
    [[nodiscard]] Vehicul* clone() const override;

    friend std::ostream& operator<<(std::ostream& os, const Autoutilitara& autoutilitara);
};

enum TipMotocicleta {
    CRUISER,
    SPORT,
    TOURING,
    ENDURO,
    NAKED
};

class Motocicleta : public Vehicul {
private:
    TipMotocicleta tip;

protected:
    void afisareDetalii(std::ostream& os) const override;

public:
    Motocicleta(std::string vin, std::string marca, std::string model, int an, int kilometraj, int pret,
                const SpecificatiiTehnice& specs, const DataOra& data, const std::string& observatiiTehnice, TipMotocicleta tip);

    [[nodiscard]] double calculPretRezerva() const override;
    [[nodiscard]] Vehicul* clone() const override;

    [[nodiscard]] std::string tipToString() const;

    friend std::ostream& operator<<(std::ostream& os, const Motocicleta& motocicleta);
};

#endif //PROIECT_POO_DERIVATE_H