#include<vector>
#include <iostream>
#include<string>
#include <costanti.h>
#include <funzioniDizionario.h>


bool controlloSpazioOrizzontale(int lunghezzaParola, int yInizio) {
    if(lunghezzaParola+yInizio >10) {
        return false;
    }
    return true;
}


bool controlloSpazioVerticale(int lunghezzaParola, int xInizio) {
    if(lunghezzaParola+xInizio >10) {
        return false;
    }
    return true;
}

int calcoloLunghezzaParola(std::string parola) {

    return parola.length();
}

bool controlloAltezza(int r, int c, int lunghezzaParola, char direzione, int matriceAltezza[][N]) {
    //fare controlli verticali e orizzontali per tutta la lunghezza delle singole caselle

    if(direzione == 'v') {
        for(int i=0; i<lunghezzaParola; i++) {
            if(matriceAltezza[r+i][c]>=5) {
                std::cout << "spazio in altezza finito" << std::endl;
                return false;
            } else return true;
        }
    } else {
        for(int i=0; i<lunghezzaParola; i++) {
            if(matriceAltezza[r][c+i]>=5) {
                std::cout << "spazio in altezza finito" << std::endl;
                return false;
            } else return true;
        }
    }
}


bool controllaParola(std::string parola, giocatore *g) {  //controlla se ho le lettere per creare la parola inserita
    if(controlloDizionario(parola)) {

        std::vector<char> temp = g->rack;
        for(unsigned int i=0; i<parola.length(); i++) {
            bool flag = false;
            for(int j=temp.size()-1; j>=0; j--) {
                if(parola[i]==temp.at(j)) {
                    temp.erase(temp.begin()+j);
                    flag = true;
                    j = 0; //per uscire subito dal ciclo
                }
            }
            if(flag == false) return false;
        }
        return true;
    } else {
        return false;
    }
}
