

#ifndef ADXL345_H
#define ADXL345_H

#include "stm32f7xx_hal.h"

// ADXL345 Register Definition
#define ADXL345_POWER_CTL      0x2D
#define ADXL345_DATA_FORMAT    0x31
#define ADXL345_BW_RATE        0x2C
#define ADXL345_DATAX0         0x32
#define ADXL345_DATAX1         0x33
#define ADXL345_DATAY0         0x34
#define ADXL345_DATAY1         0x35
#define ADXL345_DATAZ0         0x36
#define ADXL345_DATAZ1         0x37
#define ADXL345_FIFO_CTL       0x38
#define ADXL345_SPEED          0x0F          	// Buffer Speed - 3200Hz

// check hardware
//#define ADXL345_ACCEL_ADDRESS  0x1D          // if ALT ADDRESS = 1
#define ADXL345_ADDR  (0x53<<1)       // if ALT ADDRESS = 0

// Maximum timeout
#define ADXL345_TIMEOUT			0x3000

void Init_ACCEL_GPIO(I2C_HandleTypeDef hi2c);

void ADXL345_Init(void);

void ADXL345_Write(uint8_t reg, uint8_t data1);
uint8_t ADXL345_ReadByte(uint8_t reg);

void ADXL345_read_xyz(void);
uint16_t ADXL345_GetX_ACCEL(void);
uint16_t ADXL345_GetY_ACCEL(void);
uint16_t ADXL345_GetZ_ACCEL(void);


#endif /* ADXL345_H */

/*************************** End of file ****************************/
