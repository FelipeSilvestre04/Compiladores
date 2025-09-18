#include <iostream>
#include <fstream>
#include <string> 
#include <cctype> 

const int INICIAL = 0;
const int ACEITACAO = 1;
const int FINAL = 2;
const int ERRO = 3;

const int LETRA = 0;
const int DIGITO = 1;
const int OUTRO = 2;


int tabelaTransicao[4][3] = {
    //           LETRA,      DIGITO,    OUTRO      
    /*INICIAL*/ {ACEITACAO,  ERRO,      ERRO},
    /*ACEITACAO*/{ACEITACAO,  ACEITACAO, FINAL},
    /*FINAL*/   {FINAL,      FINAL,     FINAL}, 
    /*ERRO*/    {ERRO,       ERRO,      ERRO}  
};

int getCategoriaIndice(char c) {
    if (isalpha(c)) return LETRA;
    if (isdigit(c)) return DIGITO;
    return OUTRO;
}



int main() {
    std::ifstream arq("C:\\Users\\felip\\OneDrive\\Documentos\\GitHub\\Compiladores\\sort.txt");
    if (!arq.is_open()) {
        std::cerr << "Erro" << std::endl;
        return 1;
    }

    std::ofstream arqSaida("C:\\Users\\felip\\OneDrive\\Documentos\\GitHub\\Compiladores\\sort_transformado.txt");
    if (!arqSaida.is_open()) {
        std::cerr << "ERRO" << std::endl;
        return 1; 
    }

    std::string linha;
    int numero_da_linha = 1;
    int i_inicial = 0; 

    while (std::getline(arq, linha)) {
        int estado_atual = INICIAL;
        for(int i = 0; i < linha.size(); i++) {

            if (estado_atual == INICIAL) {
                i_inicial = i;
            }

            int categoria = getCategoriaIndice(linha[i]);
            estado_atual = tabelaTransicao[estado_atual][categoria];

            if (estado_atual == FINAL){

                std::string lexema = linha.substr(i_inicial, i - i_inicial);
                
                std::string token_para_escrever;

                if (lexema == "int" || lexema == "return" || lexema == "if" || lexema == "else" ||
                    lexema == "while" || lexema == "for" || lexema == "break" || lexema == "void" ||
                    lexema == "float" || lexema == "char")
                {
                    token_para_escrever = lexema; 
                } else {
                    token_para_escrever = "ID";
                }

                arqSaida << token_para_escrever; 
                
                std::cout << "Linha " << numero_da_linha << ": " << lexema << " - " << token_para_escrever << std::endl;
                
                i--;
                estado_atual = INICIAL;

            } else if (estado_atual == ERRO){
                arqSaida << linha[i];
                estado_atual = INICIAL;
            }
        }
        arqSaida << '\n';
        numero_da_linha++;
    }


    arq.close();
    arqSaida.close();

    
    std::ifstream arqResultado("C:\\Users\\felip\\OneDrive\\Documentos\\GitHub\\Compiladores\\sort_transformado.txt");
    if (!arqResultado.is_open()) {
        std::cerr << "Nao foi possivel reabrir o arquivo de resultado para verificar." << std::endl;
        return 1;
    }

    std::string linhasaida;
    while (std::getline(arqResultado, linhasaida)) {
        std::cout << linhasaida << std::endl;
    }
    arqResultado.close();
    
    return 0;
}