/************** STEPS TO FOLLOW *****************
1. Enable GPIOA clock
2. Set the PIN PA5 as input
3. Configure the Pull UP / Pull Down mode
************************************************/

RCC->AHB1ENR |= (1<<0); 

/*Since I am using pin PA1,  modify the pins 2 and 3. 
This basically works like, if the PIN is ‘y‘, 
then configure the bits ‘2y’ and ‘2y+1’
Also, in order to set the pin as input, 
set the bits (3:2) as 0:0. 
This means write a ‘0’ in  2nd and 3rd positions*/

GPIOA->MODER &= ~((1<<2) | (1<<3));

GPIOA->PUPDR |= (1<<2);
