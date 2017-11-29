#include "stdafx.h"
#include "FileStream.h"


#pragma warning(disable : 4127)  // conditional expression is constant
#define CHKHR(stmt)             do { hr = (stmt); if (FAILED(hr)) goto CleanUp; } while(0)
#define HR(stmt)                do { hr = (stmt); goto CleanUp; } while(0)




FileStream::FileStream()
{
}

FileStream::~FileStream()
{
}

HRESULT FileStream::WriteAttributes(IXmlReader* pReader, const WCHAR* Element)
{
	const WCHAR* pwszPrefix;
	const WCHAR* pwszLocalName;
	const WCHAR* pwszValue;
	HRESULT hr = pReader->MoveToFirstAttribute();

	if (S_FALSE == hr)
		return hr;
	if (S_OK != hr)
	{
		wprintf(L"Error moving to first attribute, error is %08.8lx", hr);
		return hr;
	}
	else
	{
		int index = 0;
		while (TRUE)
		{
			if (!pReader->IsDefault())
			{
				UINT cwchPrefix;
				if (FAILED(hr = pReader->GetPrefix(&pwszPrefix, &cwchPrefix)))
				{
					wprintf(L"Error getting prefix, error is %08.8lx", hr);
					return hr;
				}
				if (FAILED(hr = pReader->GetLocalName(&pwszLocalName, NULL)))
				{
					wprintf(L"Error getting local name, error is %08.8lx", hr);
					return hr;
				}
				if (FAILED(hr = pReader->GetValue(&pwszValue, NULL)))
				{
					wprintf(L"Error getting value, error is %08.8lx", hr);
					return hr;
				}
				if (cwchPrefix > 0)
					wprintf(L"Attr: %s:%s=\"%s\" \n", pwszPrefix, pwszLocalName, pwszValue);
				else
					wprintf(L"Attr: %s=\"%s\" \n", pwszLocalName, pwszValue);
				if (Element == NULL) break;
				else if (!wcscmp(pwszLocalName, L"name"))
				{
					texture = pwszValue;
					texture.append(L".png");
				}
				else if (!wcscmp(pwszLocalName, L"ShaderInstancedIndexedPrimitives"))
				{
					RenderType = std::string((char*)pwszValue);//triangleList 
				}
				else if (!wcscmp(Element, L"Vector2"))
				{
					tex[index++] = stof(pwszValue);
				}
				else if (!wcscmp(Element, L"Vector3"))
				{
					pos[index++] = stof(pwszValue);
				}


			}

			if (S_OK != pReader->MoveToNextAttribute())
				break;
		}
	}
	return hr;
}


HRESULT FileStream::LoadFromXml(const WCHAR * fileName)
{
	/* if (argc != 2)
	{
	wprintf(L"Usage: XmlLiteReader.exe name-of-input-file\n");
	return 0;
	}*/

	//Open read-only input stream
	if (FAILED(hr = SHCreateStreamOnFile(fileName, STGM_READ, &pFileStream)))
	{
		wprintf(L"Error creating file reader, error is %08.8lx", hr);
		HR(hr);
	}

	if (FAILED(hr = CreateXmlReader(__uuidof(IXmlReader), (void**)&pReader, NULL)))
	{
		wprintf(L"Error creating xml reader, error is %08.8lx", hr);
		HR(hr);
	}

	if (FAILED(hr = pReader->SetProperty(XmlReaderProperty_DtdProcessing, DtdProcessing_Prohibit)))
	{
		wprintf(L"Error setting XmlReaderProperty_DtdProcessing, error is %08.8lx", hr);
		HR(hr);
	}

	if (FAILED(hr = pReader->SetInput(pFileStream)))
	{
		wprintf(L"Error setting input for reader, error is %08.8lx", hr);
		HR(hr);
	}

	//read until there are no more nodes
	while (S_OK == (hr = pReader->Read(&nodeType)))
	{
		switch (nodeType)
		{
		case XmlNodeType_XmlDeclaration:
			wprintf(L"XmlDeclaration\n");
			if (FAILED(hr = WriteAttributes(pReader, NULL)))
			{
				wprintf(L"Error writing attributes, error is %08.8lx", hr);
				HR(hr);
			}
			break;
		case XmlNodeType_Element:
			if (FAILED(hr = pReader->GetPrefix(&pwszPrefix, &cwchPrefix)))
			{
				wprintf(L"Error getting prefix, error is %08.8lx", hr);
				HR(hr);
			}
			if (FAILED(hr = pReader->GetLocalName(&pwszLocalName, NULL)))
			{
				wprintf(L"Error getting local name, error is %08.8lx", hr);
				HR(hr);
			}
			if (cwchPrefix > 0)
				wprintf(L"Element: %s:%s\n", pwszPrefix, pwszLocalName);
			else
				wprintf(L"Element: %s\n", pwszLocalName);

			if (FAILED(hr = WriteAttributes(pReader, pwszLocalName)))
			{
				wprintf(L"Error writing attributes, error is %08.8lx", hr);
				HR(hr);
			}

			if (pReader->IsEmptyElement())
				wprintf(L" (empty)");
			break;
		case XmlNodeType_EndElement:
			if (FAILED(hr = pReader->GetPrefix(&pwszPrefix, &cwchPrefix)))
			{
				wprintf(L"Error getting prefix, error is %08.8lx", hr);
				HR(hr);
			}
			if (FAILED(hr = pReader->GetLocalName(&pwszLocalName, NULL)))
			{
				wprintf(L"Error getting local name, error is %08.8lx", hr);
				HR(hr);
			}
			if (cwchPrefix > 0)
				wprintf(L"End Element: %s:%s\n", pwszPrefix, pwszLocalName);
			else
				wprintf(L"End Element: %s\n", pwszLocalName);

			if (!strncmp((char*)pwszLocalName, (char*)L"Index", 5))
			{
				if (!strcmp((char*)pwszValue, (char*)L"\n"));
				else vecInd.push_back(stoi(pwszValue));

			}
			AddLoadData(pwszLocalName);
			break;
		case XmlNodeType_Text:
		case XmlNodeType_Whitespace:
			if (FAILED(hr = pReader->GetValue(&pwszValue, NULL)))
			{
				wprintf(L"Error getting value, error is %08.8lx", hr);
				HR(hr);
			}


			wprintf(L"Text: >%s<\n", pwszValue);
			break;
		case XmlNodeType_CDATA:
			if (FAILED(hr = pReader->GetValue(&pwszValue, NULL)))
			{
				wprintf(L"Error getting value, error is %08.8lx", hr);
				HR(hr);
			}
			wprintf(L"CDATA: %s\n", pwszValue);
			break;
		case XmlNodeType_ProcessingInstruction:
			if (FAILED(hr = pReader->GetLocalName(&pwszLocalName, NULL)))
			{
				wprintf(L"Error getting name, error is %08.8lx", hr);
				HR(hr);
			}
			if (FAILED(hr = pReader->GetValue(&pwszValue, NULL)))
			{
				wprintf(L"Error getting value, error is %08.8lx", hr);
				HR(hr);
			}
			wprintf(L"Processing Instruction name:%s value:%s\n", pwszLocalName, pwszValue);
			break;
		case XmlNodeType_Comment:
			if (FAILED(hr = pReader->GetValue(&pwszValue, NULL)))
			{
				wprintf(L"Error getting value, error is %08.8lx", hr);
				HR(hr);
			}
			wprintf(L"Comment: %s\n", pwszValue);
			break;
		case XmlNodeType_DocumentType:
			wprintf(L"DOCTYPE is not printed\n");
			break;
		}
	}

CleanUp:
	SAFE_RELEASE(pFileStream);
	SAFE_RELEASE(pReader);
	return hr;
}

void FileStream::AddLoadData(const WCHAR * endElement)
{
	if (!strcmp((char*)endElement, (char*)L"Size"))
	{
		scale = D3DXVECTOR3(pos[0], pos[1], pos[2]);
	}
	else if (!strcmp((char*)endElement, (char*)L"Position"))
	{
		vecPos.push_back(D3DXVECTOR3(pos[2], pos[1], pos[0]));
	}
	else if (!strcmp((char*)endElement, (char*)L"TextureCoord"))
	{
		vecTex.push_back(D3DXVECTOR2(tex[0], tex[1]));
	}
	//인덱스는 하나씩 나오니까 그냥 넣자
}

void FileStream::MakeMesh(LPD3DXMESH * pMesh)
{
	ST_PT_VERTEXT p;
	vector<ST_PT_VERTEXT> vecPT;
	for (int i = 0; i < vecPos.size(); i++)
	{
		p.p = vecPos[i];
		p.t = vecTex[i];
		vecPT.push_back(p);
	}

	D3DXCreateMeshFVF(vecInd.size() / 3,
		vecPT.size(),
		D3DXMESH_MANAGED,
		ST_PT_VERTEXT::FVF,
		g_pD3DDevice,
		pMesh);

	if (pMesh == NULL)
		return;
	else
	{
		vecPos.clear();
		vecTex.clear();
	}


	ST_PT_VERTEXT*	pV = NULL;
	(*pMesh)->LockVertexBuffer(0, (LPVOID*)&pV);
	for (int i = 0; i < vecPT.size(); i++)
		pV[i] = vecPT[i];
	(*pMesh)->UnlockVertexBuffer();


	WORD* pI = NULL;
	(*pMesh)->LockIndexBuffer(0, (LPVOID*)&pI);
	for (int i = 0; i < vecInd.size(); i++)
		pI[i] = vecInd[i];
	(*pMesh)->UnlockIndexBuffer();

	DWORD* pA = NULL;
	(*pMesh)->LockAttributeBuffer(0, &pA);
	pA[0] = 0;
	(*pMesh)->UnlockAttributeBuffer();

	std::vector<DWORD>	vecAdj(vecInd.size());
	(*pMesh)->GenerateAdjacency(0.0f, &vecAdj[0]);

	(*pMesh)->OptimizeInplace(
		D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_COMPACT |
		D3DXMESHOPT_VERTEXCACHE,
		&vecAdj[0],
		0, 0, 0);

	vecPT.clear();
	vecInd.clear();

}
