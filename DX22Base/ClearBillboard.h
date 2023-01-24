#ifndef _____CLEAR_BILLBOARD_H____
#define _____CLEAR_BILLBOARD_H____

#include "DirectXTex/Texture.h"
#include "AnimationBillboard.h"

class ClearBillboard : public AnimationBillboard
{
public:
	struct Info
	{
		XMFLOAT3 Pos;
		XMFLOAT2 Size;
	};
	struct UV
	{
		int U;
		int V;
	};

public:
	ClearBillboard();
	void Update(int Animflame);
	void Draw();
	int GetMaxFlame();

private:
	UV m_uv = { 4,4 }; //ï™äÑêî
	int AnimFlame;
};

#endif // !_____CLEAR_BILLBOARD_H____

