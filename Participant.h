//
// Created by Rares Ionita on 29-Nov-25.
//

#ifndef PROIECT_POO_PARTICIPANT_H
#define PROIECT_POO_PARTICIPANT_H

#include <iostream>
#include <string>

class Participant {
private:
    const int idParticipant;
    std::string numeParticipant;
    std::string email;
    double soldCurent;
    double* istoricSolduri;
    int capacitateIstoric;
    int numarIstoric;

    void actualizeazaIstoric();

public:
    Participant(int idParticipant, std::string numeParticipant, std::string email, double soldCurent);

    ~Participant();

    Participant(const Participant& other);

    Participant& operator=(Participant other);

    friend std::ostream& operator<<(std::ostream& os, const Participant& participant);

    void topUp(double suma);
    void retragere(double suma);
    void afiseazaIstoric() const;

    [[nodiscard]] const std::string& getNume() const;
    [[nodiscard]] double getSold() const;
    [[nodiscard]] int getId() const;
};

#endif //PROIECT_POO_PARTICIPANT_H