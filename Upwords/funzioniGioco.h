#ifndef FUNZIONIGIOCO_H
#define FUNZIONIGIOCO_H

#include<vector>
#include<string>
#include <costanti.h>
#include <iostream>

void estrazioneLettere(std::vector<char> &lettera, int nLettereDaEstrarre, int lettere[ALFABETO]);
void cambiaLettera(giocatore *g, int lettere[ALFABETO]);
void cancellaDaRack(char lettera, giocatore *g);

void inserimentoParola(std::string parola, char campoDiGioco[][N], int altezza[][N], giocatore *g);
void inizializzaGiocatori();

#endif // FUNZIONIGIOCO_H
