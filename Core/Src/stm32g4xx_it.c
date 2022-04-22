/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32g4xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32g4xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "arm_math.h"
#include "app_foc.h"
#include "app_input.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern DMA_HandleTypeDef hdma_adc1;
extern TIM_HandleTypeDef htim2;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */
  get_key(&g_key);
  get_pulley(&g_pulley);
  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32G4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32g4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles DMA1 channel1 global interrupt.
  */
void DMA1_Channel1_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel1_IRQn 0 */

  /* USER CODE END DMA1_Channel1_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_adc1);
  /* USER CODE BEGIN DMA1_Channel1_IRQn 1 */

  /* USER CODE END DMA1_Channel1_IRQn 1 */
}

/**
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */
  static float temp=0;
  static int sec; //扇区
  static triphase_typedef current_buff[6];
  static triphase_typedef current_last;

  g_foc_cnt ++;
  if(g_foc_cnt%25 == 0)
  {
	 g_ano_flag = 1;
  }

/*�?单高频注入程�?*/
//  sec = (sec+1)%6;
//  current_buff[sec] = np1.feedback.current;
//  np1.output_pwm.A = 4000+2000*arm_cos_f32(temp+PHASE_A)+1000.0*arm_cos_f32(PI*((float)sec+0)/3.0);
//  np1.output_pwm.B = 4000+2000*arm_cos_f32(temp+PHASE_B)+1000.0*arm_cos_f32(PI*((float)sec+2)/3.0);
//  np1.output_pwm.C = 4000+2000*arm_cos_f32(temp+PHASE_C)+1000.0*arm_cos_f32(PI*((float)sec+4)/3.0);
//  switch (sec)
//  {
//  case 0:
//    np1.expect_current.B = np1.expect_current.B + ((current_buff[0].B - current_buff[3].B) - np1.expect_current.B)/16;
//    break;
//  case 1:
//    np1.expect_current.C = np1.expect_current.C + ((current_buff[4].C - current_buff[1].C) - np1.expect_current.C)/16;
//    break;
//  case 2:
//    np1.expect_current.A = np1.expect_current.A + ((current_buff[2].A - current_buff[5].A) - np1.expect_current.A)/16;
//    break;
//  case 3:
//    np1.expect_current.B = np1.expect_current.B + ((current_buff[0].B - current_buff[3].B) - np1.expect_current.B)/16;
//    break;
//  case 4:
//    np1.expect_current.C = np1.expect_current.C + ((current_buff[4].C - current_buff[1].C) - np1.expect_current.C)/16;
//    break;
//  case 5:
//    np1.expect_current.A = np1.expect_current.A + ((current_buff[2].A - current_buff[5].A) - np1.expect_current.A)/16;
//    break;
//  default:
//    break;
//  }
//  foc_control(OPEN_LOOP, (np2.feedback.encoder_cnt%4096)/4096.0*6.28, &np1);
//  foc_control(OPEN_LOOP, (np1.feedback.encoder_cnt%4096)/4096.0*6.2832, &np2);
  get_feedback(g_adc_buff, &np1.feedback, &np2.feedback);
  foc_control(ANGLE_MODE, np1.feedback.motion_state.angle, &np2);
//#define V 400
//#define P 1500
//  np2.output_pwm.A = 4000 + V*arm_cos_f32((g_foc_cnt%P)*2*PI/P + PHASE_A);
//  np2.output_pwm.B = 4000 + V*arm_cos_f32((g_foc_cnt%P)*2*PI/P + PHASE_B);
//  np2.output_pwm.C = 4000 + V*arm_cos_f32((g_foc_cnt%P)*2*PI/P + PHASE_C);
  pwm_output(np1.output_pwm,  np2.output_pwm);
  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */

  /* USER CODE END TIM2_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
