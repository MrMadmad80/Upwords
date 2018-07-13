#include<vector>
#include <iostream>
#include<string>
#include <costanti.h>
#include <funzioniDizionario.h>


bool controlloSpazioOrizzontale(int lunghezzaParola, int colonna) {
    if(lunghezzaParola+colonna >10) {
        return false;
    }
    return true;
}


bool controlloSpazioVerticale(int lunghezzaParola, int riga) {
    if(lunghezzaParola+riga >10) {
        return false;
    }
    return true;
}

int calcoloLunghezzaParola(std::string parola) {

    return parola.length();
}

bool controlloAltezza(int r, int c, int lunghezzaParola, char direzione, int matriceAltezza[][N]) {
    //controlli verticali e orizzontali per tutta la lunghezza della parola

    if(direzione == 'v') {
        for(int i=0; i<lunghezzaParola; i++) {
            if(matriceAltezza[r+i][c]>=5) {
//                std::cout << "spazio in altezza finito" << std::endl;
                return false;
            } else return true;
        }
    } else {
        for(int i=0; i<lunghezzaParola; i++) {
            if(matriceAltezza[r][c+i]>=5) {
//                std::cout << "spazio in altezza finito" << std::endl;
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


bool controlloPosizione(std::string parola, char campoDiGioco[][N], int matriceAltezza[][N],  int r, int c, char senso) {
//controlla se posso posizionare la parola nelle coordinate inserite

    if(!controlloSpazioOrizzontale(parola.length(), c)) return false;
    if(!controlloSpazioVerticale(parola.length(),r)) return false;
    if(!controlloAltezza(r,c,parola.length(),senso,matriceAltezza)) return false;

    if(senso=='v') {
        for(unsigned int k=0; k<parola.length(); k++) {
//            std::cout << "riga " << r+k << " colonna " << c << " contenuto " << campoDiGioco[r+k][c] << std::endl;
            if(campoDiGioco[r+k][c]!='.') {
                return true;
            }
        }
    }

    if(senso=='o') {
        for(unsigned int k=0; k<parola.length(); k++) {
//            std::cout << "riga " << r << " colonna " << c+k << " contenuto " << campoDiGioco[r][c+k] << std::endl;
                         ;
            if(campoDiGioco[r][c+k]!='.') {
                return true;
            }
        }
    }

    return false;
}
