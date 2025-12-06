//
// Created by Rares Ionita on 01-Dec-25.
//

#ifndef PROIECT_POO_SPECIFICATIITEHNICE_H
#define PROIECT_POO_SPECIFICATIITEHNICE_H

#include <iostream>
#include <string>

enum TipCombustibil { BENZINA, DIESEL, ELECTRIC, HIBRID, GPL };
enum TipCutie { MANUALA, AUTOMATA };
enum Tractiune { FATA, SPATE, INTEGRALA };

class SpecificatiiTehnice {
private:
    int capacitateCilindrica;
    int putere;
    TipCombustibil combustibil;
    TipCutie cutie;
    Tractiune tractiune;

public:
    SpecificatiiTehnice(int capacitateCilindrica, int putere, TipCombustibil combustibil, TipCutie cutie, Tractiune tractiune);

    [[nodiscard]] std::string combustibilToString() const;
    [[nodiscard]] std::string cutieToString() const;
    [[nodiscard]] std::string tractiuneToString() const;

    friend std::ostream& operator<<(std::ostream& os, const SpecificatiiTehnice& spec);
};

#endif //PROIECT_POO_SPECIFICATIITEHNICE_H//PROIECT_POO_SPECIFICATIITEHNICE_H