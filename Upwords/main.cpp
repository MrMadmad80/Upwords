#include <iostream>
#include <vector>
#include <string.h>
#include <time.h>
#include <cstdlib>
#include <algorithm>
#include <conio.h>
#include <windows.h>
#include <MieFunzioni.h>
#include <funzioniDizionario.h>
#include <costanti.h>
#include <funzioniStampa.h>

using namespace std;

vector<giocatore*> elencoGiocatori;

void estrazioneLettere(vector<char> &lettera, int nLettereDaEstrarre, int lettere[ALFABETO]) {  //estrae un numero n di lettere dal sacchetto
    int temp=0;             //temp per controllare quante lettere sono rimaste nel sacchetto
    int i=0;

    while(i<nLettereDaEstrarre) {

        for(int g=0; g<ALFABETO; g++) {
            temp += lettere[g];  //temp è la somma delle lettere rimanenti nel sacchetto
        }
        if(temp==0) {
            cout << "le lettere sono finite" << endl;
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
                //                cout << (char)(j+97) << " ";
                i++;
                flag = false;
            }
        }
    }
}

void cambiaLettera(giocatore *g, int lettere[ALFABETO]) {
    cout << "quale lettera vuoi cambiare?" << endl;
    char lettera;
    bool flag = false;
    while(flag == false) {
        cin>> lettera;
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
            cout << "la lettera inserita non e' presente nel tuo rack, inserisci di nuovo una lettera: ";
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

bool controllaParola(string parola, giocatore *g) {  //controlla se ho le lettere per creare la parola inserita
    if(controlloDizionario(parola)) {

        vector<char> temp = g->rack;
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

void inserimentoParola(string parola, char campoDiGioco[][N], int altezza[][N], giocatore *g) {
    char senso;
    char r;
    char c;

    int ntentativi =0;

    bool primoturno = false;

    if(campoDiGioco[4][4]=='X') primoturno = true;

    while(ntentativi<3) {
        cout << "inserisci le coordinate di inserimento della prima lettera della parola" << endl ;
        cout << "inserisci la colonna: ";
        cin >> c;
        cout << "inserisci la riga: ";
        cin >> r;
        cout << "inserisci il senso in cui vuoi posizionare la parola(v per verticale, o per orizzontale): ";
        cin >> senso;
        cout << endl;

        unsigned int x = (unsigned int)c - 48;
        unsigned int y = (unsigned int)r - 48;

        if(primoturno && (x<4 || x>5) && (y<4 || y>5)) {
            cout << "e' il primo turno, devi coprire almeno uan casella segnata con X" << endl;
            cout << "tentativi rimasti: " << 3 - (ntentativi+1) << endl;
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
                    cout << "la parola e' troppo lunga per essere posizionata verticalmente qui" << endl;
                    cout << "tentativi rimasti: " << 3 - (ntentativi+1) << endl;
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
                    cout << "la parola e' troppo lunga per essere posizionata orizzontalmente qui" << endl;
                    cout << "tentativi rimasti: " << 3 - (ntentativi+1) << endl;
                    ntentativi++;
                }
            }
            if((senso!='v' && senso !='o') || x>9 || y>9) cout << "il carattere inserito non e' corretto" << endl;
        }
    }
    return;
}


void inizializzaGiocatori() {
    cout << "Scegli il numero di giocatori (da 2 a 4)"  << endl;
    char ngiocatori;
    bool flag = false;
    while(flag == false) {
        cin>> ngiocatori;
        if(((int)ngiocatori)-48 < 2 || ((int)ngiocatori)-48 > 4) {
            cout << "numero non valido, riprova" << endl;
        } else {
            flag = true;
        }
    }
    for(int i=0; i<((int)ngiocatori)-48; i++) {
        giocatore* g = new giocatore;
        g->punti = 0;
        cout << "inserisci il tuo nome: ";
        cin >> g->nome;
        elencoGiocatori.push_back(g);
    }
}

int main()
{
    char g1[N][N];
    srand(time(0));

    int nLettereIniziali[ALFABETO] = {7,3,4,5,8,3,3,3,7,1,2,5,5,5,7,3,1,5,6,5,5,1,1,2,2,1};

    for(int i=0; i<N; i++) {
        for(int k=0; k<N; k++) {
            g1[i][k]='.';
            if((i==4 || i == 5) && (k==4 || k==5)) {
                g1[i][k] = 'X';
            }
        }
    }

    int matriceAltezza[N][N];

    for (int k=0; k<N; k++) {
        for(int j=0; j<N; j++) {
            matriceAltezza[k][j]=0;
        }
    }

    cout << "Benvenuto in una nuova partita di UPWORDS!" << endl;

    inizializzaGiocatori();

    cout << "giocatori presenti: " << endl;
    stampaPunteggi();

    for(unsigned int i=0; i<elencoGiocatori.size(); i++) {  //estrazione iniziale lettere

        estrazioneLettere(elencoGiocatori.at(i)->rack, MAXRACK, nLettereIniziali);
    }

    vector<bool> turnoGiocato;

    for(unsigned int i=0; i<elencoGiocatori.size(); i++) {
        turnoGiocato.push_back(true);
    }
    bool terminaPartita = false;
    int counter = 0;

    while(terminaPartita == false) {

        int z = counter%elencoGiocatori.size();

        stampaMatrice(g1);

        cout << "e' il turno di: " << elencoGiocatori.at(z)->nome << endl;

        stampaRackGiocatore(elencoGiocatori.at(z));

        char suggerimento;

        cout << "vuoi un suggerimento? [s per si/qualsiasi altra per no]" <<endl;
        cin >> suggerimento;

        if(suggerimento == 's') {
            trovaSuggerimento(elencoGiocatori.at(z));
        }

        char passare;

        cout << "premi p se vuoi passare, qualsiasi altro tasto se vuoi inserire una parola" << endl;
        cin >> passare;

        if(passare == 'p') {
            turnoGiocato[z] = false;

            char cambiareLettera;

            cout << "vuoi cambiare una lettera? [s per si/qualsiasi altra per no]" << endl;
            cin >> cambiareLettera;
            cout << endl;
            if(cambiareLettera == 's') {
                cambiaLettera(elencoGiocatori.at(z), nLettereIniziali);
                stampaRackGiocatore(elencoGiocatori.at(z));
            }
        } else {


            string parola;

            bool flag = false;
            int ntentativi = 0;
            while(flag == false) {

                cout << "inserire la parola italiana desiderata: ";
                cin>> parola;

                if(parola.length()<=10) {
                    int l = parola.length();
                    cout << "lunghezza: " << l << endl;

                    if(controllaParola(parola, elencoGiocatori.at(z))) {
                        inserimentoParola(parola, g1, matriceAltezza, elencoGiocatori.at(z));
                        //riempio di nuovo il rack del giocatore
                        estrazioneLettere(elencoGiocatori.at(z)->rack, MAXRACK-elencoGiocatori.at(z)->rack.size(), nLettereIniziali);
                        flag = true;
                    } else  {
                        cout << "la parola non e' ammessa, riprovare (tentativi rimasti: " << 3-(ntentativi+1) << ")" << endl;
                        ntentativi++;
                    }
                } else {
                    cout << "la parola scelta e' troppo lunga per essere inserita in questo gioco" << endl;
                    cout << "tentativi rimasti: " << 3 - (ntentativi+1) << endl;
                    ntentativi++;
                }
                if(ntentativi>2) {
                    cout << "tentativi massimi finiti, passi il turno" << endl;
                    flag = true;
                }
            }
            stampaMatrice(g1);

        }
        if(none_of(turnoGiocato.begin(), turnoGiocato.end(), [](bool i){return i;})) {
            terminaPartita = true;
            cout << "tutti i giocatori hanno passato di loro volonta', la partita termina" << endl;
        } else {
            counter++;
            cout << elencoGiocatori.at(z)->nome << ": " << elencoGiocatori.at(z)->punti << " punti" << endl;
            cout << "il gioco passa al giocatore successivo" << endl;
        }
        Sleep(4000);
        system("cls");
    }
    cout << "CLASSIFICA FINALE" << endl;
    stampaPunteggi();
    cout << endl;
    cout << "Fine partita" << endl;
    return 0;
}

