#include "dht22.h"
#include "main.h"
extern TIM_HandleTypeDef htim1;

#define DHT22_PORT GPIOA
#define DHT22_PIN  GPIO_PIN_0

static void delay_us(uint32_t us)
{
    __HAL_TIM_SET_COUNTER(&htim1, 0);
    while (__HAL_TIM_GET_COUNTER(&htim1) < us);
}

static void DHT22_SetOutput(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = DHT22_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(DHT22_PORT, &GPIO_InitStruct);
}

static void DHT22_SetInput(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = DHT22_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(DHT22_PORT, &GPIO_InitStruct);
}

uint8_t DHT22_Read(float *temperature, float *humidity)
{
    uint8_t data[5] = {0};
    uint32_t timeout;

    DHT22_SetOutput();

    // Start signal
    HAL_GPIO_WritePin(DHT22_PORT, DHT22_PIN, GPIO_PIN_RESET);
    HAL_Delay(3);                    // Minimum 1ms, on met 3ms pour sécurité
    HAL_GPIO_WritePin(DHT22_PORT, DHT22_PIN, GPIO_PIN_SET);
    delay_us(40);

    DHT22_SetInput();

    // Attente réponse du capteur
    timeout = 10000;
    while (HAL_GPIO_ReadPin(DHT22_PORT, DHT22_PIN) == GPIO_PIN_SET)
        if (--timeout == 0) return 0;

    timeout = 10000;
    while (HAL_GPIO_ReadPin(DHT22_PORT, DHT22_PIN) == GPIO_PIN_RESET)
        if (--timeout == 0) return 0;

    timeout = 10000;
    while (HAL_GPIO_ReadPin(DHT22_PORT, DHT22_PIN) == GPIO_PIN_SET)
        if (--timeout == 0) return 0;

    // Lecture des 40 bits
    for (int i = 0; i < 40; i++)
    {
        timeout = 10000;
        while (HAL_GPIO_ReadPin(DHT22_PORT, DHT22_PIN) == GPIO_PIN_RESET)
            if (--timeout == 0) return 0;

        delay_us(45);   // temps critique

        data[i/8] <<= 1;
        if (HAL_GPIO_ReadPin(DHT22_PORT, DHT22_PIN) == GPIO_PIN_SET)
            data[i/8] |= 1;

        timeout = 10000;
        while (HAL_GPIO_ReadPin(DHT22_PORT, DHT22_PIN) == GPIO_PIN_SET)
            if (--timeout == 0) return 0;
    }

    // Vérification checksum
    if (data[4] != ((data[0] + data[1] + data[2] + data[3]) & 0xFF))
        return 0;

    *humidity    = ((data[0] << 8) | data[1]) / 10.0f;
    *temperature = (((data[2] & 0x7F) << 8) | data[3]) / 10.0f;
    if (data[2] & 0x80) *temperature = -*temperature;

    return 1;
}
