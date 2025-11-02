#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <utility>
#include <vector>
#include <chrono>
#include <ctime>

using namespace std;

class DataOra {
private:

    int an;
    int luna;
    int zi;
    int ora;
    int minut;
    int secunda;

    void valideaza() {
        if (luna < 1 || luna > 12) luna = 1;
        if (zi < 1 || zi > 31) zi = 1;
        if (ora < 0 || ora > 23) ora = 0;
        if (minut < 0 || minut > 59) minut = 0;
        if (secunda < 0 || secunda > 59) secunda = 0;
    }

public:

    explicit DataOra(int an = 2025, int luna = 1, int zi = 1, int ora = 12, int minut = 0, int secunda = 0) {
        this->an = an;
        this->luna = luna;
        this->zi = zi;
        this->ora = ora;
        this->minut = minut;
        this->secunda = secunda;
        valideaza();
    }

    friend ostream& operator<<(ostream& os, const DataOra& time) {
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

    bool operator<(const DataOra& other) const {
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

    bool operator>(const DataOra& other) const {
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

    void adaugaMinute(int minuteAdaugate) {
        minut=minut+minuteAdaugate;
        while (minut >= 60) {
            minut-=60;
            ora++;
            if (ora >= 24) {
                ora-=24;
                zi++;
            }
        }
       valideaza();
    }
};

class Participant {
private:

    const int idParticipant;
    string numeParticipant;
    string email;
    double soldCurent;
    double* istoricSolduri;
    int capacitateIstoric;
    int numarIstoric;

    void actualizeazaIstoric() {
        if (numarIstoric<capacitateIstoric) {
            numarIstoric++;
        }
        for (int i = numarIstoric-1; i >0; i--) {
            istoricSolduri[i] = istoricSolduri[i-1];
        }
        istoricSolduri[0] = soldCurent;
        cout << "Soldul lui " << numeParticipant << " a fost actualizat la " << soldCurent << " EUR.\n";
    }

public:

    Participant(int idParticipant, string  numeParticipant, string  email, double soldCurent) :
    idParticipant(idParticipant), numeParticipant(std::move(numeParticipant)), email(std::move(email)), soldCurent(soldCurent),capacitateIstoric(10),numarIstoric(1){

        istoricSolduri = new double[capacitateIstoric];
        istoricSolduri[0] = soldCurent;
        for (int i = 1; i < capacitateIstoric; i++) {
            istoricSolduri[i] = 0;
        }
    }

    ~Participant() {
        delete[] istoricSolduri;
        istoricSolduri=nullptr;
    }
    Participant(const Participant& other) : idParticipant(other.idParticipant), numeParticipant(other.numeParticipant), email(other.email), soldCurent(other.soldCurent), capacitateIstoric(other.capacitateIstoric), numarIstoric(other.numarIstoric) {
        istoricSolduri = new double[capacitateIstoric];
        for (int i = 0; i < capacitateIstoric; i++) {
            istoricSolduri[i] = other.istoricSolduri[i];
        }
    }

    Participant& operator=(Participant other) {
        swap(numeParticipant, other.numeParticipant);
        swap(email, other.email);
        swap(soldCurent, other.soldCurent);
        swap(capacitateIstoric, other.capacitateIstoric);
        swap(istoricSolduri, other.istoricSolduri);
        swap(numarIstoric, other.numarIstoric);
        return *this;
    }

    friend ostream& operator<<(ostream& os, const Participant& participant) {
        os << "ID: " << participant.idParticipant<<"\n";
        os << "Nume: " << participant.numeParticipant<<"\n";
        os << "Email: " << participant.email<<"\n";
        os << "Sold curent: " << participant.soldCurent<<"\n";
        os << "Istoric solduri:  ";
        for (int  i = 0; i < participant.numarIstoric ; i++) {
            os << participant.istoricSolduri[i]<<" ";
        }
        os << "\n";

        return os;
    }

    void topUp(double suma) {
        if (suma<=0) {
            cout<<"Suma invalida pentru topUp! introduceti o suma pozitiva!\n";
            return;
        }
        soldCurent = suma+soldCurent;
        actualizeazaIstoric();
    }

    void retragere(double suma) {
        if (suma<=0) {
            cout<<"Suma invalida pentru retragere! introduceti o suma pozitiva!\n";
            return;
        }
        if (suma>soldCurent) {
            cout<<"Donduri insuficiente!\n";
            return;
        }
        soldCurent = soldCurent-suma;
        actualizeazaIstoric();
    }

    void afiseazaIstoric() const {
        cout<<"Istoric solduri pentru "<<numeParticipant<<":\n";
        for (int i = 0; i < numarIstoric; i++) {
            cout << istoricSolduri[i]<<" ";
        }
        cout << "\n";
    }

    [[nodiscard]] const string& getNume() const {
        return numeParticipant;
    }

    [[nodiscard]] double getSold() const {
        return soldCurent;
    }

    [[nodiscard]] int getId() const {
        return idParticipant;
    }

};

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

    SpecificatiiTehnice(int capacitateCilindrica, int putere, TipCombustibil combustibil, TipCutie cutie, Tractiune tractiune) :
    capacitateCilindrica(capacitateCilindrica), putere(putere), combustibil(combustibil), cutie(cutie), tractiune(tractiune) {}

    [[nodiscard]] string combustibilToString() const {
        switch (combustibil) {
            case BENZINA: return "Benzina";
            case DIESEL: return "Diesel";
            case ELECTRIC: return "Electric";
            case HIBRID: return "Hibrid";
            case GPL: return "GPL";
            default: return "";
        }
    }

    [[nodiscard]] string cutieToString() const {
        switch (cutie) {
            case MANUALA: return "Manuala";
            case AUTOMATA: return "Automata";
            default: return "";
        }
    }

    [[nodiscard]] string tractiuneToString() const {
        switch (tractiune) {
            case FATA: return "Fata";
            case SPATE: return "Spate";
            case INTEGRALA: return "Integrala";
            default: return "";
        }
    }

    friend ostream& operator<<(ostream& os, const SpecificatiiTehnice& spec) {
        os << "Capacitate: " << spec.capacitateCilindrica << "cmc\n";
        os << "Putere: " << spec.putere << " CP\n";
        os << "Combustibil: " << spec.combustibilToString() << "\n";
        os << "Cutie de viteze: " << spec.cutieToString() << "\n";
        os << "Tractiune: " << spec.tractiuneToString() << "\n";
        return os;
    }
};

class Vehicul {
private:
    string vin;
    string marca;
    string model;
    int anFabricatie;
    int kilometraj;
    int pretInitial;
    char* observatiiTehnice;

    SpecificatiiTehnice specificatiiTehnice;
    DataOra dataOra;

public:

    Vehicul(string  vin, string  marca, string  model, int anFabricatie, int kilometraj, int pretInitial, const SpecificatiiTehnice& specificatiiTehnice, const DataOra& dataOra, const string& observatiiTehnice) :
    vin(std::move(vin)), marca(std::move(marca)), model(std::move(model)), anFabricatie(anFabricatie), kilometraj(kilometraj), pretInitial(pretInitial), specificatiiTehnice(specificatiiTehnice), dataOra(dataOra) {
        this->observatiiTehnice= new char[observatiiTehnice.length()+1];
        strcpy(this->observatiiTehnice, observatiiTehnice.c_str());
    }

    ~Vehicul() {
        delete[] observatiiTehnice;
        observatiiTehnice= nullptr;
    }

    Vehicul(Vehicul&& other) noexcept :
    vin(std::move(other.vin)), marca(std::move(other.marca)), model(std::move(other.model)), anFabricatie(other.anFabricatie), kilometraj(other.kilometraj), pretInitial(other.pretInitial), specificatiiTehnice(other.specificatiiTehnice), dataOra(other.dataOra) {
        this->observatiiTehnice=other.observatiiTehnice;
        other.observatiiTehnice = nullptr;
    }

    Vehicul& operator=(Vehicul&& other)  noexcept {
        if (this != &other) {
            this->vin=std::move(other.vin);
            this->marca=std::move(other.marca);
            this->model=std::move(other.model);
            this->dataOra=other.dataOra;
            this->specificatiiTehnice=other.specificatiiTehnice;

            this->anFabricatie=other.anFabricatie;
            this->kilometraj=other.kilometraj;
            this->pretInitial=other.pretInitial;

            delete[] this->observatiiTehnice;
            this->observatiiTehnice=other.observatiiTehnice;
            other.observatiiTehnice = nullptr;
        }
        return *this;
    }

    Vehicul(const Vehicul& other):
    vin(other.vin), marca(other.marca), model(other.model), anFabricatie(other.anFabricatie), kilometraj(other.kilometraj), pretInitial(other.pretInitial), specificatiiTehnice(other.specificatiiTehnice), dataOra(other.dataOra) {
        this->observatiiTehnice=new char[strlen(other.observatiiTehnice)+1];
        strcpy(this->observatiiTehnice, other.observatiiTehnice);
    }

    Vehicul& operator=(const Vehicul& other) {
        if(this != &other) {
            this->vin=other.vin;
            this->marca=other.marca;
            this->model=other.model;
            this->anFabricatie = other.anFabricatie;
            this->kilometraj = other.kilometraj;
            this->pretInitial = other.pretInitial;
            this->specificatiiTehnice = other.specificatiiTehnice;
            this->dataOra = other.dataOra;

            delete[] this->observatiiTehnice;
            this->observatiiTehnice = new char[strlen(other.observatiiTehnice) + 1];
            strcpy(this->observatiiTehnice, other.observatiiTehnice);
        }
        return *this;
    }


    [[nodiscard]] double calculPretRezerva() const {
        double pretRezerva = pretInitial * 1.0;
        int vechime = 2025 - anFabricatie;
        if (vechime>0)
            for (int i=0; i < vechime; i++)
                pretRezerva=pretRezerva*0.9;

        if (kilometraj>150000)
            pretRezerva=pretRezerva*0.9;
        if (kilometraj>250000)
            pretRezerva=pretRezerva*0.9;
        if (kilometraj>350000)
            pretRezerva=pretRezerva*0.9;

        return pretRezerva;
    }

    friend ostream& operator<<(ostream& os,const Vehicul& vehicul) {
        os << "VIN: " << vehicul.vin << "\n";
        os << "Marca: " << vehicul.marca << "\n";
        os << "Model: " << vehicul.model << "\n";
        os << "An fabricatie: " << vehicul.anFabricatie << "\n";
        os << "Kilometraj: " << vehicul.kilometraj << "\n";
        os<< "Specificatii: " << vehicul.specificatiiTehnice <<"\n";
        os << "Primul pret: "<< vehicul.calculPretRezerva() << "\n";
        os << "Data listarii: "<< vehicul.dataOra << "\n";
        if (vehicul.observatiiTehnice != nullptr)
            os<<"Observatii: "<<vehicul.observatiiTehnice<<"\n";
        return os;
    }

    [[nodiscard]] const string& getVIN() const {
        return vin;
    }

};

DataOra obtineOraCurenta() {
    auto now = chrono::system_clock::now();
    time_t now_time = chrono::system_clock::to_time_t(now);

    tm local_tm = *localtime(&now_time);

    return DataOra(
        local_tm.tm_year + 1900,
        local_tm.tm_mon + 1,
        local_tm.tm_mday,
        local_tm.tm_hour,
        local_tm.tm_min,
        local_tm.tm_sec
    );
}

class Licitatie {
private:
    const int idLicitatie;
    Vehicul vehiculVanzare;
    DataOra dataStart;
    DataOra dataEnd;
    int durataMinute;
    double pretCurent;
    Participant* castigatorCurent;
    vector<Participant*> participants;
    char* descriereEveniment;

public:
    Licitatie(int idLicitatie, Vehicul  vehiculVanzare, const DataOra& dataStart, int durataMinute , const string& descriereEveniment) :
    idLicitatie(idLicitatie), vehiculVanzare(std::move(vehiculVanzare)), dataStart(dataStart), durataMinute(durataMinute),pretCurent(0.0), castigatorCurent(nullptr) {

        this->pretCurent = this->vehiculVanzare.calculPretRezerva();
        this->descriereEveniment = new char[descriereEveniment.length() + 1];
        strcpy(this->descriereEveniment, descriereEveniment.c_str());
        this->dataEnd = this->dataStart;
        this->dataEnd.adaugaMinute(this->durataMinute);
    }

    ~Licitatie() {
        delete[] this->descriereEveniment;
    }

    Licitatie(const Licitatie& other) :
    idLicitatie(other.idLicitatie),vehiculVanzare(other.vehiculVanzare),dataStart(other.dataStart),dataEnd(other.dataEnd),durataMinute(other.durataMinute),
    pretCurent(other.pretCurent),castigatorCurent(other.castigatorCurent),participants(other.participants) {
        this->descriereEveniment = new char[strlen(other.descriereEveniment)+1];
        strcpy(this->descriereEveniment, other.descriereEveniment);
    }

    Licitatie& operator=(const Licitatie& other){
        if (this != &other) {
            this->vehiculVanzare=other.vehiculVanzare;
            this->dataStart=other.dataStart;
            this->durataMinute=other.durataMinute;
            this->dataEnd=other.dataEnd;
            this->pretCurent = other.pretCurent;
            this->castigatorCurent = other.castigatorCurent;
            this->participants=other.participants;

            delete[] this->descriereEveniment;
            this->descriereEveniment = new char[strlen(other.descriereEveniment)+1];
            strcpy(this->descriereEveniment, other.descriereEveniment);
        }
        return *this;
   }


    Licitatie(Licitatie&& other)  noexcept :
    idLicitatie(other.idLicitatie), vehiculVanzare(std::move(other.vehiculVanzare)),dataStart(other.dataStart), dataEnd(other.dataEnd),
    durataMinute(other.durataMinute), pretCurent(other.pretCurent), castigatorCurent(other.castigatorCurent), participants(std::move(other.participants)) {
        this->descriereEveniment = other.descriereEveniment;
        other.descriereEveniment = nullptr;
    }

    Licitatie& operator=(Licitatie&& other)  noexcept {
        if (this != &other) {
            delete[] this->descriereEveniment;
            this->vehiculVanzare = std::move(other.vehiculVanzare);
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

    void inscrieParticipant(Participant* p) {
        if (p != nullptr) {
            participants.push_back(p);
            cout << "Participantul " << p->getNume() << " s-a inscris la licitatia " << this->idLicitatie << ".\n";
        }
    }

    void plaseazaOferta(Participant* ofertant, double sumaOferita) {

        if (obtineOraCurenta() > this->dataEnd) {
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

    friend ostream& operator<<(ostream& os, const Licitatie& licitatie){
        os<<"ID licitatie: "<<licitatie.idLicitatie<<endl;
        if(licitatie.descriereEveniment != nullptr){
              os<<licitatie.descriereEveniment<<endl;
        }
        os<<"Vehicul vanzare: "<<licitatie.vehiculVanzare<<endl;
        os<<"Data start: "<<licitatie.dataStart<<endl;
        os<<"Data end: "<<licitatie.dataEnd<<endl;
        os<<"pret curent: "<<licitatie.pretCurent<<endl;
        if(licitatie.castigatorCurent!=nullptr){
            os<<*(licitatie.castigatorCurent)<<endl;
        } else {
            os<<"Momentan nu a fost inregistrata nici o oferta";
        }

        return os;

    }

    [[nodiscard]] int getId() const {
        return idLicitatie;
    }

    [[nodiscard]] Participant* getCastigatorCurent() const {
        return castigatorCurent;
    }

    [[nodiscard]] const Vehicul& getVehicul() const {
        return vehiculVanzare;
    }

    void finalizeazaLicitatie() const {
        cout << "Final licitatie ID: " << this->idLicitatie << "\n";

        if (obtineOraCurenta() > this->dataEnd) {
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


};

class AuctionManager{
private:

    string numeCasaLicitatii;
    vector<Vehicul> inventarVehicule;
    vector<Participant> listaParticipanti;
    vector<Licitatie> listaLicitatii;
    int nextLicitatieId;

public:

    explicit AuctionManager(string  numeCasaLicitatii) : numeCasaLicitatii(std::move(numeCasaLicitatii)), nextLicitatieId(1) {}

    void inregistrareParticipant(const Participant& p) {
        listaParticipanti.push_back(p);
    }

    Participant* getParticipantById(int id) {
        for (auto& p : listaParticipanti) {
            if (p.getId() == id) {
                return &p;
            }
        }
        return nullptr;
    }

    void adaugaVehiculInParc(Vehicul&& vehicul) {
        inventarVehicule.push_back(std::move(vehicul));
    }

    void creeazaLicitatie(const string& vin, const DataOra& start, int durata, const string& descriere) {
        const Vehicul* vehiculLicitatie = nullptr;
        for (auto& v : inventarVehicule) {
            if (v.getVIN() == vin) {
                vehiculLicitatie = &v;
                break;
            }
        }

        if (vehiculLicitatie != nullptr) {
            Licitatie licitatieNoua(nextLicitatieId++, *vehiculLicitatie, start, durata, descriere);
            listaLicitatii.push_back(std::move(licitatieNoua)); // Adaugam eficient licitatia in lista
            cout << "-> Licitatie noua creata cu succes pentru vehiculul cu VIN: " << vin << endl;
        } else {
            cout << "Vehiculul cu VIN " << vin << " nu a fost gasit in inventar.\n";
        }
    }

    Licitatie* getLicitatieById(int id) {
        for (auto& lic : listaLicitatii) {
            if (lic.getId() == id) {
                return &lic;
            }
        }
        return nullptr;
    }

    void afiseazaInventar() const {
        cout << "Inventar Vehicule (" << numeCasaLicitatii << ")\n";
        for (const auto& v : inventarVehicule) {
            cout << v;
        }
    }

    friend ostream& operator<<(ostream& os, const AuctionManager& manager) {
        os << "Nume: " << manager.numeCasaLicitatii << "\n";
        os << "Participanti inregistrati: " << manager.listaParticipanti.size() << "\n";
        os << "Vehicule in inventar: " << manager.inventarVehicule.size() << "\n";
        os << "Licitatii create: " << manager.listaLicitatii.size() << "\n";
        return os;
    }

};

Vehicul creeazaVehiculTemporar() {
    SpecificatiiTehnice specs(1598, 115, BENZINA, MANUALA, FATA);
    DataOra data(2025, 3, 15, 10, 0);
    // Cream un obiect local, temporar
    Vehicul v_temp("VIN_TEMP_123", "VW", "Golf 5", 2008, 210000, 4000, specs, data, "Uzura normala conform varstei");
    return v_temp;
}

int main() {
    cout << "====================================================\n";
    cout << "## INITIALIZARE SISTEM DE LICITATII AUTO ##\n";
    cout << "====================================================\n";
    AuctionManager manager("AuctionHouse SRL");
    cout << manager << endl;

    // ---------------------------------------------------------
    cout << "====================================================\n";
    cout << "## GESTIONARE PARTICIPANTI ##\n";
    cout << "====================================================\n";

    manager.inregistrareParticipant(Participant(101, "Ana Popescu", "ana.popescu@cti.ro", 25000.0));
    manager.inregistrareParticipant(Participant(102, "Mihai Ionescu", "mihai.ionescu@cti.ro", 75000.0));
    manager.inregistrareParticipant(Participant(103, "Ioana Marinescu", "ioana.marinescu@cti.ro", 15000.0));
    manager.inregistrareParticipant(Participant(104, "Radu Vasilescu", "radu.v@cti.ro", 90000.0));
    manager.inregistrareParticipant(Participant(105, "Elena Dragomir", "elena.d@cti.ro", 5000.0));

    cout << "\n--> Testare eroare: Cautare ID inexistent (999)...\n";
    Participant* pFake = manager.getParticipantById(999);
    if (pFake == nullptr) {
        cout << "SUCCES: Participantul cu ID 999 nu a fost gasit.\n";
    } else {
        cout << "EROARE: Gasit participant inexistent: " << *pFake << "\n";
    }

    Participant* pAna = manager.getParticipantById(101);
    Participant* pMihai = manager.getParticipantById(102);
    Participant* pIoana = manager.getParticipantById(103);
    Participant* pRadu = manager.getParticipantById(104);
    Participant* pElena = manager.getParticipantById(105);

    if (pElena) {
        cout << "\n--> Testare operatii pe " << pElena->getNume() << ":\n";
        pElena->topUp(500);
        pElena->retragere(200);
        pElena->retragere(99999); // caz invalid (fonduri insuficiente)
        pElena->afiseazaIstoric();
    }

    cout << "\n====================================================\n";
    cout << "## ADAUGARE VEHICULE IN INVENTAR (EXTINS) ##\n";
    cout << "====================================================\n";

    manager.adaugaVehiculInParc(creeazaVehiculTemporar()); // VW Golf (VIN_TEMP_123)

    SpecificatiiTehnice specsAudi(1968, 190, DIESEL, AUTOMATA, INTEGRALA);
    SpecificatiiTehnice specsTesla(0, 450, ELECTRIC, AUTOMATA, INTEGRALA);
    SpecificatiiTehnice specsDacia(1461, 115, DIESEL, MANUALA, FATA);
    DataOra dataAudi(2025, 10, 25, 15, 45);
    DataOra dataTesla(2025, 10, 29, 22, 0);
    DataOra dataDacia(2025, 11, 1, 10, 0);

    manager.adaugaVehiculInParc(Vehicul("VIN987ABC", "Audi", "A6", 2021, 85000, 32000, specsAudi, dataAudi, "Stare excelenta"));
    manager.adaugaVehiculInParc(Vehicul("VIN555TES", "Tesla", "Model S", 2022, 30000, 65000, specsTesla, dataTesla, "Autonomie mare"));
    manager.adaugaVehiculInParc(Vehicul("VIN111DAC", "Dacia", "Duster", 2019, 95000, 12000, specsDacia, dataDacia, "4x2, economic"));


    cout << "\n>>> Inventar actual:\n";
    manager.afiseazaInventar();

    // ---------------------------------------------------------
    cout << "\n====================================================\n";
    cout << "## CREARE LICITATII MULTIPLE SI TESTE DE EROARE ##\n";
    cout << "====================================================\n";

    // Le pornim pe toate acum
    DataOra start1 = obtineOraCurenta();
    DataOra start2 = obtineOraCurenta();
    DataOra start3 = obtineOraCurenta();

    // Licitatie pentru Bidding War
    manager.creeazaLicitatie("VIN555TES", start1, 5, "Licitatie Tesla Model S - Bid War");
    // Licitatie care va esua (fara oferte)
    manager.creeazaLicitatie("VIN111DAC", start2, 2, "Licitatie Dacia Duster - Fără Oferte");
    // Licitatie pentru testare Copiere/Mutare
    manager.creeazaLicitatie("VIN_TEMP_123", start3, 1, "Licitatie VW Golf - Pentru testare operatori");

    cout << "\n--> Testare eroare: Creare licitatie pentru VIN inexistent (VIN_FAKE)...\n";
    manager.creeazaLicitatie("VIN_FAKE", start1, 5, "Test esuat");

    Licitatie* licTesla = manager.getLicitatieById(1);
    Licitatie* licDacia = manager.getLicitatieById(2);
    Licitatie* licGolf = manager.getLicitatieById(3);

    // ---------------------------------------------------------
    cout << "\n====================================================\n";
    cout << "## LICITATIE #1: TESLA (RAZBOI AL OFERTELOR) ##\n";
    cout << "====================================================\n";
    if (licTesla && pMihai && pRadu && pAna) {
        cout << "Stari initiale participanti:\n" << *pMihai << "\n" << *pRadu << "\n" << *pAna << "\n";

        licTesla->inscrieParticipant(pMihai);
        licTesla->inscrieParticipant(pRadu);
        licTesla->inscrieParticipant(pAna);

        double pretPornireTesla = licTesla->getVehicul().calculPretRezerva();
        cout << "\n--- Incepe licitatia pentru Tesla (Pornire: " << pretPornireTesla << ") ---\n";

        licTesla->plaseazaOferta(pAna, 60000);   // Prea mica (sub pret pornire calculat)
        licTesla->plaseazaOferta(pMihai, 66000); // OK (presupunand ca pornirea e ~65k)
        licTesla->plaseazaOferta(pRadu, 68000);  // OK
        licTesla->plaseazaOferta(pMihai, 70000); // OK
        licTesla->plaseazaOferta(pRadu, 72000);  // OK
        licTesla->plaseazaOferta(pMihai, 74000); // OK
        licTesla->plaseazaOferta(pRadu, 80000);  // OK (Radu are 90k)
        licTesla->plaseazaOferta(pMihai, 82000); // EROARE: Mihai are doar 75k (fonduri insuficiente)
        licTesla->plaseazaOferta(pAna, 75000);   // EROARE: Ana are doar 25k (fonduri insuficiente)

        cout << "\n--- Stare inainte de finalizare (Licitatia #1) ---\n";
        cout << *licTesla << "\n";
    }

    // ---------------------------------------------------------
    cout << "\n====================================================\n";
    cout << "## LICITATIE #2: DACIA (LICITATIE ESUATA) ##\n";
    cout << "====================================================\n";
    if (licDacia && pIoana && pElena) {
        licDacia->inscrieParticipant(pIoana);
        licDacia->inscrieParticipant(pElena);

        cout << "\n--- Nicio oferta plasata pentru Licitatia #2 ---\n";
        cout << "\n--- Stare inainte de finalizare (Licitatia #2) ---\n";
        cout << *licDacia << "\n";
    }

    // ---------------------------------------------------------
    cout << "\n====================================================\n";
    cout << "## FINALIZARE LICITATII (Test Apel) ##\n";
    cout << "====================================================\n";

    if (licTesla) {
        cout << "\nFinalizare licitatie 1 (Tesla):\n";
        licTesla->finalizeazaLicitatie();
    }
    if (licDacia) {
        cout << "\nFinalizare licitatie 2 (Dacia):\n";
        licDacia->finalizeazaLicitatie();
    }

    // ---------------------------------------------------------
    cout << "\n====================================================\n";
    cout << "## TESTARE OPERATORI COPIERE SI MUTARE (REGULA LUI 5) ##\n";
    cout << "====================================================\n";

    cout << "\n-> Copiere Vehicul (Test Vehicul::Vehicul(const Vehicul&)):\n";
    Vehicul vehTemp = creeazaVehiculTemporar();
    Vehicul vehCopie(vehTemp);
    cout << "Original:\n" << vehTemp << "Copie:\n" << vehCopie << "\n";

    cout << "\n-> Mutare Vehicul (Test Vehicul::Vehicul(Vehicul&&)):\n";
    Vehicul vehMutat = std::move(vehTemp);
    cout << "Obiect mutat:\n" << vehMutat << "\n";
    // cout << vehTemp << "\n"; // Ar trebui sa fie intr-o stare goala/valida

    cout << "\n-> Copiere Licitatie (Test Licitatie::Licitatie(const Licitatie&)):\n";
    if (licTesla) {
        cout << "Se copiaza licitatia Tesla (care are oferte si participanti)...\n";
        Licitatie licCopy = *licTesla;
        cout << "--- LICITATIE ORIGINALA ---\n" << *licTesla << "\n";
        cout << "--- LICITATIE COPIATA ---\n" << licCopy << "\n";

        cout << "Se plaseaza o oferta pe COPIE (nu ar trebui sa afecteze originalul):\n";
        licCopy.plaseazaOferta(pRadu, 90000); // pRadu are 90k, oferta valida

        Participant* castigatorCopie = licCopy.getCastigatorCurent();
        Participant* castigatorOriginal = licTesla->getCastigatorCurent();

        cout << "Castigator curent COPIE: " << (castigatorCopie ? castigatorCopie->getNume() : "N/A") << endl;
        cout << "Castigator curent ORIGINAL: " << (castigatorOriginal ? castigatorOriginal->getNume() : "N/A") << endl;
    }

    cout << "\n-> Mutare Licitatie (Test Licitatie::Licitatie(Licitatie&&)):\n";
    if (licGolf) {
        cout << "Se muta licitatia Golf...\n";
        Licitatie licMoved = std::move(*licGolf);
        cout << "--- LICITATIE MUTATA ---\n" << licMoved << "\n";
        // *licGolf este acum intr-o stare nedefinita (mutata)
    }

    cout << "\n====================================================\n";
    cout << "## STARE FINALA SISTEM ##\n";
    cout << "====================================================\n";
    cout << manager << endl;

    cout << "\n--- Starea finala a participantilor (dupa operatii in memorie) ---\n";
    if (pAna) cout << *pAna << endl;
    if (pMihai) cout << *pMihai << endl;
    if (pIoana) cout << *pIoana << endl;
    if (pRadu) cout << *pRadu << endl;
    if (pElena) cout << *pElena << endl;

    cout << "\n====================================================\n";
    cout << "## SFARSITUL SIMULARII ##\n";
    cout << "====================================================\n";

    return 0;
}
