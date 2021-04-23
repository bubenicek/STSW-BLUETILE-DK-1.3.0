/**
 ******************************************************************************
 * @file    BlueNRG1_it.c
 * @author  VMA RF Application Team
 * @version 1.3.0
 * @date    20-July-2020
 * @brief   Main Interrupt Service Routines.
 *          This file provides template for all exceptions handler and
 *          peripherals interrupt service routine.
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

/* Includes ------------------------------------------------------------------*/
#include "BlueNRG1_it.h"
#include "BlueNRG1_conf.h"
#include "SDK_EVAL_Com.h"
#include "sensor.h"

#include "clock.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#if ENABLE_DEBUG
#include <stdio.h>
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
volatile uint32_t SystemClockTick;

extern volatile uint8_t direction;
extern volatile int16_t cycle;
extern volatile int16_t cycle_R;
extern volatile int16_t cycle_G;
extern volatile int16_t cycle_B;

extern volatile uint16_t stepSpeed_R;
extern volatile uint16_t stepSpeed_G;
extern volatile uint16_t stepSpeed_B;

axis3bit16_t data_raw_acceleration;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
 * @brief  This function handles NMI exception.
 */
void NMI_Handler(void) {
}

/**
 * @brief  This function handles Hard Fault exception.
 */
void HardFault_Handler(void) {
	/* Go to infinite loop when Hard Fault exception occurs */
	while (1) {
	}
}

/**
 * @brief  This function handles SVCall exception.
 */
void SVC_Handler(void) {

}

/**
 * @brief  This function handles SysTick Handler.
 */
void SysTick_Handler(void) {
        int16_t r_cycle = cycle_R;
        int16_t r_step;
        int16_t g_cycle = cycle_G;
        int16_t g_step;
        int16_t b_cycle = cycle_B;
        int16_t b_step;
	SystemClockTick++;
	if (SystemClockTick >= 0xFFFFFFF0) {
		SystemClockTick = 0;
	}

	if ((SystemClockTick % 100) == 0) {
                 

		memset(data_raw_acceleration.u8bit, 0x00, 3 * sizeof(int16_t));
		lsm6dso_acceleration_raw_get(0, data_raw_acceleration.u8bit);

		if (direction == 0) {
			if (data_raw_acceleration.i16bit[0] > 0) {
				stepSpeed_R = (uint16_t)(LSM6DSO_FROM_FS_2g_TO_mg(data_raw_acceleration.i16bit[0]) / 10);
			} else {
				stepSpeed_R = - (uint16_t)(LSM6DSO_FROM_FS_2g_TO_mg(data_raw_acceleration.i16bit[0]) / 10);
			}

			if (data_raw_acceleration.i16bit[1] > 0) {
				stepSpeed_G = (uint16_t) (LSM6DSO_FROM_FS_2g_TO_mg(data_raw_acceleration.i16bit[1]) / 10);
			} else {
				stepSpeed_G = - (uint16_t) (LSM6DSO_FROM_FS_2g_TO_mg(data_raw_acceleration.i16bit[1]) / 10);
			}

			if (data_raw_acceleration.i16bit[2] > 0) {
				stepSpeed_B = (uint16_t) (LSM6DSO_FROM_FS_2g_TO_mg(data_raw_acceleration.i16bit[2]) / 10);
			} else {
				stepSpeed_B = - (uint16_t) (LSM6DSO_FROM_FS_2g_TO_mg(data_raw_acceleration.i16bit[2]) / 10);
			}
		}
                
               r_step = stepSpeed_R; 
               g_step = stepSpeed_G; 
               b_step = stepSpeed_B;

		if (direction == 0) {
                  
			r_cycle = r_cycle + r_step;
			g_cycle = g_cycle + g_step;         
			b_cycle = b_cycle + b_step;
                        
                        
			if ((r_cycle > 1000) || (g_cycle > 1000) || (b_cycle > 1000)) {
                                
				r_cycle -= stepSpeed_R;
				g_cycle -= stepSpeed_G;
				b_cycle -= stepSpeed_B;

				stepSpeed_R = r_cycle / 10 + 1;
				stepSpeed_G = g_cycle / 10 + 1;
				stepSpeed_B = b_cycle / 10 + 1;

				direction = 1;
			}
		} else if (direction == 1) {
			r_cycle -= stepSpeed_R;
			g_cycle -= stepSpeed_G;
			b_cycle -= stepSpeed_B;
			if ((r_cycle < 0) && (g_cycle < 0) & (b_cycle < 0)) {
				r_cycle = 0;
				g_cycle = 0;
				b_cycle = 0;
				direction = 0;
			} else {
				if ((r_cycle < 0))
					r_cycle = 0;
				if ((g_cycle < 0))
					g_cycle = 0;
				if ((b_cycle < 0))
					b_cycle = 0;
			}
		}
	}
        cycle_R = r_cycle;
        stepSpeed_R = r_step;
        cycle_G = g_cycle;
        stepSpeed_G = g_step;
        cycle_B = b_cycle;
        stepSpeed_B = b_step;

	if ((SystemClockTick % 400) == 0) {
		PRINTF("Red:%d%%, Green:%d%%, Blue:%d%%\n\r", r_cycle / 10, g_cycle / 10, b_cycle / 10);
	}

}

void GPIO_Handler(void) {

}

/******************************************************************************/
/*                 BlueNRG-1 Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (system_bluenrg1.c).                                               */
/******************************************************************************/
/**
 * @brief  This function handles UART interrupt request.
 * @param  None
 * @retval None
 */
void UART_Handler(void) {

}

void Blue_Handler(void) {

}

/******************* (C) COPYRIGHT 2020 STMicroelectronics *****END OF FILE****/
