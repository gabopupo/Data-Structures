#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "stack.h"

int main(void) {
	int loop = 1, item;
	char op;
	stack *s = create();

	while (loop) {
		printf("\nOperation: ");
		scanf("%c", &op);
		getchar();
		switch(op) {
		case 'P': case 'p':
			printf("\nPush: ");
			scanf("%d", &item);
			getchar();

			push(s, item);
			printf("%d push'd onto stack.\n", item);
			break;
		case 'O': case 'o':
			item = pop(s);
			if (item != INT_MIN)
				printf("%d pop'd from stack.\n", item);
			else printf("Nothing to pop.\n");
			break;
		case 'T': case 't':
			item = peek(s);
			printf("%d is on top.\n", item);
			break;
		case 'D': case 'd':
			if (!empty(s)) printf("\n\n=======================\n");
			print(s);
			if (!empty(s)) printf("=======================\n\n");
			break;
		case 'Q': case 'q':
			loop = 0;
			break;
		default:
			printf("Invalid option.\n");
			break;
		}
	}
	destroy(&s);
	return 0;
}
