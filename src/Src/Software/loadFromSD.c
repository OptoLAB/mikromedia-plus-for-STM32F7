#include "fatfs.h"
#include "GUI.h"
#include "SSD1963.h"
#include "loadFromSD.h"

//#include "stm32f7xx_hal.h"


unsigned char img_lines[480*8*3]={0};

BMP_INFO loadBMPfromSD(const char *file_name)
{
	FRESULT res;
	FATFS myFAT;
	FIL myFile;
	BMP_INFO BMP;
	char data[4];
	unsigned int highByte=0, lowByte=0, i=0, j=0, k=0, byteCount;


	FATFS_LinkDriver(&SD_Driver, SDPath);
	res=f_mount(&myFAT, SDPath, 1);
	if(res==FR_OK)
	{
		f_open(&myFile, file_name, FA_READ);
		  //size
		f_lseek(&myFile, BMP_SIZE);
		f_read(&myFile, &data, 4, &byteCount);
		BMP.size=(data[3]<<24)|(data[2]<<16) |(data[1]<<8)|(data[0]);
		  //offset
		res=f_lseek(&myFile, BMP_OFFSET);
		res=f_read(&myFile, &data, 4, &byteCount);
		BMP.offset=(data[3]<<24)|(data[2]<<16)|(data[1]<<8)|(data[0]);
		  //width
		f_lseek(&myFile, BMP_WIDTH);
		f_read(&myFile, &data, 4, &byteCount);
		BMP.width=(data[3]<<24)|(data[2]<<16)|(data[1]<<8)|(data[0]);

		f_lseek(&myFile, BMP_HEIGHT);
		f_read(&myFile, &data, 4, &byteCount);
		BMP.height=(data[3]<<24)|(data[2]<<16)|(data[1]<<8)|(data[0]);

		f_lseek(&myFile, BMP_BPP);
		f_read(&myFile, &data, 4, &byteCount);
		BMP.bpp=(data[1]<<8)|(data[0]);


		SSD1963_WriteCommand(SSD1963_SET_ADDRESS_MODE); //rotation, see p.18
		SSD1963_WriteData(0x00C0);

	 	SSD1963_WriteCommand(SSD1963_WRITE_MEMORY_START);

		 f_lseek(&myFile, BMP.offset);//480*8*2
		 for(i=0; i<34; i++)
		 {
		 	uint16_t index=0;
		 	res=f_read(&myFile, &img_lines, 7680, &byteCount);//480*8*2
		 	for(k=0; k<8; k++) // reads in blocks of 8 line to reduce memory consumption
		 	{
		 		index=k*960;

		 		for(j = 0; j < 960; j++)//480*2 // x2 for 16 bpp
		 		{
		 			highByte=img_lines[index+(959-j)]; //480*2
		 			j++;
		 			lowByte=img_lines[index+(959-j)];
		 			//j++;

		 			SSD1963_WriteData((highByte<<8)|(lowByte));
		 		}
		 	}
		 }

		 SSD1963_WriteCommand(SSD1963_SET_ADDRESS_MODE);
		 SSD1963_WriteData(0x0000);
		 f_close(&myFile);
		 f_mount(0, SDPath, 1);
	}

	FATFS_UnLinkDriver(SDPath);
	return BMP;
}

void DisplayImageInfo(BMP_INFO bmp)
{
	char data[10];
	GUI_SetLineStyle(100);
	GUI_SetColor(GUI_ORANGE);
	GUI_DrawRect(5, 5, 110, 61);
	GUI_SetColor(GUI_BLACK);
	GUI_FillRect(5, 5, 110, 61);
	GUI_SetColor(GUI_ORANGE);
	GUI_DispStringAt("Image size: ", 10, 10);
	sprintf((char*)data, "%d", (unsigned int)(bmp.size/1024));
	GUI_DispStringAt(data, 80, 10);

	GUI_DispStringAt("Image offset: ", 10, 20);
	sprintf((char*)data, "%lu", bmp.offset);
	GUI_DispStringAt(data, 90, 20);

	GUI_DispStringAt("Image width: ", 10, 30);
	sprintf((char*)data, "%lu", bmp.width);
	GUI_DispStringAt(data, 85, 30);

	GUI_DispStringAt("Image height: ", 10, 40);
	sprintf((char*)data, "%lu", bmp.height);
	GUI_DispStringAt(data, 90, 40);

	GUI_DispStringAt("Image bpp: ", 10, 50);
	sprintf((char*)data, "%d", bmp.bpp);
	GUI_DispStringAt(data, 72, 50);

}
