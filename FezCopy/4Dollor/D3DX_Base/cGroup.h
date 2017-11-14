#pragma once
#include "cMtlTex.h"

class cGroup : public cObject
{
private:
	SYNTHESIZE_PASS_BY_REF(std::vector<ST_PNT_VERTEXT>, m_verVertex, Vertex);
	SYNTHESIZE_ADD_REF(cMtlTex*, m_pMtlTex, MtlTex);

public:
	cGroup();
	virtual ~cGroup();

	void Render();
};

