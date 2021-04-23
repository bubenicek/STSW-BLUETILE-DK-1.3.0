/**
  ******************************************************************************
  * @file    GPIO/IOToggle//BlueNRG1_it.h 
  * @author  MEMS Application Team
  * @version V1.3.0
  * @date    20-July-2020
  * @brief   This file contains the headers of the interrupt handlers.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2020 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef BlueNRG1_IT_H
#define BlueNRG1_IT_H

/* Includes ------------------------------------------------------------------*/
#include "BlueNRG_x_device.h"

/* Exported defines ------------------------------------------------------------*/
#define DMA_CH_UART_TX                  DMA_CH1
#define DMA_FLAG_TC_UART_TX               DMA_FLAG_TC1

#define DMA_IDLE        0
#define DMA_IN_PROGRESS 1

/* Exported constants --------------------------------------------------------*/
extern uint8_t command_in_progress;
extern uint8_t dma_state;

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void NMI_Handler(void);
void HardFault_Handler(void);
void SVC_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);


#endif /* BlueNRG1_IT_H */

/******************* (C) COPYRIGHT 2020 STMicroelectronics *****END OF FILE****/
