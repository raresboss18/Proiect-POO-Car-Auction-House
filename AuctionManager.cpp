//
// Created by Rares Ionita on 01-Dec-25.
//

#include "AuctionManager.h"
#include "Exceptii.h"
#include <utility>

#include "Derivate.h"

using namespace std;

AuctionManager::AuctionManager(string numeCasaLicitatii) : numeCasaLicitatii(std::move(numeCasaLicitatii)), nextLicitatieId(1) {}

AuctionManager::~AuctionManager() {
    for (Vehicul* v : inventarVehicule) {
        delete v;
    }
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

void AuctionManager::adaugaVehiculInParc(Vehicul* vehicul) {
    inventarVehicule.push_back(vehicul);
}

void AuctionManager::creeazaLicitatie(const string& vin, const DataOra& start, int durata, const string& descriere) {
    const Vehicul* vehiculLicitatie = nullptr;
    for (const Vehicul* v : inventarVehicule) {
        if (v->getVIN() == vin) {
            vehiculLicitatie = v;
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
    for (const Vehicul* v : inventarVehicule) {
        cout << *v;
    }
}

//dynamic_cast
void AuctionManager::afiseazaAutoturism() const {
    cout << "AUTOTURISME:\n";
    bool gasit = false;
    for (const Vehicul* v : inventarVehicule) {
        const auto* autoturism = dynamic_cast<const Autoturism*>(v);
        if (autoturism != nullptr) {
            gasit = true;
            //cout << autoturism->getVIN() << "\n";
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
    for (const Vehicul* v : inventarVehicule) {
        const auto* autoutilitara = dynamic_cast<const Autoutilitara*>(v);
        if (autoutilitara != nullptr) {
            gasit = true;
            //cout << autoutilitara->getVIN() << "\n";
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
    for (const Vehicul* v : inventarVehicule) {
        const auto* motocicleta = dynamic_cast<const Motocicleta*>(v);
        if (motocicleta != nullptr) {
            gasit = true;
            //cout << motocicleta->getVIN() << "\n";
            cout << *motocicleta;
        }
    }
    if (gasit == false) {
        cout <<"Nu s-au gasit motociclete\n";
    }
}

ostream& operator<<(ostream& os, const AuctionManager& manager) {
    os << "Nume: " << manager.numeCasaLicitatii << "\n";
    os << "Participanti inregistrati: " << manager.listaParticipanti.size() << "\n";
    os << "Vehicule in inventar: " << manager.inventarVehicule.size() << "\n";
    os << "Licitatii create: " << manager.listaLicitatii.size() << "\n";
    return os;
}