#include <iostream>

#include "AuctionManager.h"
#include "Derivate.h"
#include "DataOra.h"
#include "SpecificatiiTehnice.h"
#include "Exceptii.h"

using namespace std;

int main() {
    cout << "===============================================\n";
    cout << "=== SISTEM DE GESTIUNE LICITATII AUTO ===\n";
    cout << "===============================================\n\n";

    try {
        // 1. Initializare Manager
        AuctionManager manager("AuctionHouse");

        // 2. Setup Date Comune si Specificatii
        DataOra dataCurenta = DataOra::obtineOraCurenta();

        SpecificatiiTehnice specDiesel(2000, 150, DIESEL, MANUALA, FATA);
        SpecificatiiTehnice specSport(2998, 300, BENZINA, AUTOMATA, SPATE);
        SpecificatiiTehnice specDuba(2200, 130, DIESEL, MANUALA, FATA);

        // 3. Inregistrare Participanti
        manager.inregistrareParticipant(Participant(101, "Ion Tiriac", "ion@business.ro", 1000000));
        manager.inregistrareParticipant(Participant(102, "Student FMI", "student@fmi.ro", 500)); // Buget mic
        manager.inregistrareParticipant(Participant(103, "Firma Curierat", "logistica@fan.ro", 25000));

        cout << ">>> 1. ADAUGARE VEHICULE (POLIMORFISM & ALOCARE DINAMICA) <<<\n";

        // A. Autoturism (Coupe -> Pretul creste)
        manager.adaugaVehiculInParc(new Autoturism("BMW-X6-001", "BMW", "X6", 2021, 45000, 30000, specSport, dataCurenta, "Impecabila", true));

        // B. Autoutilitara (Masa > 3.5 -> Pretul creste)
        manager.adaugaVehiculInParc(new Autoutilitara("FORD-TR-002", "Ford", "Transit", 2018, 250000, 12000, specDuba, dataCurenta, "Urme rugina", 3.5));

        // C. Motocicleta (Sport -> Pretul scade la revanzare)
        manager.adaugaVehiculInParc(new Motocicleta("YAMA-R1-003", "Yamaha", "R1", 2022, 10000, 15000, specSport, dataCurenta, "Ca noua", SPORT));

        cout << "Vehicule adaugate cu succes.\n";

        // 4. Afisare Inventar (Testeaza 'afisareVirtuala', 'afiseaza' si 'afisareDetalii')
        cout << "\n>>> 2. AFISARE INVENTAR COMPLET (NVI PATTERN) <<<\n";
        manager.afiseazaInventar();

        // 5. Testare Rapoarte Specifice (Testeaza 'dynamic_cast')
        cout << "\n>>> 3. RAPOARTE SPECIFICE (DYNAMIC_CAST) <<<\n";
        manager.afiseazaAutoturism();
        manager.afiseazaMotocicleta();
        manager.afiseazaAutoutilitara();

        // 6. Fluxul Licitatiei
        cout << "\n>>> 4. SIMULARE LICITATIE <<<\n";

        // Cream licitatie pentru BMW (se foloseste clone() in spate)
        // Daca VIN-ul este gresit, aici se arunca LicitatieInvalidaException
        manager.creeazaLicitatie("BMW-X6-001", dataCurenta, 120, "Licitatie Premium SUV");

        // Obtinem pointer la licitatia creata (ID 1)
        Licitatie* lic = manager.getLicitatieById(1);

        if (lic != nullptr) {
            // Luam pointeri la participanti existenti
            Participant* pTiriac = manager.getParticipantById(101);
            Participant* pStudent = manager.getParticipantById(102);

            cout << "--- Incepe Licitarea ---\n";
            cout << *lic << endl; // Afisam starea initiala

            // Inscriem participantii
            lic->inscrieParticipant(pTiriac);
            lic->inscrieParticipant(pStudent);

            // Scenariu 1: Oferta prea mica (Sub pretul de rezerva calculat virtual)
            cout << "-> Studentul ofera 600 EUR...\n";
            lic->plaseazaOferta(pStudent, 600);

            // Scenariu 2: Oferta valida
            cout << "-> Tiriac ofera 35000 EUR...\n";
            lic->plaseazaOferta(pTiriac, 35000);

            // Folosim getCastigatorCurent
            if(lic->getCastigatorCurent() != nullptr) {
                cout << "Verificare getter: Castigatorul curent este " << lic->getCastigatorCurent()->getNume() << endl;
            }
            // Folosim getVehicul
            if(lic->getVehicul() != nullptr) {
                cout << "Verificare getter: Vehiculul licitat are VIN " << lic->getVehicul()->getVIN() << endl;
            }

            cout << "\n--- Status Licitatie ---\n";
            // Aici se retrag banii din contul lui Tiriac
            lic->finalizeazaLicitatie();
        }

        // 7. TESTARE EXCEPTII (Blocuri try-catch interne pentru demo)
        cout << "\n>>> 5. TESTARE EXCEPTII <<<\n";

        // TEST A: Creare vehicul cu pret negativ (Constructor Vehicul)
        cout << "\n[TEST A] Incercare creare vehicul cu pret -500...\n";
        try {
            Autoturism badCar("BAD", "Test", "Test", 2020, 100, -500, specDiesel, dataCurenta, "Err", false);
        } catch (const AuctionException& e) {
            cout << "--> EXCEPTIE PRINSA: " << e.what() << endl;
        }

        // TEST B: Creare licitatie pentru VIN inexistent (Manager)
        cout << "\n[TEST B] Creare licitatie pentru VIN 'FANTOMA'...\n";
        try {
            manager.creeazaLicitatie("VIN_FANTOMA", dataCurenta, 60, "Fail");
        } catch (const AuctionException& e) {
            cout << "--> EXCEPTIE PRINSA: " << e.what() << endl;
        }

        // TEST C: Fonduri Insuficiente (Participant)
        cout << "\n[TEST C] Studentul incearca sa retraga 5000 EUR (are doar 500)...\n";
        try {
            if ( Participant* pStudent = manager.getParticipantById(102)) {
                // Apeleaza direct retragere pentru a declansa exceptia din Participant.cpp
                pStudent->retragere(5000);
            }
        } catch (const AuctionException& e) {
            cout << "--> EXCEPTIE PRINSA: " << e.what() << endl;
        }

        // TEST D: Suma Invalida (Input negativ)
        cout << "\n[TEST D] Incercare top-up cu suma -100...\n";
        try {
            if(Participant* pStudent = manager.getParticipantById(102)) {
                pStudent->topUp(-100);
            }
        } catch (const AuctionException& e) {
            cout << "--> EXCEPTIE PRINSA: " << e.what() << endl;
        }

        cout << "\nTestare istoric participant:\n";
        if(const Participant* p = manager.getParticipantById(101)) {
            p->afiseazaIstoric(); //
        }

    }
    catch (const std::exception& e) {
        // Catch-all pentru orice alta eroare neprevazuta (ex: bad_alloc)
        cerr << "\nCRITICAL ERROR : " << e.what() << endl;
    }

    cout << "\n===============================================\n";
    cout << "=== PROGRAM FINALIZAT CU SUCCES  ===\n";
    cout << "===============================================\n";

    return 0;
}
