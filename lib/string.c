#include "types.h"

void memcpy(uint8_t *dest, const uint8_t *src, uint32_t len) {
	 for (; len != 0; len--) {
        *dest++ = *src++;
    }
}

void memset(void *dest, uint8_t val, uint32_t len) {
	uint8_t *dst = (uint8_t *)dest;

    for ( ; len != 0; len--) {
        *dst++ = val;
    }
}

void bzero(void *dest, uint32_t len) {
	 memset(dest, 0, len);
}


int strcmp(const char *str1, const char *str2) {
	//第一个字符串大于第二个字符串的时候返回正值
	//小于返回负值，等于返回0 
	while (*str1 != '\0' && *str2 != '\0') {
		if (*str1 == *str2) {
			str1++;
			str2++;
		} else if (*str1 < *str2) {
			return -1;
		} else {
			return 1;
		}
	}
	if (*str2 != '\0') {		//条件二为真
		return -1;
	} else {		//条件二为假
		if (*str1 == '\0') {		//条件一为假
			return 0;
		} else {		//条件一为真
			return 1;
		}
	}
}

int strlen(const char *src) {
	int length = 0;
	while (*src++ != '\0') {
		length++;
	}
	return length;
}

char* strcpy(char *dest, const char *src) {
	//dest不够长时情况未处理
	int src_len = strlen(src);
	for (int i = 0; i < src_len; i++) {
		*(dest + i) = *(src + i);
	}
	*(dest + src_len) = '\0';
	
	return dest;
}

char* strcat(char *dest, const char *src) {
	int dest_len = strlen(dest);
	int src_len = strlen(src);
	
	for (int i = dest_len; i < dest_len + src_len + 1; i++) {
		*(dest + i) = *(src++);
	}
	
	return dest;
}
