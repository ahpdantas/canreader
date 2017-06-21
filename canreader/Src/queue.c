/**
  ******************************************************************************
  * @file   queue.c
  * @author André Dantas
  * @brief	Implementation of queue data type using Abstract Data Type pattern
  *
 ******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "queue.h"

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
typedef struct cell_def *Cell;
/* Cell definition*/
struct cell_def
{
	void *value;
	Cell next;
};

/* Queue definition*/
struct queue_def
{
	Cell front;
	Cell end;
	uint8_t size;
	uint8_t maxSize;
};

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
* @brief  Creates a Queue
* @param[in] 	maxSize 	the max size of the queue
* @retval 		Queue		pointer to the queue structure
*/
Queue CreateQueue(uint8_t maxSize)
{
	Queue q = malloc(sizeof(struct queue_def));
	q->front = malloc(sizeof(struct cell_def));
	q->end = q->front;
	q->front->next = NULL;
	q->size = 0;
	q->maxSize = maxSize;

	return q;
}

/**
* @brief  Test if the queue is empty
* @param[in] 	q	Queue to be tested
* @retval 		1 if queue is empty or 0 if the queue isn't empty
*/
uint8_t isEmpty(Queue q)
{
	return (q->size == 0);
}

/**
* @brief  Test if the queue is full
* @param[in] 	q	Queue to be tested
* @retval 		1 if queue is full or 0 if the queue isn't full
*/
uint8_t isFull(Queue q)
{
	return (q->size == q->maxSize);
}

/**
* @brief  Get Queue size
* @param[in] 	q	Queue to be tested
* @retval 		size of the queue
*/
uint8_t getQueueSize(Queue q)
{
	return q->size;
}

/**
* @brief  add an element in the queue q
* @param[in] 	q			Queue
* @param[in] 	element		element to add in the queue
* @param[in] 	size		size of the element
* @retval 		0 element was added to the queue
* @retval 		-1 error
*/
int8_t enQueue(Queue q, void *element, uint8_t size )
{
	if( q->size == q->maxSize )
	{
		return -1;
	}

	q->end->next = malloc(sizeof(struct cell_def));
	q->end->next->value = malloc(size);

	q->end = q->end->next;
	memcpy(q->end->value, element, size);
	q->end->next = NULL;
	q->size = q->size + 1;

	return 0;
}

/**
* @brief  gets an element in the queue q
* @param[in] 	q			Queue
* @param[in] 	element		pointer to the element
* @retval 		0 element was retrivied from the queue
* @retval 		-1 error
*/
int8_t deQueue(Queue q, void **element)
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
			if( element != NULL )
			{
				*element = d->value;
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

/**
* @brief  Destroy the queue q
* @retval 	none
*/
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
