//
// Created by Rares Ionita on 01-Dec-25.
//

#ifndef PROIECT_POO_AUCTIONMANAGER_H
#define PROIECT_POO_AUCTIONMANAGER_H

#include <vector>
#include <string>
#include <memory>
#include "Vehicul.h"
#include "Participant.h"
#include "Licitatie.h"
#include "DataOra.h"

class AuctionManager {
private:
    std::string numeCasaLicitatii;
    std::vector<std::unique_ptr<Vehicul>> inventarVehicule;
    std::vector<Participant> listaParticipanti;
    std::vector<Licitatie> listaLicitatii;
    int nextLicitatieId;

    // [SINGLETON] 1. Instanta statica privata
    static AuctionManager* instance;

    // [SINGLETON] 2. Constructor privat
    explicit AuctionManager(std::string numeCasaLicitatii);

public:
    // [SINGLETON] 3. Stergem constructorii de copiere/atribuire pentru a evita duplicarea
    AuctionManager(const AuctionManager&) = delete;
    AuctionManager& operator=(const AuctionManager&) = delete;

    ~AuctionManager();

    // [SINGLETON] 4. Metoda statica de acces
    static AuctionManager& getInstance(const std::string& nume = "AuctionHouse");

    void inregistrareParticipant(const Participant& p);
    Participant* getParticipantById(int id);
    void adaugaVehiculInParc(std::unique_ptr<Vehicul> vehicul);
    void creeazaLicitatie(const std::string& vin, const DataOra& start, int durata, const std::string& descriere);
    Licitatie* getLicitatieById(int id);
    void afiseazaInventar() const;
    void afiseazaAutoturism() const;
    void afiseazaAutoutilitara() const;
    void afiseazaMotocicleta() const;
    void afiseazaMicrobuz() const;

    friend std::ostream& operator<<(std::ostream& os, const AuctionManager& manager);

    [[nodiscard]] const std::vector<Participant>& getListaParticipanti() const;
    [[nodiscard]] const std::vector<Licitatie>& getListaLicitatii() const;
};

#endif //PROIECT_POO_AUCTIONMANAGER_H