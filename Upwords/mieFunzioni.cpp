#include<vector>
#include <iostream>
#include<string>
#include <costanti.h>


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
