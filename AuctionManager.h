//
// Created by Rares Ionita on 01-Dec-25.
//

#ifndef PROIECT_POO_AUCTIONMANAGER_H
#define PROIECT_POO_AUCTIONMANAGER_H

#include <iostream>
#include <vector>
#include <string>
#include "Vehicul.h"
#include "Participant.h"
#include "Licitatie.h"
#include "DataOra.h"

class AuctionManager {
private:
    std::string numeCasaLicitatii;
    std::vector<Vehicul*> inventarVehicule;
    std::vector<Participant> listaParticipanti;
    std::vector<Licitatie> listaLicitatii;
    int nextLicitatieId;

public:
    explicit AuctionManager(std::string numeCasaLicitatii);

    ~AuctionManager();

    void inregistrareParticipant(const Participant& p);
    Participant* getParticipantById(int id);
    void adaugaVehiculInParc(Vehicul* vehicul);
    void creeazaLicitatie(const std::string& vin, const DataOra& start, int durata, const std::string& descriere);
    Licitatie* getLicitatieById(int id);
    void afiseazaInventar() const;
    void afiseazaAutoturism() const;
    void afiseazaAutoutilitara() const;
    void afiseazaMotocicleta() const;

    friend std::ostream& operator<<(std::ostream& os, const AuctionManager& manager);
};

#endif //PROIECT_POO_AUCTIONMANAGER_H