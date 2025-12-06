//
// Created by Rares Ionita on 29-Nov-25.
//

#include "Participant.h"
#include "Exceptii.h"
#include <utility>

using namespace std;

void Participant::actualizeazaIstoric() {
    if (numarIstoric < capacitateIstoric) {
        numarIstoric++;
    }
    for (int i = numarIstoric - 1; i > 0; i--) {
        istoricSolduri[i] = istoricSolduri[i - 1];
    }
    istoricSolduri[0] = soldCurent;
    cout << "Soldul lui " << numeParticipant << " a fost actualizat la " << soldCurent << " EUR.\n";
}

Participant::Participant(int idParticipant, string numeParticipant, string email, double soldCurent) :
    idParticipant(idParticipant), numeParticipant(std::move(numeParticipant)),
    email(std::move(email)), soldCurent(soldCurent), capacitateIstoric(10), numarIstoric(1) {

    istoricSolduri = new double[capacitateIstoric];
    istoricSolduri[0] = soldCurent;
    for (int i = 1; i < capacitateIstoric; i++) {
        istoricSolduri[i] = 0;
    }
}

Participant::~Participant() {
    delete[] istoricSolduri;
    istoricSolduri = nullptr;
}

Participant::Participant(const Participant& other) :
    idParticipant(other.idParticipant), numeParticipant(other.numeParticipant),
    email(other.email), soldCurent(other.soldCurent),
    capacitateIstoric(other.capacitateIstoric), numarIstoric(other.numarIstoric) {

    istoricSolduri = new double[capacitateIstoric];
    for (int i = 0; i < capacitateIstoric; i++) {
        istoricSolduri[i] = other.istoricSolduri[i];
    }
}

Participant& Participant::operator=(Participant other) {
    swap(numeParticipant, other.numeParticipant);
    swap(email, other.email);
    swap(soldCurent, other.soldCurent);
    swap(capacitateIstoric, other.capacitateIstoric);
    swap(istoricSolduri, other.istoricSolduri);
    swap(numarIstoric, other.numarIstoric);
    return *this;
}

ostream& operator<<(ostream& os, const Participant& participant) {
    os << "ID: " << participant.idParticipant << "\n";
    os << "Nume: " << participant.numeParticipant << "\n";
    os << "Email: " << participant.email << "\n";
    os << "Sold curent: " << participant.soldCurent << "\n";
    os << "Istoric solduri:  ";
    for (int i = 0; i < participant.numarIstoric; i++) {
        os << participant.istoricSolduri[i] << " ";
    }
    os << "\n";
    return os;
}

void Participant::topUp(double suma) {
    if (suma <= 0) {
        throw SumaInvalidaException(suma);
    }
    soldCurent = suma + soldCurent;
    actualizeazaIstoric();
}

void Participant::retragere(double suma) {
    if (suma <= 0) {
        throw SumaInvalidaException(suma);
    }
    if (suma > soldCurent) {
        throw FonduriInsuficienteException(numeParticipant, suma, soldCurent);
    }
    soldCurent = soldCurent - suma;
    actualizeazaIstoric();
}

void Participant::afiseazaIstoric() const {
    cout << "Istoric solduri pentru " << numeParticipant << ":\n";
    for (int i = 0; i < numarIstoric; i++) {
        cout << istoricSolduri[i] << " ";
    }
    cout << "\n";
}

const string& Participant::getNume() const {
    return numeParticipant;
}

double Participant::getSold() const {
    return soldCurent;
}

int Participant::getId() const {
    return idParticipant;
}