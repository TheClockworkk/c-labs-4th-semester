// Microsoft Visual C++ generated resource script.
//
#include "resource.h"

#define APSTUDIO_READONLY_SYMBOLS
/////////////////////////////////////////////////////////////////////////////
//
// Generated from the TEXTINCLUDE 2 resource.
//
#ifndef APSTUDIO_INVOKED
#include "targetver.h"
#endif
#define APSTUDIO_HIDDEN_SYMBOLS
#include "windows.h"
#undef APSTUDIO_HIDDEN_SYMBOLS

/////////////////////////////////////////////////////////////////////////////
#undef APSTUDIO_READONLY_SYMBOLS

/////////////////////////////////////////////////////////////////////////////
// Русский (Россия) resources

#if !defined(AFX_RESOURCE_DLL) || defined(AFX_TARG_RUS)
LANGUAGE LANG_RUSSIAN, SUBLANG_DEFAULT

/////////////////////////////////////////////////////////////////////////////
//
// Icon
//

// Icon with lowest ID value placed first to ensure application icon
// remains consistent on all systems.
IDI_LAB31               ICON                    "Timer.ico"

IDI_SMALL               ICON                    "small.ico"


/////////////////////////////////////////////////////////////////////////////
//
// Menu
//

IDC_LAB31 MENU
BEGIN
POPUP "&Файл"
BEGIN
MENUITEM "Вы&ход", IDM_EXIT
END
POPUP "&Справка"
BEGIN
MENUITEM "&О программе...", IDM_ABOUT
END
POPUP "Опции"
BEGIN
MENUITEM "Задать текущее время", ID_32774
END
END


/////////////////////////////////////////////////////////////////////////////
//
// Accelerator
//

IDC_LAB31 ACCELERATORS
BEGIN
"?", IDM_ABOUT, ASCII, ALT
"/", IDM_ABOUT, ASCII, ALT
END


/////////////////////////////////////////////////////////////////////////////
//
// Dialog
//

IDD_ABOUTBOX DIALOGEX 0, 0, 170, 62
STYLE DS_SETFONT | DS_MODALFRAME | DS_FIXEDSYS | WS_POPUP | WS_CAPTION | WS_SYSMENU
CAPTION "О программе Timer"
FONT 8, "MS Shell Dlg", 0, 0, 0x1
BEGIN
ICON            IDR_MAINFRAME, IDC_STATIC, 14, 14, 21, 20
LTEXT           "Timer, Версия 2.0", IDC_STATIC, 42, 14, 114, 8, SS_NOPREFIX
LTEXT           "(c) 2020", IDC_STATIC, 42, 26, 114, 8
DEFPUSHBUTTON   "ОК", IDOK, 113, 41, 50, 14, WS_GROUP
END


/////////////////////////////////////////////////////////////////////////////
//
// DESIGNINFO
//

#ifdef APSTUDIO_INVOKED
GUIDELINES DESIGNINFO
BEGIN
IDD_ABOUTBOX, DIALOG
BEGIN
LEFTMARGIN, 7
RIGHTMARGIN, 163
TOPMARGIN, 7
BOTTOMMARGIN, 55
END
END
#endif    // APSTUDIO_INVOKED


#ifdef APSTUDIO_INVOKED
/////////////////////////////////////////////////////////////////////////////
//
// TEXTINCLUDE
//

1 TEXTINCLUDE
BEGIN
"resource.h\0"
END

2 TEXTINCLUDE
BEGIN
"#ifndef APSTUDIO_INVOKED\r\n"
"#include ""targetver.h""\r\n"
"#endif\r\n"
"#define APSTUDIO_HIDDEN_SYMBOLS\r\n"
"#include ""windows.h""\r\n"
"#undef APSTUDIO_HIDDEN_SYMBOLS\r\n"
"\0"
END

3 TEXTINCLUDE
BEGIN
"\r\n"
"\0"
END

#endif    // APSTUDIO_INVOKED


/////////////////////////////////////////////////////////////////////////////
//
// String Table
//

STRINGTABLE
BEGIN
IDS_APP_TITLE           "Timer"
IDC_LAB31               "Timer"
END

#endif    // Русский (Россия) resources
/////////////////////////////////////////////////////////////////////////////



#ifndef APSTUDIO_INVOKED
/////////////////////////////////////////////////////////////////////////////
//
// Generated from the TEXTINCLUDE 3 resource.
//


/////////////////////////////////////////////////////////////////////////////
#endif    // not APSTUDIO_INVOKED
