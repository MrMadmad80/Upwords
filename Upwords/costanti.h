#ifndef COSTANTI_H
#define COSTANTI_H

#include <iostream>
#include <vector>
#include <string>

#define MAXRACK 7

const int N=10;
const int ALFABETO=26;

struct giocatore {
    int punti;
    std::string nome;
    std::vector<char> rack;
};

extern std::vector<giocatore*> elencoGiocatori;

#endif // COSTANTI_H
