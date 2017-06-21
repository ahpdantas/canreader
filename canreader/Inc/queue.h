/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef QUEUE_H_
#define QUEUE_H_

#include "main.h"
/* Exported typedefs ---------------------------------------------------------*/
typedef struct queue_def * Queue;
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
Queue CreateQueue(uint8_t maxSize);
uint8_t isEmpty(Queue q);
uint8_t isFull(Queue q);
uint8_t getQueueSize(Queue q);
int8_t enQueue(Queue q, void *value, uint8_t size );
int8_t deQueue(Queue q, void **value);
void destroy(Queue q);

#endif /* CANRXMSGQUEUE_H_ */
