//
// Created by Rares Ionita on 29-Nov-25.
//

#include "DataOra.h"
#include <chrono>
#include <ctime>

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
    os<<time.zi<<"/"<<time.luna<<"/"<<time.an<<"  ";
    if (time.ora==0)
        os<<time.ora<<"0:";
    else {
        os<<time.ora<<":";
    }
    if (time.minut==0)
        os<<time.minut<<"0:";
    else {
        os<<time.minut<<":";
    }
    if (time.secunda==0)
        os<<time.secunda<<"0\n";
    else {
        os<<time.secunda<<"\n";
    }
    return os;
}

bool DataOra::operator<(const DataOra& other) const {
    if (an != other.an)
        return an < other.an;
    if (luna != other.luna)
        return luna < other.luna;
    if (zi != other.zi)
        return zi < other.zi;
    if (ora != other.ora)
        return ora < other.ora;
    if (minut != other.minut)
        return minut < other.minut;
    return secunda < other.secunda;
}

bool DataOra::operator>(const DataOra& other) const {
    if (an != other.an)
        return an > other.an;
    if (luna != other.luna)
        return luna > other.luna;
    if (zi != other.zi)
        return zi > other.zi;
    if (ora != other.ora)
        return ora > other.ora;
    if (minut != other.minut)
        return minut > other.minut;
    return secunda > other.secunda;
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
    std::time_t now_time = std::chrono::system_clock::to_time_t(
        std::chrono::system_clock::now()
    );

    std::tm local_tm;
    std::memset(&local_tm, 0, sizeof(std::tm));

#if defined(_WIN32) || defined(_MSC_VER)
    localtime_s(&local_tm, &now_time);
#else
    localtime_r(&now_time, &local_tm);
#endif

    return DataOra(
        local_tm.tm_year + 1900,
        local_tm.tm_mon + 1,
        local_tm.tm_mday,
        local_tm.tm_hour,
        local_tm.tm_min,
        local_tm.tm_sec
    );
}
