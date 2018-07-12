#include<vector>
#include <string>
#include<fstream>
#include <iostream>
#include <costanti.h>

bool controlloDizionario(std::string parola) {   //controlla se la parola è presente nel dizionario
//    if(parola.length()>3) {    //controllo da specifiche solo sulle parole più lunghe di 3
        std::ifstream input;
        input.open("italiano.txt");

        if(input.fail()) {
            std::cout<<"Input file opening failed."<< std::endl;
        }

        std::string line;

        while(getline(input, line)) {
            if(line==parola) {
                input.close();
                //            cout << "parola " << parola << " trovata" << endl;
                return true;
            }
        }
        //    cout << "parola non trovata" << endl;
        input.close();
        return false;
//    } else return true;
}


std::string parolaPiuLunga(std::vector<std::string> suggerimenti) {
    std::string parola;

    for(int i=0; i<suggerimenti.size(); i++) {
        if(suggerimenti.at(i).length() > parola.length()) {
            parola = suggerimenti.at(i);
        }
    }

    return parola;
}


void trovaSuggerimento(giocatore *g) {
    std::ifstream input;
    input.open("italiano.txt");

    if(input.fail()) {
        std::cout<<"Input file opening failed."<< std::endl;
    }

    std::string line;

    std::vector<std::string> suggerimenti;

    while(getline(input, line)) {
        if(line.size()<=7) {
            std::vector<char> temp = g->rack;
            bool flag = false;
            bool parolavalida = false;
            for(unsigned int i=0; i<line.length(); i++) {
                for(int j=temp.size()-1; j>=0; j--) {
                    if(line[i]==temp.at(j)) {
                        temp.erase(temp.begin()+j);
                        flag = true;  //se trovo la lettera metto a true flag
                        j = 0; //per uscire subito dal ciclo
                    } else flag = false;
                }
                if(flag == false) {
                    i = line.length();
                    parolavalida = false;
                } else {
                    parolavalida = true;
                }
            }
            if(parolavalida) {
                suggerimenti.push_back(line);
            }
        }

    }
    if(suggerimenti.size()!=0) {
       std::cout << "suggerimento per avere piu' punti: " << parolaPiuLunga(suggerimenti) << std::endl;
    } else {
        std::cout << "non si possono formare parole" << std::endl;
    }
    input.close();
}
