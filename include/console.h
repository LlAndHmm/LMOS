#ifndef INCLUDE_CONSOLE_H_
#define INCLUDE_CONSOLE_H_

#include "types.h"

typedef enum color {
	black = 0,
	blue = 1,
	green = 2,
	cyan = 3,		//青色
	red = 4,
	magenta = 5,		//品红
	brown = 6,
	white = 7,
} color_t;			//枚举类型占四个字节

//清屏
void console_clear();

//输出一个字符，颜色自选
void console_putc_color(char c, color_t back, color_t fore);

// 屏幕打印一个以'\0'结尾的字符串，默认黑底白字
void console_write(char *cstr);

// 屏幕打印一个以'\0'结尾的字符串，带颜色
void console_write_color(char *cstr, color_t back, color_t fore);

// 屏幕输出一个十六进制的整型数
void console_write_hex(uint32_t n, color_t back, color_t fore);

// 屏幕输出一个十进制的整型数
void console_write_dec(uint32_t n, color_t back, color_t fore);

#endif //INCLUDE_CONSOLE_H_
