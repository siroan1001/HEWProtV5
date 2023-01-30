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
	struct Division
	{
		int U;
		int V;
	};

public:
	ResultBillboard();
	void Update();
	void Draw();

	bool GetFlag();

	void ResetAnim();

private:
	int m_AnimFlame;
	bool m_IsAnimFin;
};

#endif // !_____RESULT_BILLBOARD_H____

