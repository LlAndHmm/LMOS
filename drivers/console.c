#include "types.h"
#include "console.h"

// VGA 的显示缓冲的起点是 0xB8000
static uint16_t *video_memory = (uint16_t *)0xB8000;

// 屏幕"光标"的坐标
static uint8_t cursor_x = 0;
static uint8_t cursor_y = 0;

//滚屏
static void scroll() {
	uint8_t attribute_byte = (0 << 4) | (15 & 0x0F);
	uint16_t blank = (0x20) | (attribute_byte << 8);
	
	if (cursor_y >= 25) {
		//将1-24行向上移动一行，覆盖掉第0行
		for (int i = 0; i < 24 * 80; i++) {
			video_memory[i] = video_memory[i + 80];
		}
		//最后一行用空格填充
		for (int i = 80 * 24; i < 80 * 25; i++) {
			video_memory[i] = blank;
		}

		cursor_y--;
	}
	
}

//移动光标
static void move_cursor() {
	// 屏幕是 80 字节宽
    uint16_t cursorLocation = cursor_y * 80 + cursor_x;
    
    // 在这里用到的两个内部寄存器的编号为14与15，分别表示光标位置
    // 的高8位与低8位。

    outb(0x3D4, 14);                    // 告诉 VGA 我们要设置光标的高字节
    outb(0x3D5, cursorLocation >> 8);   // 发送高 8 位
    outb(0x3D4, 15);                    // 告诉 VGA 我们要设置光标的低字节
    outb(0x3D5, cursorLocation);        // 发送低 8 位
}

//清屏
void console_clear() {
	//用白底黑字的“空格符”覆盖整个屏幕的显示区域
	uint8_t attribute_byte = (0 << 4) | (15 & 0x0F);
	uint16_t blank = (0x20) | (attribute_byte << 8);
	
	for (int i = 0; i < 25 * 80; i++) {
		video_memory[i] = blank;
	}
	
	cursor_x = 0;
	cursor_y = 0;
	move_cursor();
}

//输出一个字符，颜色自选
void console_putc_color(char c, color_t back, color_t fore) {
	uint8_t back_color = (uint8_t)back;
 	uint8_t fore_color = (uint8_t)fore;
	
	uint8_t attribute_byte = (back_color << 4) | (fore_color & 0x0F);
	uint16_t attribute = attribute_byte << 8;
	
	// 0x08 是退格键的 ASCII 码, 0x09 是tab 键的 ASCII 码
	if (c == 0x08 && cursor_x > 0) {
		cursor_x--;
	} else if (c == '\n') {
		cursor_x = 0;
		cursor_y++;
	} else if (c >= ' ') {
		//8086机器采用小端法存储数据
		video_memory[cursor_y * 80 + cursor_x] = attribute | c;	
		cursor_x++;	
	}
	
	if (cursor_x >= 80) {
		cursor_x = 0;
		cursor_y++;
	}
	
	scroll();
	move_cursor();
}

// 屏幕打印一个以'\0'结尾的字符串，默认黑底白字
void console_write(char *cstr) {
	while (*cstr != '\0') {
		console_putc_color(*cstr++, black, white);
	}
}

// 屏幕打印一个以'\0'结尾的字符串，带颜色
void console_write_color(char *cstr, color_t back, color_t fore) {
	while (*cstr != '\0') {
		console_putc_color(*cstr++, back, fore);
	} 
}

// 屏幕输出一个十进制的整型数
void console_write_dec(uint32_t n, color_t back, color_t fore) {

	char digit[10];
	int length = 0;		//记录整型数有多少位

	while (n != 0) {
		//将分离的位转换为ascii码
		digit[length] = (n % 10) + 48;		
		n /= 10;
		length++;
	}	

	for (int i = length - 1; i >= 0; i--) {
		console_putc_color(digit[i], black, white);
	}
	
}


