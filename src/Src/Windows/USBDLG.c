/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.32                          *
*        Compiled Oct  8 2015, 11:59:02                              *
*        (c) 2015 Segger Microcontroller GmbH & Co. KG               *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
**********************************************************************
*/

// USER START (Optionally insert additional includes)
// USER END

#include "USBDLG.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_WINDOW_0 	(GUI_ID_USER + 0x00 + 0xA0)
#define ID_TEXT_0 		(GUI_ID_USER + 0x01 + 0xA0)
#define ID_BUTTON_0 	(GUI_ID_USER + 0x02 + 0xA0)
#define ID_MULTIEDIT_0 	(GUI_ID_USER + 0x03 + 0xA0)
#define ID_BUTTON_1 	(GUI_ID_USER + 0x04 + 0xA0)
#define ID_BUTTON_2 	(GUI_ID_USER + 0x05 + 0xA0)
#define ID_TEXT_1 		(GUI_ID_USER + 0x06 + 0xA0)

// USER START (Optionally insert additional defines)
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)
// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { WINDOW_CreateIndirect, "USB", ID_WINDOW_0, 0, 0, 480, 272, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "USB CDC", ID_TEXT_0, 170, 7, 150, 31, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Close", ID_BUTTON_0, 420, 8, 50, 30, 0, 0x0, 0 },
  { MULTIEDIT_CreateIndirect, "Edit", ID_MULTIEDIT_0, 15, 50, 385, 90, MULTIEDIT_SF_READONLY },
  { BUTTON_CreateIndirect, "Clear", ID_BUTTON_1, 405, 97, 60, 43, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Send", ID_BUTTON_2, 405, 50, 60, 42, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Message:", ID_TEXT_1, 20, 35, 100, 20, 0, 0x0, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

// USER START (Optionally insert additional static code)
// USER END

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;
  // USER START (Optionally insert additional variables)
  // USER END

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    //
    // Initialization of 'USB CDC'
    //
	hItem = pMsg->hWin;
	//WINDOW_SetBkColor(hItem, GUI_ORANGE);

    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
    TEXT_SetFont(hItem, GUI_FONT_32B_1);
    //
    // Initialization of 'Edit'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_MULTIEDIT_0);
    MULTIEDIT_SetText(hItem, "");
    MULTIEDIT_SetFocussable(hItem, 0);

	hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
	BUTTON_SetFocussable(hItem, 0);

	hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
	BUTTON_SetFocussable(hItem, 0);
    // USER START (Optionally insert additional code for further widget initialization)
    // USER END
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_BUTTON_0: // Notifications sent by 'Close'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_1: // Notifications sent by 'Clear'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    // USER START (Optionally insert additional code for further Ids)
    // USER END
    }
    break;
  // USER START (Optionally insert additional message handling)
  // USER END
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateUSB
*/
WM_HWIN CreateUSB(void);
WM_HWIN CreateUSB(void) {
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
