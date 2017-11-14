#pragma once
#include "stdafx.h"

namespace Util {
	struct Ray
	{
		D3DXVECTOR3 origin;
		D3DXVECTOR3 direction;
	};

	Ray CalcPickingRay(int x, int y)
	{
		float px = 0.0f; float py = 0.0f;

		D3DVIEWPORT9 vp;
		g_pD3DDevice->GetViewport(&vp);

		D3DXMATRIX proj;
		g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &proj);

		px = (((2.0f*x) / vp.Width) - 1.0f) / proj(0, 0);
		py = (((-2.0f*y) / vp.Height) + 1.0f) / proj(1, 1);

		Ray ray;
		ray.origin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		ray.direction = D3DXVECTOR3(px, py, 1.0f);
		return ray;
	}

	Ray D3DXVec2TransformArray(int nScreenX, int nScreenY)
	{
		Ray r = CalcPickingRay(nScreenX, nScreenY);

		D3DXMATRIXA16 matView, matInvView;
		g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
		D3DXMatrixInverse(&matInvView, 0, &matView);

		D3DXVec3TransformCoord(&r.origin, &r.origin, &matInvView);
		D3DXVec3TransformNormal(&r.direction, &r.direction, &matInvView);
		D3DXVec3Normalize(&r.direction, &r.direction);

		return r;
	}

	bool IntersectTri(IN Ray r, IN D3DXVECTOR3 & v0, IN D3DXVECTOR3 & v1, IN D3DXVECTOR3 & v2, OUT D3DXVECTOR3& vPickedPosition)
	{
		float u, v, t;
		BOOL b = D3DXIntersectTri(&v0, &v1, &v2, &r.origin, &r.direction, &u, &v, &t);
		//vPickedPosition = r.origin + (t * r.direction);
		vPickedPosition = v0 + (u*(v1 - v0)) + (v*(v2 - v0));
		return b;
	}
};