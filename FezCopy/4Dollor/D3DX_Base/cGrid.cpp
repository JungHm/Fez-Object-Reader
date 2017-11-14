#include "stdafx.h"
#include "cGrid.h"


cGrid::cGrid()
	: m_pMesh(NULL)
	, m_pTexTure(NULL)
{
	D3DXMatrixIdentity(&m_matWorld);
}


cGrid::~cGrid()
{
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pTexTure);
}

void cGrid::Setup(IN char * szFolder, IN char * szFile, IN int nRow, IN int nCol, IN float fSize)
{
	string sFullPath(szFolder);
	sFullPath += (string("/") + string(szFile));
	m_pTexTure = g_pTextureManager->GetTexture(sFullPath);

	m_nRow = nRow;			// 행 
	m_nCol = nCol;			// 열
	m_fTileSize = fSize;	// 타일 하나의 크기

	m_nTotalVertex = (m_nRow + 1) * (m_nCol + 1);		// 총 버텍스 개수 = (행 개수 + 1) x (열 개수 + 1)
	m_nTotalIndex = m_nRow * m_nCol * 6;				// 총 인덱스 개수 = 행 x 열 x 6
	m_fStartPosX = -1.0f * m_nCol * m_fTileSize * 0.5f; // x 좌표 시작 위치 = -1.0f x 열 x 크기(간격) x 0.5f(1/2)
	m_fStartPosZ = m_nRow * m_fTileSize * 0.5f;			// z 좌표 시작 위치 = 행 x 크기(간격) x 0.5f(1/2)

	m_vecVertex.resize(m_nTotalVertex);		// 총 버텍스 개수 만큼 리사이즈
	int nVIndex = 0;						// 버텍스 벡터 탐색 인덱스

											// 버텍스 지정
	for (int z = 0; z <= m_nRow; z++)		// 행(z축)
	{
		for (int x = 0; x <= m_nCol; x++)	// 열(x축)
		{
			ST_PNT_VERTEXT v;
			// 정점 좌표
			v.p.x = m_fStartPosX + (x * m_fTileSize);
			v.p.y = 0.0f;
			v.p.z = m_fStartPosZ + (-1.0f) * (z * m_fTileSize);
			// 텍스쳐 좌표
			v.t.x = ONE_XPER * x;
			v.t.y = ONE_YPER * z;
			// 버텍스 벡터에 저장
			m_vecVertex[nVIndex] = v;
			// 버텍스 벡터 인덱스 증가
			nVIndex++;
		}
	}

	m_vecIndex.resize(m_nTotalIndex);		// 총 인덱스 개수 만큼 리사이즈
	int nIIndex = 0;						// 인덱스 벡터 탐색 인덱스

											// 인덱스 지정
	for (int z = 0; z < m_nRow; z++)		// 행(z축)
	{
		for (int x = 0; x < m_nCol; x++)	// 열(x축)
		{
			m_vecIndex[nIIndex++] = DWORD(z * (m_nCol + 1) + x);
			m_vecIndex[nIIndex++] = DWORD((z + 1) * (m_nCol + 1) + x + 1);
			m_vecIndex[nIIndex++] = DWORD((z + 1) * (m_nCol + 1) + x);

			m_vecIndex[nIIndex++] = DWORD(z * (m_nCol + 1) + x);
			m_vecIndex[nIIndex++] = DWORD(z * (m_nCol + 1) + x + 1);
			m_vecIndex[nIIndex++] = DWORD((z + 1) * (m_nCol + 1) + x + 1);
		}
	}

	D3DXVECTOR3 v1, v2, n;
	for (int i = 0; i < m_nTotalIndex; i += 3)
	{
		// 법선 벡터 지정
		v1 = m_vecVertex[m_vecIndex[i + 1]].p - m_vecVertex[m_vecIndex[i]].p;
		v2 = m_vecVertex[m_vecIndex[i + 2]].p - m_vecVertex[m_vecIndex[i]].p;

		D3DXVec3Cross(&n, &v1, &v2);
		D3DXVec3Normalize(&n, &n);

		m_vecVertex[m_vecIndex[i]].n = n;
		m_vecVertex[m_vecIndex[i + 1]].n = n;
		m_vecVertex[m_vecIndex[i + 2]].n = n;
	}

	// 메터리얼 지정
	ZeroMemory(&m_mtl, sizeof(D3DMATERIAL9));
	m_mtl.Ambient = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	m_mtl.Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	m_mtl.Specular = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

	// 빈 매쉬 생성
	D3DXCreateMeshFVF(m_nTotalIndex / 3, m_nTotalVertex, D3DXMESH_MANAGED | D3DXMESH_32BIT, ST_PNT_VERTEXT::FVF, g_pD3DDevice, &m_pMesh);

	// 버텍스 버퍼 
	ST_PNT_VERTEXT* pV = NULL;
	m_pMesh->LockVertexBuffer(0, (LPVOID*)&pV);
	memcpy(pV, &m_vecVertex[0], m_nTotalVertex * sizeof(ST_PNT_VERTEXT));
	m_pMesh->UnlockVertexBuffer();

	// 인덱스 버퍼
	DWORD* pI = NULL;
	m_pMesh->LockIndexBuffer(0, (LPVOID*)&pI);
	memcpy(pI, &m_vecIndex[0], m_nTotalIndex * sizeof(DWORD));
	m_pMesh->UnlockIndexBuffer();

	// 어트리뷰트 버퍼
	DWORD* pA = NULL;
	m_pMesh->LockAttributeBuffer(0, &pA);
	ZeroMemory(pA, m_nTotalIndex / 3 * sizeof(DWORD));
	m_pMesh->UnlockAttributeBuffer();

	// 최적화
	vector<DWORD> vecAdj(m_nTotalIndex);
	m_pMesh->GenerateAdjacency(0.0f, &vecAdj[0]);
	m_pMesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE, &vecAdj[0], 0, 0, 0);

	// 중심 축 지정
	ST_PC_VERTEXT v;
	v.c = D3DCOLOR_XRGB(255, 0, 0);
	v.p = D3DXVECTOR3(m_fStartPosX, 0.0f, 0.0f);	m_vecAxis.push_back(v);
	v.p = D3DXVECTOR3(-m_fStartPosX, 0.0f, 0.0f);	m_vecAxis.push_back(v);
	v.c = D3DCOLOR_XRGB(0, 255, 0);
	v.p = D3DXVECTOR3(0.0f, m_fStartPosX, 0.0f);	m_vecAxis.push_back(v);
	v.p = D3DXVECTOR3(0.0f, -m_fStartPosX, 0.0f);	m_vecAxis.push_back(v);
	v.c = D3DCOLOR_XRGB(0, 0, 255);
	v.p = D3DXVECTOR3(0.0f, 0.0f, m_fStartPosZ);	m_vecAxis.push_back(v);
	v.p = D3DXVECTOR3(0.0f, 0.0f, -m_fStartPosZ);	m_vecAxis.push_back(v);

	// 피킹용 버텍스 지정
	ST_PC_VERTEXT vp;
	vp.c = D3DCOLOR_XRGB(255, 255, 255);
	vp.p = D3DXVECTOR3(m_fStartPosX, 0.0f, m_fStartPosZ);
	m_vecPicVertex.push_back(vp);
	vp.p = D3DXVECTOR3(-m_fStartPosX, 0.0f, -m_fStartPosZ);
	m_vecPicVertex.push_back(vp);
	vp.p = D3DXVECTOR3(m_fStartPosX, 0.0f, -m_fStartPosZ);
	m_vecPicVertex.push_back(vp);

	vp.p = D3DXVECTOR3(m_fStartPosX, 0.0f, m_fStartPosZ);
	m_vecPicVertex.push_back(vp);
	vp.p = D3DXVECTOR3(-m_fStartPosX, 0.0f, m_fStartPosZ);
	m_vecPicVertex.push_back(vp);
	vp.p = D3DXVECTOR3(-m_fStartPosX, 0.0f, -m_fStartPosZ);
	m_vecPicVertex.push_back(vp);
}

void cGrid::Render()
{
	// 그리드 렌더
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetMaterial(&m_mtl);
	g_pD3DDevice->SetTexture(0, m_pTexTure);
	m_pMesh->DrawSubset(0);

	// 축, 피킹용 버텍스 렌더
	if (KEY->m_isWireFrame)
	{
		g_pD3DDevice->SetTexture(0, NULL);
		g_pD3DDevice->SetFVF(ST_PC_VERTEXT::FVF);
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST, m_vecAxis.size() / 2, &m_vecAxis[0], sizeof(ST_PC_VERTEXT));
		g_pD3DDevice->SetFVF(ST_PC_VERTEXT::FVF);
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecPicVertex.size() / 3, &m_vecPicVertex[0], sizeof(ST_PC_VERTEXT));
	}
}

