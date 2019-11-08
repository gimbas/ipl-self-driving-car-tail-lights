/* 
 * File:   lights.
 * Author: gimbas
 *
 * Created on 7 de Novembro de 2019, 22:23
 */

#include "lights.h"

const uint8_t color_map[360] = { // sine fade technique to cycle rgb led
  0, 0, 0, 0, 0, 1, 1, 2, 2, 3, 4, 5, 6, 7, 8, 9, 11, 12, 13, 15, 17, 18, 20, 22, 24, 26, 28, 30, 32, 35, 37, 39,
 42, 44, 47, 49, 52, 55, 58, 60, 63, 66, 69, 72, 75, 78, 81, 85, 88, 91, 94, 97, 101, 104, 107, 111, 114, 117, 121, 124, 127, 131, 134, 137,
141, 144, 147, 150, 154, 157, 160, 163, 167, 170, 173, 176, 179, 182, 185, 188, 191, 194, 197, 200, 202, 205, 208, 210, 213, 215, 217, 220, 222, 224, 226, 229,
231, 232, 234, 236, 238, 239, 241, 242, 244, 245, 246, 248, 249, 250, 251, 251, 252, 253, 253, 254, 254, 255, 255, 255, 255, 255, 255, 255, 254, 254, 253, 253,
252, 251, 251, 250, 249, 248, 246, 245, 244, 242, 241, 239, 238, 236, 234, 232, 231, 229, 226, 224, 222, 220, 217, 215, 213, 210, 208, 205, 202, 200, 197, 194,
191, 188, 185, 182, 179, 176, 173, 170, 167, 163, 160, 157, 154, 150, 147, 144, 141, 137, 134, 131, 127, 124, 121, 117, 114, 111, 107, 104, 101, 97, 94, 91,
 88, 85, 81, 78, 75, 72, 69, 66, 63, 60, 58, 55, 52, 49, 47, 44, 42, 39, 37, 35, 32, 30, 28, 26, 24, 22, 20, 18, 17, 15, 13, 12,
 11, 9, 8, 7, 6, 5, 4, 3, 2, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

light_t lights_buffer[NUM_LIGHTS];

void lights::init()
{
    for (int i = 0; i < NUM_LIGHTS; i++) 
    {
        lights_buffer[i].brightness = 0x1F;
        lights_buffer[i].blue = 0x00;
        lights_buffer[i].green = 0x00;
        lights_buffer[i].red = 0x00;
    }
}

void lights::set(uint16_t index, uint8_t red, uint8_t green, uint8_t blue, uint8_t brightness, uint8_t update)
{
    if(index >= NUM_LIGHTS) return;
    
    lights_buffer[index].brightness = brightness;
    lights_buffer[index].blue = blue;
    lights_buffer[index].green = green;
    lights_buffer[index].red = red;
    
    if(update) lights::update();
}

void lights::update()
{
    uint8_t packet[4] = 
    {
        0x00, 
        0x00, 
        0x00, 
        0x00
    };
    
    spi::transfer(packet, packet, 4);
    
    for (int i = 0; i < NUM_LIGHTS; i++) 
    {
        packet[0] = 0xE0 | lights_buffer[i].brightness;
        packet[1] = lights_buffer[i].blue;
        packet[2] = lights_buffer[i].green;
        packet[3] = lights_buffer[i].red;
        spi::transfer(packet, packet, 4);
    }
    
    packet[0] = 0x00;
    packet[1] = 0x00;
    packet[2] = 0x00;
    packet[3] = 0x00;
    
    spi::transfer(packet, packet, 4);
}