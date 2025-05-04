// Alana Maria Sousa Augusto - 564976
#ifndef SET_HPP
#define SET_HPP
#include "Node.hpp"

class Set{
private:    
    // ponteiro para a raiz
    Node *root;

    // função que limpa o conjunto inteiro,
    // apagando todos os nós recursivamente
    Node *clear(Node* node){
        if(node != nullptr){
            node->left = clear(node->left);
            node->right = clear(node->right);
            delete node;
        }
        return nullptr;
    }

    // função que retorna a altura de determinado nó
    int height(Node* node){
        if(node == nullptr){
            return 0;
        } else {
            return node->height;
        }
    }

    // função que retorna o tamanho do conjunto
    int size(Node* node){
        if(node == nullptr){
            return 0;
        }

        int left = size(node->left);
        int right = size(node->right);

        return 1 + left + right;
    }

    // função que ajeita os nós em caso de desbalanceamento durante
    // o processo de remoção de um nó
    Node *fixup_deletion(Node* node){
        int bal = balance(node);

        if(bal > 1 && balance(node->right) >=0 ){
            return rotation_left(node);
        } else if (bal > 1 && balance(node->right) < 0) {
            node->right = rotation_right(node->right);
            return rotation_left(node);
        } else if (bal < -1 && balance(node->left) <= 0) {
            return rotation_right(node);
        } else if (bal < -1 && balance(node->left) > 0) {
            node->left = rotation_left(node->left);
            return rotation_right(node);
        }

        node->height = 1 + max(height(node->left), height(node->right));
        return node;
    }

    // função que remove um elemento do conjunto
    // se tiver filho direito, chama a função de remover sucessor
    // se não tiver apenas faz com que o filho esquerdo assuma o lugar do nó
    // depois disso ajeita o balanceamento do nó
    Node *remove(Node *node, int key){
        if (node == nullptr){
            return nullptr;
        } else if (key < node->key){
            remove(node->left, key);
        } else if (key > node->key) {
            remove(node->right, key);
        } else if (node->right == nullptr){
            Node *filho = node->left;
            delete node;
            return filho;
        } else {
            node->right = remove_successor(node, node->right);
        }

        node = fixup_deletion(node);
        return node;

    }    

    // função chamada em caso de remoção de um nó que possui filho direito
    // essa função faz com que o nó a ser removido receba a chave de seu sucessor
    // e logo em seguida o sucessor é liberado
    Node *remove_successor(Node *root, Node *node) {
        if(node->left != nullptr){
            node->left = remove_successor(root, node->left);
        } else {
            root->key = node->key;
            Node *aux = node->right;
            delete node;
            return aux;
        }
        node = fixup_deletion(node);
        return node;
    }

    // função que retorna um nó de acordo com 
    // a chave passada como parâmetro
    Node *get(Node *node, int key){
        if (node == nullptr) {
            return nullptr;
        }

        if(node->key == key){
            return node;
        } else if (key < node->key) {
            return get(node->left, key);
        } else {
            return get(node->right, key);
        } 


    }

    // função que retorna o maior elemento 
    Node *maximum(Node *node){
        if(node != nullptr && node->right != nullptr){
            return maximum(node->right);
        } else {
            return node;
        }
    }

    // função que retorna o menor elemento 
    Node *minimum(Node *node){
        if(node != nullptr && node->left != nullptr){
            return minimum(node->left);
        } else {
            return node;
        }
    }

    // função que rotaciona a subárvore de node à direita
    Node *rotation_right(Node *node){
        Node *u = node->left;
        node->left = u->right;
        u->right = node;

        node->height = 1 + max(height(node->right), height(node->left));
        u->height = 1 + max(height(u->right), height(u->left));

        return u;
    }

    // função que rotaciona a subárvore de node à esquerda
    Node *rotation_left(Node *node){
        Node *u = node->right;
        node->right = u->left;
        u->left = node;

        node->height = 1 + max(height(node->right), height(node->left));
        u->height = 1 + max(height(u->right), height(u->left));

        return u;
    }

    // função que retorna o balanço de um nó
    int balance(Node *node){
        return height(node->right) - height(node->left);
    }

    // função que conserta o balanço dos nós
    // caso exista algum nó desbalanceado
    Node *fixupNode(Node *p, int key){

        p->height = 1 + max(height(p->left), height(p->right));

        int bal = balance(p);

        if(bal < -1 && key < p->left->key){
            return rotation_right(p);
        }

        if(bal < -1 && key > p->left->key){
            p->left = rotation_left(p->left);
            return rotation_right(p);
        }

        if(bal > 1 && key > p->right->key){
            return rotation_left(p);
        }

        if(bal > 1 && key < p->right->key){
            p->right = rotation_right(p->right);
            return rotation_left(p);
        }
        
        return p;

    }

    // função que insere um elemento no conjunto
    Node *insert(Node* node, int key){

        if(node == nullptr){
            return new Node(key, nullptr, nullptr);
        } else if (key < node->key) {
            node->left = insert(node->left, key);
        } else if (key > node->key) {
            node->right = insert(node->right, key);
        }

        node = fixupNode(node, key);

        return node;
    }

    // função que escreve o conjunto com seus
    // elementos em ordem crescente
    void printInfix(Node* node, bool& espaco) {
        if (node != nullptr) {
            printInfix(node->left, espaco);
            if (espaco) {
                cout << node->key;
                espaco = false;
            } else {
                cout << ", " << node->key;
            }
            printInfix(node->right, espaco);
        }
    }

    // função que retorna o sucessor de um
    // elemento no conjunto
    Node *successor(Node *node){
        if(node->right != nullptr){
            return minimum(node->right);
        } else {
            Node *aux = root;
            Node *pai = nullptr;

            while(aux != nullptr){
                if(node->key < aux->key){
                    pai = aux;
                    aux = aux->left;
                } else if (node->key > aux->key){
                    aux = aux->right;
                } else {
                    break;
                }
            }

            return pai;
        }
    }

    // função que retorna o predecessor de um
    // elemento no conjunto
    Node *predecessor(Node *node){
        if(node->left != nullptr){
            return maximum(node->left);
        } else {
            Node *aux = root;
            Node *pai = nullptr;

            while(aux != nullptr){
                if(node->key > aux->key){
                    pai = aux;
                    aux = aux->right;
                } else if (node->key < aux->key){
                    aux = aux->left;
                } else {
                    break;
                }
            }

            return pai;
        }
    }

    // função auxiliar que copia um nó em outro
    // auxilia na lógica da sobrecarga do operador de atribuição
    Node* copiaNo(Node* no){
        if(no == nullptr){
            return nullptr;
        }

        Node* novo_no = new Node(no->key, nullptr, nullptr);

        novo_no->left = copiaNo(no->left);
        novo_no->right = copiaNo(no->right);
        novo_no->height = no->height;

        return novo_no;
    }

    // função auxiliar de uniao entre conjuntos
    // insere todos os elem dos outros dois conjuntos
    // no conjunto que chama a função
    void uniaux(Node* node){
        if(node == nullptr) return;

        uniaux(node->left);
        this->insert(node->key);
        uniaux(node->right);
    }

    // função auxiliar de interseccao
    // insere todos os elem que pertencem
    // aos dois conjuntos simultaneamente
    // verifica isso utilizando a função contains()
    void interaux(Node* n1, Set* s2){
        if(n1 == nullptr){
            return;
        }

        interaux(n1->left, s2);

        if(s2->contains(n1->key)){
            this->insert(n1->key);
        }

        interaux(n1->right, s2);

    }

    // função auxiliar da diferenca
    // insere todos os elem que pertencem ao 
    // conjunto A mas não pertencem ao conjunto B
    // utiliza a função contains() para fazer essa verificacao
    void difaux(Node* n1, Set* s2){
        if(n1 == nullptr){
            return;
        }

        difaux(n1->left, s2);

        if(!s2->contains(n1->key)){
            this->insert(n1->key);
        }

        difaux(n1->right, s2);
    }

    void bshow(Node *node, std::string heranca) const {
        if(node != nullptr && (node->left != nullptr || node->right != nullptr))
            bshow(node->right , heranca + "r");
        for(int i = 0; i < (int) heranca.size() - 1; i++)
            std::cout << (heranca[i] != heranca[i + 1] ? "│   " : "    ");
        if(heranca != "")
            std::cout << (heranca.back() == 'r' ? "┌───" : "└───");
        if(node == nullptr){
            std::cout << "#" << std::endl;
            return;
        }
        std::cout << node->key << std::endl;
        if(node != nullptr && (node->left != nullptr || node->right != nullptr))
            bshow(node->left, heranca + "l");
    }

    // função auxiliar de busca
    // veri
    /*bool buscar(Node* node, int key){
        if(node == nullptr){
            return false;
        }

        if(node->key == key){
            return true;
        } else if (key < node->key){
            return buscar(node->left, key);
        } else {
            return buscar(node->right, key);
        }
    }*/

    

public:

    void show() {
        bshow(root, "");
    }

    // construtor vazio
    // cria um conjunto vazio
    Set(){
        root = nullptr;
    }

    // construtor de cópia
    // cria um conjunto baseado em outro
    Set(const Set& s) : Set() {
        *this = s;
    }
    
    // função publica da uniao
    void uniao(Set* s1, Set* s2){
        uniaux(s1->root);
        uniaux(s2->root);
    }

    // função publica da interseccao
    void interseccao(Set* s1, Set* s2){
        interaux(s1->root, s2);
    }

    // função publica da diferenca
    void diferenca(Set* s1, Set* s2){
        difaux(s1->root, s2);
    }


    // função que retorna a altura total da árvore
    int total_height(){
        return height(root);
    }

    // função que retorna a altura de um determinado nó
    int height(int key){
        if(get(root, key) == nullptr){
            return 0;
        } else {
            return height(get(root, key));
        }
    }

    // função que insere um novo elemento no conjunto
    void insert(int key){
        root = insert(root, key);
    }

    // função que remove um elemento do conjunto
    void erase(int key){
        root = remove(root, key);
    }

    // função que troca os elementos entre dois conjuntos
    void swap(Set& s){
        Node *aux = this->root;
        this->root = s.root;
        s.root = aux;
    }

    // função pública que retorna tamanho do conjunto
    // chamando a sua versão privada
    int size(){
        return size(root);
    }

    // verifica se o conjunto é vazio
    bool empty(){
        return root == nullptr;
    }

    // verifica se um elemento pertence ao conjunto
    bool contains(int k){
        return get(root, k) != nullptr;
    }

    // função pública que mostra os elementos do conjunto
    // em ordem crescente
    void printInfix(){
        bool espaco = true;
        cout << "{";
        printInfix(root, espaco);
        cout << "}" << endl;
    }

    // função pública que retorna o maior elemento
    int maximum(){
        if(root == nullptr){
            throw out_of_range("erro: arvore vazia");
        } else {
            return maximum(root)->key;
        }
    }

    // função pública que retorna o menor elemento
    int minimum(){
        if(root == nullptr){
            throw out_of_range("erro: arvore vazia");
        } else {
            return minimum(root)->key;
        }
    }

    // função pública do sucessor
    int successor(int key){

        Node *no = get(root, key);

        if(no==nullptr){
            throw out_of_range("erro: nó não existe na árvore");
        } 

        Node *succ = successor(no);

        if(succ == nullptr){
            throw logic_error("erro: nó não possui sucessor");
        }

        return succ->key;
    }

    // função pública do predecessor
    int predecessor(int key){

        Node *no = get(root, key);

        if(no==nullptr){
            throw out_of_range("erro: nó não existe na árvore");
        } 

        Node *pre = predecessor(no);

        if(pre == nullptr){
            throw logic_error("erro: nó não possui predecessor");
        }

        return pre->key;
    }

    // sobrecarga do operador de atribuição
    Set& operator=(const Set& s){

        if (this == &s){
            return *this;
        }

        this->clear(root);

        this->root = copiaNo(s.root);

        return *this;
    }

    // função publica que limpa um conjunto
    // deletando todos os seus elementos
    void clear(){
        root = clear(root);
    }


    // destrutor
    ~Set(){
        root = clear(root);
    }



};

#endif