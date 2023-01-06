/*
*
* add the next function to main.c
*
*
*/

void EXTI15_10_IRQHandler()
{
		// Clear pending bit 13 by writing a '1'
		EXTI->PR = EXTI_PR_PR13;
		printf("\r\n\r\nPush Button Pressed in User Application 1\r\n\r\n");
		for(uint32_t i = 0 ; i<100000; i++);
}


/*
*
*
* content of the gpio.c file
*
*/

#include <stdint.h>
#include <stm32f446xx.h>
#include "main.h"
#include "gpio.h"

void GPIO_Init(void){
	/* Clock Init */
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOCEN;
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	/* GPIO Init */
	GPIOA->MODER |= OUTPUT_MODE <<10;		// PA5 Output LED

	GPIOC->MODER |= INPUT_MODE	<< 26;		// PC13 Input Push-Button

	// Active les interruptions sur la pin PC13
	SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI13_PC;
	EXTI->IMR |= EXTI_IMR_IM13;

	// Configure le sens de détection de l'interruption (front montant)
	//EXTI->RTSR |= EXTI_RTSR_TR13;
	//EXTI->FTSR &= ~EXTI_FTSR_TR13;


	// Configure le sens de détection de l'interruption (front descendant)
	EXTI->RTSR &= ~EXTI_RTSR_TR13;
	EXTI->FTSR |= EXTI_FTSR_TR13;


	// Associe l'interruption de la pin PC13 au vecteur d'interruption
	NVIC_EnableIRQ(EXTI15_10_IRQn);

	// Configure le niveau de priorité de l'interruption
	NVIC_SetPriority(EXTI15_10_IRQn, 4);
}
