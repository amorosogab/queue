#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

void stampa_coda(queue_t Q);
void *copia_elemento(void *elem);

int main(void)
{
	queue_t Q = NULL;
	int esci;

	do
	{
		int cmd;

		esci = 0;
		printf("1: Stampa Coda\n"
			   "2: Visualizza Testa\n"
			   "3: E' vuota?\n"
			   "4: Inserisci elemento\n"
			   "5: Estrai elemento\n"
			   "6: Crea coda\n"
			   "7: Distruggi coda\n"
			   "Inserisci comando: ");
		scanf("%d", &cmd);

		switch(cmd)
		{
			case 1: stampa_coda(Q);
			break;

			case 2:
			{
				void *testa;

				if(testa = top(Q))
					printf("Testa della coda: %d\n", *((int *) testa));
				else
					printf("Testa della coda: NULL\n");
			}
			break;

			case 3:
			{
				if(is_empty(Q))
					printf("La coda è vuota.\n");
				else
					printf("La coda non è vuota.\n");
			}
			break;

			case 4:
			{
				int elem;

				printf("Inserisci elemento: \n");
				scanf("%d", &elem);
				if(Q->with_copy)
					Q = enqueue_copy(Q, &elem, copia_elemento);
				else
					Q = enqueue(Q, &elem);
			}
			break;

			case 5:
			{
				if(Q)
				{
					printf("Estrazione elemento...\n");
					if(Q->with_copy)
						Q = dequeue_destroy(Q, free);
					else
						Q = dequeue(Q);

					printf("Elemento estratto.\n");
				}
				else
					printf("La coda non esiste\n");
			}
			break;

			case 6:
			{
				int with_copy;

				if(Q)
					printf("La coda corrente non è vuota.\n");
				else
				{
					printf("Tipo coda da creare (!= 1 = senza copia; 1 = con copia)\n");
					scanf("%d", &with_copy);
					Q = new_queue(with_copy);
				}
			}
			break;

			case 7:
			{
				if(Q)
				{
					if(Q->with_copy)
						queue_destroy_copy(Q, free);
					else
						queue_destroy(Q);

					Q = NULL;
					printf("Coda distrutta.\n");
				}
				else
					printf("Coda non esistente.\n");
			}
			break;

			default: esci = 1;
		}

		printf("\n\n");

	}while(!esci);
	printf("bye bye!\n");

	return 0;
}

void stampa_coda(queue_t Q)
{
	int i;

	if(Q)
	{
		printf("Q: %p\n"
			   "Q->head: %p\n"
			   "Q->tail: %p\n", Q, Q->head, Q->tail);
		struct queue_node *head = Q->head;
		printf("with_copy: %d\n", Q->with_copy);
		for(i = 0; head != NULL; i++)
		{
			if(head->object)
				printf("%d: %d\n", i, *((int *) head->object));
			else
				printf("%d: NULL\n", i);
			head = head->next;
		}
	}
	else
		printf("La coda non esiste.\n");
}

void *copia_elemento(void *elem)
{
	int *intero = (int *) malloc(sizeof(int));
	if(intero)
		*intero = *((int *) elem);
}
