#pragma once
#include "Helpers.h"
#include <process.h>

unsigned int __stdcall WorldGod(void *pData);



HANDLE m_ThreadHandle = (HANDLE)_beginthreadex(NULL, 0, WorldGod, 0, 0,  (unsigned int *)&m_ThreadHandle);
