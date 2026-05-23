#include "keypad.h"
#include "main.h"
#include "cmsis_os.h"

static GPIO_TypeDef* ROW_PORTS[] = {
    Keypad_Row1_GPIO_Port,
    Keypad_Row2_GPIO_Port,
    Keypad_Row3_GPIO_Port,
    Keypad_Row4_GPIO_Port
};

static uint16_t ROW_PINS[] = {
    Keypad_Row1_Pin,
    Keypad_Row2_Pin,
    Keypad_Row3_Pin,
    Keypad_Row4_Pin
};

static GPIO_TypeDef* COL_PORTS[] = {
    Keypad_Columns1_GPIO_Port,
    Keypad_Columns2_GPIO_Port,
    Keypad_Columns3_GPIO_Port,
    Keypad_Columns4_GPIO_Port
};

static uint16_t COL_PINS[] = {
    Keypad_Columns1_Pin,
    Keypad_Columns2_Pin,
    Keypad_Columns3_Pin,
    Keypad_Columns4_Pin
};

static const char keys[4][4] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};

char Keypad_Read(void)
{
    for (int row = 0; row < 4; row++)
    {
        for (int r = 0; r < 4; r++)
            HAL_GPIO_WritePin(ROW_PORTS[r], ROW_PINS[r], GPIO_PIN_SET);

        HAL_GPIO_WritePin(ROW_PORTS[row], ROW_PINS[row], GPIO_PIN_RESET);
        osDelay(2);

        for (int col = 0; col < 4; col++)
        {
            if (HAL_GPIO_ReadPin(COL_PORTS[col], COL_PINS[col]) == GPIO_PIN_RESET)
            {
                while (HAL_GPIO_ReadPin(COL_PORTS[col], COL_PINS[col]) == GPIO_PIN_RESET)
                    osDelay(10);
                return keys[row][col];
            }
        }
    }
    return 0;
}
