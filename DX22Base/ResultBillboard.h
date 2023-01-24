#ifndef _____RESULT_BILLBOARD_H____
#define _____RESULT_BILLBOARD_H____

#include "DirectXTex/Texture.h"
#include "AnimationBillboard.h"

class ResultBillboard : public AnimationBillboard
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
	ResultBillboard();
	void Update(int Animflame);
	void Draw();
	int GetMaxFlame();

private:
	UV m_uv = { 4,4 }; //ï™äÑêî
	//UV m_uv = { 5,6 }; //ï™äÑêî
	int AnimFlame;
};

#endif // !_____RESULT_BILLBOARD_H____

