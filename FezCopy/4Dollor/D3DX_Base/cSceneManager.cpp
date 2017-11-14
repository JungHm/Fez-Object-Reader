#include "stdafx.h"
#include "cSceneManager.h"
#include "iScene.h"


cSceneManager::cSceneManager()
{
}


cSceneManager::~cSceneManager()
{
}

void cSceneManager::SetUp()
{
	m_pScene[m_SceneName]->SetUp();
}

void cSceneManager::Destroy()
{
	for each(auto p in m_pScene)
	{
		p.second->Destroy();
		SAFE_DELETE(p.second);
	}
}

void cSceneManager::Update()
{
	m_pScene[m_SceneName]->Update();
}

void cSceneManager::Render()
{
	m_pScene[m_SceneName]->Render();
}

void cSceneManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	m_pScene[m_SceneName]->WndProc(hWnd, message, wParam, lParam);
}

void cSceneManager::AddScene(char * SceneName, iScene * pScene)
{
	if (m_pScene.find(SceneName) == m_pScene.end())
	{
		if (m_pScene.empty()) m_SceneName = SceneName;
		m_pScene[SceneName] = pScene;
	}
}

void cSceneManager::ChangeScene(char * SceneName)
{
	if (!strcmp(SceneName, m_SceneName))
	{
		return;
	}
	if (!(m_pScene.find(SceneName) == m_pScene.end()))
	{
		m_pScene[m_SceneName]->Destroy();
		m_SceneName = SceneName;
		this->SetUp();
		//m_pScene[m_SceneName]->SetUp();
	}
}
