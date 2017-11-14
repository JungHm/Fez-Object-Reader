#include "stdafx.h"
#include "cKeyManager.h"


cKeyManager::cKeyManager()
{
}


cKeyManager::~cKeyManager()
{
}

HRESULT cKeyManager::init()
{
	//키값을 전부 눌려있지 않는 상태로 최기화 한다.
	for (int i = 0; i < KEYMAX; i++)
	{
		_keyUp.set(i, false);
		_keyDown.set(i, false);
	}

	return S_OK;
}

void cKeyManager::release()
{
}

bool cKeyManager::isOnceKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!_keyDown[key])
		{
			_keyDown.set(key, true);
			return true;
		}
	}
	else
	{
		_keyDown.set(key, false);
	}
	return false;
}

bool cKeyManager::isOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		_keyUp.set(key, true);
	}
	else
	{
		if (_keyUp[key])
		{
			_keyUp.set(key, false);
			return true;
		}
	}
	return false;
}

bool cKeyManager::isStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) return true;
	return false;
}

bool cKeyManager::isToggleKey(int key)
{
	if (GetKeyState(key) & 0x0001) return true;
	return false;
}

void cKeyManager::WireFrame()
{
	if (KEY->isOnceKeyDown('Z'))
	{
		if (!m_isWireFrame) m_isWireFrame = true;
		else m_isWireFrame = false;
	}

	if (m_isWireFrame) g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	else g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}
