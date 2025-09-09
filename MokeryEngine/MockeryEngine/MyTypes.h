#pragma once
#include <windows.h>
struct DrawSet 
{								
	HDC hDC;					
	HDC hDCBack;				
	HBITMAP backBuffer;
};
