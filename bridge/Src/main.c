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
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include "NRF24L01.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
	//uint8_t rx_data[3];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
#define UART1_BUFFER_SIZE 3
/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */
	//uint8_t tx_data[32];
	uint8_t rx_data[3];
	//extern uint8_t rx_data[3];
	//uint8_t erreur[8] = {' ','=',' ','E','C','H','E','C'};

	// STM32F091 (DEBUG a L'appart)
	//uint64_t cable_cam_add = 0x010203;

	// Bridge
	uint64_t cable_cam_add = 0x515151;
	uint8_t NRF24L01_Status;
	//uint8_t size_uart1 = 3;
  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI3_Init();
  MX_TIM9_Init();
  MX_USART2_UART_Init();
  MX_USART1_UART_Init();

  /* USER CODE BEGIN 2 */
  // Bridge
  NRF24l01_Initialization(&hspi3,PTX);

  // Cable Cam
  //NRF24l01_Initialization(&hspi3,PRX);

  HAL_TIM_Base_Start_IT(&htim9);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  //HAL_UART_Transmit_IT(&huart2,tx_data,3);

  // Bridge
  // DEBUG
  //rx_data[0] = 'O';
  //rx_data[1] = 'K';
  //rx_data[2] = ' ';
  // FIN DEBUG
  //NRF24L01_Transmit(&hspi3,cable_cam_add,rx_data,RX_PIPE_1_PAYLOAD,TRUE); // DEBUG
  HAL_UART_Receive_IT(&huart2,rx_data,1);   // PUTTY DEBUG
  HAL_UART_Receive_IT(&huart1,rx_data,UART1_BUFFER_SIZE);	// Bluetooth
  //HAL_UART_Receive_IT(&huart1,rx_data,2);

  while (1)
  {
	  if(get_tim9_flag() == FLAG_STATUS){
		  HAL_GPIO_TogglePin(LD2_GPIO_Port,LD2_Pin);
		  //HAL_UART_Transmit_IT(&huart2,rx_data,RX_PIPE_1_PAYLOAD);
		  //NRF24L01_Transmit(&hspi3,cable_cam_add,rx_data,RX_PIPE_1_PAYLOAD,TRUE);
		  clear_tim9_flag(FLAG_STATUS);
	  }

	  // Si aucun message n'a ete envoye pendant les 300 dernieres ms
	  if(get_tim9_flag() == FLAG_COMM){
		  HAL_GPIO_TogglePin(LD2_GPIO_Port,LD2_Pin);
		  rx_data[0]='}';
		  rx_data[1]='~';
		  rx_data[2]='K';
		  NRF24L01_Transmit(&hspi3,cable_cam_add,rx_data,RX_PIPE_1_PAYLOAD,TRUE);
		  clear_tim9_flag(FLAG_COMM);
	  }

	  // DEBUG
	  /* Si un caractere est recu en provenance du terminal */
	  if(get_uart_flag(2)){
		  // DEBUG
		  if((rx_data[0]=='\n')||(rx_data[0]=='\r')) {
			  rx_data[0]='\n';
			  rx_data[1]='\r';
			  HAL_UART_Transmit_IT(&huart2,rx_data,2);
			  //NRF24L01_Transmit(&hspi3,cable_cam_add,&rx_data[0],1,TRUE);
			  //NRF24L01_Transmit(&hspi3,cable_cam_add,&rx_data[1],1,TRUE);
		  }
		  else {
			  HAL_UART_Transmit_IT(&huart2,rx_data,1);
			  //NRF24L01_Transmit(&hspi3,cable_cam_add,rx_data,1,TRUE);
		  }
		  clear_uart_flag(2);
		  HAL_UART_Receive_IT(&huart2,rx_data,1);
	  }// FIN DEBUG

	  if(get_uart_flag(1)){
		  read_buffer(rx_data,3);
		  //HAL_Delay(10);
		  HAL_UART_Transmit_IT(&huart2,rx_data,UART1_BUFFER_SIZE);  // Envoi sur la console
		  NRF24L01_Transmit(&hspi3,cable_cam_add,rx_data,RX_PIPE_1_PAYLOAD,TRUE);
		  clear_uart_flag(1);
		  //HAL_UART_Receive_IT(&huart1,rx_data,size_uart1);
	  }

	  if(get_uart_error_flag(1)){
		  //__HAL_UART_CLEAR_OREFLAG(&huart1);
		  HAL_UART_Transmit_IT(&huart2,"ERROR",5);
		  HAL_UART_Receive(&huart1,rx_data,1,100);
		  clear_uart_error_flag(1);
	  }

	  // NRF24L01
	  if(get_IRQ_flag()){
		  NRF24L01_Status = NRF24L01_Read_Status(&hspi3);
		  if(NRF24L01_Status & (1<<TX_DS)){
			  NRF24L01_Clear_TX_DS(&hspi3,NRF24L01_Status);
		  }
		  if(NRF24L01_Status & (1<<MAX_RT)){
			  //HAL_UART_Transmit_IT(&huart2,erreur,sizeof(erreur));	// DEBUG
			  //rx_data[0]='\n';								// DEBUG
			  //rx_data[1]='\r';								// DEBUG
			  //HAL_UART_Transmit_IT(&huart2,rx_data,2);		// DEBUG
			  NRF24L01_Flush(&hspi3,TX);
			  NRF24L01_Clear_MAX_RT(&hspi3,NRF24L01_Status);
		  }
		  if(NRF24L01_Status & (1<<RX_DR)){
			  rx_data[0]=NRF24L01_Read_Data_Pipe_Number(&hspi3,NRF24L01_Status);
			  NRF24L01_Read_RX_Payload(&hspi3,rx_data,1);
			  //HAL_UART_Transmit_IT(&huart2,rx_data,1);
			  NRF24L01_Clear_RX_DR(&hspi3,NRF24L01_Status);
		  }
		  clear_IRQ_flag();
	  }

  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  __HAL_RCC_PWR_CLK_ENABLE();

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
