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
	struct Division
	{
		int U;
		int V;
	};

public:
	ClearBillboard();
	void Update();
	void Draw();
	bool GetFlag();

	void ResetAnim();
private:
	int m_AnimFlame;
	bool m_IsAnimFin;
};

#endif // !_____CLEAR_BILLBOARD_H____

