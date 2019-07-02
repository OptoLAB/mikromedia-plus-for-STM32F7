

#include "ADXL345.h"

uint16_t accel_x=0, accel_y=0, accel_z=0;
unsigned char id=0;

I2C_HandleTypeDef hi2c;

void Init_ACCEL_GPIO(I2C_HandleTypeDef i2c_handle)
{
	hi2c=i2c_handle;
}



void ADXL345_Write(uint8_t reg, uint8_t val)
{
	uint8_t	txbuf[2];

	txbuf[0]=reg;
	txbuf[1]=val;

	while(HAL_I2C_Master_Transmit(&hi2c, ADXL345_ADDR, (uint8_t *)txbuf, 2, ADXL345_TIMEOUT)!= HAL_OK);
}


uint8_t ADXL345_ReadByte(uint8_t reg)
{
	uint8_t rxbuf[1];
	rxbuf[0] = 0;

	while(HAL_I2C_Master_Transmit(&hi2c, ADXL345_ADDR, &reg, 1, ADXL345_TIMEOUT)!= HAL_OK);
	while(HAL_I2C_Master_Receive(&hi2c, ADXL345_ADDR, (uint8_t *)rxbuf, 1, ADXL345_TIMEOUT) != HAL_OK);

	return rxbuf[0];
}



void ADXL345_read_xyz(void)
{
	uint8_t rx[6];
	uint8_t address;

	address=ADXL345_DATAX0;
	
	while(HAL_I2C_Master_Transmit(&hi2c, ADXL345_ADDR, &address, 1, ADXL345_TIMEOUT)!= HAL_OK);
	while(HAL_I2C_Master_Receive(&hi2c, ADXL345_ADDR, (uint8_t *)rx, 6, ADXL345_TIMEOUT) != HAL_OK);

	accel_x=(((uint16_t)rx[1]) << 8) | rx[0];
	accel_y=(((uint16_t)rx[3]) << 8) | rx[2];
	accel_z=(((uint16_t)rx[5]) << 8) | rx[4];

}

uint16_t ADXL345_GetX_ACCEL(void)
{
	return accel_x;
}

uint16_t ADXL345_GetY_ACCEL(void)
{
	return accel_y;
}

uint16_t ADXL345_GetZ_ACCEL(void)
{
	return accel_z;
}

void ADXL345_Init(void)
{

  ADXL345_Write(ADXL345_POWER_CTL, 0x00);
  id = ADXL345_ReadByte(0x00);

  ADXL345_Write(ADXL345_DATA_FORMAT, 0x08);       // Full resolution, +/-2g, 4mg/LSB, right justified
  ADXL345_Write(ADXL345_BW_RATE, 0x0A);           // Set 100 Hz data rate
  ADXL345_Write(ADXL345_FIFO_CTL, 0x80);          // stream mode
  ADXL345_Write(ADXL345_POWER_CTL, 0x08);         // POWER_CTL reg: measurement mode
}
