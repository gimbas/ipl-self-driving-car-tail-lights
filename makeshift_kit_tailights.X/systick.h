/* 
 * File:   PIC32mx_SysTick.h
 * Author: Rafael Silva
 *
 * Created on May 27, 2018, 7:02 PM
 */



#ifndef SYSTICK_H
#define SYSTICK_H

#define SYSCLOCK()            (8000000)
#define PERCLOCK()        (SYSCLOCK())
#define INSTCLOCK()       (SYSCLOCK()/4)

#include <xc.h>
#include <stdint.h>
#include <sys/attribs.h>

namespace systick
{
	volatile extern uint64_t count;

	void __attribute__((nomips16)) init(void);

	inline void __attribute__((nomips16)) delay_us(uint16_t duration)
	{
		uint32_t count_reg = 0;
		// get the count reg
		asm volatile("mfc0   %0, $9" : "=r"(count_reg));
		uint64_t timestamp = ((SYSCLOCK()/20000000) * duration) + count_reg;
        
		while(count_reg < timestamp)
			asm volatile("mfc0   %0, $9" : "=r"(count_reg));
	}

	inline void delay_ms(uint16_t duration)
	{
		uint64_t timestamp = (uint64_t)duration + count;
		while(count < timestamp);
	}
}

#endif	/* SYSTICK_H */

