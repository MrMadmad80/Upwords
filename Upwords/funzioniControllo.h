#ifndef MIEFUNZIONI_H
#define MIEFUNZIONI_H

#include <costanti.h>

int controlloIntero(std::string input);
bool controlloSpazioOrizzontale(int lunghezzaParola, int yInizio);
bool controlloSpazioVerticale(int lunghezzaParola, int xInizio);
int calcoloLunghezzaParola(std::string parola);

bool controlloAltezza(int ascisse, int ordinate, int lunghezzaParola, char direzione, int matriceAltezza[][N]);
bool controllaParola(std::string parola, giocatore *g);
bool controlloPosizione(std::string parola, char campoDiGioco[][N], int matriceAltezza[][N],  int r, int c, char senso);

bool controlloIncrocio (std::string parola, char campoDiGioco[][N], int r, int c, char senso, giocatore *g);
#endif // MIEFUNZIONI_H
