#pragma once
#include <bitset>

#define KEYMAX 256
#define KEY cKeyManager::GetInstance()

using namespace std;

class cKeyManager
{
	SINGLETONE(cKeyManager)
private:
	bitset<KEYMAX> _keyUp;
	bitset<KEYMAX> _keyDown;


public:
	HRESULT init();
	void release();
	bool m_isWireFrame;

	//키가 한번만 눌렷냐?
	bool isOnceKeyDown(int key);
	//키가 한번 눌렀다 띄었냐?
	bool isOnceKeyUp(int key);
	//키가 계속 눌러있냐?
	bool isStayKeyDown(int key);
	//토글키냐?(캡스락,넘버락)
	bool isToggleKey(int key);
	// 와이어 프레임 
	void WireFrame();
};

