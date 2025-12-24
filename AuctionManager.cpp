//
// Created by Rares Ionita on 01-Dec-25.
//

#include "AuctionManager.h"
#include "Exceptii.h"
#include <utility>

#include "Derivate.h"
#include "Microbuz.h"

using namespace std;

// [SINGLETON] Initializare membru static
AuctionManager* AuctionManager::instance = nullptr;

// [SINGLETON] Implementare getInstance
AuctionManager& AuctionManager::getInstance(const std::string& nume) {
    if (instance == nullptr) {
        instance = new AuctionManager(nume);
    }
    return *instance;
}

// Constructorul devine privat (aici a ramas implementarea, doar ca e apelata doar de getInstance)
AuctionManager::AuctionManager(string numeCasaLicitatii)
    : numeCasaLicitatii(std::move(numeCasaLicitatii)), nextLicitatieId(1) {}


AuctionManager::~AuctionManager(){
    inventarVehicule.clear();
}


void AuctionManager::inregistrareParticipant(const Participant& p) {
    listaParticipanti.push_back(p);
}

Participant* AuctionManager::getParticipantById(int id) {
    for (Participant& p : listaParticipanti) {
        if (p.getId() == id) {
            return &p;
        }
    }
    return nullptr;
}

void AuctionManager::adaugaVehiculInParc(std::unique_ptr<Vehicul> vehicul) {
    inventarVehicule.push_back(std::move(vehicul));
}

void AuctionManager::creeazaLicitatie(const string& vin, const DataOra& start, int durata, const string& descriere) {
    const Vehicul* vehiculLicitatie = nullptr;
    for (const auto& v_ptr : inventarVehicule) {
        if (v_ptr->getVIN() == vin) {
            vehiculLicitatie = v_ptr.get();
            break;
        }
    }

    if (vehiculLicitatie != nullptr) {
        Licitatie licitatieNoua(nextLicitatieId++, vehiculLicitatie, start, durata, descriere);
        listaLicitatii.push_back(licitatieNoua);
        cout << "Licitatie noua creata cu succes pentru vehiculul cu VIN: " << vin << endl;
    } else {
        throw LicitatieInvalidaException(vin);
    }
}

Licitatie* AuctionManager::getLicitatieById(int id) {
    for (Licitatie& lic : listaLicitatii) {
        if (lic.getId() == id) {
            return &lic;
        }
    }
    return nullptr;
}

void AuctionManager::afiseazaInventar() const {
    cout << "Inventar Vehicule (" << numeCasaLicitatii << ")\n";
    for (const auto& v_ptr : inventarVehicule) {
        cout << *v_ptr;
    }
}

//dynamic_cast
void AuctionManager::afiseazaAutoturism() const {
    cout << "AUTOTURISME:\n";
    bool gasit = false;
    for (const auto& v_ptr : inventarVehicule) {
        const auto* autoturism = dynamic_cast<const Autoturism*>(v_ptr.get());
        if (autoturism != nullptr) {
            gasit = true;
            cout << *autoturism;
        }
    }
    if (gasit == false) {
        cout <<"Nu s-au gasit autoturisme\n";
    }
}

void AuctionManager::afiseazaAutoutilitara() const {
    cout << "AUTOUTILITARE:\n";
    bool gasit = false;
    for (const auto& v_ptr : inventarVehicule) {
        const auto* autoutilitara = dynamic_cast<const Autoutilitara*>(v_ptr.get());
        if (autoutilitara != nullptr) {
            gasit = true;
            cout << *autoutilitara;
        }
    }
    if (gasit == false) {
        cout <<"Nu s-au gasit autoutilitare\n";
    }
}

void AuctionManager::afiseazaMotocicleta() const {
    cout << "MOTOCICLETE:\n";
    bool gasit = false;
    for (const auto& v_ptr : inventarVehicule) {
        const auto* motocicleta = dynamic_cast<const Motocicleta*>(v_ptr.get());
        if (motocicleta != nullptr) {
            gasit = true;
            cout << *motocicleta;
        }
    }
    if (gasit == false) {
        cout <<"Nu s-au gasit motociclete\n";
    }
}

void AuctionManager::afiseazaMicrobuz() const {
    cout << "MICROBUZE:\n";
    bool gasit = false;
    for (const auto& v_ptr : inventarVehicule) {
        const auto* microbuz = dynamic_cast<const Microbuz*>(v_ptr.get());
        if (microbuz != nullptr) {
            gasit = true;
            cout << *microbuz;
        }
    }
    if (gasit == false) {
        cout <<"Nu s-au gasit microbuze\n";
    }
}

ostream& operator<<(ostream& os, const AuctionManager& manager) {
    os << "Nume: " << manager.numeCasaLicitatii << "\n";
    os << "Participanti inregistrati: " << manager.listaParticipanti.size() << "\n";
    os << "Vehicule in inventar: " << manager.inventarVehicule.size() << "\n";
    os << "Licitatii create: " << manager.listaLicitatii.size() << "\n";
    return os;
}

const std::vector<Participant>& AuctionManager::getListaParticipanti() const {
    return listaParticipanti;
}

const std::vector<Licitatie>& AuctionManager::getListaLicitatii() const {
    return listaLicitatii;
}