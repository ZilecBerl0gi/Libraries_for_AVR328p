/*
 * OLED128x64.h
 *
 * Created: 06.04.2022 20:40:36
 *  Author: Mikhail
 */ 


#ifndef OLED128X64_H_
#define OLED128X64_H_
#include "I2C.h"
#include <stdint.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <string.h>
#define SSD1306_DEFAULT_ADDRESS 0x78
#define SSD1306_SETCONTRAST 0x81
#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define SSD1306_DISPLAYALLON 0xA5
#define SSD1306_NORMALDISPLAY 0xA6
#define SSD1306_INVERTDISPLAY 0xA7
#define SSD1306_DISPLAYOFF 0xAE
#define SSD1306_DISPLAYON 0xAF
#define SSD1306_SETDISPLAYOFFSET 0xD3
#define SSD1306_SETCOMPINS 0xDA
#define SSD1306_SETVCOMDETECT 0xDB
#define SSD1306_SETDISPLAYCLOCKDIV 0xD5
#define SSD1306_SETPRECHARGE 0xD9
#define SSD1306_SETMULTIPLEX 0xA8
#define SSD1306_SETLOWCOLUMN 0x00
#define SSD1306_SETHIGHCOLUMN 0x10
#define SSD1306_SETSTARTLINE 0x40
#define SSD1306_MEMORYMODE 0x20
#define SSD1306_COLUMNADDR 0x21
#define SSD1306_PAGEADDR   0x22
#define SSD1306_COMSCANINC 0xC0
#define SSD1306_COMSCANDEC 0xC8
#define SSD1306_SEGREMAP 0xA0
#define SSD1306_CHARGEPUMP 0x8D
#define SSD1306_SWITCHCAPVCC 0x2
#define SSD1306_NOP 0xE3

#define SSD1306_WIDTH 128
#define SSD1306_HEIGHT 64
#define SSD1306_BUFFERSIZE (SSD1306_WIDTH*SSD1306_HEIGHT)/8

#define FAST_SPEED 1
#define LOW_SPEED 0
class OLED
{
public:
void init(int freq, bool Speed);
void drawPixel(uint8_t pos_x, uint8_t pos_y, bool pixel_status = 1);
void drawRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, bool fill = 1);
void drawRectangleFillIn(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, bool fill = 1);
void drawQuadrilateral(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1,uint8_t x2, uint8_t y2, uint8_t x3, uint8_t y3, bool fill = 1);
void drawQuadrilateralFillIn(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1,uint8_t x2, uint8_t y2, uint8_t x3, uint8_t y3, bool fill = 1);
void drawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, bool fill = 1);
void fastLineV(uint8_t x, uint8_t y0, uint8_t y1, bool fill = 1);
void fastLineH(uint8_t y, uint8_t x0, uint8_t x1, bool fill = 1);
void drawCircle(uint8_t x, uint8_t y, uint8_t radius, bool fill = 1);
void drawCircleFillIn(uint8_t x, uint8_t y, uint8_t Radius, bool fill = 1);
void setContrast(uint8_t value);
void update();
void clear();
void invert(bool inv);
void setCursor(uint8_t x, uint8_t y);
void print(const char str[]);
void print(long long Number);
void print(int Number);
void print(double Number);
void print(double Number, int Precision);
void home();
void setAutoPrtLN(bool state);
void setCursorStr(uint8_t x, uint8_t y);
void drawBITMAP(const int *BITMAP, int Width, int Height, int x, int y, bool Invert);
void invertText(bool state);
private:
uint8_t buffer[SSD1306_BUFFERSIZE];
I2C oled_;
int freq_;
uint8_t _x, _y;
unsigned char port_;
void sendCommand(uint8_t Command);
void sendFramebuffer(uint8_t *buffer);
uint8_t getFont(uint8_t font, uint8_t row);
bool AutoPrtLn;
uint8_t inv;
};




#endif /* OLED128X64_H_ */