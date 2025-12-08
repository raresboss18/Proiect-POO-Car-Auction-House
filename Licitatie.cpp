#include "Licitatie.h"

#include <utility>

using namespace std;

Licitatie::Licitatie(int idLicitatie,
                     const Vehicul* vehicul,
                     const DataOra& dataStart,
                     int durataMinute,
                     string  descriereEveniment)
    : idLicitatie(idLicitatie),
      vehiculVanzare(vehicul ? vehicul->clone() : nullptr),
      dataStart(dataStart),
      durataMinute(durataMinute),
      pretCurent(vehicul ? vehicul->calculPretRezerva() : 0.0),
      castigatorCurent(nullptr),
      descriereEveniment(std::move(descriereEveniment))
{
    dataEnd = dataStart;
    dataEnd.adaugaMinute(durataMinute);
}

// --- COPY ---

Licitatie::Licitatie(const Licitatie& other)
    : idLicitatie(other.idLicitatie),
      vehiculVanzare(other.vehiculVanzare
                         ? std::unique_ptr<Vehicul>(other.vehiculVanzare->clone())
                         : nullptr),
      dataStart(other.dataStart),
      dataEnd(other.dataEnd),
      durataMinute(other.durataMinute),
      pretCurent(other.pretCurent),
      castigatorCurent(other.castigatorCurent),
      participants(other.participants),
      descriereEveniment(other.descriereEveniment) { }

Licitatie& Licitatie::operator=(const Licitatie& other) {
    if (this != &other) {
        dataStart = other.dataStart;
        dataEnd = other.dataEnd;
        durataMinute = other.durataMinute;
        pretCurent = other.pretCurent;
        castigatorCurent = other.castigatorCurent;
        descriereEveniment = other.descriereEveniment;
        participants = other.participants;

        vehiculVanzare.reset(
            other.vehiculVanzare
                ? other.vehiculVanzare->clone()
                : nullptr
        );
    }
    return *this;
}

// --- Logic ---

void Licitatie::inscrieParticipant(Participant* p) {
    if (p) {
        participants.push_back(p);
        cout << "Participantul " << p->getNume()
             << " s-a inscris la licitatia "
             << idLicitatie << ".\n";
    }
}

void Licitatie::plaseazaOferta(Participant* ofertant, double sumaOferita) {
    if (!ofertant) return;

    if (DataOra::obtineOraCurenta() > dataEnd) {
        cout << "Licitatia a expirat! Nu se mai pot plasa oferte.\n";
        return;
    }

    if (sumaOferita <= pretCurent) {
        cout << "Oferta de " << sumaOferita
             << " EUR este prea mica. Pretul curent este "
             << pretCurent << " EUR.\n";
        return;
    }

    if (sumaOferita > ofertant->getSold()) {
        cout << "Participantul " << ofertant->getNume()
             << " nu are fonduri suficiente.\n";
        return;
    }

    pretCurent = sumaOferita;
    castigatorCurent = ofertant;
    dataEnd.adaugaMinute(15);

    cout << "Oferta noua a fost acceptata! "
         << ofertant->getNume()
         << " a ofertat " << sumaOferita << " EUR!\n";
    cout << "Timpul pentru plasat oferte a fost prelungit cu 15 minute!\n";
}

void Licitatie::finalizeazaLicitatie() const {
    cout << "Licitatie ID: " << idLicitatie << "\n";

    if (DataOra::obtineOraCurenta() > dataEnd) {
        if (castigatorCurent != nullptr) {
            cout << "Licitatia s-a incheiat!\n";
            cout << "Castigator: "
                 << castigatorCurent->getNume()
                 << " cu suma de " << pretCurent << " EUR.\n";

            cout << "Procesare plata...\n";
            castigatorCurent->retragere(pretCurent);

            cout << "Soldul final al castigatorului:\n"
                 << *castigatorCurent;
        } else {
            cout << "Licitatia s-a incheiat fara oferte.\n";
        }
    } else {
        cout << "Licitatia inca este in desfasurare.\n";
    }
}

// --- Getters ---

ostream& operator<<(ostream& os, const Licitatie& lic) {
    os << "ID licitatie: " << lic.idLicitatie << endl;
    os << lic.descriereEveniment << endl;

    if (lic.vehiculVanzare)
        os << "Vehicul vanzare: " << *lic.vehiculVanzare << endl;

    os << "Data start: " << lic.dataStart << endl;
    os << "Data end: " << lic.dataEnd << endl;
    os << "pret curent: " << lic.pretCurent << endl;

    if (lic.castigatorCurent)
        os << *lic.castigatorCurent << endl;
    else
        os << "Momentan nu a fost inregistrata nici o oferta";

    return os;
}

int Licitatie::getId() const {
    return idLicitatie;
}

Participant* Licitatie::getCastigatorCurent() const {
    return castigatorCurent;
}

const Vehicul* Licitatie::getVehicul() const {
    return vehiculVanzare.get();
}
