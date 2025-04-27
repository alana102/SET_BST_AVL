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

    

public:

    void show() {
        bshow(root, "");
    }

    // construtor vazio
    // cria um conjunto vazio
    Set(){
        root = nullptr;
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
            throw runtime_error("erro: arvore vazia");
        } else {
            return maximum(root)->key;
        }
    }

    // função pública que retorna o menor elemento
    int minimum(){
        if(root == nullptr){
            throw runtime_error("erro: arvore vazia");
        } else {
            return minimum(root)->key;
        }
    }

    // função pública do sucessor
    int successor(int key){

        Node *no = get(root, key);

        if(no==nullptr){
            throw runtime_error("erro: nó não existe na árvore");
        } 

        Node *succ = successor(no);

        if(succ == nullptr){
            throw runtime_error("erro: nó não possui sucessor");
        }

        return succ->key;
    }

    // função pública do predecessor
    int predecessor(int key){

        Node *no = get(root, key);

        if(no==nullptr){
            throw runtime_error("erro: nó não existe na árvore");
        } 

        Node *pre = predecessor(no);

        if(pre == nullptr){
            throw runtime_error("erro: nó não possui predecessor");
        }

        return pre->key;
    }

    // destrutor
    ~Set(){
        root = clear(root);
    }



};

#endif