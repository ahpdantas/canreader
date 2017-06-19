/*
 * Queues.h
 *
 *  Created on: 24 de mai de 2016
 *      Author: andre
 */

#ifndef CANRXMSGQUEUE_H_
#define CANRXMSGQUEUE_H_

#include "main.h"
/* Exported typedefs ---------------------------------------------------------*/
typedef struct queue_def * Queue;
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
Queue CreateQueue(uint8_t maxSize);
uint8_t isEmpty(Queue q);
uint8_t isFull(Queue q);
uint8_t getQueueSize(Queue q);
int8_t enQueue(Queue q, CanRxMsgTypeDef *msg );
int8_t deQueue(Queue q, CanRxMsgTypeDef *msg);
void print(Queue q);
void destroy(Queue q);

#endif /* CANRXMSGQUEUE_H_ */
