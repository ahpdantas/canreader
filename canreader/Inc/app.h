/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef APP_H_
#define APP_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void AppInit(void);
void AppStateMachineHandler(CanRxMsgTypeDef* CanRx);

#endif /* APP_H_ */
