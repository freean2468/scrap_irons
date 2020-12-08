////////////////////////////////////////////////////////////////////////////////
// Engine에서 사용되는 헤더파일과 라이브러리, 상수등을 선언
////////////////////////////////////////////////////////////////////////////////
#ifndef _SystemDefines_H_
#define _SystemDefines_H_

#define WIN32_LEAN_AND_MEAN		// 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dxerr9.lib")
#pragma comment(lib, "winmm.lib")

// window
#include <windows.h>
#include <WindowsX.h>
#include <objbase.h>
#include <mmsystem.h>

// DirectX
#include <d3dx9.h>

// 각종
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <math.h>

// STL
#include <new>
#include <fstream>
#include <vector>
#include <list>
#include <cmath>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <set>
#include <map>
#include <cassert>

using std::bad_alloc;

const int SYSTEMWIDTH = 800;
const int SYSTEMHEIGHT = 600;

using std::ofstream;
using std::ifstream;

#define _WIN32_WINNT 0x400
#define WM_MOUSEWHEEL 0x020A

#define SYSTEM_FRAME_INTERVAL_VER_60 0.01f
#define SYSTEM_FRAME_INTERVAL_VER_30 0.02f

#endif