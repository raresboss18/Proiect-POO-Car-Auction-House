#include <iostream>
#include <memory>

#include "AuctionManager.h"
#include "Derivate.h"
#include "Microbuz.h"
#include "DataOra.h"
#include "SpecificatiiTehnice.h"
#include "Exceptii.h"

using namespace std;

int main() {
    cout << "===============================================\n";
    cout << "=== SISTEM DE GESTIUNE LICITATII AUTO ===\n";
    cout << "===============================================\n\n";

    try {
        AuctionManager manager("AuctionHouse");

        DataOra dataCurenta = DataOra::obtineOraCurenta();

        SpecificatiiTehnice specAuto(2000, 150, DIESEL, MANUALA, FATA);
        SpecificatiiTehnice specSport(2998, 300, BENZINA, AUTOMATA, SPATE);
        SpecificatiiTehnice specDuba(2200, 130, DIESEL, MANUALA, FATA);
        SpecificatiiTehnice specMicro(2200, 163, DIESEL, AUTOMATA, SPATE);

        manager.inregistrareParticipant(Participant(101, "Ion Tiriac", "ion@business.ro", 100000));
        manager.inregistrareParticipant(Participant(102, "Student FMI", "student@fmi.ro", 500));
        manager.inregistrareParticipant(Participant(103, "Firma Curierat", "logistica@fan.ro", 25000));

        // --- 1. ADAUGARE CU SMART POINTERS ---
        cout << ">>> 1. ADAUGARE VEHICULE (SMART POINTERS) <<<\n";

        // A. Autoturism
        manager.adaugaVehiculInParc(std::make_unique<Autoturism>(
            "BMW-X6-001", "BMW", "X6", 2021, 45000, 30000, specSport, dataCurenta, "Impecabila", true
        ));

        // B. Autoutilitara
        manager.adaugaVehiculInParc(std::make_unique<Autoutilitara>(
            "FORD-TR-002", "Ford", "Transit", 2018, 250000, 12000, specDuba, dataCurenta, "Urme rugina", 3.5
        ));

        // C. Motocicleta
        manager.adaugaVehiculInParc(std::make_unique<Motocicleta>(
            "YAMA-R1-003", "Yamaha", "R1", 2022, 10000, 15000, specSport, dataCurenta, "Ca noua", SPORT
        ));

        // D. Microbuz (TESTARE CLASA NOUA)
        manager.adaugaVehiculInParc(std::make_unique<Microbuz>(
            "MB-SPR-2020", "Mercedes", "Sprinter", 2020, 180000, 35000, specMicro, dataCurenta, "AC functional pasageri", 20));

        cout << "Vehicule adaugate cu succes.\n";

        // --- 2. AFISARE INVENTAR ---
        cout << "\n>>> 2. AFISARE INVENTAR COMPLET <<<\n";
        manager.afiseazaInventar(); // Aici va aparea si Microbuzul automat (polimorfism)

        // --- 3. RAPOARTE SPECIFICE ---
        cout << "\n>>> 3. RAPOARTE SPECIFICE (DYNAMIC_CAST) <<<\n";
        manager.afiseazaAutoturism();
        manager.afiseazaMotocicleta();
        manager.afiseazaAutoutilitara();

        // <--- AICI TESTAM FUNCTIA NOUA PENTRU MICROBUZ --->
        manager.afiseazaMicrobuz();

        // --- 4. LICITATIE ---
        cout << "\n>>> 4. SIMULARE LICITATIE <<<\n";
        manager.creeazaLicitatie("BMW-X6-001", dataCurenta, 120, "Licitatie Premium SUV");
        Licitatie* lic = manager.getLicitatieById(1);

        if (lic != nullptr) {
            Participant* pTiriac = manager.getParticipantById(101);
            Participant* pStudent = manager.getParticipantById(102);

            cout << "--- Incepe Licitarea ---\n";
            lic->inscrieParticipant(pTiriac);
            lic->inscrieParticipant(pStudent);

            cout << "-> Studentul ofera 600 EUR...\n";
            lic->plaseazaOferta(pStudent, 600);

            cout << "-> Tiriac ofera 35000 EUR...\n";
            lic->plaseazaOferta(pTiriac, 35000);

            lic->finalizeazaLicitatie();
        }

        // --- 5. EXCEPTII ---
        cout << "\n>>> 5. TESTARE EXCEPTII <<<\n";
        // TEST A: PretInvalidException (Vehicul)
        cout << "\n[TEST A] Creare vehicul cu pret negativ...\n";
        try {
            Autoturism badCar("BAD", "Test", "Test", 2020, 100, -500, specAuto, dataCurenta, "Err", false);
        } catch (const AuctionException& e) {
            cout << "--> EXCEPTIE PRINSA: " << e.what() << endl;
        }

        // TEST B: LicitatieInvalidaException (Manager)
        cout << "\n[TEST B] Creare licitatie pentru VIN inexistent...\n";
        try {
            manager.creeazaLicitatie("VIN_FANTOMA", dataCurenta, 60, "Fail");
        } catch (const AuctionException& e) {
            cout << "--> EXCEPTIE PRINSA: " << e.what() << endl;
        }

        // TEST C: FonduriInsuficienteException (Participant)
        cout << "\n[TEST C] Retragere suma mai mare decat soldul...\n";
        try {
            if (Participant* pStudent = manager.getParticipantById(102)) {
                pStudent->retragere(5000); // Are doar 500
            }
        } catch (const AuctionException& e) {
            cout << "--> EXCEPTIE PRINSA: " << e.what() << endl;
        }

        // TEST D: SumaInvalidaException (la topUp)
        cout << "\n[TEST D] Adaugare fonduri (topUp) cu suma negativa...\n";
        try {
            if(Participant* pStudent = manager.getParticipantById(102)) {
                pStudent->topUp(-100);
            }
        } catch (const AuctionException& e) {
            cout << "--> EXCEPTIE PRINSA: " << e.what() << endl;
        }

        // TEST E: SumaInvalidaException (la retragere) <--- SCENARIU NOU ADAUGAT
        cout << "\n[TEST E] Retragere fonduri cu suma negativa...\n";
        try {
            if(Participant* pStudent = manager.getParticipantById(102)) {
                pStudent->retragere(-50);
            }
        } catch (const AuctionException& e) {
            cout << "--> EXCEPTIE PRINSA: " << e.what() << endl;
        }

        // Verificare istoric
         if(const Participant* p = manager.getParticipantById(101)) {
            p->afiseazaIstoric();
        }

    } catch (const std::exception& e) {
        cerr << "\nCRITICAL ERROR : " << e.what() << endl;
    }

    cout << "\n=== PROGRAM FINALIZAT CU SUCCES ===\n";
    return 0;
}