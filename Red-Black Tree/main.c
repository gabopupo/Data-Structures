// Gabriel Romualdo Silveira Pupo
// 9896250
// TRABALHO 3: ARVORE VERMELHO-PRETA

#include <stdio.h>
#include "redblack.h"

int main(void) {
	int n, op, k, i, res;
	node *rbt = NULL;
	scanf("%d", &n);

	for (i = 0; i < n; ++i) {
		scanf("%d", &op);
		switch (op) {
		case 1: // ADICIONA NODE
			scanf("%d", &k);
			add(&rbt, k);
			break;
		case 2: // SUCESSOR DE K
			scanf("%d", &k);
			res = successor(rbt, k);
			if (res >= 0) printf("%d\n", res);
			else printf("erro\n");
			break;
		case 3: // PREDECESSOR DE K
			scanf("%d", &k);
			res = predecessor(rbt, k);
			if (res >= 0) printf("%d\n", res);
			else printf("erro\n");
			break;
		case 4: // VALOR MAXIMO DA ARVORE
			printf("%d\n", max_value(rbt));
			break;
		case 5: // VALOR MINIMO DA ARVORE
			printf("%d\n", min_value(rbt));
			break;
		case 6: // NAVEGA PELA ARVORE EM PRE-ORDEM
		case 7: //			 EM-ORDEM
		case 8: // 			 POS-ORDEM
			browse(rbt, op);
			printf("\n");
			break;
		}
	}

	destroy(&rbt); // DESALOCA A ARVORE AO FINAL DA EXECUCAO
	return 0;
}
