#include <stdint.h>
#include <stm32f446xx.h>
#include <stdio.h>
#include "main.h"
#include "gpio.h"
#include "usart.h"

#define FLASH_SECTOR_0 ((uint32_t*) 0x8000000)
#define FLASH_SECTOR_2 ((uint32_t*) 0x8008000) // Beginning of userapplication0, address has been set up in STM32F446RETX_FLASH.ld of the userapplication0 project

void (*userApp) (void);

int main(void)
{
	GPIO_Init();
	USART2_Init();

	// Code projet 2
	if(gpio_is_button_pressed()) {
		printf("Button pressed !\r\n");
		userApp = *(FLASH_SECTOR_2 + 1);
		(*userApp)();
	} else {
		printf("Button not pressed !\r\n");
	}
	// Fin Code projet 2

	while(1){
		for(uint32_t i = 0 ; i<100000; i++);
		GPIOA->ODR ^= 1<<5;
		printf("Hello from bootloader0\r\n");
	}
}

