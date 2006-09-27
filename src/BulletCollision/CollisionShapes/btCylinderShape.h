/*
Bullet Continuous Collision Detection and Physics Library
Copyright (c) 2003-2006 Erwin Coumans  http://continuousphysics.com/Bullet/

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose, 
including commercial applications, and to alter it and redistribute it freely, 
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#ifndef CYLINDER_MINKOWSKI_H
#define CYLINDER_MINKOWSKI_H

#include "btBoxShape.h"
#include "BulletCollision/BroadphaseCollision/btBroadphaseProxy.h" // for the types
#include "LinearMath/btVector3.h"

/// implements cylinder shape interface
class btCylinderShape : public btBoxShape

{

public:
	btCylinderShape (const btVector3& halfExtents);
	
	///GetAabb's default implementation is brute force, expected derived classes to implement a fast dedicated version
	void GetAabb(const btTransform& t,btVector3& aabbMin,btVector3& aabbMax) const
	{
		GetAabbSlow(t,aabbMin,aabbMax);
	}

	virtual btVector3	LocalGetSupportingVertexWithoutMargin(const btVector3& vec)const;

	virtual void	BatchedUnitVectorGetSupportingVertexWithoutMargin(const btVector3* vectors,btVector3* supportVerticesOut,int numVectors) const;

	virtual btVector3	LocalGetSupportingVertex(const btVector3& vec) const
	{

		btVector3 supVertex;
		supVertex = LocalGetSupportingVertexWithoutMargin(vec);
		
		if ( GetMargin()!=0.f )
		{
			btVector3 vecnorm = vec;
			if (vecnorm .length2() < (SIMD_EPSILON*SIMD_EPSILON))
			{
				vecnorm.setValue(-1.f,-1.f,-1.f);
			} 
			vecnorm.normalize();
			supVertex+= GetMargin() * vecnorm;
		}
		return supVertex;
	}


	//use box inertia
	//	virtual void	CalculateLocalInertia(btScalar mass,btVector3& inertia);

	virtual int	GetShapeType() const
	{
		return CYLINDER_SHAPE_PROXYTYPE;
	}
	
	virtual int	GetUpAxis() const
	{
		return 1;
	}

	virtual float GetRadius() const
	{
		return GetHalfExtents().getX();
	}

	//debugging
	virtual char*	GetName()const
	{
		return "CylinderY";
	}



};

class btCylinderShapeX : public btCylinderShape
{
public:
	btCylinderShapeX (const btVector3& halfExtents);

	virtual btVector3	LocalGetSupportingVertexWithoutMargin(const btVector3& vec)const;
	virtual void	BatchedUnitVectorGetSupportingVertexWithoutMargin(const btVector3* vectors,btVector3* supportVerticesOut,int numVectors) const;
	virtual int	GetUpAxis() const
	{
		return 0;
	}
		//debugging
	virtual char*	GetName()const
	{
		return "CylinderX";
	}

	virtual float GetRadius() const
	{
		return GetHalfExtents().getY();
	}

};

class btCylinderShapeZ : public btCylinderShape
{
public:
	btCylinderShapeZ (const btVector3& halfExtents);

	virtual btVector3	LocalGetSupportingVertexWithoutMargin(const btVector3& vec)const;
	virtual void	BatchedUnitVectorGetSupportingVertexWithoutMargin(const btVector3* vectors,btVector3* supportVerticesOut,int numVectors) const;

	virtual int	GetUpAxis() const
	{
		return 2;
	}
		//debugging
	virtual char*	GetName()const
	{
		return "CylinderZ";
	}

	virtual float GetRadius() const
	{
		return GetHalfExtents().getX();
	}

};


#endif //CYLINDER_MINKOWSKI_H

