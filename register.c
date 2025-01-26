/*******************
1. enable HSE, wait for HSE -> ready
2. set 'power enable clock' and 'voltage regulator'
3. config 'flash prefetch' and 'latency' related settings
4. config 'prescalars HCLK', 'PCLK1', 'PCLK2'
5. config -> 'main pll'
6. enable 'pll' and wait untill -> ready
7. select 'clock source' and wait untill -> set
*******************/ 
/*******************************************
 HSE is a extern Quarz or osci tact source 
> we need HSE for eg USB or CAN communication
< HSE is more exact as HSI 
< Der PLL ist ein Baustein im Mikrocontroller, 
der den Grundtakt (z. B. 8 MHz vom HSE) „hochschalten“ kann. 
Er multipliziert diese Frequenz, sodass du z. B. 72 MHz oder 168 MHz 
für den Mikrocontroller bekommst. Das ist wichtig,
wenn dein Mikrocontroller schneller arbeiten soll

> RCC_CR-Konfiguration:
Aktivieren des HSE:
  Das Bit HSEON im RCC_CR-Register wird gesetzt, 
  um den HSE zu aktivieren. Sobald dieses Bit gesetzt ist, 
  beginnt der Mikrocontroller, den externen Quarz zu starten.

Statusüberwachung:
  Das Bit HSERDY (HSE Ready) im selben Register zeigt an, 
  ob der HSE erfolgreich gestartet wurde und stabil ist. 
  Es wird als Indikator verwendet, bevor der Mikrocontroller 
  die Taktquelle wechselt.
**************************************************/

/* The setup below will allow the controller to run at 180 MHz*/

RCC ->CR |= 1<<16;
while (!(RCC->CR & (1<<17)));

/* power enable lock: to control voltage regulator /leistungskomponente
> which have higher taktfreuency  */

RCC->APB1ENR |= 1<<28; 

/*PWR 28th bit
> in  cubemx the voltage regulator is selected 
for 'scale 1' by default*/

PWR->CR |= 3<<14; /* 3= 11 in binary, set 1 in the 14th and 15th bit*/

/* scale 3 = 00 = low power 
   scale 2 = 01 = mid power
   scale 1 = 11 = high power for high frequeny > 75MHZ 
   
    zusätzliche Taktzyklen wartet, bevor er den nächsten Befehl ausführt.
    Dies wird gemacht, um sicherzustellen, dass die Daten 
    aus dem langsameren Flash-Speicher korrekt und stabil verfügbar sind.

    000: 0 Wait States
    001: 1 Wait State
    010: 2 Wait States
    ...
    101: 5 Wait States (bzw. 5WS) -> latency

    set 1 -> data cash, prefetch buffer, instruction cache

    Besonders bei linearen Programmabläufen (ohne viele Sprünge) 
    ist der Prefetch Buffer äußerst effektiv,
*/

FLASH->ACR = (1<<8) | (1<<9) | (1<<10) | (5<<0);

/*

    The AHB Prescalar is 1, so the HPRE (bits 7:4) will be all 0s.
    APB1 Prescalar is 4, so the PPRE1 (bits 12:10) will be “101” i.e write 5 to the 10th position
    APB2 Prescalar is 2, so the PPRE2 (bits 15:13) will be “100” i.e write 4 to the 13th position

*/

RCC->CFGR &= ~(1<<4); /* 0xxx*/
RCC->CFGR |= (5<<10);
RCC->CFGR |= (4<<13);

/*

    PLLP value, according to the CubeMX is 2, and to set it, need to write 0s in the PLLP (Bits 17:16)
    PLLM and PLLN values are 4 and 180, according to the CubeMX, and will directly set them in the PLLM (Bits 5:0) and PLLN (Bits 14:6)
    As using HSE crystal for the clock, I need to set the PLLSRC (Bit 22) to 1.

*/

#define PLL_M 4
#define PLL_N 180
#define PLL_P 0 //PLLP = 2

RCC->PLLCFGR = (PLL_M <<0) | (PLL_N << 6) | (PLL_P <<16) | (1<<22);

/*
 enable the PLL, we must write a 1 to the PLL ON (24th bit), 
 then will wait for the PLL RDY (25th bit) to set, 
 which will indicate that the PLL is ready.
*/

RCC->CR |= (1<<24);
while (!(RCC->CR & (1<<25)));

/*Select the Clock Source and wait for it to be set*/

RCC->CFGR |= (2<<0);
while (!(RCC->CFGR & (2<<2)));