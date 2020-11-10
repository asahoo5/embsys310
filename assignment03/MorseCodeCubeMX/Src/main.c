/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define RXBUFFERSIZE 1
#define MAXWORDSIZE  50

#define DOTDELAY     200 // length of a dot is one unit
#define DASHDELAY    600 // length of a dash is three units
#define PARTDELAY    200 // the space between parts of the same letter is one unit
#define LETTERDELAY  400 // space between letters is three units, since one unit delay is carried over from part delay as per assignment 
#define WORDDELAY    1400 // Not Used for this task! space between words is seven units
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
uint8_t* morseEncode(uint8_t charVal);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t myTxData[] = "Provide your first name to display and lit it's Morse Code, and hit enter: ";
uint8_t myRxData[RXBUFFERSIZE];

uint8_t MorseCode[MAXWORDSIZE * 5];
uint8_t MorseCodeAnalysis[MAXWORDSIZE * 6];

uint8_t RxData[MAXWORDSIZE];
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  int Word_Rx = 0;
  int RxDataIndex = 0;
  int MorseCodeIndex = 0;
  int MorseCodeAnalysisIndex = 0;
 
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  
  /* Provide instruction the user on how to use the tool and what to expect */
  if(HAL_UART_Transmit(&huart1, myTxData, sizeof(myTxData), 10) != HAL_OK)
  {
      Error_Handler();
  }
  
  /* Read and Store the user input for the first name, upon enter transition to the new line*/
  while(Word_Rx != 1 && RxDataIndex < MAXWORDSIZE)
  {
    while(HAL_UART_Receive(&huart1, myRxData, RXBUFFERSIZE, 5000) != HAL_OK)
    {
        Error_Handler();
    }
    
    if(HAL_UART_Transmit(&huart1, myRxData, RXBUFFERSIZE, 10) != HAL_OK)
    {
        Error_Handler();
    }
  
    RxData[RxDataIndex] = myRxData[0];
    ++RxDataIndex;
    
    if(myRxData[0] == '\r')
    {
        Word_Rx = 1;
        uint8_t newline[] = "\n";   
        
        if(HAL_UART_Transmit(&huart1, newline, RXBUFFERSIZE, 10) != HAL_OK)
        {
            Error_Handler();
        }
    }
  }
  /* End of User Access */

  /* Compute the Morse code for the provided string and store */
  for(int i = 0; i < (RxDataIndex - 1); ++i)
  {
      uint8_t* code = morseEncode(RxData[i]);
      for(int j = 0; code[j] != NULL; ++j)
      {
          MorseCode[MorseCodeIndex++]                 = code[j];
          MorseCodeAnalysis[MorseCodeAnalysisIndex++] = code[j];
          
      }
      MorseCodeAnalysis[MorseCodeAnalysisIndex++] = '!'; //Signifies letter gap - for LED output purpose
  }
  
  /* Storing Completed */
  
  /* Transmit/Output the Morse Code to the user */
  if(HAL_UART_Transmit(&huart1, MorseCode, sizeof(MorseCode), 10) != HAL_OK)
  {
        Error_Handler();
  }
  
  /* Toggle the LED with proper delay (based on Morse Code Logic)*/
  for (int index = 0; index < MorseCodeAnalysisIndex; ++index)
  {        
        if(MorseCodeAnalysis[index] == '!')
        {
            HAL_Delay(LETTERDELAY);
        }
        else
        {
            //HAL_GPIO_TogglePin(MLED_GPIO_Port, MLED_Pin);
            HAL_GPIO_WritePin(MLED_GPIO_Port, MLED_Pin, GPIO_PIN_SET);
            
            if(MorseCodeAnalysis[index] == '.')
            {
                HAL_Delay(DOTDELAY);
            }
            else
            {
                HAL_Delay(DASHDELAY);
            }
            
            //HAL_GPIO_TogglePin(MLED_GPIO_Port, MLED_Pin);
            HAL_GPIO_WritePin(MLED_GPIO_Port, MLED_Pin, GPIO_PIN_RESET);
            
            HAL_Delay(PARTDELAY);
        }   
  }
  
  return 0;
}

/**
  * @brief Encode Morse Code from the obtained character.
  * @param 8 bit character value 
  */
  
uint8_t* morseEncode(uint8_t charVal) {   
  // refer to the Morse table 
  switch (charVal) { 
  case 'a': 
    return ".-"; 
  case 'b': 
    return "-..."; 
  case 'c': 
    return "-.-."; 
  case 'd': 
    return "-.."; 
  case 'e': 
    return "."; 
  case 'f': 
    return "..-."; 
  case 'g': 
    return "--."; 
  case 'h': 
    return "...."; 
  case 'i': 
    return ".."; 
  case 'j': 
    return ".---"; 
  case 'k': 
    return "-.-"; 
  case 'l': 
    return ".-.."; 
  case 'm': 
    return "--"; 
  case 'n': 
    return "-."; 
  case 'o': 
    return "---"; 
  case 'p': 
    return ".--."; 
  case 'q': 
    return "--.-"; 
  case 'r': 
    return ".-."; 
  case 's': 
    return "..."; 
  case 't': 
    return "-"; 
  case 'u': 
    return "..-"; 
  case 'v': 
    return "...-"; 
  case 'w': 
    return ".--"; 
  case 'x': 
    return "-..-"; 
  case 'y': 
    return "-.--"; 
  case 'z': 
    return "--..";
  case '1': 
    return ".----";
  case '2': 
    return "..---";
  case '3': 
    return "...--";
  case '4': 
    return "....-";
  case '5': 
    return ".....";
  case '6': 
    return "-....";
  case '7': 
    return "--...";
  case '8': 
    return "---..";
  case '9': 
    return "----..";
  case '0': 
    return "-----";
  default:
    return ".";
  } 
} 

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 40;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(MLED_GPIO_Port, MLED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(ErLED_GPIO_Port, ErLED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : MLED_Pin */
  GPIO_InitStruct.Pin = MLED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(MLED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : ErLED_Pin */
  GPIO_InitStruct.Pin = ErLED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(ErLED_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  HAL_GPIO_WritePin(ErLED_GPIO_Port, ErLED_Pin, GPIO_PIN_RESET);
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
