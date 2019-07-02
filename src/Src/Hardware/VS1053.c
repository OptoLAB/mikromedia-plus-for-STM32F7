/*
J. Bajic - 2018.
*/

#include "VS1053.h"

SPI_HandleTypeDef hspi;


void Init_MP3_GPIO(SPI_HandleTypeDef spi_handle)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	__HAL_RCC_CRC_CLK_ENABLE();
	  /* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOD_CLK_ENABLE();
	  
	 /*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8|GPIO_PIN_10|GPIO_PIN_11, GPIO_PIN_RESET);

	  /*Configure GPIO pins : PD8 PD10 PD11 */
	GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_10|GPIO_PIN_11;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	/*Configure GPIO pins : PD9*/
    GPIO_InitStruct.Pin = GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	
    hspi=spi_handle;
}

void SPI_Write(uint8_t data)
{
	uint8_t rxbuf[1];
	rxbuf[0] = data;
	while(HAL_SPI_Transmit(&hspi, (uint8_t *)rxbuf, 1, 1000)!= HAL_OK);
}

uint8_t SPI_Read(void)
{
	uint8_t rxbuf[1];
	rxbuf[0] = 0;
	while(HAL_SPI_Receive(&hspi, (uint8_t *)rxbuf, 1, 1000)!= HAL_OK);
	return rxbuf[0];
}


void VS1053_SCI_Write(uint8_t address, uint16_t data_in)
{
  SET_MP3_BSYNC;

  CLR_MP3_CS;                    // select MP3 SCI
  SPI_Write(VS1053_WRITE_CODE);
  SPI_Write(address);
  SPI_Write(Hi(data_in));       // high byte
  SPI_Write(Lo(data_in));       // low byte
  SET_MP3_CS;                    // deselect MP3 SCI
  while (DREQ == 0);             // wait until DREQ becomes 1, see MP3 codec datasheet, Serial Protocol for SCI
}

void VS1053_SCI_Read(uint8_t start_address, uint8_t words_count, uint16_t *data_buffer)
{
  uint16_t temp;

  CLR_MP3_CS;                    // select MP3 SCI
  SPI_Write(VS1053_READ_CODE);
  SPI_Write(start_address);

  while (words_count--) {        // read words_count words byte per byte
    temp = SPI_Read();
    temp <<= 8;
    temp += SPI_Read();
    *(data_buffer++) = temp;
  }
  SET_MP3_CS;                   // deselect MP3 SCI
  while (DREQ == 0);             // wait until DREQ becomes 1, see MP3 codec datasheet, Serial Protocol for SCI
}

void VS1053_SDI_Write(char data_)
{

  SET_MP3_CS;
  CLR_MP3_BSYNC;

  while (DREQ == 0);             // wait until DREQ becomes 1, see MP3 codec datasheet, Serial Protocol for SCI

  SPI_Write(data_);
  SET_MP3_BSYNC;
}

void VS1053_SDI_Write_32(uint8_t *data_)
{
  uint8_t i;

  SET_MP3_CS;
  CLR_MP3_BSYNC;

  while (DREQ == 0);             // wait until DREQ becomes 1, see MP3 codec datasheet, Serial Protocol for SCI

  for (i=0; i<32; i++)
  SPI_Write(data_[i]);
  SET_MP3_BSYNC;
}

void VS1053_ResetTime(void)
{
  VS1053_SCI_Write(VS1053_DECODE_TIME_ADDR, 0);
}

void VS1053_GetDecodeTime(uint16_t *time)
{
  VS1053_SCI_Read(VS1053_DECODE_TIME_ADDR, 1, time);
}


void VS1053_SetVolume(uint8_t left, uint8_t right)
{
  uint16_t volume;

  volume = (left<<8) + right;             // calculate value
  VS1053_SCI_Write(VS1053_VOL_ADDR, volume);    // Write value to VOL register
}

void VS1053_SetDefaultMode(void)
{
  SET_MP3_BSYNC;
  SET_MP3_CS;

  // Hardware reset
  CLR_MP3_RST;
  HAL_Delay(10);
  SET_MP3_RST;

  while (DREQ == 0);

  VS1053_SCI_Write(VS1053_MODE_ADDR, 0x0800);
  VS1053_SCI_Write(VS1053_BASS_ADDR, 0x7A00);
  VS1053_SCI_Write(VS1053_CLOCKF_ADDR, 0xC000);   // default 12 288 000 Hz

  // Maximum volume is 0x00 and total silence is 0xFE.
}

void VS1053_Init(void)
{
	SET_MP3_CS;
	SET_MP3_RST;
	CLR_MP3_BSYNC;
	SET_MP3_BSYNC;

	hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
	HAL_SPI_Init(&hspi);
    VS1053_SetDefaultMode();
    hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
    HAL_SPI_Init(&hspi);

    VS1053_SetVolume(50, 50);
    VS1053_ResetTime();
}



