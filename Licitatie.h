//
// Created by Rares Ionita on 01-Dec-25.
//

#ifndef PROIECT_POO_LICITATIE_H
#define PROIECT_POO_LICITATIE_H

#include <iostream>
#include <vector>
#include <string>
#include "Vehicul.h"
#include "DataOra.h"
#include "Participant.h"

class Licitatie {
private:
    const int idLicitatie;
    Vehicul* vehiculVanzare;
    DataOra dataStart;
    DataOra dataEnd;
    int durataMinute;
    double pretCurent;
    Participant* castigatorCurent;
    std::vector<Participant*> participants;
    char* descriereEveniment;

public:
    Licitatie(int idLicitatie, const Vehicul* vehiculVanzare, const DataOra& dataStart, int durataMinute, const std::string& descriereEveniment);
    ~Licitatie();
    Licitatie(const Licitatie& other);
    Licitatie& operator=(const Licitatie& other);
    Licitatie(Licitatie&& other) noexcept;
    Licitatie& operator=(Licitatie&& other) noexcept;

    void inscrieParticipant(Participant* p);
    void plaseazaOferta(Participant* ofertant, double sumaOferita);
    void finalizeazaLicitatie() const;

    friend std::ostream& operator<<(std::ostream& os, const Licitatie& licitatie);

    [[nodiscard]] int getId() const;
    [[nodiscard]] Participant* getCastigatorCurent() const;
    [[nodiscard]] const Vehicul* getVehicul() const;
};

#endif //PROIECT_POO_LICITATIE_H