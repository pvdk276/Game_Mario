/*+===================================================================
File:      Collision.h

Summary:   ??nh ngh?a l?p CCollision.
===================================================================+*/

#include <limits>
#include "Singleton.h"
#include "Box.h"

#ifndef _COLLISION_H_
#define _COLLISION_H_

/*C+==================================================================
Class:    CCollision

Summary:  L?p CCollision h? tr? c�c ph??ng th?c ?? x�t va ch?m gi?a 2
??i t??ng trong game theo thu?t to�n Sweep AABB.
==================================================================-C*/
class CCollision:public CSingleton<CCollision>
{
public:
	CCollision();
	~CCollision();

	/*M+==================================================================
	Method:	    CCollision::GetSwpetBroadphaseBox

	Summary:	Ph??ng th?c t?o ra Broadphase box.
	==================================================================-M*/
	static CBox GetSweptBroadphaseBox(CBox b, float t);

	/*M+==================================================================
	Method:	    CCollision::AABBCheck

	Summary:	Ph??ng th?c ki?m tra xem 2 ??i t??ng c� th? x?y ra va ch?m
	hay kh�ng tr??c khi ki?m tra b?ng SweepAABB. T?ng hi?u xu?t
	c?a ch??ng tr�nh khi c� nhi?u ??i t??ng.
	==================================================================-M*/
	static bool AABBCheck(CBox b1, CBox b2);

	/*M+==================================================================
	Method:	    CCollision::SweepAABB

	Summary:	Ph??ng th?c ki?m tra xem 2 ??i t??ng x?y ra va ch?m kh�ng
	(theo thu?t to�n Sweep AAABB).

	Args:       b1 - Box c?a ??i t??ng di chuy?n.
	b2 - Box c?a ??i t??ng ??ng y�n.
	normalx, normaly - H??ng va ch?m.
	timeFrame - Th?i gian c?a frame hi?n t?i.

	Return:     Th?i gian x?y ra va ch?m n?u c� va ch?m ho?c
	timeFrame n?u kh�ng c� va ch?m.
	==================================================================-M*/
	static float SweepAABB(CBox b1, CBox b2, float& normalx, float& normaly, float timeFrame);
};

#endif // _COLLISION_H_