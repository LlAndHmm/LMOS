#include "string.h"
#include "vargs.h"

int vprintf(char* buff, char* format, va_list args) {
	//比对占位符和参数数量
	//
	char* str = buff;
	char buffer[10];
	char* num;
	while (*format != '\0') {
		if (*format != '%') {
			*str++ = *format++;
			continue;
		}
		//略过%
		//通过占位符判断下一个参数的类型
		format++;
		switch (*format) {
			case 'c':
				*str++ = (unsigned char) va_arg(args, int);	//4字节内存对齐
				break;
			case 'd':
				num = itoa(va_arg(args, int), buffer, 10);
				while (*num != '\0') {
					*str++ = *num++;
				}
				break;
			case 'x':
				num = itoa(va_arg(args, int), buffer, 16);
				while (*num != '\0') {
					*str++ = *num++;
				}
				break;
			default:
				*str++ = '%';	
				
		}
		format++;
	}
	*str = '\0';
	return (str - buff);
}

void printk(const char *format, ...) {
	va_list args;
	va_start(args, format);	//初始化后var_test指向可变参数部分第一个参数
	char buff[1024];
	int i = vprintf(buff, format, args);
//	buff[i] = '\0';
	console_write(buff);
	va_end(args);
}


