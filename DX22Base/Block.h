#ifndef __BLOCK_H__
#define __BLOCK_H__

#include <DirectXMath.h>
#include "CameraBase.h"
#include "Model.h"
#include "ConstantBuffer.h"
#include "Stage.h"

class Block
{
public:
	Block();
	~Block();
	void Update();
	void Draw();
	void SetCamera(CameraBase* pCamera);

private:
	CameraBase* m_pCamera;
	Stage::Info m_Info;
	Model* m_pModel;
	VertexShader* m_pVS;
	ConstantBuffer* m_pWVP;
};

#endif // __BLOCK_H__