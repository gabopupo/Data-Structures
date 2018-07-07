// Gabriel Romualdo Silveira Pupo
// 9896250
// TRABALHO 3: ARVORE VERMELHO-PRETA

#include <stdlib.h>
#include <stdio.h>
#include "redblack.h"

// Cria um node de chave k, alocando um espaco para ele na Heap.

node *create_node(int k) {
	node *new = (node *) malloc (sizeof(node));
	if (new != NULL) {
		new->left = NULL; new->right = NULL;
		new->parent = NULL;	// Inicializa os nodes parentes
		new->key = k;
		new->color = RED;	// todos os nodes comecam com a cor vermelha
	}
	return new;
}

// Visita o node, imprimindo sua chave na saida padrao.

void visit(node *n) {
	printf("%d ", n->key);
}

// Navega pela arvore, seguindo determinada ordem. (Pos-ordem, Em-ordem, Pos-ordem)

void browse(node *n, int t) {
	if (n != NULL) {
		if (t == PREORDER) visit(n);
		browse(n->left, t);
		if (t == INORDER) visit(n);
		browse(n->right, t);
		if (t == POSTORDER) visit(n);
	}
}

// Determina se o filho eh esquerdo ao pai.

int is_left_child(node *father, node *child) {
	return (father->left != NULL && father->left->key == child->key);
}

// Determina se o filho eh direito ao pai.

int is_right_child(node *father, node *child) {
	return (father->right != NULL && father->right->key == child->key);
}

// Esta funcao se destina a recolorir os nodes da arvore, e rotaciona-los se necessario, a partir de um node dado
// que pertence a arvore e dos casos de recoloracao proprios da arvore vermelho-preta, a fim de nao haver dois
// nodes vermelhos consecutivos na arvore.

void recolor(node *n) {
	node *father = n->parent;		// pai de n
	node *grandpa = father->parent;		// avo de n
	node *uncle = NULL;			// tio de n
	node *aux = NULL;			// node auxiliar

	if (grandpa != NULL && father != NULL) {
		// CASO 1: o pai e o tio de n sao vermelhos, e seu avo eh preto
		// nao rotacionar, recolorir pai, tio e avo
		if (grandpa->left != NULL && grandpa->left->key != father->key)
			uncle = grandpa->left;
		else if (grandpa->right != NULL && grandpa->right->key != father->key)
			uncle = grandpa->right;

		if (uncle != NULL && father->color == RED && uncle->color == RED && grandpa->color == BLACK) {
			grandpa->color = RED;
			father->color = uncle->color = BLACK;
		}
	

		// CASO 2: n eh filho esquerdo de um pai vermelho, filho esquerdo de um avo preto
		// aplicar rotacao direita, recolorir pai e avo
		if (is_left_child(father, n) && is_left_child(grandpa, father) && father->color == RED && grandpa->color == BLACK) {
			if (grandpa->parent != NULL) grandpa->parent->left = father;
			father->parent = grandpa->parent;
			aux = father->right;
			father->right = grandpa;
			grandpa->parent = father;
			grandpa->left = aux;
			if (grandpa->left != NULL) grandpa->left->parent = grandpa;
			father->color = BLACK;
			grandpa->color = RED;
		}

		// CASO 3: n eh filho direito de um pai vermelho, filho direito de um avo preto
		// aplicar rotacao esquerda, recolorir pai e avo
		if (is_right_child(father, n) && is_right_child(grandpa, father) && father->color == RED && grandpa->color == BLACK){
			if (grandpa->parent != NULL) grandpa->parent->right = father;
			father->parent = grandpa->parent;
			aux = father->left;
			father->left = grandpa;
			grandpa->parent = father;
			grandpa->right = aux;
			if (grandpa->right != NULL) grandpa->right->parent = grandpa;
			father->color = BLACK;
			grandpa->color = RED;
		}

		// CASO 4: n eh filho esquerdo de um pai vermelho, filho direito de um avo preto
		// aplicar rotacao dupla esquerda, recolorir avo e n
		if (is_left_child(father, n) && is_right_child(grandpa, father) && father->color == RED && grandpa->color == BLACK) {
			// ROTACAO DIREITA
			grandpa->right = n;
			n->parent = grandpa;
			father->left = n->right;
			if (father->left != NULL) father->left->parent = father;
			n->right = father;
			father->parent = n;
			// ROTACAO ESQUERDA
			if (grandpa->parent != NULL) grandpa->parent->right = n;
			n->parent = grandpa->parent;
			grandpa->right = n->left;
			if (grandpa->right != NULL) grandpa->right->parent = grandpa;
			n->left = grandpa;
			grandpa->parent = n;
			n->color = BLACK;
			grandpa->color = RED;
		}

		// CASO 5: n eh filho direito de um pai vermelho, filho esquerdo de um avo preto
		// aplicar rotacao dupla direita, recolorir avo e n
		if (is_right_child(father, n) && is_left_child(grandpa, father) && father->color == RED && grandpa->color == BLACK) {
			// ROTACAO ESQUERDA
			grandpa->left = n;
			n->parent = grandpa;
			father->right = n->left;
			if (father->right != NULL) father->right->parent = father;
			n->left = father;
			father->parent = n;
			// ROTACAO DIREITA
			if (grandpa->parent != NULL) grandpa->parent->left = n;
			n->parent = grandpa->parent;
			grandpa->left = n->right;
			if (grandpa->left != NULL) grandpa->left->parent = grandpa;
			n->right = grandpa;
			grandpa->parent = n;
			n->color = BLACK;
			grandpa->color = RED;
		}

		// eh possivel que apos a recoloracao da arvore, a partir do node dado, surjam dois nodes vermelhos consecutivos
		// na arvore. o laco a seguir checa se algum parente de n tem pai vermelho e, se tiver, chama a funcao de novo a
		// partir desse novo node encontrado

		while (n != NULL) {
			if (n->color == RED && n->parent != NULL && n->parent->color == RED)
				recolor(n);
			n = n->parent;
		}
	}
}

// Esta funcao atualiza a raiz da arvore apos a recoloracao, para se certificar que a arvore sempre tem uma raiz preta

void update_root(node **r) {
	while ((*r)->parent != NULL)
		*r = (*r)->parent;
	(*r)->color = BLACK;
}

// Adiciona um node na arvore vermelho-preta

void add(node **n, int k) {
	node **p = NULL;	// ponteiro auxiliar
	node **root = n;	// raiz

	if (*n == NULL) { // se a arvore esta vazia, crie a raiz
		*n = create_node(k);
		(*n)->color = BLACK;
	} else {
		while (*n != NULL) { // procure uma posicao adequada para o novo node com base na chave k
			// a navegacao funciona como numa arvore binaria de busca (menores a esqueda, maiores a direita)
			if (k < (*n)->key) {
				p = n; // guarde o node atual (para ter uma referencia ao pai na proxima iteracao)
				n = &(*n)->left;
			} else if (k > (*n)->key) {
				p = n;
				n = &(*n)->right;
			} else return;
		} // ao achar uma posicao adequada, saia do loop

		*n = create_node(k);	// alocacao do espaco
		(*n)->parent = *p;	// referencia ao pai
		recolor(*n);		// recoloracao
		update_root(root);	// atualizacao da raiz
	}
}

// Retorna a menor chave da arvore.

int min_value(node *n) {
	while (n->left != NULL)
		n = n->left; // a menor chave esta na posicao mais a esquerda da arvore
	return n->key;
}

// Retorna a maior chave da arvore.

int max_value(node *n) {
	while (n->right != NULL)
		n = n->right; // a maior chave esta na posicao mais a direita da arvore
	return n->key;
}

// Retorna uma referencia ao node que contem a chave k na arvore.

node *search(node *n, int k) {
	if (n == NULL) return NULL;
	if (n->key == k) return n;
	if (n->key > k) return search(n->left, k);
	return search(n->right, k);
}

// Retorna o predecessor a uma chave k presente na arvore.

int predecessor(node *n, int k) {
	node *match = search(n, k); // pesquise o node na arvore para ter uma referencia a ele
	if (match != NULL) { // se o node existe...
		if (match->left != NULL) { // se ele tem um filho esquerdo
			match = match->left; // va para a esquerda
			while (match->right != NULL) // navegue ate um node folha a partir do neto direito
				match = match->right;
			return match->key; // retorne a chave da folha
		}
		if (match->parent != NULL && match->parent->key < k) // caso contrario, se ele tem um pai, de chave menor que a sua
			return match->parent->key; // retorne a chave do pai
	}
	return -1; // o node nao existe ou ele tem a menor chave da arvore
}

// Retorna o sucessor a uma chave k presente na arvore.

int successor(node *n, int k) {
	node *match = search(n, k); // pesquise o node na arvore para ter uma referencia a ele
	if (match != NULL) { // se o node existe...
		if (match->right != NULL) { // se ele tem um filho direito
			match = match->right; // va para a direita
			while (match->left != NULL) // navegue ate um node folha a partir do neto esquerdo
				match = match->left;
			return match->key; // retorne a chave da folha
		}
		if (match->parent != NULL && match->parent->key > k) // caso contrario, se ele tem um pai, de chave maior que a sua
			return match->parent->key; // retorne a chave do pai
	}
	return -1; // o node nao existe ou ele tem a menor chave da arvore
}

// Desaloca a arvore completamente. Navega em pos-ordem e libera todos os nodes filhos da raiz,
// e entao libera a raiz e depois a arvore.

void destroy(node **n) {
	if (*n != NULL) {
		destroy(&(*n)->left);
		destroy(&(*n)->right);
		free(*n);
		*n = NULL;
	}
}
