#pragma once
#include "iScene.h"
class cInGame :
	public iScene
{
public:
	cInGame();
	~cInGame();

	virtual void SetUp() override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void Render() override;
};

