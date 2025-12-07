//
// Created by Rares Ionita on 29-Nov-25.
//

#include "DataOra.h"
#include <iostream>

using namespace std;

void DataOra::valideaza() {
    if (luna < 1 || luna > 12) luna = 1;
    if (zi < 1 || zi > 31) zi = 1;
    if (ora < 0 || ora > 23) ora = 0;
    if (minut < 0 || minut > 59) minut = 0;
    if (secunda < 0 || secunda > 59) secunda = 0;
}

DataOra::DataOra(int an, int luna, int zi, int ora, int minut, int secunda) {
    this->an = an;
    this->luna = luna;
    this->zi = zi;
    this->ora = ora;
    this->minut = minut;
    this->secunda = secunda;
    valideaza();
}

ostream& operator<<(ostream& os, const DataOra& time) {
    os << time.zi << "/" << time.luna << "/" << time.an << "  ";
    
    if (time.ora < 10) os << "0";
    os << time.ora << ":";
    
    if (time.minut < 10) os << "0";
    os << time.minut << ":";
    
    if (time.secunda < 10) os << "0";
    os << time.secunda;
    
    return os;
}

bool DataOra::operator<(const DataOra& other) const {
    if (an != other.an) return an < other.an;
    if (luna != other.luna) return luna < other.luna;
    if (zi != other.zi) return zi < other.zi;
    if (ora != other.ora) return ora < other.ora;
    if (minut != other.minut) return minut < other.minut;
    return secunda < other.secunda;
}

bool DataOra::operator>(const DataOra& other) const {
    return other < *this;
}

void DataOra::adaugaMinute(int minuteAdaugate) {
    minut += minuteAdaugate;
    while (minut >= 60) {
        minut -= 60;
        ora++;
        if (ora >= 24) {
            ora -= 24;
            zi++;
        }
    }
    valideaza();
}

DataOra DataOra::obtineOraCurenta() {
    // simulam timpul 
    static int minuteSimulate = 0;
    
    // pornim de la 07.12.2025, ora 12:00
    DataOra time(2025, 12, 7, 12, 0, 0);
    
    // avansam timpul
    time.adaugaMinute(minuteSimulate);
    
    //pPregatim urmatorul apel sa fie cu 60 minute mai tarziu
    minuteSimulate += 60;
    
    return time;
}
