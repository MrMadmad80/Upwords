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
    std::string s;
    std::string r;
    std::string c;

    int ntentativi =0;

    while(ntentativi<3) {
        std::cout << "inserisci le coordinate di inserimento della prima lettera della parola" << std::endl ;
        std::cout << "inserisci la riga: ";
        std::cin >> r;
        std::cout << "inserisci la colonna: ";
        std::cin >> c;
        std::cout << "inserisci il senso in cui vuoi posizionare la parola(v per verticale, o per orizzontale): ";
        std::cin >> s;
        std::cout << std::endl;

        int colonna = stoi(c);
        int riga = stoi(r);
        char senso = s[0];

        if((senso!='v' && senso !='o') || colonna>9 || riga>9 || colonna<0 || riga<0) {
//            std::cout << "riga " <<  riga << " colonna " << colonna << " senso " << senso << std::endl;
            std::cout << "il carattere inserito non e' corretto" << std::endl;
            std::cout << "tentativi rimasti: " << 3 - (ntentativi+1) << std::endl;
            ntentativi++;

        } else if(!controlloPosizione(parola,campoDiGioco, altezza,riga,colonna,senso)) {

            std::cout << "non puoi posizionare la parola qui, ";
            if((senso=='o' && !controlloSpazioOrizzontale(parola.length(), colonna)) ||
                    (senso=='v' && !controlloSpazioVerticale(parola.length(), riga))) {
                std::cout << "la parola e' troppo lunga per questo posto" << std::endl;
            } else if(!controlloAltezza(riga, colonna, parola.length(), senso, altezza)) {
                std::cout << "hai raggiunto il limite in altezza" << std::endl;
            } else std::cout << "la parola non rispetta le regole del gioco" << std::endl;

            std::cout << "tentativi rimasti: " << 3 - (ntentativi+1) << std::endl;
            ntentativi++;

        } else {
            if(senso=='v') {
                if(controlloAltezza(riga,colonna,parola.length(),senso,altezza)) {  //inserire qui controllo incroci
                    for(unsigned int k=0; k<parola.length(); k++) {
                        if(parola[k]=='\0') break;
                        campoDiGioco[riga+k][colonna] = parola[k];
                        if(altezza[riga+k][colonna]==0) {
                            g->punti += 2;
                            altezza[riga+k][colonna]++;
                        } else g->punti += 1;
                        cancellaDaRack(parola[k], g);
                    }
                    if(g->rack.size()==7) g->punti += 20;

                    //ciclo per togliere X
                    for(int g=0; g<N; g++) {
                        for (int h=0; h<N; h++) {
                            if(campoDiGioco[g][h]=='X') {
                                campoDiGioco[g][h] = '.';
                            }
                        }
                    }

                    break;
                }
            }

            if(senso=='o') {
                if(controlloAltezza(riga,colonna,parola.length(), senso ,altezza)) {  //inserire qui controllo incroci
                    for(unsigned int k=0; k<parola.length(); k++) {
                        if(parola[k]=='\0') break;
                        campoDiGioco[riga][colonna+k] = parola[k];
                        if(altezza[riga][colonna+k]==0) {
                            g->punti += 2;
                            altezza[riga][colonna+k]++;
                        } else g->punti+= 1;
                        cancellaDaRack(parola[k], g);
                    }
                    if(g->rack.size()==7) g->punti += 20;

                    //ciclo per togliere X
                    for(int g=0; g<N; g++) {
                        for (int h=0; h<N; h++) {
                            if(campoDiGioco[g][h]=='X') {
                                campoDiGioco[g][h] = '.';
                            }
                        }
                    }

                    break;
                }
            }
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
