//
// Created by Rares Ionita on 29-Nov-25.
//

#ifndef PROIECT_POO_DATAORA_H
#define PROIECT_POO_DATAORA_H
#include <iostream>

class DataOra {
private:

    int an;
    int luna;
    int zi;
    int ora;
    int minut;
    int secunda;

    void valideaza();

public:

    explicit DataOra(int an = 2025, int luna = 1, int zi = 1, int ora = 12, int minut = 0, int secunda = 0);
    static DataOra obtineOraCurenta();
    friend std::ostream& operator<<(std::ostream& os, const DataOra& time);
    bool operator<(const DataOra& other) const;
    bool operator>(const DataOra& other) const;
    void adaugaMinute(int minuteAdaugate);
};




#endif //PROIECT_POO_DATAORA_H