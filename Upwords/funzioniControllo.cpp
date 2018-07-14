#include<vector>
#include <iostream>
#include<string>
#include <costanti.h>
#include <funzioniDizionario.h>
#include <funzioniStampa.h>



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


bool controllaParola(std::string parola, char temp[][N], int r, int c, char senso, giocatore *g) {  //controlla se ho le lettere per creare la parola inserita
    std::vector<char> racktemp = g->rack;

    if(senso=='v') {
        for(unsigned int i=0; i<parola.length(); i++) {
            bool flag = false;
            if(temp[r+i][c]!=parola[i]){
                for(int j=racktemp.size()-1; j>=0; j--) {
                    if(parola[i]==racktemp.at(j)) {
                        racktemp.erase(racktemp.begin()+j);
                        flag = true;
                        j = 0; //per uscire subito dal ciclo
                    }
                }
                if(flag == false) return false;
            }
        }
    }

    if(senso=='o') {
        for(unsigned int i=0; i<parola.length(); i++) {
            bool flag = false;
            if(temp[r][c+i]!=parola[i]){
                for(int j=racktemp.size()-1; j>=0; j--) {
                    if(parola[i]==racktemp.at(j)) {
                        racktemp.erase(racktemp.begin()+j);
                        flag = true;
                        j = 0; //per uscire subito dal ciclo
                    }
                }
                if(flag == false) return false;
            }
        }
    }
    return true;

}

std::vector<std::string> paroleSulCampo(char temp[][N]) {

    std::vector<std::string> vettoreParole;
    std::vector<std::string> vettoretemp;

    for(int r=0; r<N; r++) {
        std::string parola;
        for (int c=0; c<N; c++) {
            if(temp[r][c]!='.') {
                parola.push_back(temp[r][c]);

                if(temp[r][c+1]=='.' && c<N) {
                    parola.push_back('.');
                }


            }
        }
        vettoretemp.push_back(parola);
    }

    for(int c=0; c<N; c++) {
        std::string parola;
        for (int r=0; r<N; r++) {
            if(temp[r][c]!='.') {
                parola.push_back(temp[r][c]);

                if(temp[r+1][c]=='.' && r<N) {
                    parola.push_back('.');
                }

            }
        }
        vettoretemp.push_back(parola);
    }


    std::string delimiter = ".";

    size_t pos = 0;
    std::string token;
    for(int i=0; i<vettoretemp.size(); i++) {
        while ((pos = vettoretemp[i].find(delimiter)) != std::string::npos) {
            token = vettoretemp[i].substr(0, pos);
            vettoreParole.push_back(token);
            vettoretemp[i].erase(0, pos + delimiter.length());
        }
    }

    return vettoreParole;
}

bool controlloIncrocio (std::string parola, char campoDiGioco[][N], int r, int c, char senso, giocatore *g) {

    char temp[N][N];

    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            temp[i][j] = campoDiGioco[i][j];
        }
    }

    if(controllaParola(parola, temp, r, c, senso, g)) {
        if(campoDiGioco[4][4]!='X') {

            std::vector<std::string> vettoreParole;

            if(senso=='v') {
                //inserisco la parola nella matrice temporanea
                for(unsigned int i=0; i<parola.length(); i++) {
                    temp[r+i][c] = parola[i];
                }

            }

            if(senso=='o') {
                for(unsigned int i=0; i<parola.length(); i++) {
                    temp[r][c+i] = parola[i];
                }


            }

            //            stampaMatrice(temp);

            vettoreParole = paroleSulCampo(temp);

            //            for(int i=0; i<vettoreParole.size(); i++) {
            //                std::cout << vettoreParole[i] << " ";
            //            }
            //            std::cout << std::endl;
            //            std::cout << vettoreParole.size() << std::endl;

            for(unsigned int i=0; i<vettoreParole.size(); i++) {
                if(vettoreParole[i].length()>1) {
                    if(!controlloDizionario(vettoreParole[i]) && !vettoreParole.empty()) return false;
                }
            }
        }
        return true;
    } else return false;
}


bool controlloPosizione(std::string parola, char campoDiGioco[][N], int matriceAltezza[][N],  int r, int c, char senso) {
    //controlla se posso posizionare la parola nelle coordinate inserite

    if(!controlloAltezza(r,c,parola.length(),senso,matriceAltezza)) return false;

    if(senso=='v') {
        if(!controlloSpazioVerticale(parola.length(),r)) return false;

        for(unsigned int k=0; k<parola.length(); k++) {
            //            std::cout << "riga " << r+k << " colonna " << c << " contenuto " << campoDiGioco[r+k][c] << std::endl;
            //            std::cout << campoDiGioco[r+k][c] << " ";
            if(campoDiGioco[r+k][c]!='.') {
                return true;
            }
        }
        //        std::cout << std::endl;
    }

    if(senso=='o') {
        if(!controlloSpazioOrizzontale(parola.length(), c)) return false;

        for(unsigned int k=0; k<parola.length(); k++) {
            //            std::cout << "riga " << r << " colonna " << c+k << " contenuto " << campoDiGioco[r][c+k] << std::endl;
            //             std::cout << campoDiGioco[r][c+k] << " ";
            if(campoDiGioco[r][c+k]!='.') {
                return true;
            }
        }
        //        std::cout << std::endl;
    }

    return false;
}
