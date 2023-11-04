#ifndef __SYSFS_GPIO_
#define __SYSFS_GPIO_

#include <stdio.h>

#define SYSFS_GPIO_IN  0
#define SYSFS_GPIO_OUT 1

#define SYSFS_GPIO_LOW  0
#define SYSFS_GPIO_HIGH 1

#define NUM_MAXBUF  4
#define DIR_MAXSIZ  60

#define SYSFS_GPIO_DEBUG 0
#if SYSFS_GPIO_DEBUG 
	#define SYSFS_GPIO_Debug(__info,...) printf("Debug: " __info,##__VA_ARGS__)
#else
	#define SYSFS_GPIO_Debug(__info,...)  
#endif 

void LIBGPIO_GPIO_Init();
void LIBGPIO_GPIO_Exit();
int LIBGPIO_GPIO_Export(int Pin);
int LIBGPIO_GPIO_Unexport(int Pin);
int LIBGPIO_GPIO_Direction(int Pin, int Dir);
int LIBGPIO_GPIO_Read(int Pin);
int LIBGPIO_GPIO_Write(int Pin, int value);

#endif
