#include <stdint.h>
#include <stm32f446xx.h>
#include "main.h"
#include "gpio.h"

void GPIO_Init(void){
	/* Clock Init */
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOCEN;

	/* GPIO Init */
	GPIOA->MODER |= OUTPUT_MODE <<10;		// PA5 Output LED

	GPIOC->MODER |= INPUT_MODE	<< 26;		// PC13 Input Push-Button3
	GPIOC->PUPDR |= (1 << (13 * 2));   // PC13 Active la résistance de tirage

}


uint8_t gpio_is_button_pressed(void)
{
	return ((GPIOC->IDR & (1 << 13)) == 0);
}
