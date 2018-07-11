#include<vector>
#include <string>
#include<fstream>
#include <iostream>

bool controlloDizionario(std::string parola) {   //controlla se la parola è presente nel dizionario
    if(parola.length()>3) {    //controllo da specifiche solo sulle parole più lunghe di 3
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
    } else return true;
}
