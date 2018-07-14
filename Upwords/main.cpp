#include <iostream>
#include <vector>
#include <string.h>
#include <time.h>
#include <algorithm>
#include <conio.h>
#include <windows.h>
#include <funzioniControllo.h>
#include <funzioniDizionario.h>
#include <costanti.h>
#include <funzioniStampa.h>
#include <funzioniGioco.h>

using namespace std;

vector<giocatore*> elencoGiocatori;

int main()
{
    char g1[N][N];
    srand(time(0));

    int nLettereIniziali[ALFABETO] = {7,3,4,5,8,3,3,3,7,0,0,5,5,5,7,3,1,5,6,5,5,1,0,0,0,1};

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

    cout << "ricorda: il gioco finisce quando tutti i giocatori scelgono di passare" << endl;
    cout << endl;

    for(unsigned int i=0; i<elencoGiocatori.size(); i++) {
        turnoGiocato.push_back(true);
    }
    bool terminaPartita = false;
    int counter = 0;

    while(terminaPartita == false) {

        int z = counter%elencoGiocatori.size();

        stampaMatrice(g1);

        cout << "e' il turno di: " << elencoGiocatori.at(z)->nome << endl;
        cout <<"hai " << elencoGiocatori.at(z)->punti << " punti" << endl;
        cout << endl;

        stampaRackGiocatore(elencoGiocatori.at(z));

        cout << endl;
        string input;

        cout << "vuoi un suggerimento? [s per si/qualsiasi altra per no]" <<endl;
        cin >> input;

        if(input[0] == 's') {
            trovaSuggerimento(elencoGiocatori.at(z));
        }

        cout << "premi p se vuoi passare, qualsiasi altro tasto se vuoi inserire una parola" << endl;
        cin >> input;

        if(input[0] == 'p') {
            turnoGiocato[z] = false;

            cout << "vuoi cambiare una lettera? [s per si/qualsiasi altra per no]" << endl;
            cin >> input;
            cout << endl;
            if(input[0] == 's') {
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

                    if(controlloDizionario(parola)) {
                        inserimentoParola(parola, g1, matriceAltezza, elencoGiocatori.at(z));
                        //riempio di nuovo il rack del giocatore
                        estrazioneLettere(elencoGiocatori.at(z)->rack, MAXRACK-elencoGiocatori.at(z)->rack.size(), nLettereIniziali);
                        flag = true;
                    } else  {
                        cout << "la parola non e' presente nel dizionario, riprovare" << endl;
                        cout << "tentativi rimasti: " << 3-(ntentativi+1) << endl;
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
//            cout << endl;
//            for(int i=0; i<N; i++) {
//                for(int j=0; j<N; j++) {
//                    cout << matriceAltezza[i][j] << " ";
//                }
//                cout << endl;
//            }

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

