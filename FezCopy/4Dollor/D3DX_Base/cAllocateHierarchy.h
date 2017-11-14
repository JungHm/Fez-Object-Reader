#pragma once

using namespace std;
class cMtlTex;
struct ST_BONE : public D3DXFRAME
{
	D3DXMATRIXA16 matWorldTM; //각 Bone의 월드 매트릭스. D3DXFRAME안에는 변환매트릭스(Local?)만 있음.
};

struct ST_BONE_MESH : public D3DXMESHCONTAINER
{
	DWORD					numSubset; //메쉬를 이루는 폴리곤 마다 재질이 다른경우 같은 재질을 사용하는 폴리곤 끼리 set로 묶어서 렌더시 재질설정.
	std::vector<cMtlTex*>	vecMtlTex; //재질과 재질에 상응하는 텍스쳐를 담고있는 cMtlTex 클래스를 재질 갯수만큼 생성. 벡터로 보관.
	LPD3DXMESH				pOrigMesh; //원본 메쉬
	D3DXMATRIX**			ppBoneMatrixPtrs; // 이 메쉬에 영향을 주는 프레임들의 월드매트릭스 포인터 '배열'
	D3DXMATRIXA16*			pBoneOffsetMatrices; //원본 메쉬를 로컬스페이스로 보내는 매트릭스들? NodeTM역행렬?
	D3DXMATRIXA16*          pCurrentBoneMatrices;	// 각 본의 계산된 월드매트릭스
};

class cAllocateHierarchy : public ID3DXAllocateHierarchy
{
public:
	cAllocateHierarchy();
	~cAllocateHierarchy();

	STDMETHOD(CreateFrame)(THIS_ LPCSTR Name, LPD3DXFRAME *ppNewFrame) override;

	STDMETHOD(CreateMeshContainer(
		THIS_ LPCSTR Name,
		CONST D3DXMESHDATA* pMeshData,
		CONST D3DXMATERIAL* pMaterials,
		CONST D3DXEFFECTINSTANCE* pEffectInstance,
		DWORD NumMaterials,
		CONST DWORD* pAdjacency,
		LPD3DXSKININFO pSkinInfo,
		LPD3DXMESHCONTAINER* ppNewMeshContainer));

	STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree);

	STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree);

};

