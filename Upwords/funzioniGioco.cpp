#include<vector>
#include<string>
#include <costanti.h>
#include <iostream>
#include <funzioniControllo.h>


void estrazioneLettere(std::vector<char> &lettera, int nLettereDaEstrarre, int lettere[ALFABETO]) {  //estrae un numero n di lettere dal sacchetto
    int temp=0;             //temp per controllare quante lettere sono rimaste nel sacchetto
    int i=0;

    while(i<nLettereDaEstrarre) {

        for(int g=0; g<ALFABETO; g++) {
            temp += lettere[g];  //temp è la somma delle lettere rimanenti nel sacchetto
        }
        if(temp==0) {
            std::cout << "le lettere sono finite" << std::endl;
            break;
        }

        bool flag = true;
        while(flag) {           //ciclo per continuare a pescare anche se mi imbatto in una lettera finita
            int j = rand()%ALFABETO;

            if(lettere[j]==0) {
                flag = true;
            } else {
                lettere[j]--;
                lettera.push_back((char)(j+97));
                //                std::cout << (char)(j+97) << " ";
                i++;
                flag = false;
            }
        }
    }
}



void cambiaLettera(giocatore *g, int lettere[ALFABETO]) {
    std::cout << "quale lettera vuoi cambiare?" << std::endl;
    char lettera;
    bool flag = false;
    while(flag == false) {
        std::cin>> lettera;
        bool presente = false;
        for(unsigned int i=0; i<g->rack.size(); i++) {
            if(g->rack[i]==lettera) {
                presente = true;

                lettere[(int) g->rack[i] - 97]++;  //reinserisco la lettera nel sacchetto
                bool flag2 = true;
                while(flag2) {           //ciclo per continuare a pescare anche se mi imbatto in una lettera finita
                    int j = rand()%ALFABETO;

                    if(lettere[j]==0) {
                        flag2 = true;
                    } else {
                        lettere[j]--;
                        g->rack[i] = ((char)(j+97));
                        flag2 = false;
                    }
                }

                break;
            }
        }
        if(presente == false) {
            std::cout << "la lettera inserita non e' presente nel tuo rack, inserisci di nuovo una lettera: ";
        } else flag = true;
    }

}


void cancellaDaRack(char lettera, giocatore *g) {
    for(int j=g->rack.size()-1; j>=0; j--) {
        if(lettera==g->rack.at(j)) {
            g->rack.erase(g->rack.begin()+j);
            j = 0; //per uscire subito dal ciclo
        }
    }
}


void inserimentoParola(std::string parola, char campoDiGioco[][N], int altezza[][N], giocatore *g) {
    char senso;
    char r;
    char c;

    int ntentativi =0;

    bool primoturno = false;

    if(campoDiGioco[4][4]=='X') primoturno = true;

    while(ntentativi<3) {
        std::cout << "inserisci le coordinate di inserimento della prima lettera della parola" << std::endl ;
        std::cout << "inserisci la colonna: ";
        std::cin >> c;
        std::cout << "inserisci la riga: ";
        std::cin >> r;
        std::cout << "inserisci il senso in cui vuoi posizionare la parola(v per verticale, o per orizzontale): ";
        std::cin >> senso;
        std::cout << std::endl;

        unsigned int x = (unsigned int)c - 48;
        unsigned int y = (unsigned int)r - 48;

        if(primoturno && (x<4 || x>5) && (y<4 || y>5)) {
            std::cout << "e' il primo turno, devi coprire almeno uan casella segnata con X" << std::endl;
            std::cout << "tentativi rimasti: " << 3 - (ntentativi+1) << std::endl;
            ntentativi++;
        } else {
            if(senso=='v' && x<10 && y<10) {
                if(senso=='v' && controlloSpazioVerticale(parola.length(), y) && controlloAltezza(y,x,parola.length(),senso,altezza)) {
                    for(unsigned int k=0; k<parola.length(); k++) {
                        if(parola[k]=='\0') break;
                        campoDiGioco[y+k][x] = parola[k];
                        if(altezza[y+k][x]==0) {
                            g->punti += 2;
                            altezza[y+k][x]++;
                        } else g->punti += 1;
                        cancellaDaRack(parola[k], g);
                    }
                    if(g->rack.size()==7) g->punti += 20;

                    primoturno = false;                 //tolgo i vincoli del primo turno
                    for(int g=0; g<N; g++) {
                        for (int h=0; h<N; h++) {
                            if(campoDiGioco[g][h]=='X') {
                                campoDiGioco[g][h] = '.';
                            }
                        }
                    }

                    break;
                } else{
                    std::cout << "la parola e' troppo lunga per essere posizionata verticalmente qui" << std::endl;
                    std::cout << "tentativi rimasti: " << 3 - (ntentativi+1) << std::endl;
                    ntentativi++;
                }
            }

            if(senso=='o' && x<10 && y<10) {
                if(senso=='o' && controlloSpazioOrizzontale(parola.length(), x) && controlloAltezza(y,x,parola.length(), senso ,altezza)) {
                    for(unsigned int k=0; k<parola.length(); k++) {
                        if(parola[k]=='\0') break;
                        campoDiGioco[y][x+k] = parola[k];
                        if(altezza[y][x+k]==0) {
                            g->punti += 2;
                            altezza[y][x+k]++;
                        } else g->punti+= 1;
                        cancellaDaRack(parola[k], g);
                    }
                    if(g->rack.size()==7) g->punti += 20;

                    primoturno = false;                 //tolgo i vincoli del primo turno
                    for(int g=0; g<N; g++) {
                        for (int h=0; h<N; h++) {
                            if(campoDiGioco[g][h]=='X') {
                                campoDiGioco[g][h] = '.';
                            }
                        }
                    }

                    break;
                } else {
                    std::cout << "la parola e' troppo lunga per essere posizionata orizzontalmente qui" << std::endl;
                    std::cout << "tentativi rimasti: " << 3 - (ntentativi+1) << std::endl;
                    ntentativi++;
                }
            }
            if((senso!='v' && senso !='o') || x>9 || y>9) std::cout << "il carattere inserito non e' corretto" << std::endl;
        }
    }
    return;
}


void inizializzaGiocatori() {
    std::cout << "Scegli il numero di giocatori (da 2 a 4)"  << std::endl;
    char ngiocatori;
    bool flag = false;
    while(flag == false) {
        std::cin>> ngiocatori;
        if(((int)ngiocatori)-48 < 2 || ((int)ngiocatori)-48 > 4) {
            std::cout << "numero non valido, riprova" << std::endl;
        } else {
            flag = true;
        }
    }
    for(int i=0; i<((int)ngiocatori)-48; i++) {
        giocatore* g = new giocatore;
        g->punti = 0;
        std::cout << "inserisci il tuo nome: ";
        std::cin >> g->nome;
        elencoGiocatori.push_back(g);
    }
}
