/**
  ******************************************************************************
  * File Name          : TIM.c
  * Description        : This file provides code for the configuration
  *                      of the TIM instances.
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 STMicroelectronics
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
#include "tim.h"

/* USER CODE BEGIN 0 */
static uint8_t flag_tim9_it;
static uint16_t keepalive_counter;
/* USER CODE END 0 */

TIM_HandleTypeDef htim9;

/* TIM9 init function */
void MX_TIM9_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig;

  htim9.Instance = TIM9;
  htim9.Init.Prescaler = 1;
  htim9.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim9.Init.Period = 42000;
  htim9.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  HAL_TIM_Base_Init(&htim9);

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  HAL_TIM_ConfigClockSource(&htim9, &sClockSourceConfig);

}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base)
{

  if(htim_base->Instance==TIM9)
  {
  /* USER CODE BEGIN TIM9_MspInit 0 */

  /* USER CODE END TIM9_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_TIM9_CLK_ENABLE();

    /* Peripheral interrupt init */
    HAL_NVIC_SetPriority(TIM1_BRK_TIM9_IRQn, 0, 4);
    HAL_NVIC_EnableIRQ(TIM1_BRK_TIM9_IRQn);
  /* USER CODE BEGIN TIM9_MspInit 1 */

  /* USER CODE END TIM9_MspInit 1 */
  }
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* htim_base)
{

  if(htim_base->Instance==TIM9)
  {
  /* USER CODE BEGIN TIM9_MspDeInit 0 */

  /* USER CODE END TIM9_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM9_CLK_DISABLE();

    /* Peripheral interrupt Deinit*/
    HAL_NVIC_DisableIRQ(TIM1_BRK_TIM9_IRQn);

  }
  /* USER CODE BEGIN TIM9_MspDeInit 1 */

  /* USER CODE END TIM9_MspDeInit 1 */
} 

/* USER CODE BEGIN 1 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	static uint16_t i;

	if(i< STATUS_DELAY) i++;

	//if(i==DELAY) {
	else{
		flag_tim9_it = FLAG_STATUS;
		i=0;
	}

	if(keepalive_counter < COMM_TIMEOUT) keepalive_counter++;
	else{
		flag_tim9_it = FLAG_COMM;
		keepalive_counter=0;
	}
}

uint8_t get_tim9_flag(){
	return flag_tim9_it;
}

void clear_tim9_flag(uint8_t flag){
	switch(flag){
	case(FLAG_STATUS): flag_tim9_it = 0;
	break;
	case(FLAG_COMM): flag_tim9_it = 0;
	break;
	default:
		flag_tim9_it = 0;
		flag_tim9_it = 0;
	break;
	}
}
void clear_keepalive_counter(){
	keepalive_counter = 0;
}
/* USER CODE END 1 */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
