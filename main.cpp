// Alana Maria Sousa Augusto - 564976
#include<iostream>
#include<vector>
#include<sstream>
#include<iomanip>
#include "Set.hpp"
using namespace std;

// Função que transforma os comandos feitos no terminal em um vetor
vector<string> lerComando(){
    string frase; 
    vector<string> comando; 
    string aux; 
    getline(cin, frase); 

    stringstream ss(frase);

    while(ss >> aux){ 
        comando.push_back(aux);
    }

    return comando;
}

// função que mostra os comandos disponíveis no sistema
// para manipular os conjuntos
void mostrarAjuda(){
    cout << "|***************************************************************************************************|" << endl;
    cout << "|COMANDOS DISPONIVEIS:                                                                              |" << endl;
    cout << "|***************************************************************************************************|" << endl;
    cout << "|sair ............................................................................. fecha o programa|" << endl;
    cout << "|criar ..................................... cria um conjunto vazio e armazena na lista de conjuntos|" << endl;
    cout << "|copia i ................ cria um conjunto com os mesmos elementos do conjunto da posicao i do vetor|" << endl;
    cout << "|troca i j ....................... troca os elementos do conjunto i pelos do conjunto j e vice-versa|" << endl;
    cout << "|vazio i .................................... verfica se o conjunto na posicao i do vetor esta vazio|" << endl;
    cout << "|mostrar i ................................................. mostra o conjunto na posicao i do vetor|" << endl;
    cout << "|listar ...................................................... lista os conjuntos que estao no vetor|" << endl;
    cout << "|removerConjunto i ........................................ remove um conjunto na posicao i do vetor|" << endl;
    cout << "|apagarTudo ............................................ apaga todas os conjuntos atuais do programa|" << endl;
    cout << "|***************************************************************************************************|" << endl;
    cout << "|OPERACOES ENTRE CONJUNTOS:                                                                         |" << endl;
    cout << "|***************************************************************************************************|" << endl;
    cout << "|uni i j ......................................... retorna a uniao entre o conjunto i e o conjunto j|" << endl;
    cout << "|inter i j .................................. retorna a insersecao entre o conjunto i e o conjunto j|" << endl;
    cout << "|dif i j ..................................... retorna a diferenca entre o conjunto i e o conjunto j|" << endl;
    cout << "|***************************************************************************************************|" << endl;
    cout << "|MANIPULACAO DE ELEMENTOS:                                                                          |" << endl;
    cout << "|***************************************************************************************************|" << endl;
    cout << "|limpar i ................................................... limpa o conjunto na posicao i do vetor|" << endl;
    cout << "|add i elem ................................. adiciona um elemento no conjunto da posicao i do vetor|" << endl;
    cout << "|remover i elem ...................... remove determinado elemento do conjunto da posicao i do vetor|" << endl;
    cout << "|succ elem i ................... retorna o sucessor de um elemento no conjunto da posicao i do vetor|" << endl;
    cout << "|pred elem i ................ retorna o predecessor de um elemento no conjunto da posicao i do vetor|" << endl;
    cout << "|pertence elem i ................ verifica se um elemento pertence ao conjunto da posicao i do vetor|" << endl;
    cout << "|min i .................................. retorna o menor elemento do conjunto da posicao i do vetor|" << endl;
    cout << "|max i .................................. retorna o maior elemento do conjunto da posicao i do vetor|" << endl;
    cout << "|tam i ......................................... retorna o tamanho do conjunto da posicao i do vetor|" << endl;
    cout << "|***************************************************************************************************|" << endl;
}

int main(){

    cout << "Sistema de Conjuntos" << endl;
    cout << "Digite 'ajuda' para ver a lista de comandos disponiveis" << endl; 

    // vetor que armazena todos os conjuntos do sistema
    vector<Set*> listaSet;

    while(true){
        vector<string> comando = lerComando();

        // caso o usuário não escreva nada
        if(comando.empty()){
            cout << "Escreva um comando valido." << endl;
            continue;
        }

        // comando de ajuda
        if(comando[0] == "ajuda" && comando.size() == 1){
            mostrarAjuda();
            continue;
        }

        // comando de sair
        if(comando[0] == "sair" && comando.size() == 1){

            if(!listaSet.empty()){
                for(size_t i = 0; i < listaSet.size(); i++){
                    delete listaSet[i];
                }

                listaSet.clear();
            }

            cout << "Encerrando sistema..." << endl;
            break;
        }

        // comando de criar um conjunto
        if(comando[0] == "criar" && comando.size() == 1){
            Set *newSet = new Set();
            listaSet.push_back(newSet);
            cout << "conjunto " << listaSet.size() - 1 << " foi criado com sucesso" << endl;
            continue;
        }

        // comando que mostra um determinado conjunto de acordo com o índice
        if(comando[0] == "mostrar" && comando.size() == 2){
            try{
                if(comando[1].find(".") != string::npos || comando[1].find(",") != string::npos){
                    throw invalid_argument("valor int nao inserido");
                }
    
                size_t i = stoi(comando[1]);
    
                if(listaSet.empty()){
                    cout << "a lista de conjuntos esta vazia, crie um conjunto e tente novamente" << endl;
                    continue;
                } else if (i == 0 || i < listaSet.size()){
                    cout << "conjunto " << i << " = ";
                    listaSet[i] -> printInfix();
                    continue;
                } else {
                    cout << "nao existe conjunto nessa posicao" << endl;
                    continue;
                }
            } catch (const invalid_argument& e){
                cout << "erro: tipo do indice inserido e invalido, insira valores inteiros." << endl;
                continue;
            }
            
        }

        // comando que cria um conjunto sendo a cópia de outro
        if(comando[0] == "copia" && comando.size() == 2){
            try {
                if(comando[1].find(".") != string::npos || comando[1].find(",") != string::npos){
                    throw invalid_argument("valor int nao inserido");
                }
    
                size_t i = stoi(comando[1]);

                if(listaSet.empty()){
                    cout << "a lista de conjuntos esta vazia, crie um conjunto e tente novamente" << endl;
                    continue;
                } else if(i == 0 || i < listaSet.size()){
                    Set *newSet = new Set(*listaSet[i]);
                    listaSet.push_back(newSet);
                    cout << "conjunto " << listaSet.size() - 1 << " foi criado com sucesso com os mesmos elementos do conjunto " << i << endl;
                    continue;
                } else {
                    cout << "o conjunto que voce quer copiar nao existe na lista de conjuntos" << endl;
                    continue;
                }


            } catch (const invalid_argument& e){
                cout << "erro: tipo do indice inserido e invalido, insira valores inteiros." << endl;
                continue;
            }
        }

        // comando que troca os elementos de dois conjuntos
        if(comando[0] == "troca" && comando.size() == 3){

            try{
                if((comando[1].find(".") != string::npos || comando[1].find(",") != string::npos) &&
                    (comando[2].find(".") != string::npos || comando[2].find(",") != string::npos)){
                    throw invalid_argument("valor int nao inserido");
                }   

                size_t i = stoi(comando[1]);
                size_t j = stoi(comando[2]);

                if(listaSet.empty()){
                    cout << "a lista de conjuntos esta vazia, crie um conjunto e tente novamente" << endl;
                    continue;
                } else if((i == 0 || i < listaSet.size()) && (j == 0 || j < listaSet.size())){
                    listaSet[i]->swap(*listaSet[j]);
                    cout << "conjunto " << i << " trocou seus elementos com o conjunto " << j << endl;
                    continue;
                } else {
                    cout << "nao existe conjunto em uma das posicoes que voce digitou" << endl;
                    continue;
                }

            } catch (const invalid_argument& e){
                cout << "erro: tipo do indice inserido e invalido, insira valores inteiros." << endl;
                continue;
            }

        }

        // comando que verifica se um conjunto está vazio
        if(comando[0] == "vazio" && comando.size() == 2){
            try{
                if(comando[1].find(".") != string::npos || comando[1].find(",") != string::npos){
                    throw invalid_argument("valor int nao inserido");
                }
    
                size_t i = stoi(comando[1]);

                if(listaSet.empty()){
                    cout << "a lista de conjuntos esta vazia, crie um conjunto e tente novamente" << endl;
                    continue;
                } else if (i == 0 || i < listaSet.size()){
                    if(listaSet[i]->empty()){
                        cout << "o conjunto " << i << " esta vazio." << endl;
                        continue;
                    } else {
                        cout << "o conjunto " << i << " NAO esta vazio." << endl;
                        continue;
                    }
                } else {
                    cout << "nao existe conjunto nessa posicao" << endl;
                    continue;
                }

            } catch (const invalid_argument& e){
                cout << "erro: tipo do indice inserido e invalido, insira valores inteiros." << endl;
                continue;
            }
        }

        // comando que lista todos os conjuntos do vetor
        // especificando index, nome e cardinalidade
        if(comando[0] == "listar" && comando.size() == 1){

            if(listaSet.empty()){
                cout << "nao ha nenhum conjunto registrado, insira um conjunto na lista." << endl;
                continue;
            }

            int tamanho_coluna = 10;

            int largura_total = tamanho_coluna * 3 + 5;

            for(int i = 0; i < largura_total; ++i){
                cout << "-";
            }

            cout << "\n";

            cout << "|" << setw(tamanho_coluna) << left << "Index" << "|";
            cout << setw(tamanho_coluna) << left << "Nome" << "|";
            cout << setw(tamanho_coluna) << left << "Tamanho" << "|";

            cout << "\n";
            
            for (size_t i = 0; i < listaSet.size() ; i++){
                string nome = ("Conj " + to_string(i));
                string tamanho = to_string(listaSet[i]->size());

                cout << "|" << setw(tamanho_coluna) << left << i << "|";

                cout << setw(tamanho_coluna) << left << nome << "|";
                cout << setw(tamanho_coluna) << left << tamanho << "|";

                cout << endl;
            }

            for(int i = 0; i < largura_total; ++i){
                cout << "-";
            }

            cout << "\n";
            continue;
        }

        // comando que remove determinado conjunto da lista de conjuntos
        if(comando[0] == "removerConjunto" && comando.size() == 2){
            try{
            
                if((comando[1].find(".") != string::npos || comando[1].find(",") != string::npos)){
                    throw invalid_argument("valor int nao inserido");
                }
           
                size_t i = stoi(comando[1]);
                
                if(listaSet.empty()){
                    cout << "nao ha conjuntos na lista para serem removidas." << endl;
                    continue;
                }else if(i == 0 || i < listaSet.size()){
                    delete listaSet[i];
                    listaSet.erase(listaSet.begin() + i);

                    cout << "conjunto na posicao " << i << " foi removido com sucesso" << endl;
                    continue;
                }else{
                    cout << "nao existe conjunto nessa posicao, digite uma posicao valida." << endl;
                    continue;
                }

            }
            catch(const invalid_argument& e){
                cout << "erro: tipo do indice inserido e invalido, insira valores inteiros" << endl;
                continue;
            }
        }

        // comando que apaga todos os conjuntos presentes na lista
        if(comando[0] == "apagarTudo"  && comando.size() == 1){
            if(listaSet.empty()){
                cout << "nao ha conjuntos no vetor para serem removidas." << endl;
                continue;
            }

            for(size_t i = 0; i < listaSet.size(); i++){
                delete listaSet[i];
            }

            listaSet.clear();
            cout << "lista de conjuntos apagada com sucesso!" << endl;
            continue;
        }

        // comando que limpa um determinado conjunto da lista
        if(comando[0] == "limpar" && comando.size() == 2){
            try{
                if(comando[1].find(".") != string::npos || comando[1].find(",") != string::npos){
                    throw invalid_argument("valor int nao inserido");
                }

                size_t i = stoi(comando[1]);

                if(listaSet.empty()){
                    cout << "sua lista de conjuntos esta vazia, adicione um conjunto." << endl;
                    continue;
                }else if(i == 0 || i < listaSet.size()){
                    listaSet[i]->clear();
                    cout << "conjunto " << i << " foi limpo com sucesso." << endl;
                    continue;
                }else{
                    cout << "nao existe conjunto nessa posicao, digite uma posicao valida." << endl;
                    continue;
                }
            } catch(const invalid_argument& e){
                cout << "erro: tipo do indice inserido e invalido, insira valores inteiros." << endl;
                continue;
            } 

        }

        // comando que adiciona um elemento em determinado conjunto
        if(comando[0] == "add" && comando.size() == 3){
            try{
                if((comando[1].find(".") != string::npos || comando[1].find(",") != string::npos) &&
                    (comando[2].find(".") != string::npos || comando[2].find(",") != string::npos)){
                    throw invalid_argument("valor int nao inserido");
                }   

                size_t i = stoi(comando[1]);
                int elem = stoi(comando[2]);

                if(listaSet.empty()){
                    cout << "a lista de conjuntos esta vazia, crie um conjunto e tente novamente" << endl;
                    continue;
                } else if(i == 0 || i < listaSet.size()){

                    if(!listaSet[i]->contains(elem)){
                        listaSet[i]->insert(elem);
                        cout << "elemento " << elem << " inserido com sucesso no conjunto " << i << endl;
                        continue;
                    } else {
                        cout << "conjunto " << i << " ja possui o elemento " << elem << endl;
                        continue;
                    }
                    
                } else {
                    cout << "nao existe conjunto nessa posicao, digite uma posicao valida." << endl;
                    continue;
                }

            } catch (const invalid_argument& e){
                cout << "erro: tipo do indice inserido e invalido, insira valores inteiros." << endl;
                continue;
            }
        }

        // comando que remove um elemento em determinado conjunto
        if(comando[0] == "remover" && comando.size() == 3){
            try{
                if((comando[1].find(".") != string::npos || comando[1].find(",") != string::npos) &&
                    (comando[2].find(".") != string::npos || comando[2].find(",") != string::npos)){
                    throw invalid_argument("valor int nao inserido");
                }   

                size_t i = stoi(comando[1]);
                int elem = stoi(comando[2]);

                if(listaSet.empty()){
                    cout << "a lista de conjuntos esta vazia, crie um conjunto e tente novamente" << endl;
                    continue;
                } else if(i == 0 || i < listaSet.size()){

                    if(listaSet[i]->contains(elem)){
                        listaSet[i]->erase(elem);
                        cout << "elemento " << elem << " removido com sucesso do conjunto " << i << endl;
                        continue;
                    } else {
                        cout << "conjunto " << i << " nao possui o elemento " << elem << endl;
                        continue;
                    }
                    
                } else {
                    cout << "nao existe conjunto nessa posicao, digite uma posicao valida." << endl;
                    continue;
                }

            } catch (const invalid_argument& e){
                cout << "erro: tipo do indice inserido e invalido, insira valores inteiros." << endl;
                continue;
            }
        }

        // comando que retorna o sucessor de um elemento de um conjunto
        if(comando[0] == "succ" && comando.size() == 3){
            try{
                if((comando[1].find(".") != string::npos || comando[1].find(",") != string::npos) &&
                    (comando[2].find(".") != string::npos || comando[2].find(",") != string::npos)){
                    throw invalid_argument("valor int nao inserido");
                }   

                size_t i = stoi(comando[2]);
                int elem = stoi(comando[1]);

                if(listaSet.empty()){
                    cout << "a lista de conjuntos esta vazia, crie um conjunto e tente novamente" << endl;
                    continue;
                } else if(i == 0 || i < listaSet.size()){
 
                    int succ = listaSet[i]->successor(elem);
                    cout << "conjunto " << i << " | sucessor de " << elem << ": " << succ << endl;
                    continue; 
                    
                } else {
                    cout << "nao existe conjunto nessa posicao, digite uma posicao valida." << endl;
                    continue;
                }

            } catch (const invalid_argument& e){
                cout << "erro: tipo do indice inserido e invalido, insira valores inteiros." << endl;
                continue;
            } catch (const out_of_range& e){
                cout << "erro: elemento nao pertence ao conjunto" << endl;
                continue;
            } catch (const logic_error& e){
                cout << "erro: elemento nao possui sucessor" << endl;
                continue;
            }
        }

        // comando que retorna o predecessor de um elemento de um conjunto
        if(comando[0] == "pred" && comando.size() == 3){
            try{
                if((comando[1].find(".") != string::npos || comando[1].find(",") != string::npos) &&
                    (comando[2].find(".") != string::npos || comando[2].find(",") != string::npos)){
                    throw invalid_argument("valor int nao inserido");
                }   

                size_t i = stoi(comando[2]);
                int elem = stoi(comando[1]);

                if(listaSet.empty()){
                    cout << "a lista de conjuntos esta vazia, crie um conjunto e tente novamente" << endl;
                    continue;
                } else if(i == 0 || i < listaSet.size()){
 
                    int pred = listaSet[i]->predecessor(elem);
                    cout << "conjunto " << i << " | predecessor de " << elem << ": " << pred << endl;
                    continue; 
                    
                } else {
                    cout << "nao existe conjunto nessa posicao, digite uma posicao valida." << endl;
                    continue;
                }

            } catch (const invalid_argument& e){
                cout << "erro: tipo do indice inserido e invalido, insira valores inteiros." << endl;
                continue;
            } catch (const out_of_range& e){
                cout << "erro: elemento nao pertence ao conjunto" << endl;
                continue;
            } catch (const logic_error& e){
                cout << "erro: elemento nao possui predecessor" << endl;
                continue;
            }
        }

        // comando que verifica se um elemento pertence a determinado conjunto
        if(comando[0] == "pertence" && comando.size() == 3){
            try{
                if((comando[1].find(".") != string::npos || comando[1].find(",") != string::npos) &&
                    (comando[2].find(".") != string::npos || comando[2].find(",") != string::npos)){
                    throw invalid_argument("valor int nao inserido");
                }   

                size_t i = stoi(comando[2]);
                int elem = stoi(comando[1]);

                if(listaSet.empty()){
                    cout << "a lista de conjuntos esta vazia, crie um conjunto e tente novamente" << endl;
                    continue;
                } else if(i == 0 || i < listaSet.size()){

                    if(listaSet[i]->contains(elem)){
                        cout << "elemento " << elem << " pertence ao conjunto " << i << endl;
                    } else {
                        cout << "elemento " << elem << " NAO pertence ao conjunto " << i << endl;
                        continue;
                    }
                    
                } else {
                    cout << "nao existe conjunto nessa posicao, digite uma posicao valida." << endl;
                    continue;
                }

            } catch (const invalid_argument& e){
                cout << "erro: tipo do indice inserido e invalido, insira valores inteiros." << endl;
                continue;
            }
        }

        // comando que retorna o mínimo elemento de um conjunto
        if(comando[0] == "min" && comando.size() == 2){
            try{
                if((comando[1].find(".") != string::npos || comando[1].find(",") != string::npos)){
                    throw invalid_argument("valor int nao inserido");
                }   

                size_t i = stoi(comando[1]);

                if(listaSet.empty()){
                    cout << "a lista de conjuntos esta vazia, crie um conjunto e tente novamente" << endl;
                    continue;
                } else if(i == 0 || i < listaSet.size()){
 
                    int min = listaSet[i]->minimum();
                    cout << "conjunto " << i << " | elemento minimo: " << min << endl;
                    continue; 
                    
                } else {
                    cout << "nao existe conjunto nessa posicao, digite uma posicao valida." << endl;
                    continue;
                }

            } catch (const invalid_argument& e){
                cout << "erro: tipo do indice inserido e invalido, insira valores inteiros." << endl;
                continue;
            }
        }

        // comando que retorna o máximo elemento de um conjunto
        if(comando[0] == "max" && comando.size() == 2){
            try{
                if((comando[1].find(".") != string::npos || comando[1].find(",") != string::npos)){
                    throw invalid_argument("valor int nao inserido");
                }   

                size_t i = stoi(comando[1]);

                if(listaSet.empty()){
                    cout << "a lista de conjuntos esta vazia, crie um conjunto e tente novamente" << endl;
                    continue;
                } else if(i == 0 || i < listaSet.size()){
 
                    int max = listaSet[i]->maximum();
                    cout << "conjunto " << i << " | elemento maximo: " << max << endl;
                    continue; 
                    
                } else {
                    cout << "nao existe conjunto nessa posicao, digite uma posicao valida." << endl;
                    continue;
                }

            } catch (const invalid_argument& e){
                cout << "erro: tipo do indice inserido e invalido, insira valores inteiros." << endl;
                continue;
            }
        }

        // comando que retorna o tamanho de determinado conjunto
        if(comando[0] == "tam" && comando.size() == 2){
            try{
                if((comando[1].find(".") != string::npos || comando[1].find(",") != string::npos)){
                    throw invalid_argument("valor int nao inserido");
                }   

                size_t i = stoi(comando[1]);

                if(listaSet.empty()){
                    cout << "a lista de conjuntos esta vazia, crie um conjunto e tente novamente" << endl;
                    continue;
                } else if(i == 0 || i < listaSet.size()){
 
                    int tam = listaSet[i]->size();
                    cout << "conjunto " << i << " | tamanho: " << tam << endl;
                    continue; 
                    
                } else {
                    cout << "nao existe conjunto nessa posicao, digite uma posicao valida." << endl;
                    continue;
                }

            } catch (const invalid_argument& e){
                cout << "erro: tipo do indice inserido e invalido, insira valores inteiros." << endl;
                continue;
            }
        }

        // comando que retorna a união entre dois conjuntos
        if(comando[0] == "uni" && comando.size() == 3){
            try{
                if((comando[1].find(".") != string::npos || comando[1].find(",") != string::npos) &&
                    (comando[2].find(".") != string::npos || comando[2].find(",") != string::npos)){
                    throw invalid_argument("valor int nao inserido");
                }   

                size_t i = stoi(comando[1]);
                size_t j = stoi(comando[2]);

                if(listaSet.empty()){
                    cout << "a lista de conjuntos esta vazia, crie um conjunto e tente novamente" << endl;
                    continue;
                } else if((i == 0 || i < listaSet.size()) && (j == 0 || 0 < listaSet.size())){

                    Set *uni = new Set();

                    uni->uniao(listaSet[i], listaSet[j]);

                    cout << "uniao entre conjunto " << i << " e conjunto " << j << " = "; 
                    uni->printInfix();

                    delete uni;

                    continue;
                    
                } else {
                    cout << "nao existe conjunto nessa posicao, digite uma posicao valida." << endl;
                    continue;
                }

            } catch (const invalid_argument& e){
                cout << "erro: tipo do indice inserido e invalido, insira valores inteiros." << endl;
                continue;
            }
        }

         // comando que retorna a interseção entre dois conjuntos
         if(comando[0] == "inter" && comando.size() == 3){
            try{
                if((comando[1].find(".") != string::npos || comando[1].find(",") != string::npos) &&
                    (comando[2].find(".") != string::npos || comando[2].find(",") != string::npos)){
                    throw invalid_argument("valor int nao inserido");
                }   

                size_t i = stoi(comando[1]);
                size_t j = stoi(comando[2]);

                if(listaSet.empty()){
                    cout << "a lista de conjuntos esta vazia, crie um conjunto e tente novamente" << endl;
                    continue;
                } else if((i == 0 || i < listaSet.size()) && (j == 0 || 0 < listaSet.size())){

                    Set *inter = new Set();

                    inter->interseccao(listaSet[i], listaSet[j]);

                    cout << "interseccao entre conjunto " << i << " e conjunto " << j << " = "; 
                    inter->printInfix();

                    delete inter;

                    continue;
                    
                } else {
                    cout << "nao existe conjunto nessa posicao, digite uma posicao valida." << endl;
                    continue;
                }

            } catch (const invalid_argument& e){
                cout << "erro: tipo do indice inserido e invalido, insira valores inteiros." << endl;
                continue;
            }
        }

         // comando que retorna a união entre dois conjuntos
         if(comando[0] == "dif" && comando.size() == 3){
            try{
                if((comando[1].find(".") != string::npos || comando[1].find(",") != string::npos) &&
                    (comando[2].find(".") != string::npos || comando[2].find(",") != string::npos)){
                    throw invalid_argument("valor int nao inserido");
                }   

                size_t i = stoi(comando[1]);
                size_t j = stoi(comando[2]);

                if(listaSet.empty()){
                    cout << "a lista de conjuntos esta vazia, crie um conjunto e tente novamente" << endl;
                    continue;
                } else if((i == 0 || i < listaSet.size()) && (j == 0 || 0 < listaSet.size())){

                    Set *dif = new Set();

                    dif->diferenca(listaSet[i], listaSet[j]);

                    cout << "diferenca entre conjunto " << i << " e conjunto " << j << " = "; 
                    dif->printInfix();

                    delete dif;

                    continue;
                    
                } else {
                    cout << "nao existe conjunto nessa posicao, digite uma posicao valida." << endl;
                    continue;
                }

            } catch (const invalid_argument& e){
                cout << "erro: tipo do indice inserido e invalido, insira valores inteiros." << endl;
                continue;
            }
        }

        cout <<  "comando invalido. Cheque 'ajuda' para ver os comandos disponiveis" << endl;

    }

    return 0;

}