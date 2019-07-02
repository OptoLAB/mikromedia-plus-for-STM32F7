/*
J. Bajic - 2018.
*/

#include "stm32f7xx_hal.h"
#include "VS1053.h"
#include "MP3.h"
#include "fatfs.h"
#include "GUI.h"
#include "MP3DLG.h"
#include "string.h"

#define BYTES_2_WRITE 32
#define BUFFER_SIZE 256
uint8_t mp3_buffer[BUFFER_SIZE];
unsigned long file_size=0;
unsigned long Buffer_count, Total_Buffers;
char song_path[270]={0};
FRESULT res;
FATFS mp3FAT;
FIL song;

WM_HWIN hwin;
static TCHAR song_name[_MAX_LFN]={0};
uint8_t MP3_state=0;
int num_of_songs=0, current_song, prev_song;



void MP3_MountSD(void)
{
	FATFS_LinkDriver(&SD_Driver, SDPath);
	res=f_mount(&mp3FAT, SDPath, 1);
}

void MP3_Open(const char *name)
{
	int ind=0;
	MP3_MountSD();

	ind=LISTBOX_GetSel(WM_GetDialogItem(hwin, (GUI_ID_USER + 0x08 + 0x90)));
	//song_name="";
	LISTBOX_GetItemText(WM_GetDialogItem(hwin, (GUI_ID_USER + 0x08 + 0x90)), ind, song_name, sizeof(song_name));

	sprintf((char*)song_path, "%s/%s", (char*)"music", (char*)song_name);
	TEXT_SetText(WM_GetDialogItem(hwin, (GUI_ID_USER + 0x0B + 0x90)),song_path);

	f_open(&song, name, FA_READ);
	//size
	file_size=f_size(&song);
	Buffer_count=0;
	Total_Buffers = file_size / BUFFER_SIZE;

	VS1053_SetVolume(50, 50);
	VS1053_ResetTime();

}

void MP3_Close(void)
{
	file_size=0;
	f_close(&song);
	f_mount(0, SDPath, 1);
	FATFS_UnLinkDriver(SDPath);
}

void MP3_Play(const char *name)
{
	unsigned int byteCount, i;
	if(file_size==0)
	{
		MP3_Open(name);

	}
	if(file_size!=0)
	{
		if(file_size >= BUFFER_SIZE)
		{     // while there is still data, send it to mp3 codec chip
			f_read(&song, &mp3_buffer, BUFFER_SIZE, &byteCount);

			for (i=0; i<BUFFER_SIZE/BYTES_2_WRITE; i++)
			{
				VS1053_SDI_Write_32(mp3_buffer + i*BYTES_2_WRITE);
			}

			file_size -= BUFFER_SIZE;
			Buffer_count ++;
		}

		if (file_size < BUFFER_SIZE)
		{     // finish playing file
			f_read(&song, &mp3_buffer, file_size, &byteCount);

			for (i=0; i<file_size; i++)
			{
				VS1053_SDI_Write(mp3_buffer[i]);
			}
			Buffer_count ++;
			MP3_state=FORWARD;
		}
	}
}
void PopulateMP3List(WM_HWIN handle)
{
	FRESULT fr;     /* Return value */
	DIR dj;         /* Directory search object */
	FILINFO fno;    /* File information */
	hwin=handle;

	num_of_songs=0;
	strcpy(fno.fname,song_name);
    fno.fsize = _MAX_LFN - 1;

	fr = f_findfirst(&dj, &fno, "music", "*.mp3");  /* Start to search for mp3 files */

	while (fr == FR_OK && fno.fname[0])
	{         /* Repeat while an item is found */
	   num_of_songs++;
	   LISTBOX_AddString(WM_GetDialogItem(hwin, (GUI_ID_USER + 0x08 + 0x90)), fno.fname);
	   fr = f_findnext(&dj, &fno);               /* Search for next item */

	}

	f_closedir(&dj);
}
void MP3_SetState(uint8_t state)
{
	MP3_state=state;
}
void MP3_Exec(void)
{

 int val=0;



	switch (MP3_state)
	{
		case STOP:
			MP3_Close();
			break;
		case PLAY:
			MP3_Play(song_path);
			val=(Buffer_count * 100) / Total_Buffers;
			PROGBAR_SetValue(WM_GetDialogItem(hwin, (GUI_ID_USER + 0x06 + 0x90)), val);
			break;
		case PAUSE:
			break;
		case BACKWARD:
			MP3_Close();
			LISTBOX_DecSel(WM_GetDialogItem(hwin, (GUI_ID_USER + 0x08 + 0x90)));
			prev_song=current_song;
			current_song=LISTBOX_GetSel(WM_GetDialogItem(hwin, (GUI_ID_USER + 0x08 + 0x90)));
			if(current_song==prev_song)current_song=num_of_songs-1;
			LISTBOX_SetItemSel(WM_GetDialogItem(hwin, (GUI_ID_USER + 0x08 + 0x90)), current_song, 1);
			LISTBOX_SetSel(WM_GetDialogItem(hwin, (GUI_ID_USER + 0x08 + 0x90)), current_song);
			MP3_state=PLAY;
			break;
		case FORWARD:
			MP3_Close();
			LISTBOX_IncSel(WM_GetDialogItem(hwin, (GUI_ID_USER + 0x08 + 0x90)));
			prev_song=current_song;
			current_song=LISTBOX_GetSel(WM_GetDialogItem(hwin, (GUI_ID_USER + 0x08 + 0x90)));
			if(current_song==prev_song)current_song=0;
			LISTBOX_SetItemSel(WM_GetDialogItem(hwin, (GUI_ID_USER + 0x08 + 0x90)), current_song, 1);
			LISTBOX_SetSel(WM_GetDialogItem(hwin, (GUI_ID_USER + 0x08 + 0x90)), current_song);
			MP3_state=PLAY;
			break;

	}
}
