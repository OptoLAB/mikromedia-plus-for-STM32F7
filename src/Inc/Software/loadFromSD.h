#ifndef LOADFROMSD_H
#define LOADFROMSD_H



#define BMP_SIZE 0x02
#define BMP_OFFSET 0x0A
#define BMP_WIDTH 0x12
#define BMP_HEIGHT 0x16
#define BMP_BPP 0x1C

typedef struct {

	unsigned long size;
	unsigned long offset;
	unsigned long width;
	unsigned long height;
	unsigned int bpp;


} BMP_INFO;


BMP_INFO loadBMPfromSD(const char *file_name);
void DisplayImageInfo(BMP_INFO bmp);

#endif
