#include<vector>
#include <costanti.h>
#include <iostream>

void stampaMatrice(char matrice[N][N]) {
    std::cout << "  ";
    for(int h=0; h<N; h++) {
        std::cout << h << " ";
    }
    std::cout << "x" << std::endl;
    for(int j=0; j<N; j++) {
        std::cout << j << " ";
        for(int l=0; l<N; l++) {
            std::cout << matrice[j][l] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "y" <<std::endl;
}

void stampaParola(std::vector<char> parola) {
    for (int i=0; i<N; i++) {
        std::cout << parola[i] << " ";
    }
    std::cout << std::endl;
}

void stampaRackGiocatore(giocatore *g) {
    for(unsigned int i=0; i< g->rack.size(); i++) {
        std::cout << g->rack[i] << " ";
    }
    std::cout << std::endl;
}

void stampaPunteggi() {
    for(unsigned int i=0; i< elencoGiocatori.size(); i++) {
        std::cout << elencoGiocatori.at(i)->nome << ": " << elencoGiocatori.at(i)->punti << " punti" << std::endl;
    }
}
