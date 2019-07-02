/*
J. Bajic - 2018.
*/

#ifndef MP3_H
#define MP3_H

#include "DIALOG.h"

#define STOP 0
#define PLAY 1
#define PAUSE 2
#define BACKWARD 3
#define FORWARD 4

void MP3_MountSD(void);
void MP3_Open(const char *name);
void MP3_Close(void);
void MP3_Play(const char *name);
void MP3_SetState(uint8_t state);
void MP3_Exec(void);
void PopulateMP3List(WM_HWIN handle);

#endif /* MP3_H */
