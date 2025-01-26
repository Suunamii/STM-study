/**** STEPS FOLLOWED  ************
1. Enable the I2C CLOCK and GPIO CLOCK
2. Configure the I2C PINs for ALternate Functions
	a) Select Alternate Function in MODER Register
	b) Select Open Drain Output 
	c) Select High SPEED for the PINs
	d) Select Pull-up for both the Pins
	e) Configure the Alternate Function in AFR Register
3. Reset the I2C 	
4. Program the peripheral input clock in I2C_CR2 Register in order to generate correct timings
5. Configure the clock control registers
6. Configure the rise time register
7. Program the I2C_CR1 register to enable the peripheral
*/

RCC->APB1ENR |= (1<<21); 

RCC->AHB1ENR |= (1<<1);

GPIOB->MODER |= (2<<16) | (2<<18);  
// Bits (17:16)= 1:0 --> Alternate Function for Pin PB8; Bits (19:18)= 1:0 --> Alternate Function for Pin PB9

GPIOB->OTYPER |= (1<<8) | (1<<9);  //  Bit8=1, Bit9=1  output open drain

GPIOB->OSPEEDR |= (3<<16) | (3<<18);  // Bits (17:16)= 1:1 --> High Speed for PIN PB8; Bits (19:18)= 1:1 --> High Speed for PIN PB9

GPIOB->PUPDR |= (1<<16) | (1<<18);  // Bits (17:16)= 0:1 --> Pull up for PIN PB8; Bits (19:18)= 0:1 --> pull up for PIN PB9

GPIOB->AFR[1] |= (4<<0) | (4<<4);  // Bits (3:2:1:0) = 0:1:0:0 --> AF4 for pin PB8;  Bits (7:6:5:4) = 0:1:0:0 --> AF4 for pin PB9

I2C1->CR1 |= (1<<15);  // reset the I2C
I2C1->CR1 &= ~(1<<15);  // Normal operation

// Program the peripheral input clock in I2C_CR2 Register in order to generate correct timings
I2C1->CR2 |= (45<<0);  // PCLK1 FREQUENCY in MHz

// Configure the clock control registers
I2C1->CCR = 225<<0; 

// Configure the rise time register
I2C1->TRISE = 46;  

// Program the I2C_CR1 register to enable the peripheral
I2C1->CR1 |= (1<<0);  // Enable I2C