/* USER CODE BEGIN Header */
/**
  **
  • @file           : main.c
  • @brief          : Main program body
  **
  • @attention
  *
  • Copyright (c) 2025 STMicroelectronics.
  • All rights reserved.
  *
  • This software is licensed under terms that can be found in the LICENSE file
  • in the root directory of this software component.
  • If no LICENSE file comes with this software, it is provided AS-IS.
  *
  **
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include<math.h>
/* USER CODE END Includes */
/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/* USER CODE END PTD */
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
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
/* USER CODE END PFP */
/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/* USER CODE END 0 */
/**
  • @brief  The application entry point.
  • @retval int
  */
int main(void) {
    /* USER CODE BEGIN 1 */
    int mode = 2;
    int modeTotal = 5;
    float dt =.001;
    float t = .0;
    int tk = 0;

    int beepContinue = 100;
    int beepCurrent = beepContinue;
    // bool beepA = false;

    int sosA = 1;

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
    /* USER CODE BEGIN 2 */
    void BlowOut3LED () {
        HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, 1);
        HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, 1);
        HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, 1);
    }

    void RHeart(int lt) {
        for (int i = 0; i<100; i++) {
            if (i < lt) {
                HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, 0);
            } else {
                HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, 1);
            }
        }
    }

    int SOS_s = 3000;
    int SOS_l = 1000;

    int SOS_data[] = {
            1,
            2, // 亮
            SOS_s*1,
            SOS_s*2,
            SOS_s*3,
            SOS_s*4,
            SOS_s*5,
            SOS_s*5+SOS_l*1,
            SOS_s*5+SOS_l*2,
            SOS_s*5+SOS_l*3,
            SOS_s*5+SOS_l*4,
            SOS_s*5+SOS_l*5,
            SOS_s*5+SOS_l*5+SOS_s*1,
            SOS_s*5+SOS_l*5+SOS_s*2,
            SOS_s*5+SOS_l*5+SOS_s*3,
            SOS_s*5+SOS_l*5+SOS_s*4,
            SOS_s*5+SOS_l*5+SOS_s*5
    };


    /* USER CODE END 2 */
    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1) {
        /* USER CODE END WHILE */

        // 处理按键
        HAL_GPIO_ReadPin(KEY_2_GPIO_Port, KEY_2_Pin);
        if (HAL_GPIO_ReadPin(KEY_2_GPIO_Port, KEY_2_Pin)==1) {
            if (mode == modeTotal) { mode = 1; } else { mode+=1; }
            beepCurrent = 0;
            HAL_Delay(dt*1e3);
            while (HAL_GPIO_ReadPin(KEY_2_GPIO_Port, KEY_2_Pin)==1) {}
        } else {
            HAL_Delay(dt*1e3);
        }

        // 蜂鸣器
        if (beepCurrent < beepContinue) {
            HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, 1);
            beepCurrent +=1;
        } else {
            HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, 0);
        }

        // 模式处理
        if (mode==1) {
           // HappyParty(200);
        } else if (mode == 2) {
           // HappyParty(500);
        } else if (mode == 3) {
            int length = sizeof(SOS_data) / sizeof(SOS_data[0]);
            for (int i = 0; i < length; i++) {
              int item = SOS_data[i];
              if (abs(item - tk)<1e-8) {
                  sosA = 1 - sosA;
              }
            }
            HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, 1 - sosA);
           // BlowOut3LED();
          //  SOS();
        } else if (mode == 4) {
            RHeart(50 + 48 * sin(5.0 * t));
        } else if (mode == 5) {
            BlowOut3LED();
        }

        // 环境时间
        t += dt;
        tk += 1;

        /* USER CODE BEGIN 3 */
    }
    /* USER CODE END 3 */
}
/**
  • @brief System Clock Configuration
  • @retval None
  */
void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {
            0
    }
    ;
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {
            0
    }
    ;
    /** Initializes the RCC Oscillators according to the specified parameters
  • in the RCC_OscInitTypeDef structure.
  */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }
    /** Initializes the CPU, AHB and APB buses clocks
  */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                  |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
        Error_Handler();
    }
}
/**
  • @brief GPIO Initialization Function
  • @param None
  • @retval None
  */
static void MX_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {
            0
    }
    ;
    /* USER CODE BEGIN MX_GPIO_Init_1 */
    /* USER CODE END MX_GPIO_Init_1 */
    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOB, LED_G_Pin|LED_B_Pin|LED_R_Pin, GPIO_PIN_SET);
    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_RESET);
    /*Configure GPIO pin : KEY_2_Pin */
    GPIO_InitStruct.Pin = KEY_2_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(KEY_2_GPIO_Port, &GPIO_InitStruct);
    /*Configure GPIO pin : KEY_1_Pin */
    GPIO_InitStruct.Pin = KEY_1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(KEY_1_GPIO_Port, &GPIO_InitStruct);
    /*Configure GPIO pins : LED_G_Pin LED_B_Pin */
    GPIO_InitStruct.Pin = LED_G_Pin|LED_B_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    /*Configure GPIO pin : BEEP_Pin */
    GPIO_InitStruct.Pin = BEEP_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(BEEP_GPIO_Port, &GPIO_InitStruct);
    /*Configure GPIO pin : LED_R_Pin */
    GPIO_InitStruct.Pin = LED_R_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(LED_R_GPIO_Port, &GPIO_InitStruct);
    /* USER CODE BEGIN MX_GPIO_Init_2 */
    /* USER CODE END MX_GPIO_Init_2 */
}
/* USER CODE BEGIN 4 */
/* USER CODE END 4 */
/**
  • @brief  This function is executed in case of error occurrence.
  • @retval None
  */
void Error_Handler(void) {
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1) {
    }
    /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  • @brief  Reports the name of the source file and the source line number
  •         where the assert_param error has occurred.
  • @param  file: pointer to the source file name
  • @param  line: assert_param error line source number
  • @retval None
  */
void assert_failed(uint8_t *file, uint32_t line) {
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}
#endif
/* USE_FULL_ASSERT */