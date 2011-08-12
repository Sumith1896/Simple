#pragma once

//includes for windows functions and asserts
#include <stdio.h>
#include <windows.h>
#include <assert.h>
#include <math.h>

//Direct3D includes
#include <d3d9.h>
#include <d3dx9.h>
#include <dxerr.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#pragma warning (error: 4715)  //treat warning 4715 as an error (not all paths defined)
#pragma warning (disable: 4996) //This function or variable may be unsafe. Consider using strcpy_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS.

enum BlockType { BLOCK_NULL, BLOCK_BLANK, BLOCK_DIRT, BLOCK_ROCK, BLOCK_GRASS };

//////////////////////////////////////////////////////////////////////////
//Vertex Formats
//////////////////////////////////////////////////////////////////////////
#define FVF_SIMPLE (D3DFVF_XYZ)
#define FVF_SIMPLETEX (D3DFVF_XYZ | D3DFVF_TEX1)
#define FVF_COLOR (D3DFVF_XYZ | D3DFVF_DIFFUSE)
#define FVF_NORMAL (D3DFVF_XYZ | D3DFVF_NORMAL)
#define FVF_NORMAL_TEX (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)
#define FVF_NORMAL_TEX2 (D3DFVF_XYZ | D3DFVF_NORMAL |  D3DFVF_TEX2)
#define FVF_NORMAL_TEX3 (D3DFVF_XYZ | D3DFVF_NORMAL |  D3DFVF_TEX3)
#define FVF_NORMAL_TEX4 (D3DFVF_XYZ | D3DFVF_NORMAL |  D3DFVF_TEX4)
#define FVF_COLOR_NORMAL_TEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_NORMAL | D3DFVF_TEX1)
#define FVF_COLOR_NORMAL_TEX2 (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_NORMAL |  D3DFVF_TEX2)
#define FVF_COLOR_NORMAL_TEX3 (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_NORMAL |  D3DFVF_TEX3)
#define FVF_COLOR_NORMAL_TEX4 (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_NORMAL |  D3DFVF_TEX4)

struct VoxelPosition
{
	int		nX;
	int		nY;
	int		nZ;
};
struct SimpleVertex
{
	float _x, _y, _z;

	char pad[4];	//128bit alligned
};

struct SimpleVertexTex
{
	float _x, _y, _z;
	float _u, _v;
};


struct ColorVertex
{
	float _x, _y, _z;
	unsigned long _color;
};

struct NormalVertex
{
	float _x, _y, _z;
	float _nx, _ny, _nz;

	char pad[8];	//256bit alligned
};

struct NormalTexVertex
{
	float _x, _y, _z;
	float _nx, _ny, _nz;
	float _u, _v;
};

struct NormalTex2Vertex
{
	float _x, _y, _z;
	float _nx, _ny, _nz;
	float _u1, _v1;
	float _u2, _v2;
};

struct NormalTex3Vertex
{
	float _x, _y, _z;
	float _nx, _ny, _nz;
	float _u1, _v1;
	float _u2, _v2;
	float _u3, _v3;
};

struct NormalTex4Vertex
{
	float _x, _y, _z;
	float _nx, _ny, _nz;
	float _u1, _v1;
	float _u2, _v2;
	float _u3, _v3;
	float _u4, _v4;
};

struct ColorNormalTexVertex
{
	float _x, _y, _z;
	unsigned long _color;
	float _nx, _ny, _nz;
	float _u, _v;
};

struct ColorNormalTex2Vertex
{
	float _x, _y, _z;
	unsigned long _color;
	float _nx, _ny, _nz;
	float _u1, _v1;
	float _u2, _v2;
};

struct ColorNormalTex3Vertex
{
	float _x, _y, _z;
	unsigned long _color;
	float _nx, _ny, _nz;
	float _u1, _v1;
	float _u2, _v2;
	float _u3, _v3;
};

struct ColorNormalTex4Vertex
{
	float _x, _y, _z;
	unsigned long _color;
	float _nx, _ny, _nz;
	float _u1, _v1;
	float _u2, _v2;
	float _u3, _v3;
	float _u4, _v4;
};

//strict error checking
#ifdef _DEBUG
#ifndef STRICT
#define STRICT
#endif
#else
#ifndef NO_STRICT 
#define NO_STRICT
#endif
#endif

// To get a random double
#ifndef RAND_double
#define RAND_double(min,max) (((rand()/(double)RAND_MAX)*((max)-(min)))+(min))
#endif

// center
#ifndef FIND_CENTER
#define FIND_CENTER(sp,sc) ((sc-sp) * 0.5f)
#endif

//macro for safely releasing a COM object
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)	if(p){p->Release();p=NULL;}
#endif

//turn on direct3d debugging, but only in debug mode
#ifdef _DEBUG
#ifndef D3D_DEBUG_INFO
#define D3D_DEBUG_INFO
#endif
#endif

//macro for safely releasing a COM object
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)	if(p){p->Release();p=NULL;}
#endif

//macro for safely deleting a pointer
#ifndef SAFE_DELETE
#define SAFE_DELETE(p)	if(p){delete p;p=NULL;}
#endif

//macro for safely deleting an array
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#endif   

#ifndef V
#define V(x)           { hr = x; }
#endif

#ifndef V_RETURN
#define V_RETURN(x)    { hr = x; if( FAILED(hr) ) { return hr; } }
#endif

//macro for ARGB (alpha only)
#ifndef ALPHA
#define ALPHA(a)	((a << 24)|0xFFFFFF)
#endif

//macro for ARGB (red only)
#ifndef RED
#define RED(a)		((a << 16)|0xFFFFFF)
#endif

//macro for ARGB (green only)
#ifndef GREEN
#define GREEN(a)	((a << 8)|0xFFFFFF)
#endif

//macro for ARGB (blue only)
#ifndef BLUE
#define BLUE(a)		(a | 0xFFFFFF)
#endif

//includes for cout
#ifdef _DEBUG
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>
using namespace std;
#endif

//comment defined
#ifndef COMMENT
#define COMMENT /
#endif

//the amount to align structures to
#ifndef CACHE_LINE
#define CACHE_LINE  16
#endif

//a little something to make alignment easier
#ifndef CACHE_ALIGN
#define CACHE_ALIGN __declspec(align(CACHE_LINE))
#endif

//used when comparing doubleing point values
#ifndef EPSILON
#define EPSILON 0.0001f
#endif

//check if 2 doubleing point numbers are equal
#ifndef FLOAT_EQ
#define FLOAT_EQ(x,v) ( ((v - EPSILON) < x) && (x <( v + EPSILON)))
#endif

//check if 2 doubleing point numbers are equal or greater
#ifndef FLOAT_EQGR
#define FLOAT_EQGR(x,v) ( ((v - EPSILON) < x) && (x <( v + EPSILON)) || (x > v) )
#endif

//check if 2 doubleing point numbers are equal or lesser
#ifndef FLOAT_EQLS
#define FLOAT_EQLS(x,v) ( ((v - EPSILON) < x) && (x <( v + EPSILON)) || (x < v) )
#endif

//prevents a divide by zero
#ifndef NO_DIV_0
#define NO_DIV_0(x) (x + 0.000001f)
#endif

//cout defined
#ifndef COUT
#define COUT COMMENT/
#endif

//defines for the Mouse Axis
#ifndef XAXIS
#define XAXIS 0
#endif
#ifndef YAXIS
#define YAXIS 1
#endif
#ifndef ZAXIS
#define ZAXIS 2
#endif

//defines for the Mouse Buttons
#ifndef MOUSE_LEFT
#define MOUSE_LEFT			0
#endif
#ifndef MOUSE_RIGHT
#define MOUSE_RIGHT			1
#endif
#ifndef MOUSE_MIDDLE
#define MOUSE_MIDDLE		2
#endif
#ifndef MOUSE_BUTTON4
#define MOUSE_BUTTON4		3
#endif
#ifndef MOUSE_BUTTON5
#define MOUSE_BUTTON5		4
#endif
#ifndef MOUSE_BUTTON6
#define MOUSE_BUTTON6		5
#endif
#ifndef MOUSE_BUTTON7
#define MOUSE_BUTTON7		6
#endif
#ifndef MOUSE_BUTTON8
#define MOUSE_BUTTON8		7
#endif