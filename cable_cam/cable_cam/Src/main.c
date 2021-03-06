/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
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
#include "stm32f4xx_hal.h"
#include "adc.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include "NRF24L01.h"
#include "stdio.h"
#include "string.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
 uint32_t adcValue = 0;
 uint8_t rx_data[10];
 uint8_t NRF24L01_Status;
 sRX controlStruct;
 uTelemetry utelemetry;
 sTelemetry telemetryStruct;

 uint8_t printBuffer[64];
 uint8_t n;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
void parseRXMessages(uint8_t *rxBuffer, sRX *rxData);
void wallDetection(sRX *control,sTelemetry *telemetry);
/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_TIM1_Init();
  MX_TIM3_Init();
  MX_USART2_UART_Init();
  MX_TIM11_Init();
  MX_TIM4_Init();
  MX_SPI3_Init();
  MX_TIM2_Init();
  MX_TIM10_Init();
  MX_TIM5_Init();

  /* USER CODE BEGIN 2 */
  HAL_TIM_Encoder_Start(&htim3,TIM3);
  HAL_TIM_PWM_Start (&htim1, TIM1);
  HAL_TIM_PWM_Start (&htim2, TIM2);
  HAL_TIM_PWM_Start (&htim10, TIM10);
  HAL_ADC_Start(&hadc1);
  HAL_TIM_Base_Start_IT(&htim4);
  HAL_TIM_Base_Start_IT(&htim5);
  HAL_TIM_Base_Start_IT(&htim11);

  NRF24l01_Initialization(&hspi3,PRX);
  NRF24L01_Status= NRF24L01_Read_Status(&hspi3);
  NRF24L01_Clear_RX_DR(&hspi3,NRF24L01_Status);
  NRF24L01_Flush(&hspi3,RX);
//  HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {
//	  n = sprintf(printBuffer,"a\n\r");
//	  HAL_UART_Transmit(&huart2,printBuffer,n,1000);
	  adcValue = TIM3->CNT;
//      adcValue = HAL_ADC_GetValue(&hadc1);
//      TIM_PWM_SetPulse(&htim1,000);
//	  n = sprintf(printBuffer,"%d, %d\n\r",utelemetry.telemetry.distanceFront,utelemetry.telemetry.distanceBack);
//	  HAL_UART_Transmit(&huart2,printBuffer,n,1000);
//	  memcpy(rx_data,"{|}",3);
//	  parseRXMessages(rx_data,&controlStruct);
//	  wallDetection(&controlStruct,&telemetryStruct);
	  TIM_PWM_SetPulse(&htim1,(controlStruct.torque*50)+2500);
      if (controlStruct.requestTelem == 1)
      {
    	  HAL_GPIO_TogglePin(GPIOA, LD2_Pin);
    	  NRF24L01_Mode(&hspi3,PTX);
    	  HAL_Delay(10);
    	  NRF24L01_Transmit(&hspi3,0x385338,utelemetry.aTelemetry,9,TRUE);
		  clear_flag_IRQ();
    	  NRF24L01_Mode(&hspi3,PRX);
    	  controlStruct.requestTelem = 0;
    	  n = sprintf(printBuffer,"value sent\n\r");
    	  HAL_UART_Transmit(&huart2,printBuffer,n,1000);
      }
	  if(get_flag_IRQ()||((HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_7)==GPIO_PIN_RESET))){
		  __HAL_TIM_SetCounter(&htim5, 0);//reset keepalive counter
		  NRF24L01_Status= NRF24L01_Read_Status(&hspi3);
		  //printf("IRQ\r");
		  if((NRF24L01_Status >> 1)==1){
			  NRF24L01_Flush(&hspi3,RX);
		  }
		  if(NRF24L01_Status & (1<<RX_DR)){
			  rx_data[0]=NRF24L01_Read_Data_Pipe_Number(&hspi3,NRF24L01_Status);
			  NRF24L01_Read_RX_Payload(&hspi3,rx_data,RX_PIPE_1_PAYLOAD);
			  HAL_UART_Transmit(&huart2,rx_data,3,1000);			  
			  parseRXMessages(rx_data,&controlStruct);
			  NRF24L01_Clear_RX_DR(&hspi3,NRF24L01_Status);
//			  HAL_GPIO_TogglePin(GPIOA, LD2_Pin);
		  }
		  if(NRF24L01_Status & (1<<TX_DS)){
			  NRF24L01_Flush(&hspi3,TX);
			  NRF24L01_Clear_TX_DS(&hspi3,NRF24L01_Status);
		  }
		  if(NRF24L01_Status & (1<<MAX_RT)){
			  NRF24L01_Flush(&hspi3,TX);
			  NRF24L01_Clear_MAX_RT(&hspi3,NRF24L01_Status);
		  }
		  clear_flag_IRQ();
	  }
     // HAL_Delay(20);
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
//	  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
  }






  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  __PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */
void parseRXMessages(uint8_t *rxBuffer, sRX *rxData)
{
	__HAL_TIM_SetCounter(&htim5, 0);//reset keepalive counter

	char *torqueHeader = "{|";
	char *commandHeader = "}~";

	if (!(memcmp(torqueHeader,rxBuffer,2)))
	{
		rxData->torque = rxBuffer[2];
	}
	else if (!(memcmp(commandHeader,rxBuffer,2)))
	{
		switch ( rxBuffer[2] )
		{
			case 'A':
				rxData->emergencyStop = 1;
			  break;
			case 'K':
				rxData->keepAlive = 1;
			  break;
			case 'T':
				rxData->requestTelem = 1;
			  break;
			default:
		    	  n = sprintf(printBuffer,"invalid rxData\n\r");
		    	  HAL_UART_Transmit(&huart2,printBuffer,n,1000);
			  break;
		}
	}
}

void wallDetection(sRX *control,sTelemetry *telemetry)
{
	if (telemetry->distanceFront <100)
	{
		control->torque = (float)control->torque/100*telemetry->distanceFront;
	}
	else if (telemetry->distanceBack <100)
	{
		control->torque = (float)control->torque/100*telemetry->distanceBack;
	}
}
/* USER CODE END 4 */

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
