*****************************************************************************
** ChibiOS/RT port for ARM-Cortex-M4 STM32L422.                            **
*****************************************************************************

** TARGET **

The demo runs on an STM32 ELGO32_422 devboard

The card design is open source and github repo for this card will be linked
in this file in a near future. 

** The Demo **

The demo flashes the board LED using a thread, after initialisation,
the test procedure is activated with output on the serial port
SD1 (USART1, mapped on USB virtual COM port).

** Build Procedure **

The demo has been tested by using the free Codesourcery GCC-based toolchain
and YAGARTO.
Just modify the TRGT line in the makefile in order to use different GCC ports.

** Notes **

Some files used by the demo are not part of ChibiOS/RT but are copyright of
ST Microelectronics and are licensed under a different license.
Also note that not all the files present in the ST library are distributed
with ChibiOS/RT, you can find the whole library on the ST web site:

                             http://www.st.com
