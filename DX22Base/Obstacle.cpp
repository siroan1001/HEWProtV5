#include "Obstacle.h"

Obstacle::Obstacle()
{
	m_Info = { {-6.0f, 4.7f, 0.0f}, {1.0f, 1.0f, 0.3f}, {0.0f, 0.0f, 0.0f} };;
	m_ModelSize.x = 1.0f;
	m_ModelSize.y = 1.0f;
	m_ModelSize.z = 1.0f;

	m_pModel = new Model;
	if (!m_pModel->Load("Assets/box/box.fbx", 1.0f))
	{
		MessageBox(NULL, "モデルの生成に失敗", "エラー", MB_OK);
	}
	m_pModel->SetVertexShader(m_pVS);
}

void Obstacle::Update()
{

}