#pragma once
class cGrid
{
private:
	vector<ST_PNT_VERTEXT>  m_vecVertex;	// 버텍스
	vector<DWORD>			m_vecIndex;		// 인덱스
	vector<ST_PC_VERTEXT>	m_vecAxis;		// 축 베텍스
	LPD3DXMESH				m_pMesh;		// 매쉬
	D3DMATERIAL9			m_mtl;			// 메터리얼
	LPDIRECT3DTEXTURE9		m_pTexTure;		// 텍스처
	D3DXMATRIXA16			m_matWorld;		// 그리드 월드

	int   m_nRow;			// 행 개수
	int   m_nCol;			// 열 개수
	int   m_nTotalVertex;	// 총 버덱스 개수
	int	  m_nTotalIndex;	// 총 인덱스 개수
	float m_fTileSize;		// 그리드 간격(크기)
	float m_fStartPosX;		// 그리드 생성 시작 x좌표
	float m_fStartPosZ;		// 그리드 생성 시작 z좌표

private:
	SYNTHESIZE(vector<ST_PC_VERTEXT>, m_vecPicVertex, PicVertex); // 피킹용 버텍스

public:
	MATRIX16_FIX;
	cGrid();
	~cGrid();

	// 초기화
	void Setup(IN char* szFolder, IN char* szFile, IN int nRow, IN int nCol, IN float fSize);
	// 렌더
	void Render();
};

