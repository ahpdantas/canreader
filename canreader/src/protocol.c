/**
  ******************************************************************************
  * @file    protocol.c
  * @author  André Dantas
  * @brief
  *
 ******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "protocol.h"

/* UART handler declaration */
extern UART_HandleTypeDef UartHandle;

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
 void SendMessage(CanRxMsgTypeDef* CanRxMsg)
 {
	 HAL_UART_Transmit(&UartHandle, (uint8_t*)CanRxMsg, sizeof(CanRxMsgTypeDef),100);
	 HAL_UART_Transmit(&UartHandle, (uint8_t*)"\n", strlen("\n"),100);
 }
