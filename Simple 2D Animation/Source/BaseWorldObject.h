//////////////////////////////////////////////////////////////////////////
//
//	Filename: 	BaseWorldObject.h
//
//	Author:		Nicholas Legg
//
//	Purpose:	the base class for 3D world objects
//
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Helpers.h"

class CACHE_ALIGN BaseWorldObject
{
private:
	D3DXVECTOR3	d3dPosition;
	BOOL		bDirty;
	BOOL		bBase;	//true if base object, false if not

public:

	BaseWorldObject()
	{
		d3dPosition.x = 0.0f;
		d3dPosition.y = 0.0f;
		d3dPosition.z = 0.0f;

		bDirty = FALSE;
	}
	BaseWorldObject(const BaseWorldObject &a)
	{
		d3dPosition.x = a.d3dPosition.x;
		d3dPosition.y = a.d3dPosition.y;
		d3dPosition.z = a.d3dPosition.z;

		bDirty = a.bDirty;
	}
	BaseWorldObject &operator=(const BaseWorldObject &a)
	{
		d3dPosition.x = a.d3dPosition.x;
		d3dPosition.y = a.d3dPosition.y;
		d3dPosition.z = a.d3dPosition.z;

		bDirty = a.bDirty;
	}
	~BaseWorldObject(){}

	//////////////////////////////////////////////////////////////////////////
	//the inlines
	//////////////////////////////////////////////////////////////////////////
	inline D3DXVECTOR3 GetPosition(){return d3dPosition;}
};