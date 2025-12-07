cmake_minimum_required(VERSION 3.10)
project(proiect_poo)

set(CMAKE_CXX_STANDARD 20)

add_executable(proiect_poo main.cpp
        DataOra.h
        DataOra.cpp
        Participant.cpp
        SpecificatiiTehnice.cpp
        SpecificatiiTehnice.h
        Vehicul.cpp
        Vehicul.h
        Licitatie.cpp
        Licitatie.h
        AuctionManager.cpp
        AuctionManager.h
        Derivate.cpp
        Derivate.h
        Exceptii.h)
