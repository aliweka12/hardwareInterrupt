/**
 * @file main.c
 * @brief This program uses the user button as a hardware interrupt to toggle led.
 *
 * This program initializes the user button using GPIO.
 */
#include "main.h"

/**
 * @class ClockManager
 * @brief Manages the system clock configuration.
 */
class ClockManager {
public:
    /**
     * @brief Configures the system clock.
     * @note Sets up the clock source, voltage scaling, PLL, and flash latency.
     */
    static void Configure() {
        RCC_ClkInitTypeDef RCC_ClkInitStruct;
        RCC_OscInitTypeDef RCC_OscInitStruct;
        HAL_StatusTypeDef ret = HAL_OK;

        __HAL_RCC_PWR_CLK_ENABLE();
        __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

        RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
        RCC_OscInitStruct.HSEState = RCC_HSE_ON;
        RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
        RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
#if defined(USE_STM32469I_DISCO_REVA)
        RCC_OscInitStruct.PLL.PLLM = 25;
#else
        RCC_OscInitStruct.PLL.PLLM = 8;
#endif
        RCC_OscInitStruct.PLL.PLLN = 360;
        RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
        RCC_OscInitStruct.PLL.PLLQ = 7;
        RCC_OscInitStruct.PLL.PLLR = 6;

        ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);
        if(ret != HAL_OK) { while(1) {} }

        ret = HAL_PWREx_EnableOverDrive();
        if(ret != HAL_OK) { while(1) {} }

        RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
        RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
        RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
        RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
        RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

        ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
        if(ret != HAL_OK) { while(1) {} }
    }
};

/**
 * @class IndicatorLED
 * @brief Manages LED operations.
 */
class IndicatorLED {
public:
    /**
     * @brief Initializes LED1.
     */
    static void Initialize() {
        BSP_LED_Init(LED1);
    }

    /**
     * @brief Toggles LED1 state.
     */
    static void ToggleState() {
        BSP_LED_Toggle(LED1);
    }
};

/**
 * @class InterruptManager
 * @brief Manages external interrupts.
 */
class InterruptManager {
public:
    /**
     * @brief Configures EXTI line 0 (connected to PA.00 pin) in interrupt mode.
     * @note Initializes GPIOA and configures the EXTI line for interrupt on rising edge.
     */
    static void Configure() {
        GPIO_InitTypeDef GPIO_InitStructure;

        __HAL_RCC_GPIOA_CLK_ENABLE();

        GPIO_InitStructure.Mode = GPIO_MODE_IT_RISING;
        GPIO_InitStructure.Pull = GPIO_NOPULL;
        GPIO_InitStructure.Pin = GPIO_PIN_0;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

        HAL_NVIC_SetPriority(EXTI0_IRQn, 2, 0);
        HAL_NVIC_EnableIRQ(EXTI0_IRQn);
    }
};

/**
 * @brief Main program entry point.
 * @note Initializes the system and enters an infinite loop.
 */
int main() {
    HAL_Init(); // Initialize HAL library
    ClockManager::Configure(); // Configure system clock
    IndicatorLED::Initialize(); // Initialize LED
    InterruptManager::Configure(); // Configure external interrupt

    while (1) {} // Infinite loop
}

/**
 * @brief Callback function for EXTI line detection.
 * @note Toggles the LED when EXTI line 0 is triggered.
 * @param GPIO_Pin Specifies the pins connected to the EXTI line.
 */
extern "C" void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == GPIO_PIN_0) {
        IndicatorLED::ToggleState();
    }
}

#ifdef USE_FULL_ASSERT
/**
 * @brief Reports assert_param error.
 * @param file Pointer to the source file name.
 * @param line assert_param error line source number.
 */
extern "C" void assert_failed(uint8_t *file, uint32_t line) {
    while (1) {} // Infinite loop for error handling
}
#endif
