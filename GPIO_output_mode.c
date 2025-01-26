/************** STEPS TO FOLLOW *****************
1. Enable GPIOA clock
2. Set the PIN PA5 as output
3. Configure the output mode i.e state, speed, and pull
************************************************/

RCC->ABH1ENR |= (1<<0);

GPIOA->MODER &= ~(1 << 11);  // Bit 11 auf 0 setzen
GPIOA->MODER |= (1 << 10);   // Bit 10 auf 1 setzen

GPIOA->OTYPER |= (1<<5);

GPIOA->OSPEEDR |= (1<<11);  // Pin PA5 (bits 11:10) as Fast Speed (1:0)

GPIOA->PUPDR &= ~((1<<10) | (1<<11));  // Pin PA5 (bits 11:10) are 0:0 --> no pull up or pulldown

/*To set or reset an individual pin, 
we need to modify the GPIOx_BSRR Register*/

GPIOA->BSRR |= (1<<5); //set

GPIOA->BSRR |= (1<<21); //reset

/*Output Data Register (ODR) can also be used 
to Set/Reset an individual Pin or the entire Port.*/

GPIOA->ODR |= 1<<5; // Set the Pin PA5

GPIOA->ODR &= ~(1<<5); // Reset the Pin PA5

/*main code*/

void Delay (uint32_t time){
    while (time--);
}

int main (void){
    SysClockConfig ();
    GPIOConfig ();

    while(1)
    {
        GPIOA->BSRR |= (1<<5);
        Delay (1000000);
        GPIOA->BSRR |= (1<<5) <<16;
    }
}