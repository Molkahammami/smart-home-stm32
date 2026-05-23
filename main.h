#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);
void Error_Handler(void);

/* LED */
#define LED_Pin                    GPIO_PIN_13
#define LED_GPIO_Port              GPIOC

/* DHT22 */
#define DHT22_Pin           GPIO_PIN_0
#define DHT22_GPIO_Port     GPIOA

/* LCD RS */
#define LCD_RS_Pin                 GPIO_PIN_4
#define LCD_RS_GPIO_Port           GPIOA

/* Keypad Rows */
#define Keypad_Row1_Pin            GPIO_PIN_0
#define Keypad_Row1_GPIO_Port      GPIOB
#define Keypad_Row2_Pin            GPIO_PIN_1
#define Keypad_Row2_GPIO_Port      GPIOB
#define Keypad_Row3_Pin            GPIO_PIN_2
#define Keypad_Row3_GPIO_Port      GPIOB
#define Keypad_Row4_Pin            GPIO_PIN_6
#define Keypad_Row4_GPIO_Port      GPIOB

/* Keypad Columns */
#define Keypad_Columns1_Pin        GPIO_PIN_4
#define Keypad_Columns1_GPIO_Port  GPIOB
#define Keypad_Columns2_Pin        GPIO_PIN_5
#define Keypad_Columns2_GPIO_Port  GPIOB
#define Keypad_Columns3_Pin        GPIO_PIN_8
#define Keypad_Columns3_GPIO_Port  GPIOB
#define Keypad_Columns4_Pin        GPIO_PIN_9
#define Keypad_Columns4_GPIO_Port  GPIOB

/* Buzzer */
#define Buzzer_Pin                 GPIO_PIN_10
#define Buzzer_GPIO_Port           GPIOB

/* LCD */
#define LCD_EN_Pin                 GPIO_PIN_11
#define LCD_EN_GPIO_Port           GPIOB
#define LCD_Pin                    GPIO_PIN_12
#define LCD_GPIO_Port              GPIOB
#define LCDB13_Pin                 GPIO_PIN_13
#define LCDB13_GPIO_Port           GPIOB
#define LCDB14_Pin                 GPIO_PIN_14
#define LCDB14_GPIO_Port           GPIOB
#define LCDB15_Pin                 GPIO_PIN_15
#define LCDB15_GPIO_Port           GPIOB

/* Capteur pluie */
#define DrainRain_Sensor_Pin       GPIO_PIN_8
#define DrainRain_Sensor_GPIO_Port GPIOA

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
