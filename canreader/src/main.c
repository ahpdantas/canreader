/**
  ******************************************************************************
  * @file    main.c
  * @author  André Dantas
  * @brief   This sample code shows how to use CAN HAL API to transmit
  *          and receive a data buffer with a communication process based on
  *          polling transfer.
    ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "protocol.h"
#include "CanRxMsgQueue.h"
/* Private typedef -----------------------------------------------------------*/
typedef enum {
	INIT_FIFO_QUEUES,
	SAVE_CAN_BUS_DATA_FIFO_0,
	SAVE_CAN_BUS_DATA_FIFO_1,
	WAIT_FREE_FIFO
}saveStates_t;

typedef enum {
	NO_DATA_TO_SEND,
	SEND_CAN_BUS_DATA_FIFO_0,
	SEND_CAN_BUS_DATA_FIFO_1
}sendStates_t;

/* Private define ------------------------------------------------------------*/
#define CAN_RX_MSG_QUEUE_SIZE 10
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Machine State of the application */
saveStates_t saveState = INIT_FIFO_QUEUES;
sendStates_t sendState = NO_DATA_TO_SEND;
/* UART handler declaration */
UART_HandleTypeDef UartHandle;
/* CAN handler declaration */
CAN_HandleTypeDef CanHandle;
/* CAN Messages */
CanTxMsgTypeDef        CAN_TxMessage;
CanRxMsgTypeDef        CAN_RxMessage;
/* CAN RX FIFO Queues */
Queue RxFIFO0;
Queue RxFIFO1;

/* Welcome Message */
int8_t WelcomeMessage[] = "Trixlog CanReader Application\n";

/* Buffer used for transmission */
uint8_t TxBuffer[TXBUFFERSIZE];
uint8_t RxBuffer[RXBUFFERSIZE];
/* Buffer used for reception */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  while (1)
  {
  }
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSI)
  *            SYSCLK(Hz)                     = 48000000
  *            HCLK(Hz)                       = 48000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            HSI Frequency(Hz)              = 8000000
  *            PREDIV                         = 1
  *            PLLMUL                         = 6
  *            Flash Latency(WS)              = 1
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* No HSE Oscillator on Nucleo, Activate PLL with HSI as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_NONE;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct)!= HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1)!= HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }
}

/**
  * @brief  Init virtual UART configuration
  * @param  None
  * @retval None
  */
void UART_Config(void)
{
	 /*##-1- Configure the UART peripheral ######################################*/
	  /* Put the USART peripheral in the Asynchronous mode (UART Mode) */
	  /* UART configured as follows:
	      - Word Length = 8 Bits
	      - Stop Bit = One Stop bit
	      - Parity = None
	      - BaudRate = 9600 baud
	      - Hardware flow control disabled (RTS and CTS signals) */
	  UartHandle.Instance        = USARTx;

	  UartHandle.Init.BaudRate     = 115200;
	  UartHandle.Init.WordLength   = UART_WORDLENGTH_8B;
	  UartHandle.Init.StopBits     = UART_STOPBITS_1;
	  UartHandle.Init.Parity       = UART_PARITY_NONE;
	  UartHandle.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
	  UartHandle.Init.Mode         = UART_MODE_TX_RX;

	  HAL_UART_Init(&UartHandle);

}

/**
  * @brief  Configures the CAN.
  * @param  None
  * @retval None
  */
static void CAN_Config(void)
{
  CAN_FilterConfTypeDef  sFilterConfig;
  uint32_t CAN_ErrorCode = 0;

  /*##-1- Configure the CAN peripheral #######################################*/
  CanHandle.Instance = CANx;
  CanHandle.pTxMsg = &CAN_TxMessage;
  CanHandle.pRxMsg = &CAN_RxMessage;

  CanHandle.Init.TTCM = DISABLE;
  CanHandle.Init.ABOM = DISABLE;
  CanHandle.Init.AWUM = DISABLE;
  CanHandle.Init.NART = DISABLE;
  CanHandle.Init.RFLM = DISABLE;
  CanHandle.Init.TXFP = DISABLE;
  CanHandle.Init.Mode = CAN_MODE_LOOPBACK;
  CanHandle.Init.SJW = CAN_SJW_1TQ;
  CanHandle.Init.BS1 = CAN_BS1_5TQ;
  CanHandle.Init.BS2 = CAN_BS2_6TQ;
  CanHandle.Init.Prescaler = 4;

  if (HAL_CAN_Init(&CanHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }

  /*##-2- Configure the CAN Filter ###########################################*/
  sFilterConfig.FilterNumber = 0;
  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
  sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
  sFilterConfig.FilterIdHigh = 0x0000;
  sFilterConfig.FilterIdLow = 0x0000;
  sFilterConfig.FilterMaskIdHigh = 0x0000;
  sFilterConfig.FilterMaskIdLow = 0x0000;
  sFilterConfig.FilterFIFOAssignment = 0;
  sFilterConfig.FilterActivation = ENABLE;
  sFilterConfig.BankNumber = 14;

  if (HAL_CAN_ConfigFilter(&CanHandle, &sFilterConfig) != HAL_OK)
  {
    /* Filter configuration Error */
    Error_Handler();
  }

  /*##-3- Configure Transmission process #####################################*/
  CanHandle.pTxMsg->StdId = 0x321;
  CanHandle.pTxMsg->ExtId = 0x01;
  CanHandle.pTxMsg->RTR = CAN_RTR_DATA;
  CanHandle.pTxMsg->IDE = CAN_ID_STD;
}

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
void SaveCanBusDataHandler(void)
{
	switch(saveState)
	{
	case INIT_FIFO_QUEUES:
		RxFIFO0 = CreateQueue(CAN_RX_MSG_QUEUE_SIZE);
		RxFIFO1 = CreateQueue(CAN_RX_MSG_QUEUE_SIZE);
		saveState = SAVE_CAN_BUS_DATA_FIFO_0;
		break;
	case SAVE_CAN_BUS_DATA_FIFO_0:
		if( HAL_CAN_Receive(&CanHandle, CAN_FIFO0,1) == HAL_OK )
		{
			if( enQueue(RxFIFO0, CanHandle.pRxMsg ) == -1 ){
				if( isEmpty(RxFIFO1) )
				{
					saveState = SAVE_CAN_BUS_DATA_FIFO_1;
				}
				else{
					saveState = WAIT_FREE_FIFO;
				}
			}
		}
		break;
	case SAVE_CAN_BUS_DATA_FIFO_1:
		if( HAL_CAN_Receive(&CanHandle, CAN_FIFO0,1) == HAL_OK )
		{
			if( enQueue(RxFIFO1, CanHandle.pRxMsg ) == -1 ){
				if( isEmpty(RxFIFO0) )
				{
					saveState = SAVE_CAN_BUS_DATA_FIFO_1;
				}
				else{
					saveState = WAIT_FREE_FIFO;
				}
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
  * @brief  Main program
  * @param  None
  * @retval None
  */
void SendCanBusDataHandler(void)
{
	CanRxMsgTypeDef RxMsg;

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
				SendMessage(&RxMsg);
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
				SendMessage(&RxMsg);
			}
		} else {
			sendState = NO_DATA_TO_SEND;
		}

		break;
	}
}

void SendCanBusDummyData()
{
	static uint8_t strToSend = 0;
	uint8_t HelloStr[] = "Hellooo";
	uint8_t TrixlogStr[] = "Trixlog";
	if( strToSend == 0 )
	{
		CanHandle.pTxMsg->DLC = strlen(HelloStr);
		memcpy(CanHandle.pTxMsg->Data, HelloStr, CanHandle.pTxMsg->DLC);
	}
	else{
		CanHandle.pTxMsg->DLC =  strlen(TrixlogStr);
		memcpy(CanHandle.pTxMsg->Data, TrixlogStr, CanHandle.pTxMsg->DLC);
	}

	strToSend^=1;

	if(HAL_CAN_Transmit(&CanHandle,1000) != HAL_OK)
	{
		Error_Handler();
	}
}

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{

	HAL_Init();

	/* Configure the system clock to 48 MHz */
	SystemClock_Config();

	/* Configure LED3 */
	BSP_LED_Init(LED3);

	UART_Config();
	CAN_Config();

	HAL_UART_Transmit(&UartHandle, (uint8_t*)WelcomeMessage, strlen(WelcomeMessage), 5000);

	while(1){
		SendCanBusDummyData();
		SaveCanBusDataHandler();
		SendCanBusDataHandler();
		BSP_LED_Toggle(LED3);
		HAL_Delay(500);
	}
}


