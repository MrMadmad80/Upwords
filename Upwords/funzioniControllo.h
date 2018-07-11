#ifndef MIEFUNZIONI_H
#define MIEFUNZIONI_H
#include<vector>
#include <string>
#include <costanti.h>
#include <iostream>

bool controlloSpazioOrizzontale(int lunghezzaParola, int yInizio);
bool controlloSpazioVerticale(int lunghezzaParola, int xInizio);
int calcoloLunghezzaParola(std::string parola);

bool controlloAltezza(int ascisse, int ordinate, int lunghezzaParola, char direzione, int matriceAltezza[][N]);
bool controllaParola(std::string parola, giocatore *g);
#endif // MIEFUNZIONI_H
