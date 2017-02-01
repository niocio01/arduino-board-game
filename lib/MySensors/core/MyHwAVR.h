/**
 * The MySensors Arduino library handles the wireless radio link and protocol
 * between your home built sensors/actuators and HA controller of choice.
 * The sensors forms a self healing radio network with optional repeaters. Each
 * repeater and gateway builds a routing tables in EEPROM which keeps track of the
 * network topology allowing messages to be routed to nodes.
 *
 * Created by Henrik Ekblad <henrik.ekblad@mysensors.org>
 * Copyright (C) 2013-2015 Sensnology AB
 * Full contributor list: https://github.com/mysensors/Arduino/graphs/contributors
 *
 * Documentation: http://www.mysensors.org
 * Support Forum: http://forum.mysensors.org
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 */

#ifndef MyHwAVR_h
#define MyHwAVR_h

#include "MyHw.h"
#include <avr/eeprom.h>
#include <avr/pgmspace.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/atomic.h>


#ifdef __cplusplus
#include <Arduino.h>
#endif

#ifndef MY_SERIALDEVICE
#define MY_SERIALDEVICE Serial
#endif

#if defined __AVR_ATmega328P__
#ifndef sleep_bod_disable
#define sleep_bod_disable() 										\
	do { 																\
		unsigned char tempreg; 											\
		__asm__ __volatile__("in %[tempreg], %[mcucr]" "\n\t" 			\
		                     "ori %[tempreg], %[bods_bodse]" "\n\t" 		\
		                     "out %[mcucr], %[tempreg]" "\n\t" 			\
		                     "andi %[tempreg], %[not_bodse]" "\n\t" 		\
		                     "out %[mcucr], %[tempreg]" 					\
		                     : [tempreg] "=&d" (tempreg) 					\
		                     : [mcucr] "I" _SFR_IO_ADDR(MCUCR), 			\
		                     [bods_bodse] "i" (_BV(BODS) | _BV(BODSE)), \
		                     [not_bodse] "i" (~_BV(BODSE))); 			\
	} while (0)
#endif
#endif


// Define these as macros to save valuable space
#define hwDigitalWrite(__pin, __value) digitalWriteFast(__pin, __value)
#define hwDigitalRead(__pin) digitalReadFast(__pin)
#define hwPinMode(__pin, __value) pinModeFast(__pin, __value)

#if defined(MY_DISABLED_SERIAL)
#define hwInit()
#else
#define hwInit() MY_SERIALDEVICE.begin(MY_BAUD_RATE)
#endif

#define hwWatchdogReset() wdt_reset()
#define hwReboot() wdt_enable(WDTO_15MS); while (1)
#define hwMillis() millis()
#define hwRandomNumberInit() randomSeed(analogRead(MY_SIGNING_SOFT_RANDOMSEED_PIN))
#define hwReadConfig(__pos) eeprom_read_byte((uint8_t*)(__pos))
#define hwWriteConfig(__pos, __val) eeprom_update_byte((uint8_t*)(__pos), (__val))
#define hwReadConfigBlock(__buf, __pos, __length) eeprom_read_block((void*)(__buf), (void*)(__pos), (__length))
#define hwWriteConfigBlock(__buf, __pos, __length) eeprom_update_block((void*)(__buf), (void*)(__pos), (__length))



enum period_t {
	SLEEP_15MS,
	SLEEP_30MS,
	SLEEP_60MS,
	SLEEP_120MS,
	SLEEP_250MS,
	SLEEP_500MS,
	SLEEP_1S,
	SLEEP_2S,
	SLEEP_4S,
	SLEEP_8S,
	SLEEP_FOREVER
};

void hwInternalSleep(unsigned long ms);

#ifndef DOXYGEN
#define MY_CRITICAL_SECTION     ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
#endif  /* DOXYGEN */

#endif
