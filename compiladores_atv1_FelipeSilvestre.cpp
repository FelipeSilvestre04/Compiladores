#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string> 
#include <cctype> 

// RESULTADO:

/* ID ID ID ID ID ID 
   ID ID ID ID ID. */

// KEY ID[ 10 ];

// KEY ID ( KEY ID[], KEY ID, KEY ID )
// {	KEY ID; KEY ID; KEY ID;
// 	ID = ID;
// 	ID = ID[ID];
// 	ID = ID + 1;
// 	KEY (ID < ID){
// 		KEY (ID[ID] < ID){
// 			ID = ID[ID];
// 			ID = ID;
// 		}
// 		ID = ID + 1;
// 	}
// 	KEY ID;
// }

// KEY ID( KEY ID[], KEY ID, KEY ID)
// {	KEY ID; KEY ID;
// 	ID = ID;
// 	KEY (ID < ID-1){
// 		KEY ID;
// 		ID = ID(ID,ID,ID);
// 		ID = ID[ID];
// 		ID[ID] = ID[ID];
// 		ID[ID] = ID;
// 		ID = ID + 1;
// 	}
// }

// KEY ID(KEY)
// {
// 	KEY ID;
// 	ID = 0;
// 	KEY (ID < 10){
// 		ID[ID] = ID();
// 		ID = ID + 1;
// 	}
// 	ID(ID,0,10);
// 	ID = 0;
// 	KEY (ID < 10){
// 		ID(ID[ID]);
// 		ID = ID + 1;
// 	}
// }

			


// Estados
const int INICIAL = 0;
const int ACEITACAO = 1;
const int FINAL = 2;
const int ERRO = 3;

// Categorias
const int LETRA = 0;
const int DIGITO = 1;
const int OUTRO = 2;


int tabelaTransicao[4][3] = {
    //           LETRA,    DIGITO,     OUTRO      (COLUNAS)
    /*INICIAL*/ {ACEITACAO, ERRO,       ERRO},
    /*ACEITACAO*/{ACEITACAO, ACEITACAO,  FINAL},
    /*FINAL*/   {FINAL,     FINAL,      FINAL}, 
    /*ERRO*/    {ERRO,      ERRO,       ERRO}  
};

int getCategoriaIndice(char c) {
    if (isalpha(c)) return LETRA;
    if (isdigit(c)) return DIGITO;
    return OUTRO;
}



int main() {
    std::ifstream arq("C:\\Users\\felip\\OneDrive\\Documentos\\GitHub\\Compiladores\\sort.txt");
    if (!arq.is_open()) {
        std::cerr << "Erro ao abrir o arquivo!" << std::endl;
        return 1;
    }

    std::ofstream arqSaida("C:\\Users\\felip\\OneDrive\\Documentos\\GitHub\\Compiladores\\sort_transformado.txt");
    if (!arqSaida.is_open()) {
        std::cerr << "ERRO: Nao foi possivel criar o arquivo 'sort_transformado.txt' para escrita." << std::endl;
        return 1; 
    }

    std::string linha;
    int numero_da_linha = 1;
    int entrada;
    int i_inicial;
    int i_final;


  
    while (std::getline(arq, linha)) {
        int estado_atual = INICIAL;
        for(int i = 0; i < linha.size(); i++) {
            // std::cout << linha[i] ;
            if (estado_atual == INICIAL) {
                i_inicial = i;
                
            }
            entrada = getCategoriaIndice(linha[i]);
            estado_atual = tabelaTransicao[estado_atual][entrada];
            if (estado_atual == FINAL){
                i_final = i - 1;
                std :: string token;
                if (linha.substr(i_inicial, i_final - i_inicial + 1) == "int" || linha.substr(i_inicial, i_final - i_inicial + 1) == "return"
                || linha.substr(i_inicial, i_final - i_inicial + 1) == "if" || linha.substr(i_inicial, i_final - i_inicial + 1) == "else"
                || linha.substr(i_inicial, i_final - i_inicial + 1) == "while" || linha.substr(i_inicial, i_final - i_inicial + 1) == "for"
                || linha.substr(i_inicial, i_final - i_inicial + 1) == "break" || linha.substr(i_inicial, i_final - i_inicial + 1) == "void"
                || linha.substr(i_inicial, i_final - i_inicial + 1) == "float" || linha.substr(i_inicial, i_final - i_inicial + 1) == "char"){
                    token = "KEY";
                } else {
                    token = "ID";
                }
                arqSaida << token;
                std::cout << "Linha " << numero_da_linha << ": " << linha.substr(i_inicial, i_final - i_inicial + 1) << " - " << token << std::endl;
                i--;
                estado_atual = INICIAL;
            } else if (estado_atual == ERRO){
                arqSaida << linha[i];
                // std::cout << "Linha " << numero_da_linha << ": " << linha[i] << " - Símbolo inválido!" << std::endl;
                estado_atual = INICIAL;
            // std :: cout << " -> " << estado_atual << " " ;
        }
    
        

        
    }
    arqSaida << '\n';
    numero_da_linha++;
    }

        arqSaida.close();



  
    std::ifstream arqResultado("C:\\Users\\felip\\OneDrive\\Documentos\\GitHub\\Compiladores\\sort_transformado.txt");

    std:: string linhasaida;
    while (std::getline(arqResultado, linhasaida)) {
        
        for (int i = 0; i < linhasaida.size(); i++) {
            std::cout << linhasaida[i];
        }
        std::cout << std::endl;
    }
    arq.close();
    arqSaida.close();
    return 0;
}