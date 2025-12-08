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

        // --- 4. LICITATII ---
        cout << "\n>>> 4. SIMULARE LICITATII <<<\n";
       // Pas 1: Obtinem participantii
        Participant* pTiriac = manager.getParticipantById(101);
        Participant* pStudent = manager.getParticipantById(102);

        // Validare Participanti
        if (pTiriac != nullptr && pStudent != nullptr) {
            cout << "[CHECK] Se verifica identitatea participantilor...\n";
            if (*pTiriac == *pStudent) {
                cout << "EROARE CRITICA: Participantii sunt aceeasi persoana!\n";
                return 1;
            } else {
                cout << "-> VALID: Participantii sunt diferiti.\n";
            }
        }

        // Pas 2: Creare Licitatii
        cout << "\n--- Creare Licitatie #1 ---\n";
        manager.creeazaLicitatie("BMW-X6-001", dataCurenta, 120, "Licitatie SUV Premium");

        cout << "\n--- Creare Licitatie #2 ---\n";
        manager.creeazaLicitatie("MB-SPR-2020", dataCurenta, 60, "Licitatie Transport Persoane");

        // Pas 3: luam pointerii
        Licitatie* lic1 = manager.getLicitatieById(1);
        Licitatie* lic2 = manager.getLicitatieById(2);

        // --- VALIDARE VEHICULE (Operator ==) ---
        if (lic1 != nullptr && lic2 != nullptr) {
            cout << "[CHECK] Se verifica unicitatea vehiculelor scoase la licitatie...\n";

            const Vehicul* v1 = lic1->getVehicul();
            const Vehicul* v2 = lic2->getVehicul();

            if (v1 != nullptr && v2 != nullptr) {
                if (*v1 == *v2) {
                    cout << "ALERTA: Se incearca vanzarea aceluiasi vehicul (" << v1->getVIN() << ") in doua licitatii simultan!\n";
                } else {
                    cout << "-> VALID: Vehiculele sunt diferite (" << v1->getVIN() << " vs " << v2->getVIN() << ").\n";
                }
            }
        }

        // Pas 4: Desfasurare Licitatie #1 (BMW)
        if (lic1 != nullptr) {
            cout << "\n--- START Desfasurare Licitatie #1 (BMW) ---\n";
            lic1->inscrieParticipant(pTiriac);
            lic1->inscrieParticipant(pStudent);

            cout << "-> Studentul ofera 600 EUR...\n";
            lic1->plaseazaOferta(pStudent, 600);

            cout << "-> Tiriac ofera 35000 EUR...\n";
            lic1->plaseazaOferta(pTiriac, 35000);

            if(lic1->getCastigatorCurent() != nullptr) {
                cout << " Castigatorul curent este " << lic1->getCastigatorCurent()->getNume() << endl;
            }
            if(lic1->getVehicul() != nullptr) {
                cout << " Vehiculul licitat are VIN " << lic1->getVehicul()->getVIN() << endl;
            }


            lic1->finalizeazaLicitatie();
        }

        // Pas 5: Desfasurare Licitatie #2 (Microbuz)
        if (lic2 != nullptr) {
            cout << "\n--- START Desfasurare Licitatie #2 (Microbuz) ---\n";
            Participant* pFirma = manager.getParticipantById(103);

            lic2->inscrieParticipant(pFirma);
            lic2->inscrieParticipant(pTiriac); // Tiriac participa si aici

            cout << "-> Firma Curierat ofera 36000 EUR...\n";
            lic2->plaseazaOferta(pFirma, 36000);

            if(lic2->getCastigatorCurent() != nullptr) {
                cout << " Castigatorul curent este " << lic2->getCastigatorCurent()->getNume() << endl;
            }
            if(lic2->getVehicul() != nullptr) {
                cout << " Vehiculul licitat are VIN " << lic2->getVehicul()->getVIN() << endl;
            }


            lic2->finalizeazaLicitatie();
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
            if (Participant* pStudent1 = manager.getParticipantById(102)) {
                pStudent1->retragere(5000); // Are doar 500
            }
        } catch (const AuctionException& e) {
            cout << "--> EXCEPTIE PRINSA: " << e.what() << endl;
        }

        // TEST D: SumaInvalidaException (la topUp)
        cout << "\n[TEST D] Adaugare fonduri (topUp) cu suma negativa...\n";
        try {
            if(Participant* pStudent2 = manager.getParticipantById(102)) {
                pStudent2->topUp(-100);
            }
        } catch (const AuctionException& e) {
            cout << "--> EXCEPTIE PRINSA: " << e.what() << endl;
        }

        // TEST E: SumaInvalidaException (la retragere) <--- SCENARIU NOU ADAUGAT
        cout << "\n[TEST E] Retragere fonduri cu suma negativa...\n";
        try {
            if(Participant* pStudent3 = manager.getParticipantById(102)) {
                pStudent3->retragere(-50);
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