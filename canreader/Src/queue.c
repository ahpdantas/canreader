/*
 * Queues.c
 *
 *  Created on: 24 de mai de 2016
 *      Author: andre
 */
#include <stdlib.h>
#include <stdio.h>
#include "main.h"
#include "queue.h"

typedef struct cell_def *Cell;
struct cell_def
{
	void *value;
	Cell next;
};


struct queue_def
{
	Cell front;
	Cell end;
	uint8_t size;
	uint8_t maxSize;
};

Queue CreateQueue(uint8_t maxSize)
{
	Queue q = malloc(sizeof(struct queue_def));
	q->front = malloc(sizeof(struct cell_def));
	q->end = q->front;
	q->front->next = NULL;
	q->size = 0;
	q->maxSize = maxSize;
}
uint8_t isEmpty(Queue q)
{
	return (q->size == 0);
}

uint8_t isFull(Queue q)
{
	return (q->size == q->maxSize);
}

uint8_t getQueueSize(Queue q)
{
	return q->size;
}

int8_t enQueue(Queue q, void *value, uint8_t size )
{
	if( q->size == q->maxSize )
	{
		return -1;
	}

	q->end->next = malloc(sizeof(struct cell_def));
	q->end->next->value = malloc(size);

	q->end = q->end->next;
	memcpy(q->end->value, value, size);
	q->end->next = NULL;
	q->size = q->size + 1;
}

int8_t deQueue(Queue q, void **value)
{
	if(isEmpty(q))
	{
		return -1;
	}
	else
	{
		Cell d;

		d = q->front->next;
		q->front->next = d->next;
		if(d != NULL)
		{
			if( value != NULL )
			{
				*value = d->value;
			}
			free(d);
		}
		if( q->size )
		{
			q->size--;
			if( q->size == 0)
			{
				q->end = q->front;
			}
		}
		return 0;
	}
}

void destroy(Queue q)
{
	if( q  != NULL )
	{
		while( isEmpty(q) )
		{
			deQueue(q,NULL);
		}
		free(q->front);
		free(q);
	}
}
