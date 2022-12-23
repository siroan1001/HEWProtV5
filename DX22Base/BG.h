//#pragma once
#ifndef _____BG_H____
#define _____BG_H____

#include "DirectXTex/Texture.h"

class BG
{
public:
	BG();
	~BG();
	void Draw();

private:
	ID3D11ShaderResourceView* m_pTex;

};

#endif // !_____BG_H____
