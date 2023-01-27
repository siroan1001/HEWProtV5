//#pragma once
#ifndef _____BG_H____
#define _____BG_H____

#include "DirectXTex/Texture.h"
#include "Billboard.h"

class BG : public Billboard
{
public:
	enum BGKind
	{
		E_BG_KIND_TITLE = 0,
		E_BG_KIND_STAGESELECT,

		E_BG_KIND_FOREST,

		E_BG_KIND_MAX
	};
public:
	BG(BGKind);
	void Update();
	void Draw();

private:
	BGKind m_bgKind;
};

#endif // !_____BG_H____
