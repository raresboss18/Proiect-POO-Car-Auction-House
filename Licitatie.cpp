//
// Created by Rares Ionita on 01-Dec-25.
//

#include "Licitatie.h"
#include <cstring>
#include <utility>

using namespace std;

Licitatie::Licitatie(int idLicitatie, const Vehicul* vehiculVanzare, const DataOra& dataStart, int durataMinute, const string& descriereEveniment) :
    idLicitatie(idLicitatie), vehiculVanzare(nullptr), dataStart(dataStart), durataMinute(durataMinute), pretCurent(0.0), castigatorCurent(nullptr) {

    if (vehiculVanzare != nullptr) {
        this->vehiculVanzare = vehiculVanzare->clone();
        this->pretCurent = this->vehiculVanzare->calculPretRezerva();
    }

    this->descriereEveniment = new char[descriereEveniment.length() + 1];
    strcpy(this->descriereEveniment, descriereEveniment.c_str());
    this->dataEnd = this->dataStart;
    this->dataEnd.adaugaMinute(this->durataMinute);
}

Licitatie::~Licitatie() {
    delete[] this->descriereEveniment;
    delete this->vehiculVanzare;
}

Licitatie::Licitatie(const Licitatie& other) :
    idLicitatie(other.idLicitatie), vehiculVanzare(nullptr), dataStart(other.dataStart), dataEnd(other.dataEnd), durataMinute(other.durataMinute),
    pretCurent(other.pretCurent), castigatorCurent(other.castigatorCurent), participants(other.participants) {

    if (other.vehiculVanzare !=nullptr) {
        this->vehiculVanzare = other.vehiculVanzare->clone();
    }
    this->descriereEveniment = new char[strlen(other.descriereEveniment) + 1];
    strcpy(this->descriereEveniment, other.descriereEveniment);
}

Licitatie& Licitatie::operator=(const Licitatie& other) {
    if (this != &other) {
        delete vehiculVanzare;
        vehiculVanzare = nullptr;

        if (other.vehiculVanzare != nullptr) {
            vehiculVanzare = other.vehiculVanzare->clone();
        }

        this->dataStart = other.dataStart;
        this->durataMinute = other.durataMinute;
        this->dataEnd = other.dataEnd;
        this->pretCurent = other.pretCurent;
        this->castigatorCurent = other.castigatorCurent;
        this->participants = other.participants;

        delete[] this->descriereEveniment;
        this->descriereEveniment = new char[strlen(other.descriereEveniment) + 1];
        strcpy(this->descriereEveniment, other.descriereEveniment);
    }
    return *this;
}

Licitatie::Licitatie(Licitatie&& other) noexcept :
    idLicitatie(other.idLicitatie), vehiculVanzare(other.vehiculVanzare), dataStart(other.dataStart), dataEnd(other.dataEnd),
    durataMinute(other.durataMinute), pretCurent(other.pretCurent), castigatorCurent(other.castigatorCurent), participants(std::move(other.participants)) {

    other.vehiculVanzare = nullptr;

    this->descriereEveniment = other.descriereEveniment;
    other.descriereEveniment = nullptr;
}

Licitatie& Licitatie::operator=(Licitatie&& other) noexcept {
    if (this != &other) {

        delete[] this->descriereEveniment;
        delete this->vehiculVanzare;

        this->vehiculVanzare = other.vehiculVanzare;
        other.vehiculVanzare = nullptr;
        this->dataStart = other.dataStart;
        this->durataMinute = other.durataMinute;
        this->dataEnd = other.dataEnd;
        this->pretCurent = other.pretCurent;
        this->castigatorCurent = other.castigatorCurent;
        this->participants = std::move(other.participants);
        this->descriereEveniment = other.descriereEveniment;
        other.descriereEveniment = nullptr;
    }
    return *this;
}

void Licitatie::inscrieParticipant(Participant* p) {
    if (p != nullptr) {
        participants.push_back(p);
        cout << "Participantul " << p->getNume() << " s-a inscris la licitatia " << this->idLicitatie << ".\n";
    }
}

void Licitatie::plaseazaOferta(Participant* ofertant, double sumaOferita) {
    if (DataOra::obtineOraCurenta() > this->dataEnd) {
        cout << "Licitatia a expirat! Nu se mai pot plasa oferte.\n";
        return;
    }
    if (ofertant == nullptr)
        return;

    if (sumaOferita <= this->pretCurent) {
        cout << "Oferta de " << sumaOferita << " EUR este prea mica. Pretul curent este " << this->pretCurent << " EUR.\n";
        return;
    }

    if (sumaOferita > ofertant->getSold()) {
        cout << "Participantul " << ofertant->getNume() << " nu are fonduri suficiente.\n";
        return;
    }

    this->pretCurent = sumaOferita;
    this->castigatorCurent = ofertant;
    dataEnd.adaugaMinute(15);

    cout << "Oferta noua a fost acceptata! " << ofertant->getNume() << " a ofertat " << sumaOferita << " EUR!\n";
    cout << "Timpul pentru plasat oferte a fost prelungit cu 15 minute!\n";
}

void Licitatie::finalizeazaLicitatie() const {
    cout << "Licitatie ID: " << this->idLicitatie << "\n";

    if (DataOra::obtineOraCurenta() > this->dataEnd) {
        if (this->castigatorCurent != nullptr) {
            cout << "Licitatia s-a incheiat!\n";
            cout << "Castigator: " << this->castigatorCurent->getNume() << " cu suma de " << this->pretCurent << " EUR.\n";
            cout << "Procesare plata...\n";

            this->castigatorCurent->retragere(this->pretCurent);

            cout << "Soldul final al castigatorului:\n" << *(this->castigatorCurent);
        } else {
            cout << "Licitatia s-a incheiat fara oferte.\n";
        }
    } else {
        cout << "Licitatia inca este in desfasurare.\n";
    }
}

ostream& operator<<(ostream& os, const Licitatie& licitatie) {
    os << "ID licitatie: " << licitatie.idLicitatie << endl;
    if (licitatie.descriereEveniment != nullptr) {
        os << licitatie.descriereEveniment << endl;
    }
    
    if (licitatie.vehiculVanzare != nullptr) {
        os << "Vehicul la licitatie: " << licitatie.vehiculVanzare->getVIN() << endl;
    }

    os << "Data start: " << licitatie.dataStart;
    os << "Data end: " << licitatie.dataEnd;
    os << "Pret curent: " << licitatie.pretCurent << " EUR" << endl;

    if (licitatie.castigatorCurent != nullptr) {
        os << "Castigator curent: " << licitatie.castigatorCurent->getNume() << endl;
    } else {
        os << "Momentan nu a fost inregistrata nici o oferta" << endl;
    }
    return os;
}

int Licitatie::getId() const {
    return idLicitatie;
}

Participant* Licitatie::getCastigatorCurent() const {
    return castigatorCurent;
}

const Vehicul* Licitatie::getVehicul() const {
    return vehiculVanzare;
}