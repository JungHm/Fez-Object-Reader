#pragma once

#include <xmllite.h>
#include <stdio.h>
#include <shlwapi.h>

class FileStream
{


private:
	HRESULT hr = S_OK;
	IStream *pFileStream = NULL;
	IXmlReader *pReader = NULL;
	XmlNodeType nodeType;
	const WCHAR* pwszPrefix;
	const WCHAR* pwszLocalName;
	const WCHAR* pwszValue;
	UINT cwchPrefix;

	//메쉬 저장용
	
	vector<D3DXVECTOR3> vecPos;
	vector<D3DXVECTOR2> vecTex;
	vector<DWORD> vecInd;
	std::wstring texture;
	std::string RenderType;
	D3DXVECTOR3 scale;
	float pos[3];
	float tex[2];
public:
	FileStream();
	~FileStream();
	HRESULT WriteAttributes(IXmlReader* pReader, const WCHAR* Element);
	HRESULT LoadFromXml(const WCHAR* fileName);
	void AddLoadData(const WCHAR* endElement);

	void MakeMesh(LPD3DXMESH* pMesh);
};
