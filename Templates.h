//
// Created by Rares Ionita on 24-Dec-25.
//

#ifndef PROIECT_POO_TEMPLATES_H
#define PROIECT_POO_TEMPLATES_H

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

template <typename T>
class ColectieGenerica {
private:
    std::vector<T> elemente;
    std::string numeColectie;

public:
    explicit ColectieGenerica(std::string nume) : numeColectie(std::move(nume)) {}

    // Operator += pentru a adauga elemente usor
    void operator+=(const T& element) {
        elemente.push_back(element);
    }

    // Operator [] pentru acces rapid
    T& operator[](int index) {
        if (index >= 0 && index < elemente.size()) {
            return elemente[index];
        }
        throw std::out_of_range("Index invalid in ColectieGenerica");
    }

    // Afisarea intregii colectii
    void afiseaza() const {
        std::cout << "=== Colectie: " << numeColectie << " ===\n";
        if (elemente.empty()) {
            std::cout << "(Goala)\n";
            return;
        }
        for (const auto& elem : elemente) {
            std::cout << " -> " << elem << "\n";
        }
    }

    [[nodiscard]] int getSize() const { return elemente.size(); }
};

template <typename T>
void afiseazaVectorCuTitlu(const std::vector<T>& lista, const std::string& titlu) {
    std::cout << "\n>>> RAPORT: " << titlu << " <<<\n";
    std::cout << "Numar elemente: " << lista.size() << "\n";
    if (lista.empty()) {
        std::cout << " - Niciun element gasit -\n";
    } else {
        for (const auto& item : lista) {
            std::cout << item << "\n"; // Se bazeaza pe operatorul << al clasei T
        }
    }
}

// Tratam double-urile ca fiind sume de bani (afisare cu 2 zecimale + moneda).

template <>
inline void afiseazaVectorCuTitlu<double>(const std::vector<double>& lista, const std::string& titlu) {
    std::cout << "\n RAPORT FINANCIAR: " << titlu << " \n";
    std::cout << "Tranzactii procesate: " << lista.size() << "\n";

    if (lista.empty()) {
        std::cout << " - Nicio tranzactie inregistrata -\n";
    } else {
        // Setam formatarea pentru bani
        std::cout << std::fixed << std::setprecision(2);

        double total = 0;
        for (const double& valoare : lista) {
            std::cout << " -> " << valoare << " EUR\n";
            total += valoare;
        }
        std::cout << " TOTAL: " << total << " EUR\n";

        // Resetam formatarea cout la default
        std::cout.unsetf(std::ios::fixed);
    }
}

#endif //PROIECT_POO_TEMPLATES_H