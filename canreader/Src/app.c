/**
  ******************************************************************************
  * @file    main.c
  * @author  André Dantas
  * @brief
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "app.h"
#include "queue.h"
#include "protocol.h"



/* Private typedef -----------------------------------------------------------*/
typedef enum {
	SAVE_CAN_BUS_DATA_FIFO_0,
	SAVE_CAN_BUS_DATA_FIFO_1,
	WAIT_FREE_FIFO
}SaveStates_t;

typedef enum {
	NO_DATA_TO_SEND,
	SEND_CAN_BUS_DATA_FIFO_0,
	SEND_CAN_BUS_DATA_FIFO_1
}SendStates_t;

/* Private define ------------------------------------------------------------*/
#define CAN_RX_MSG_QUEUE_SIZE 10
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Machine State of the application */
SaveStates_t saveState = SAVE_CAN_BUS_DATA_FIFO_0;
SendStates_t sendState = NO_DATA_TO_SEND;
/* FIFO Queues for data received in CAN Bus */
static Queue RxFIFO0;
static Queue RxFIFO1;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Application Machine State Handler
  * @param  None
  * @retval None
  */
void SaveStateMachineHandler(CanRxMsgTypeDef* CanRx)
{

	switch(saveState)
	{

	case SAVE_CAN_BUS_DATA_FIFO_0:
			if( enQueue(RxFIFO0, CanRx, sizeof(CanRxMsgTypeDef) ) == -1 ){
				if( isEmpty(RxFIFO1) )
				{
					saveState = SAVE_CAN_BUS_DATA_FIFO_1;
				}
				else{
					saveState = WAIT_FREE_FIFO;
				}
			}

		break;
	case SAVE_CAN_BUS_DATA_FIFO_1:
		if( enQueue(RxFIFO1, CanRx, sizeof(CanRxMsgTypeDef) ) == -1 ){
			if( isEmpty(RxFIFO0) )
			{
				saveState = SAVE_CAN_BUS_DATA_FIFO_0;
			}
			else{
				saveState = WAIT_FREE_FIFO;
			}
		}

		break;
	case WAIT_FREE_FIFO:
		if( isEmpty(RxFIFO0) )
		{
			saveState = SAVE_CAN_BUS_DATA_FIFO_0;
		} else if( isEmpty(RxFIFO1))
		{
			saveState = SAVE_CAN_BUS_DATA_FIFO_1;
		}
		break;
	}

}

/**
  * @brief  Send Machine State Handler
  * @param  None
  * @retval None
  */
void SendStateMachineHandler(void)
{
	CanRxMsgTypeDef* RxMsg = NULL;
	switch(sendState)
	{
	case NO_DATA_TO_SEND:
		if( isFull(RxFIFO0) )
		{
			sendState = SEND_CAN_BUS_DATA_FIFO_0;
		} else if( isFull(RxFIFO1))
		{
			sendState = SEND_CAN_BUS_DATA_FIFO_1;
		}
		break;
	case SEND_CAN_BUS_DATA_FIFO_0:
		if( !isEmpty(RxFIFO0) )
		{
			if( deQueue(RxFIFO0, &RxMsg) == 0 )
			{
				SendMessage(RxMsg);
				free(RxMsg);
			}

		} else {
			sendState = NO_DATA_TO_SEND;
		}

		break;
	case SEND_CAN_BUS_DATA_FIFO_1:
		if( !isEmpty(RxFIFO1) )
		{
			if( deQueue(RxFIFO1, &RxMsg) == 0 )
			{
				SendMessage(RxMsg);
				free(RxMsg);
			}
		} else {
			sendState = NO_DATA_TO_SEND;
		}

		break;
	}
}

/**
  * @brief  Init global variables of Application
  * @param  None
  * @retval None
  */
void AppInit(void)
{
	RxFIFO0 = CreateQueue(CAN_RX_MSG_QUEUE_SIZE);
	RxFIFO1 = CreateQueue(CAN_RX_MSG_QUEUE_SIZE);
}

/**
  * @brief  Application Machine State Handler
  * @param  None
  * @retval None
  */
void AppStateMachineHandler(CanRxMsgTypeDef* CanRx)
{
	SaveStateMachineHandler(CanRx);
	SendStateMachineHandler();
}


