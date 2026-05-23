# smart-home-stm32
Smart home automation system with FreeRTOS — STM32F407
# 🏠 Smart Home System — STM32F407

> Real-time home automation with FreeRTOS — 6 concurrent tasks

![STM32](https://img.shields.io/badge/STM32F407-03234B?style=flat&logo=stmicroelectronics&logoColor=white)
![FreeRTOS](https://img.shields.io/badge/FreeRTOS-8CC84B?style=flat&logo=freertos&logoColor=white)
![C](https://img.shields.io/badge/C-00599C?style=flat&logo=c&logoColor=white)
![Altium](https://img.shields.io/badge/Altium_Designer-A5915F?style=flat&logo=altiumdesigner&logoColor=white)

## Overview

A complete smart home automation system built on STM32F407 with FreeRTOS.
The system runs 6 concurrent tasks managing sensors, actuators, security,
and display — all synchronized with mutexes.

## Hardware

| Component | Details |
|---|---|
| MCU | STM32F407VGTx |
| Temperature/Humidity | DHT22 sensor |
| Rain sensor | Digital input with pull-up |
| Door control | Servo motor via PWM (TIM2_CH2) |
| Clothes protection | Servo motor via PWM (TIM2_CH3) |
| Security | 4x4 matrix keypad + PIN code |
| Display | LCD 16x2 — 4 cycling screens |
| Feedback | Buzzer + LED |
| PCB | Custom design — Altium Designer |

## FreeRTOS Tasks

| Task | Priority | Role |
|---|---|---|
| RainTask | AboveNormal | Rain detection → servo clothes |
| DHT22Task | AboveNormal | Temperature & humidity reading |
| KeypadTask | Normal | PIN code input → door servo |
| BuzzerTask | AboveNormal | Audio feedback |
| LCDTask | Normal | 4 screens cycling display |
| ControleTask | Normal | System control (reserved) |

## Features

- Real-time multitasking with FreeRTOS (6 tasks)
- Automatic clothes protection when rain detected
- PIN code door lock (4 digits) with wrong attempt alert
- DHT22 temperature and humidity monitoring
- LCD display cycling: Temperature / Humidity / Rain / Door status
- Mutex-protected shared variables
- Custom PCB designed in Altium Designer

## Project Structure
Core/Src/
├── main.c        ← FreeRTOS tasks, system init
├── dht22.c       ← DHT22 sensor driver
├── keypad.c      ← 4x4 matrix keypad driver
└── lcd.c         ← LCD 16x2 driver
Core/Inc/
├── dht22.h
├── keypad.h
├── lcd.h
└── FreeRTOSConfig.h
## Author

**Molka Hammami** — Microelectronics Engineering Student, Tunisia
[LinkedIn](https://linkedin.com/in/molka-hammami) · [GitHub](https://github.com/Molkahammami)
