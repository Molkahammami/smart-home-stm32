#include "lcd.h"
#include "main.h"
#include "cmsis_os.h"

#define LCD_RS_PORT  GPIOA
#define LCD_RS_PIN   GPIO_PIN_4
#define LCD_EN_PORT  GPIOB
#define LCD_EN_PIN   GPIO_PIN_11
#define LCD_D4_PORT  GPIOB
#define LCD_D4_PIN   GPIO_PIN_12
#define LCD_D5_PORT  GPIOB
#define LCD_D5_PIN   GPIO_PIN_13
#define LCD_D6_PORT  GPIOB
#define LCD_D6_PIN   GPIO_PIN_14
#define LCD_D7_PORT  GPIOB
#define LCD_D7_PIN   GPIO_PIN_15

static void LCD_Pulse(void)
{
    HAL_GPIO_WritePin(LCD_EN_PORT, LCD_EN_PIN, GPIO_PIN_SET);
    osDelay(1);
    HAL_GPIO_WritePin(LCD_EN_PORT, LCD_EN_PIN, GPIO_PIN_RESET);
    osDelay(1);
}

static void LCD_SendNibble(uint8_t nibble)
{
    HAL_GPIO_WritePin(LCD_D4_PORT, LCD_D4_PIN, (nibble >> 0) & 0x01);
    HAL_GPIO_WritePin(LCD_D5_PORT, LCD_D5_PIN, (nibble >> 1) & 0x01);
    HAL_GPIO_WritePin(LCD_D6_PORT, LCD_D6_PIN, (nibble >> 2) & 0x01);
    HAL_GPIO_WritePin(LCD_D7_PORT, LCD_D7_PIN, (nibble >> 3) & 0x01);
    LCD_Pulse();
}

static void LCD_Send(uint8_t byte, uint8_t isData)
{
    HAL_GPIO_WritePin(LCD_RS_PORT, LCD_RS_PIN,
                      isData ? GPIO_PIN_SET : GPIO_PIN_RESET);
    LCD_SendNibble(byte >> 4);
    LCD_SendNibble(byte & 0x0F);
    osDelay(2);
}

void LCD_Init(void)
{
    osDelay(50);
    HAL_GPIO_WritePin(LCD_RS_PORT, LCD_RS_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LCD_EN_PORT, LCD_EN_PIN, GPIO_PIN_RESET);

    LCD_SendNibble(0x03); osDelay(5);
    LCD_SendNibble(0x03); osDelay(1);
    LCD_SendNibble(0x03); osDelay(1);
    LCD_SendNibble(0x02); osDelay(1);

    LCD_Send(0x28, 0);   /* 4 bits, 2 lignes */
    LCD_Send(0x0C, 0);   /* Display ON        */
    LCD_Send(0x06, 0);   /* Increment         */
    LCD_Send(0x01, 0);   /* Clear             */
    osDelay(5);
}

void LCD_Clear(void)
{
    LCD_Send(0x01, 0);
    osDelay(5);
}

void LCD_SetCursor(uint8_t row, uint8_t col)
{
    uint8_t address = (row == 0) ? 0x80 : 0xC0;
    LCD_Send(address + col, 0);
}

void LCD_Print(char *str)
{
    while (*str)
        LCD_Send((uint8_t)(*str++), 1);
}

void LCD_SetRTOS(uint8_t started) { (void)started; }
