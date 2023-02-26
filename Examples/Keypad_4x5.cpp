#include "main.h"
#include "gpio.h"
#include "Keypad.h"

uint8_t rowPins[] = {8, 7, 6, 5, 4};  // GPIO Input Pull_Up
uint8_t colPins[] = {0, 1, 2, 3};     // GPIO Output
char customKey;

char keypadArray[sizeof(rowPins)][sizeof(colPins)] =
{
  {'A','B','#','*'},
  {'1','2','3','U'},
  {'4','5','6','D'},
  {'7','8','9','C'},
  {'<','0','>','E'}
};

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();

  Keypad keypad(GPIOA, (char*)keypadArray, rowPins, colPins, sizeof(rowPins), sizeof(colPins));

  while (1)
  {
  	customKey = keypad.getKey();

  	if(customKey)
  	{
		// Your code here 
  	}
  }
}
