/**
  ******************************************************************************
  * @file   protocol.c
  * @author André Dantas
  * @brief	Implementation of the trixlog protocol
  *
 ******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "protocol.h"
#include "stm32f0xx_hal.h"

extern UART_HandleTypeDef huart2;
/* Private define ------------------------------------------------------------*/
#define TRIXLOG_PROTOCOL_BUFFER_SIZE 100
/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t StartPacket = 0x01;
uint8_t EndPacket = 0x04;
uint8_t TrixlogProtocolBuffer[TRIXLOG_PROTOCOL_BUFFER_SIZE];
uint8_t TrixlogProtocolMessageSize = 0;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void AddStartByte()
{
	TrixlogProtocolBuffer[0] = 0x01;
	TrixlogProtocolMessageSize++;
}

void AddEndByte()
{
	TrixlogProtocolBuffer[TrixlogProtocolMessageSize] = 0x04;
	TrixlogProtocolMessageSize++;
}

void AddFieldToBuffer(uint8_t* field, uint8_t fieldSize)//, uint8_t* buffer, uint8_t bufferSize; uint8_t* messageSize)
{
	uint8_t i = 0;
	uint8_t* buffer = &TrixlogProtocolBuffer[TrixlogProtocolMessageSize];

	for( i = 0; i < fieldSize; i++)
	{
		if( (field[i] == 0x01) || (field[i] == 0x04) )
		{
			*buffer = 0x10;
			buffer++;
			TrixlogProtocolMessageSize++;
			*buffer = field[i] + 0x20;
		}
		else{
			*buffer = field[i];
		}
		TrixlogProtocolMessageSize++;
		buffer++;

	}
}

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
 void SendMessage(CanRxMsgTypeDef* CanRxMsg)
 {
	 static uint16_t seq = 0;
	 uint16_t i = 0;
	 message_t message;

	 message.id = 0xFF;
	 message.version = 0x0000;
	 message.serial = 0x0001;
	 message.seq = seq;
	 message.type = 0x09;
	 message.subType = 0x80;
	 message.checksum = 0;

	 TrixlogProtocolMessageSize = 0;
	 memset(TrixlogProtocolBuffer,0,TRIXLOG_PROTOCOL_BUFFER_SIZE);

	 AddStartByte();
	 AddFieldToBuffer(&message.id, sizeof(message.id) );
	 AddFieldToBuffer(&message.version, sizeof(message.version));
	 AddFieldToBuffer((uint8_t *)&message.serial, sizeof(message.serial));
	 AddFieldToBuffer((uint8_t *)&message.seq, sizeof(message.seq));
	 AddFieldToBuffer(&message.type, sizeof(message.type));
	 AddFieldToBuffer(&message.subType, sizeof(message.subType));
	 AddFieldToBuffer((uint8_t *)&CanRxMsg->IDE, sizeof(uint32_t));
	 AddFieldToBuffer((uint8_t *)&CanRxMsg->DLC, sizeof(uint32_t));
	 AddFieldToBuffer((uint8_t *)&CanRxMsg->Data, CanRxMsg->DLC);

	 for(i = 0; i < TrixlogProtocolMessageSize; i++ )
	 {
		 message.checksum += TrixlogProtocolBuffer[i];
	 }
	 AddFieldToBuffer(&message.checksum, sizeof(message.checksum));
	 AddEndByte();
	 HAL_UART_Transmit(&huart2,TrixlogProtocolBuffer , TrixlogProtocolMessageSize,100);
	 seq++;

 }
