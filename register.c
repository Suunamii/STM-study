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
RCC ->CR |= 1<<16;
while (!(RCC->CR & (1<<17)));


