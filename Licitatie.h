#ifndef PROIECT_POO_LICITATIE_H
#define PROIECT_POO_LICITATIE_H

#include <vector>
#include <string>
#include <memory>

#include "Vehicul.h"
#include "DataOra.h"
#include "Participant.h"

class Licitatie {
private:
    const int idLicitatie;
    std::unique_ptr<Vehicul> vehiculVanzare;
    DataOra dataStart;
    DataOra dataEnd;
    int durataMinute;
    double pretCurent;
    Participant* castigatorCurent;
    std::vector<Participant*> participants;
    std::string descriereEveniment;

public:
    Licitatie(int idLicitatie, const Vehicul* vehiculVanzare,
              const DataOra& dataStart, int durataMinute,
              std::string  descriereEveniment);

    ~Licitatie() = default;

    Licitatie(const Licitatie& other);
    Licitatie& operator=(const Licitatie& other);

    Licitatie(Licitatie&&) noexcept = default;
    Licitatie& operator=(Licitatie&&) noexcept = delete;

    void inscrieParticipant(Participant* p);
    void plaseazaOferta(Participant* ofertant, double sumaOferita);
    void finalizeazaLicitatie() const;

    friend std::ostream& operator<<(std::ostream& os, const Licitatie& licitatie);

    [[nodiscard]] int getId() const;
    [[nodiscard]] Participant* getCastigatorCurent() const;
    [[nodiscard]] const Vehicul* getVehicul() const;
};

#endif
