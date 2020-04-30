/**
  ******************************************************************************
  * @file    system_stm32f10x.h
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    06/19/2009
  * @brief   CMSIS Cortex-M3 Device Peripheral Access Layer System Header File.
  ******************************************************************************  
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  ******************************************************************************
  */


#ifndef __SYSTEM_STM32F10X_H
#define __SYSTEM_STM32F10X_H

#ifdef __cplusplus
 extern "C" {
#endif 

extern const uint32_t SystemFrequency;          /*!< System Clock Frequency (Core Clock) */
extern const uint32_t SystemFrequency_SysClk;   /*!< System clock                        */
extern const uint32_t SystemFrequency_AHBClk;   /*!< AHB System bus speed                */
extern const uint32_t SystemFrequency_APB1Clk;  /*!< APB Peripheral Bus 1 (low)  speed   */
extern const uint32_t SystemFrequency_APB2Clk;  /*!< APB Peripheral Bus 2 (high) speed   */

extern void SystemInit(void);

#ifdef __cplusplus
}
#endif

#endif /*__SYSTEM_STM32F10X_H */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
