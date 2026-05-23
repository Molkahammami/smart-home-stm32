#ifndef DHT22_H
#define DHT22_H

#include "stm32f4xx_hal.h"

uint8_t DHT22_Read(float *temperature, float *humidity);

#endif /* DHT22_H */
