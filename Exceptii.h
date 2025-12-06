#ifndef PROIECT_POO_EXCEPTIONS_H
#define PROIECT_POO_EXCEPTIONS_H

#include <exception>
#include <string>
#include <utility>

class AuctionException : public std::exception {
protected:
    std::string mesaj;
public:
    explicit AuctionException(std::string  mesaj) : mesaj(std::move(mesaj)) {}

    [[nodiscard]] const char* what() const noexcept override {
        return mesaj.c_str();
    }
};

// exceptie pentru suma negativa sau 0 (Participant)
class SumaInvalidaException : public AuctionException {
public:
    explicit SumaInvalidaException(double suma)
        : AuctionException("EROARE INPUT: Suma introdusa (" + std::to_string(suma) + ") trebuie sa fie strict pozitiva") {}
};

// exceptie pentru fonduri insuficiente (Participant)
class FonduriInsuficienteException : public AuctionException {
public:
    FonduriInsuficienteException(const std::string& nume, double necesar, double disponibil)
        : AuctionException("EROARE TRANZACTIE: " + nume + " nu are fonduri suficiente. Necesar: "
                           + std::to_string(necesar) + " | Disponibil: " + std::to_string(disponibil)) {}
};

// exceptie pentru pret invalid (Vehicul)
class PretInvalidException : public AuctionException {
public:
    explicit PretInvalidException(double pret)
        : AuctionException("EROARE VALIDARE: Pretul nu poate fi negativ! Ai introdus: " + std::to_string(pret)) {}
};

// exceptie pentru licitatie invalida (Manager)
class LicitatieInvalidaException : public AuctionException {
public:
    explicit LicitatieInvalidaException(const std::string& vin)
        : AuctionException("EROARE LICITATIE: Nu s-a putut crea licitatia. Vehiculul cu VIN " + vin + " nu exista in stoc.") {}
};

#endif //PROIECT_POO_EXCEPTIONS_H