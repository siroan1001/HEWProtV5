//#pragma once
#ifndef _____BILLBOARD_H____
#define _____BILLBOARD_H____

#include "DirectXTex/Texture.h"
//#include "Stage.h"
#include "CameraBase.h"
#include "Def.h"

class Billboard
{
public:
	struct Info
	{
		XMFLOAT3 Pos;
		XMFLOAT2 Size;
	};

public:
	Billboard();
	~Billboard();
	void Draw();

	Def::Info GetInfo();

protected:
	Info m_Info;
	ID3D11ShaderResourceView* m_pTex;

};

#endif // !_____BILLBOARD_H____
