#include "console.h"
#include "types.h"
#include "vargs.h"

// 内核的打印函数
void printk(const char *format, ...);

// 内核的打印函数 带颜色
void printk_color(color_t back, color_t fore, const char *format, ...);
