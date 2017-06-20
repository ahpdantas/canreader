/*
 * protocol.h
 *
 *  Created on: 19 de jun de 2017
 *      Author: andre
 */

#ifndef PROTOCOL_H_
#define PROTOCOL_H_
/* Exported constants --------------------------------------------------------*/
#define DATA_SIZE 100
/* Exported types ------------------------------------------------------------*/
typedef struct{
	uint8_t buffer[DATA_SIZE];
	uint8_t size;
}data_t;

typedef struct {
	uint8_t id;
	uint8_t version;
	uint16_t serial;
	uint16_t seq;
	uint8_t type;
	uint8_t subType;
	uint8_t checksum;
}message_t;
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void SendMessage(CanRxMsgTypeDef* CanRxMsg);
#endif /* PROTOCOL_H_ */
