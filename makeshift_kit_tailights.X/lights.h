/* 
 * File:   lights.
 * Author: gimbas
 *
 * Created on 7 de Novembro de 2019, 22:23
 */

#ifndef LIGHTS_H
#define	LIGHTS_H

#include <xc.h>
#include <stdint.h>
#include <sys/attribs.h>
#include "spi.h"

#define NUM_LIGHTS      8

extern const uint8_t color_map[360];

typedef struct light
{
    uint8_t brightness;
    uint8_t blue;
    uint8_t green;
    uint8_t red;
} light_t;

namespace lights
{
    void init();
    void set(uint16_t index, uint8_t red, uint8_t green, uint8_t blue, uint8_t brightness = 0x1F, uint8_t update = 0);
	void update();
}

#endif	/* LIGHTS_H */

