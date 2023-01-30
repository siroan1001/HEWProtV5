#include "Geometory.h"
#include "MeshBuffer.h"
#include "Shader.h"
#include "ConstantBuffer.h"
#include <vector>

//--- �}�N��
#define GEOMETORY_SAFE_DELETE(p) if(p){delete p; p = nullptr;}

using namespace DirectX;
using namespace std;

//--- �萔
//const int GEOMETORY_SPLIT = 16;
//const int GEOMETORY_SPLIT_VTX_X = GEOMETORY_SPLIT + 1;
//const int GEOMETORY_SPLIT_VTX_Y = GEOMETORY_SPLIT / 2 + 1;
//const int GEOMETORY_SPLIT_IDX_X = GEOMETORY_SPLIT;
//const int GEOMETORY_SPLIT_IDX_Y = GEOMETORY_SPLIT / 2;

//--- �\����
struct GeometoryVertex
{
	XMFLOAT3 pos;
	XMFLOAT3 normal;
	XMFLOAT2 uv;
};

//--- �񋓑�
enum GeometorMatNum
{
	E_GEOMETOR_MAT_NUM_TRNS = 0,
	E_GEOMETOR_MAT_NUM_ROT,
	E_GEOMETOR_MAT_NUM_SCL,
	E_GEOMETOR_MAT_NUM_MAX,
};

//--- �v���g�^�C�v�錾
void CreateGeometoryBox();
void CreateGeometorySphere();
void CreateGeometoryCylinder();
void CreateGeometoryCapsule();
void CreateGeometoryCone();
void CreateGeometoryShader();
void CreateGeometoryConstantBuffer();
void UpdateGeometoryMatrix();
void UpdateGeometoryColor();
void UpdateGeometoryLight();

//--- �O���[�o���ϐ�
MeshBuffer* g_pGeometoryBox;
MeshBuffer* g_pGeometorySphere;
MeshBuffer* g_pGeometoryCylinder;
MeshBuffer* g_pGeometoryCapsule;
MeshBuffer* g_pGeometoryCone;
VertexShader* g_pGeometoryVS;
PixelShader* g_pGeometoryPS;
ConstantBuffer* g_pGeometoryWVP;
ConstantBuffer* g_pGeometoryColor;
ConstantBuffer* g_pGeometoryLight;
DirectX::XMFLOAT4X4 g_geometoryMat[E_GEOMETOR_MAT_NUM_MAX];
struct GeometoryColor { DirectX::XMFLOAT4 Color; };
GeometoryColor g_geometoryColor;
Lig::Light g_geometoryLight;
Lig* g_pLight;
DirectX::XMFLOAT3 g_geometoryTransform[E_GEOMETOR_MAT_NUM_MAX];

float g_CyliderRadius;

HRESULT InitGeometory()
{
	CreateGeometoryShader();
	CreateGeometoryConstantBuffer();
	CreateGeometoryBox();
	CreateGeometorySphere();
	CreateGeometoryCylinder();
	CreateGeometoryCapsule();
	CreateGeometoryCone();
	g_pLight = new Lig;
	return S_OK;
}
void UninitGeometory()
{
	delete g_pLight;
	GEOMETORY_SAFE_DELETE(g_pGeometoryCone);
	GEOMETORY_SAFE_DELETE(g_pGeometoryCapsule);
	GEOMETORY_SAFE_DELETE(g_pGeometoryCylinder);
	GEOMETORY_SAFE_DELETE(g_pGeometorySphere);
	GEOMETORY_SAFE_DELETE(g_pGeometoryBox);
	GEOMETORY_SAFE_DELETE(g_pGeometoryPS);
	GEOMETORY_SAFE_DELETE(g_pGeometoryVS);
}
void SetGeometoryTranslate(float x, float y, float z)
{
	g_geometoryTransform[0] = DirectX::XMFLOAT3(x, y, z);
}
void SetGeometoryRotation(float x, float y, float z)
{
	g_geometoryTransform[1] = DirectX::XMFLOAT3(x, y, z);
}
void SetGeometoryScaling(float x, float y, float z)
{
	g_geometoryTransform[2] = DirectX::XMFLOAT3(x, y, z);
}
void SetGeometoryVPMatrix(DirectX::XMFLOAT4X4 view, DirectX::XMFLOAT4X4 proj, DirectX::XMFLOAT3 eyePos)
{
	g_geometoryMat[1] = view;
	g_geometoryMat[2] = proj;
	g_geometoryLight.eyePos = eyePos;
}
void SetGeometoryColor(DirectX::XMFLOAT4 color)
{
	g_geometoryColor.Color = color;
}
void SetGeometoryPtLigPos(DirectX::XMFLOAT3 PtLigPos)
{
	g_geometoryLight.ptPos = PtLigPos;
}
void SetGeometorySpLigPos(DirectX::XMFLOAT3 pos)
{
	g_geometoryLight.spPos = pos;
}
Lig::Light GetLig()
{
	return g_geometoryLight;
}
void DrawBox()
{
	UpdateGeometoryMatrix();
	UpdateGeometoryColor();
	UpdateGeometoryLight();
	g_pGeometoryVS->Bind();
	g_pGeometoryPS->Bind();
	g_pGeometoryWVP->BindVS(0);
	g_pGeometoryColor->BindVS(1);
	g_pGeometoryLight->BindPS(0);
	g_pGeometoryBox->Draw();
}
void DrawSphere()
{
	UpdateGeometoryMatrix();
	g_pGeometoryVS->Bind();
	g_pGeometoryPS->Bind();
	g_pGeometoryWVP->BindVS(0);
	g_pGeometorySphere->Draw();
}
void DrawCylinder()
{
	UpdateGeometoryMatrix();
	UpdateGeometoryColor();
	UpdateGeometoryLight();
	g_pGeometoryVS->Bind();
	g_pGeometoryPS->Bind();
	g_pGeometoryWVP->BindVS(0);
	g_pGeometoryColor->BindVS(1);
	g_pGeometoryLight->BindPS(0);
	g_pGeometoryCylinder->Draw();
}
void DrawCone()
{
	UpdateGeometoryMatrix();
	g_pGeometoryVS->Bind();
	g_pGeometoryPS->Bind();
	g_pGeometoryWVP->BindVS(0);
	g_pGeometoryCone->Draw();
}
void DrawCapsule()
{
}
void DrawArrow()
{
}

float GetCylinderRadius()
{
	return g_CyliderRadius;
}



void CreateGeometoryBox()
{
	GeometoryVertex vtx[] =
	{
		//�ʂ̏��Ԃ͕K�����v���ɐݒ肷��
		//�i�������ݒ肵�Ă��Ȃ��Ɨ������\������Ėʂ������Ȃ��Ȃ�j
		
		//Z��
		{ { 0.5f,  0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f }, {1.0f, 0.0f} },	//0
		{ {-0.5f,  0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f }, {0.0f, 0.0f} },	//1
		{ { 0.5f, -0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f }, {1.0f, 1.0f} },	//2
		{ {-0.5f, -0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f }, {0.0f, 1.0f} },	//3
												 
		//-X��								    
		{ {-0.5f,  0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f }, {1.0f, 0.0f} },	//5
		{ {-0.5f,  0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f }, {0.0f, 0.0f} },	//4
		{ {-0.5f, -0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f }, {1.0f, 1.0f} },	//7
		{ {-0.5f, -0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f }, {0.0f, 1.0f} },	//6
												 
		//-Y��								    
		{ {-0.5f, -0.5f, -0.5f}, { 0.0f, -1.0f,  0.0f }, {0.0f, 0.0f} },	//8
		{ { 0.5f, -0.5f, -0.5f}, { 0.0f, -1.0f,  0.0f }, {1.0f, 0.0f} },	//9
		{ { 0.5f, -0.5f,  0.5f}, { 0.0f, -1.0f,  0.0f }, {1.0f, 1.0f} },	//11
		{ {-0.5f, -0.5f,  0.5f}, { 0.0f, -1.0f,  0.0f }, {0.0f, 1.0f} },	//10

		//-Z��
		{ {-0.5f,  0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f }, {0.0f, 0.0f} },	//12
		{ { 0.5f,  0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f }, {1.0f, 0.0f} },	//13
		{ {-0.5f, -0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f }, {0.0f, 1.0f} },	//14
		{ { 0.5f, -0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f }, {1.0f, 1.0f} },	//15

		//Y��
		{ {-0.5f,  0.5f,  0.5f}, { 0.0f,  1.0f,  0.0f }, {0.0f, 0.0f} },	//16
		{ { 0.5f,  0.5f,  0.5f}, { 0.0f,  1.0f,  0.0f }, {1.0f, 0.0f} },	//17
		{ {-0.5f,  0.5f, -0.5f}, { 0.0f,  1.0f,  0.0f }, {0.0f, 1.0f} },	//18
		{ { 0.5f,  0.5f, -0.5f}, { 0.0f,  1.0f,  0.0f }, {1.0f, 1.0f} },	//19

		//X��
		{ { 0.5f,  0.5f, -0.5f}, {1.0f,  0.0f,  0.0f }, {0.0f, 0.0f} },	//20
		{ { 0.5f,  0.5f,  0.5f}, {1.0f,  0.0f,  0.0f }, {1.0f, 0.0f} },	//21
		{ { 0.5f, -0.5f, -0.5f}, {1.0f,  0.0f,  0.0f }, {0.0f, 1.0f} },	//22
		{ { 0.5f, -0.5f,  0.5f}, {1.0f,  0.0f,  0.0f }, {1.0f, 1.0f} },	//23

	};

	//���̏��Ԃɐ����q���Ń|���S��������Ă���
	int idx[] =
	{
		 0,  1,  2,   2,  1,  3,	//Z��
		 4,  5,  6,   6,  5,  7,	//-X��
		 8,  9, 10,  10,  9, 11,	//-Y��
		12, 13, 14,  14, 13, 15,	//-Z��
		16, 17, 18,  18, 17, 19,	//Y��
		20, 21, 22,  22, 21, 23,	//X��
	};

	MeshBuffer::Description desc = {};
	desc.pVtx = vtx;	//���_���
	desc.vtxCount = sizeof(vtx) / sizeof(GeometoryVertex);	//���_�̐�
	desc.vtxSize = sizeof(GeometoryVertex);		//���_1�̃f�[�^�T�C�Y
	desc.pIdx = idx;	//�����q�����ԁi�C���f�b�N�X�j
	desc.idxCount = sizeof(idx) / sizeof(int);	//�C���f�b�N�X�̐�
	desc.idxSize = sizeof(int);		//�C���f�b�N�X1�̃f�[�^�T�C�Y
	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;		//�ǂ̌`�̃|���S������邩�ݒ肷��
	//���L�L���̎Q��
	//file:///C:/Users/yukku/OneDrive/�f�X�N�g�b�v/HAL/HAL2�N/DX22/DX22Base/DX22Base/DX22Base/rom/�[������n�߂�DirectX11�Q�[���v���O���~���O����%20%234�u�ˉe���W�ƃV�F�[�_�[�`��̉���v%20-%20�Q�[���Y�K���h.com.html

	//���̐���
	g_pGeometoryBox = new MeshBuffer(desc);
}
void CreateGeometorySphere()
{
}
void CreateGeometoryCylinder()
{
	g_CyliderRadius = 0.5f;

	//GeometoryVertex vtx[] = 
	//{
	//	//���
	//	{{0.5f * cosf(XMConvertToRadians(40.0f)), 0.5f, 0.5f * sinf(XMConvertToRadians(40.0f))}, {0.5f * cosf(XMConvertToRadians(40.0f)) + 0.5f, 0.5f * sinf(XMConvertToRadians(40.0f)) + 0.5f} },		//0
	//	{{0.5f * cosf(XMConvertToRadians( 0.0f)), 0.5f, 0.5f * sinf(XMConvertToRadians( 0.0f))}, {0.5f * cosf(XMConvertToRadians( 0.0f)) + 0.5f, 0.5f * sinf(XMConvertToRadians( 0.0f)) + 0.5f} },			//1
	//	{{0.0f, 0.5f, 0.0f}, {0.0f + 0.5f, 0.0f + 0.5f} },																			//2
	//																													//
	//	{{0.5f * cosf(XMConvertToRadians(80.0f)), 0.5f, 0.5f * sinf(XMConvertToRadians(80.0f))}, {0.5f * cosf(XMConvertToRadians(80.0f)) + 0.5f, 0.5f * sinf(XMConvertToRadians(80.0f)) + 0.5f} },		//3
	//	{{0.5f * cosf(XMConvertToRadians(40.0f)), 0.5f, 0.5f * sinf(XMConvertToRadians(40.0f))}, {0.5f * cosf(XMConvertToRadians(40.0f)) + 0.5f, 0.5f * sinf(XMConvertToRadians(40.0f)) + 0.5f} },		//4
	//	{{0.0f, 0.5f, 0.0f}, {0.0f + 0.5f, 0.0f + 0.5f} },																			//5
	//																													//
	//	{{0.5f * cosf(XMConvertToRadians(120.0f)), 0.5f, 0.5f * sinf(XMConvertToRadians(120.0f))}, {0.5f * cosf(XMConvertToRadians(120.0f)) + 0.5f, 0.5f * sinf(XMConvertToRadians(120.0f)) + 0.5f} },		//6
	//	{{0.5f * cosf(XMConvertToRadians( 80.0f)), 0.5f, 0.5f * sinf(XMConvertToRadians( 80.0f))}, {0.5f * cosf(XMConvertToRadians( 80.0f)) + 0.5f, 0.5f * sinf(XMConvertToRadians( 80.0f)) + 0.5f} },		//7
	//	{{0.0f, 0.5f, 0.0f}, {0.0f + 0.5f, 0.0f + 0.5f} },																			//8
	//																													//
	//	{{0.5f * cosf(XMConvertToRadians(160.0f)), 0.5f, 0.5f * sinf(XMConvertToRadians(160.0f))}, {0.5f * cosf(XMConvertToRadians(160.0f)) + 0.5f, 0.5f * sinf(XMConvertToRadians(160.0f)) + 0.5f} },		//9
	//	{{0.5f * cosf(XMConvertToRadians(120.0f)), 0.5f, 0.5f * sinf(XMConvertToRadians(120.0f))}, {0.5f * cosf(XMConvertToRadians(120.0f)) + 0.5f, 0.5f * sinf(XMConvertToRadians(120.0f)) + 0.5f} },		//10
	//	{{0.0f, 0.5f, 0.0f}, {0.0f + 0.5f, 0.0f + 0.5f} },																			//11
	//																													//
	//	{{0.5f * cosf(XMConvertToRadians(200.0f)), 0.5f, 0.5f * sinf(XMConvertToRadians(200.0f))}, {0.5f * cosf(XMConvertToRadians(200.0f)) + 0.5f, 0.5f * sinf(XMConvertToRadians(200.0f)) + 0.5f} },		//12
	//	{{0.5f * cosf(XMConvertToRadians(160.0f)), 0.5f, 0.5f * sinf(XMConvertToRadians(160.0f))}, {0.5f * cosf(XMConvertToRadians(160.0f)) + 0.5f, 0.5f * sinf(XMConvertToRadians(160.0f)) + 0.5f} },		//13
	//	{{0.0f, 0.5f, 0.0f}, {0.0f + 0.5f, 0.0f + 0.5f} },																			//14
	//																													//
	//	{{0.5f * cosf(XMConvertToRadians(240.0f)), 0.5f, 0.5f * sinf(XMConvertToRadians(240.0f))}, {0.5f * cosf(XMConvertToRadians(240.0f)) + 0.5f, 0.5f * sinf(XMConvertToRadians(240.0f)) + 0.5f} },		//15
	//	{{0.5f * cosf(XMConvertToRadians(200.0f)), 0.5f, 0.5f * sinf(XMConvertToRadians(200.0f))}, {0.5f * cosf(XMConvertToRadians(200.0f)) + 0.5f, 0.5f * sinf(XMConvertToRadians(200.0f)) + 0.5f} },		//16
	//	{{0.0f, 0.5f, 0.0f}, {0.0f + 0.5f, 0.0f + 0.5f} },																			//17
	//																													//
	//	{{0.5f * cosf(XMConvertToRadians(280.0f)), 0.5f, 0.5f * sinf(XMConvertToRadians(280.0f))}, {0.5f * cosf(XMConvertToRadians(280.0f)) + 0.5f, 0.5f * sinf(XMConvertToRadians(280.0f)) + 0.5f} },		//18
	//	{{0.5f * cosf(XMConvertToRadians(240.0f)), 0.5f, 0.5f * sinf(XMConvertToRadians(240.0f))}, {0.5f * cosf(XMConvertToRadians(240.0f)) + 0.5f, 0.5f * sinf(XMConvertToRadians(240.0f)) + 0.5f} },		//19
	//	{{0.0f, 0.5f, 0.0f}, {0.0f + 0.5f, 0.0f + 0.5f} },																			//20
	//																													//
	//	{{0.5f * cosf(XMConvertToRadians(320.0f)), 0.5f, 0.5f * sinf(XMConvertToRadians(320.0f))}, {0.5f * cosf(XMConvertToRadians(320.0f)) + 0.5f, 0.5f * sinf(XMConvertToRadians(320.0f)) + 0.5f} },		//21
	//	{{0.5f * cosf(XMConvertToRadians(280.0f)), 0.5f, 0.5f * sinf(XMConvertToRadians(280.0f))}, {0.5f * cosf(XMConvertToRadians(280.0f)) + 0.5f, 0.5f * sinf(XMConvertToRadians(280.0f)) + 0.5f} },		//22
	//	{{0.0f, 0.5f, 0.0f}, {0.0f + 0.5f, 0.0f + 0.5f} },																			//23
	//																													//
	//	{{0.5f * cosf(XMConvertToRadians(360.0f)), 0.5f, 0.5f * sinf(XMConvertToRadians(360.0f))}, {0.5f * cosf(XMConvertToRadians(360.0f)) + 0.5f, 0.5f * sinf(XMConvertToRadians(360.0f)) + 0.5f} },		//24
	//	{{0.5f * cosf(XMConvertToRadians(320.0f)), 0.5f, 0.5f * sinf(XMConvertToRadians(320.0f))}, {0.5f * cosf(XMConvertToRadians(320.0f)) + 0.5f, 0.5f * sinf(XMConvertToRadians(320.0f)) + 0.5f} },		//25
	//	{{0.0f, 0.5f, 0.0f}, {0.0f + 0.5f, 0.0f + 0.5f} },																			//26
	//																													//
	//	//����																										  /	 /
	//	{{0.5f * cosf(XMConvertToRadians(0.0f)), -0.5f, 0.5f * sinf(XMConvertToRadians(0.0f))}, {0.0f, 0.0f} },			//27
	//	{{0.5f * cosf(XMConvertToRadians(40.0f)), -0.5f, 0.5f * sinf(XMConvertToRadians(40.0f))}, {0.0f, 1.0f} },		//28
	//	{{0.0f, -0.5f, 0.0f}, {0.5f, 1.0f} },																			//29
	//																													//
	//	{{0.5f * cosf(XMConvertToRadians(40.0f)), -0.5f, 0.5f * sinf(XMConvertToRadians(40.0f))}, {0.0f, 0.0f} },		//30
	//	{{0.5f * cosf(XMConvertToRadians(80.0f)), -0.5f, 0.5f * sinf(XMConvertToRadians(80.0f))}, {0.0f, 1.0f} },		//31
	//	{{0.0f, -0.5f, 0.0f}, {0.5f, 1.0f} },																			//32
	//																													//
	//	{{0.5f * cosf(XMConvertToRadians(80.0f)), -0.5f, 0.5f * sinf(XMConvertToRadians(80.0f))}, {0.0f, 0.0f} },		//33
	//	{{0.5f * cosf(XMConvertToRadians(120.0f)), -0.5f, 0.5f * sinf(XMConvertToRadians(120.0f))}, {0.0f, 1.0f} },		//34
	//	{{0.0f, -0.5f, 0.0f}, {0.5f, 1.0f} },																			//35
	//																													//
	//	{{0.5f * cosf(XMConvertToRadians(120.0f)), -0.5f, 0.5f * sinf(XMConvertToRadians(120.0f))}, {0.0f, 0.0f} },		//36
	//	{{0.5f * cosf(XMConvertToRadians(160.0f)), -0.5f, 0.5f * sinf(XMConvertToRadians(160.0f))}, {0.0f, 1.0f} },		//37
	//	{{0.0f, -0.5f, 0.0f}, {0.5f, 1.0f} },																			//38
	//																													//
	//	{{0.5f * cosf(XMConvertToRadians(160.0f)), -0.5f, 0.5f * sinf(XMConvertToRadians(160.0f))}, {0.0f, 0.0f} },		//39
	//	{{0.5f * cosf(XMConvertToRadians(200.0f)), -0.5f, 0.5f * sinf(XMConvertToRadians(200.0f))}, {0.0f, 1.0f} },		//40
	//	{{0.0f, -0.5f, 0.0f}, {0.5f, 1.0f} },																			//41
	//																													//
	//	{{0.5f * cosf(XMConvertToRadians(200.0f)), -0.5f, 0.5f * sinf(XMConvertToRadians(200.0f))}, {0.0f, 0.0f} },		//42
	//	{{0.5f * cosf(XMConvertToRadians(240.0f)), -0.5f, 0.5f * sinf(XMConvertToRadians(240.0f))}, {0.0f, 1.0f} },		//43
	//	{{0.0f, -0.5f, 0.0f}, {0.5f, 1.0f} },																			//44
	//																													//
	//	{{0.5f * cosf(XMConvertToRadians(240.0f)), -0.5f, 0.5f * sinf(XMConvertToRadians(240.0f))}, {0.0f, 0.0f} },		//45
	//	{{0.5f * cosf(XMConvertToRadians(280.0f)), -0.5f, 0.5f * sinf(XMConvertToRadians(280.0f))}, {0.0f, 1.0f} },		//46
	//	{{0.0f, -0.5f, 0.0f}, {0.5f, 1.0f} },																			//47
	//																													//
	//	{{0.5f * cosf(XMConvertToRadians(280.0f)), -0.5f, 0.5f * sinf(XMConvertToRadians(280.0f))}, {0.0f, 0.0f} },		//48
	//	{{0.5f * cosf(XMConvertToRadians(320.0f)), -0.5f, 0.5f * sinf(XMConvertToRadians(320.0f))}, {0.0f, 1.0f} },		//49
	//	{{0.0f, -0.5f, 0.0f}, {0.5f, 1.0f} },																			//50
	//																													//
	//	{{0.5f * cosf(XMConvertToRadians(320.0f)), -0.5f, 0.5f * sinf(XMConvertToRadians(320.0f))}, {0.0f, 0.0f} },		//51
	//	{{0.5f * cosf(XMConvertToRadians(360.0f)), -0.5f, 0.5f * sinf(XMConvertToRadians(360.0f))}, {0.0f, 1.0f} },		//52
	//	{{0.0f, -0.5f, 0.0f}, {0.5f, 1.0f} },																			//53
	//																													//
	//	//�T�C�h																										 //
	//	{{0.5f * cosf(XMConvertToRadians( 0.0f)),  0.5f, 0.5f * sinf(XMConvertToRadians( 0.0f))}, {0.0f, 0.0f}},		//54
	//	{{0.5f * cosf(XMConvertToRadians(40.0f)),  0.5f, 0.5f * sinf(XMConvertToRadians(40.0f))}, {1.0f, 0.0f}},		//55
	//	{{0.5f * cosf(XMConvertToRadians( 0.0f)), -0.5f, 0.5f * sinf(XMConvertToRadians( 0.0f))}, {0.0f, 1.0f}},		//56
	//	{{0.5f * cosf(XMConvertToRadians(40.0f)), -0.5f, 0.5f * sinf(XMConvertToRadians(40.0f))}, {1.0f, 1.0f}},		//57
	//																													//
	//	{{0.5f * cosf(XMConvertToRadians(40.0f)),  0.5f, 0.5f * sinf(XMConvertToRadians(40.0f))}, {0.0f, 0.0f}},		//58
	//	{{0.5f * cosf(XMConvertToRadians(80.0f)),  0.5f, 0.5f * sinf(XMConvertToRadians(80.0f))}, {1.0f, 0.0f}},		//59
	//	{{0.5f * cosf(XMConvertToRadians(40.0f)), -0.5f, 0.5f * sinf(XMConvertToRadians(40.0f))}, {0.0f, 1.0f}},		//60
	//	{{0.5f * cosf(XMConvertToRadians(80.0f)), -0.5f, 0.5f * sinf(XMConvertToRadians(80.0f))}, {1.0f, 1.0f}},		//61
	//																													//
	//	{{0.5f * cosf(XMConvertToRadians( 80.0f)),  0.5f, 0.5f * sinf(XMConvertToRadians( 80.0f))}, {0.0f, 0.0f}},		//62
	//	{{0.5f * cosf(XMConvertToRadians(120.0f)),  0.5f, 0.5f * sinf(XMConvertToRadians(120.0f))}, {1.0f, 0.0f}},		//63
	//	{{0.5f * cosf(XMConvertToRadians( 80.0f)), -0.5f, 0.5f * sinf(XMConvertToRadians( 80.0f))}, {0.0f, 1.0f}},		//64
	//	{{0.5f * cosf(XMConvertToRadians(120.0f)), -0.5f, 0.5f * sinf(XMConvertToRadians(120.0f))}, {1.0f, 1.0f}},		//65
	//																													//
	//	{{0.5f * cosf(XMConvertToRadians(120.0f)),  0.5f, 0.5f * sinf(XMConvertToRadians(120.0f))}, {0.0f, 0.0f}},		//66
	//	{{0.5f * cosf(XMConvertToRadians(160.0f)),  0.5f, 0.5f * sinf(XMConvertToRadians(160.0f))}, {1.0f, 0.0f}},		//67
	//	{{0.5f * cosf(XMConvertToRadians(120.0f)), -0.5f, 0.5f * sinf(XMConvertToRadians(120.0f))}, {0.0f, 1.0f}},		//68
	//	{{0.5f * cosf(XMConvertToRadians(160.0f)), -0.5f, 0.5f * sinf(XMConvertToRadians(160.0f))}, {1.0f, 1.0f}},		//69
	//																													//
	//	{{0.5f * cosf(XMConvertToRadians(160.0f)),  0.5f, 0.5f * sinf(XMConvertToRadians(160.0f))}, {0.0f, 0.0f}},		//70
	//	{{0.5f * cosf(XMConvertToRadians(200.0f)),  0.5f, 0.5f * sinf(XMConvertToRadians(200.0f))}, {1.0f, 0.0f}},		//71
	//	{{0.5f * cosf(XMConvertToRadians(160.0f)), -0.5f, 0.5f * sinf(XMConvertToRadians(160.0f))}, {0.0f, 1.0f}},		//72
	//	{{0.5f * cosf(XMConvertToRadians(200.0f)), -0.5f, 0.5f * sinf(XMConvertToRadians(200.0f))}, {1.0f, 1.0f}},		//73
	//																													//
	//	{ {0.5f * cosf(XMConvertToRadians(200.0f)),  0.5f, 0.5f * sinf(XMConvertToRadians(200.0f))}, {0.0f, 0.0f} },	//74
	//	{ {0.5f * cosf(XMConvertToRadians(240.0f)),  0.5f, 0.5f * sinf(XMConvertToRadians(240.0f))}, {1.0f, 0.0f} },	//75
	//	{ {0.5f * cosf(XMConvertToRadians(200.0f)), -0.5f, 0.5f * sinf(XMConvertToRadians(200.0f))}, {0.0f, 1.0f} },	//76
	//	{ {0.5f * cosf(XMConvertToRadians(240.0f)), -0.5f, 0.5f * sinf(XMConvertToRadians(240.0f))}, {1.0f, 1.0f} },	//77
	//																													//
	//	{ {0.5f * cosf(XMConvertToRadians(240.0f)),  0.5f, 0.5f * sinf(XMConvertToRadians(240.0f))}, {0.0f, 0.0f} },	//78
	//	{ {0.5f * cosf(XMConvertToRadians(280.0f)),  0.5f, 0.5f * sinf(XMConvertToRadians(280.0f))}, {1.0f, 0.0f} },	//79
	//	{ {0.5f * cosf(XMConvertToRadians(240.0f)), -0.5f, 0.5f * sinf(XMConvertToRadians(240.0f))}, {0.0f, 1.0f} },	//80
	//	{ {0.5f * cosf(XMConvertToRadians(280.0f)), -0.5f, 0.5f * sinf(XMConvertToRadians(280.0f))}, {1.0f, 1.0f} },	//81
	//																													//
	//	{ {0.5f * cosf(XMConvertToRadians(280.0f)),  0.5f, 0.5f * sinf(XMConvertToRadians(280.0f))}, {0.0f, 0.0f} },	//82
	//	{ {0.5f * cosf(XMConvertToRadians(320.0f)),  0.5f, 0.5f * sinf(XMConvertToRadians(320.0f))}, {1.0f, 0.0f} },	//83
	//	{ {0.5f * cosf(XMConvertToRadians(280.0f)), -0.5f, 0.5f * sinf(XMConvertToRadians(280.0f))}, {0.0f, 1.0f} },	//84
	//	{ {0.5f * cosf(XMConvertToRadians(320.0f)), -0.5f, 0.5f * sinf(XMConvertToRadians(320.0f))}, {1.0f, 1.0f} },	//85
	//																													//
	//	{ {0.5f * cosf(XMConvertToRadians(320.0f)),  0.5f, 0.5f * sinf(XMConvertToRadians(320.0f))}, {0.0f, 0.0f} },	//86
	//	{ {0.5f * cosf(XMConvertToRadians(360.0f)),  0.5f, 0.5f * sinf(XMConvertToRadians(360.0f))}, {1.0f, 0.0f} },	//87
	//	{ {0.5f * cosf(XMConvertToRadians(320.0f)), -0.5f, 0.5f * sinf(XMConvertToRadians(320.0f))}, {0.0f, 1.0f} },	//88
	//	{ {0.5f * cosf(XMConvertToRadians(360.0f)), -0.5f, 0.5f * sinf(XMConvertToRadians(360.0f))}, {1.0f, 1.0f} },	//89
	//};
	
	std::vector<GeometoryVertex> vector;

	//���
	for (int Angle = 0; Angle < 360; Angle += 24)
	{
		GeometoryVertex tempVtx[3];

		tempVtx[0].pos = { 0.5f * cosf(XMConvertToRadians(Angle + 24)), 0.5f, 0.5f * sinf(XMConvertToRadians(Angle + 24)) };
		tempVtx[1].pos = { 0.5f * cosf(XMConvertToRadians(Angle)), 0.5f, 0.5f * sinf(XMConvertToRadians(Angle)) };
		tempVtx[2].pos = { 0.0f, 0.5f, 0.0f };

		tempVtx[0].normal = { 0.0f, 1.0f, 0.0f };
		tempVtx[1].normal = { 0.0f, 1.0f, 0.0f };
		tempVtx[2].normal = { 0.0f, 1.0f, 0.0f };

		tempVtx[0].uv = { tempVtx[0].pos.x + 0.5f, tempVtx[0].pos.z + 0.5f };
		tempVtx[1].uv = { tempVtx[1].pos.x + 0.5f, tempVtx[1].pos.z + 0.5f };
		tempVtx[2].uv = { tempVtx[2].pos.x + 0.5f, tempVtx[2].pos.z + 0.5f };

		for (int i = 0; i < 3; i++)
		{
			vector.push_back(tempVtx[i]);
		}
	}

	//����
	for (int Angle = 0; Angle < 360; Angle += 24)
	{
		GeometoryVertex tempVtx[3];

		tempVtx[0].pos = { 0.5f * cosf(XMConvertToRadians(Angle)), -0.5f, 0.5f * sinf(XMConvertToRadians(Angle)) };
		tempVtx[1].pos = { 0.5f * cosf(XMConvertToRadians(Angle + 24)), -0.5f, 0.5f * sinf(XMConvertToRadians(Angle + 24)) };
		tempVtx[2].pos = { 0.0f, -0.5f, 0.0f };

		tempVtx[0].normal = { 0.0f, -1.0f, 0.0f };
		tempVtx[1].normal = { 0.0f, -1.0f, 0.0f };
		tempVtx[2].normal = { 0.0f, -1.0f, 0.0f };

		tempVtx[0].uv = { tempVtx[0].pos.x + 0.5f, tempVtx[0].pos.z + 0.5f };
		tempVtx[1].uv = { tempVtx[1].pos.x + 0.5f, tempVtx[1].pos.z + 0.5f };
		tempVtx[2].uv = { tempVtx[2].pos.x + 0.5f, tempVtx[2].pos.z + 0.5f };

		for (int i = 0; i < 3; i++)
		{
			vector.push_back(tempVtx[i]);
		}
	}

	//�T�C�h
	for (int Angle = 0; Angle < 360; Angle += 24)
	{
		GeometoryVertex tempVtx[4];

		tempVtx[0].pos = { 0.5f * cosf(XMConvertToRadians(Angle))		, 0.5f	, 0.5f * sinf(XMConvertToRadians(Angle)) };
		tempVtx[1].pos = { 0.5f * cosf(XMConvertToRadians(Angle + 24))	, 0.5f	, 0.5f * sinf(XMConvertToRadians(Angle + 24)) };
		tempVtx[2].pos = { 0.5f * cosf(XMConvertToRadians(Angle))		, -0.5f	, 0.5f * sinf(XMConvertToRadians(Angle)) };
		tempVtx[3].pos = { 0.5f * cosf(XMConvertToRadians(Angle + 24))	, -0.5f	, 0.5f * sinf(XMConvertToRadians(Angle + 24)) };

		tempVtx[0].normal = { 1.0f, 0.0f, 0.0f };
		tempVtx[1].normal = { 1.0f, 0.0f, 0.0f };
		tempVtx[2].normal = { 1.0f, 0.0f, 0.0f };
		tempVtx[3].normal = { 1.0f, 0.0f, 0.0f };

		tempVtx[0].uv = { 0.0f, 0.0f };
		tempVtx[1].uv = { 1.0f, 0.0f };
		tempVtx[2].uv = { 0.0f, 1.0f };
		tempVtx[3].uv = { 1.0f, 1.0f };

		for (int i = 0; i < 4; i++)
		{
			vector.push_back(tempVtx[i]);
		}
	}

	std::vector<int> nIdx;

	//�㉺��
	for (int i = 0; i < 90; i++)
	{
		nIdx.push_back(i);
	}

	//�T�C�h
	for (int Angle = 0; Angle < 360; Angle += 24)
	{
		int num = 90 + 4 * (Angle / 24);

		nIdx.push_back(num);
		nIdx.push_back(num + 1);
		nIdx.push_back(num + 2);

		nIdx.push_back(num + 2);
		nIdx.push_back(num + 1);
		nIdx.push_back(num + 3);
	}

	MeshBuffer::Description desc = {};
	desc.pVtx = vector.data();	//���_���
	desc.vtxCount = vector.size();	//���_�̐�
	desc.vtxSize = sizeof(GeometoryVertex);		//���_1�̃f�[�^�T�C�Y
	desc.pIdx = nIdx.data();	//�����q�����ԁi�C���f�b�N�X�j
	desc.idxCount = nIdx.size();	//�C���f�b�N�X�̐�
	desc.idxSize = sizeof(int);		//�C���f�b�N�X1�̃f�[�^�T�C�Y
	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;		//�ǂ̌`�̃|���S������邩�ݒ肷��



	//���̐���
	g_pGeometoryCylinder = new MeshBuffer(desc);

}
void CreateGeometoryCone()
{
}
void CreateGeometoryCapsule()
{
}

void CreateGeometoryShader()
{
	const char* GeometoryVS = R"EOT(
struct VS_IN {
	float3 pos    : POSITION0;
    float3 normal : NORMAL; 
	float2 uv     : TEXCOORD0;
};
struct VS_OUT {
	float4 pos    : SV_POSITION;
    float3 normal : NORMAL;
	float2 uv     : TEXCOORD0;
    float4 color  : COLOR;
	float4 wPos   : TEXCOORD1;
};
cbuffer WVP : register(b0) {
	float4x4 world;
	float4x4 view;
	float4x4 proj;
};
cbuffer COLOR : register(b1) {
    float4 geometoryColor;
};
VS_OUT main(VS_IN vin) {
	VS_OUT vout;
	vout.pos = float4(vin.pos, 1.0f);
	vout.pos = mul(vout.pos, world);
	vout.wPos = vout.pos;
	vout.pos = mul(vout.pos, view);
	vout.pos = mul(vout.pos, proj);
    vout.normal = mul(vin.normal, world);
	vout.uv = vin.uv;
    vout.color = geometoryColor;
	return vout;
})EOT";
	const char* GeometoryPS = R"EOT(
struct PS_IN {
	float4 pos    : SV_POSITION;
    float3 normal : NORMAL;
	float2 uv     : TEXCOORD0;
    float4 color  : COLOR;
	float4 wPos   : TEXCOORD1;	
};
cbuffer LIGHT : register(b0) {
    float3 ptPos;
    float3 ptCol;
	float ptRange;        
    float3 spPos;
    float3 spCol;
    float spRange;
    float3 spDir;
	float spAng;
	float3 eyePos;
	float3 amCol;
};
float3 CalcLambertFromLight(float3 Direction, float3 Color, float3 Pixelnormal);
float3 CalcPhongSpecularFromLight(float3 Direction, float3 Color, float3 wPos, float3 Pixelnormal);
float3 CalcLightFromPointLight(PS_IN pin);
float3 CalcLightFromSpotLight(PS_IN pin);
float4 main(PS_IN pin) : SV_TARGET
{
	float4 color = pin.color;
    pin.normal = normalize(pin.normal);
    float3 pointLig = CalcLightFromPointLight(pin); float3 spotLig = CalcLightFromSpotLight(pin); 
    float3 finalLig = pointLig + spotLig + amCol;
    color.rgb *= finalLig; 
	//float2 mGrid = floor(abs(pin.uv) * 2.0f);
	//float2 sGrid = floor(abs(pin.uv) * 8.0f);
	//float mid = fmod(mGrid.x + mGrid.y, 2.0f);
	//float small = fmod(sGrid.x + sGrid.y, 2.0f);
	//color.rgb = ((mid * 0.1f) * small + 0.45f) + (1 - small) * 0.05f;
	return color;
}
float3 CalcLambertFromLight(float3 Direction, float3 Color, float3 Pixelnormal){
    float t = dot(Pixelnormal, Direction) * -1.0f; t = max(0.0f, t); return Color * t;
}
float3 CalcPhongSpecularFromLight(float3 Direction, float3 Color, float3 wPos, float3 Pixelnormal){
   float3 refVec = reflect(Direction, Pixelnormal); float3 toEye = eyePos - wPos; toEye = normalize(toEye);
   float t = dot(refVec, toEye); t = max(0.0f, t); t = pow(t, 3.0f); return Color * t;
}
float3 CalcLightFromPointLight(PS_IN pin)
{
    float3 ptIncidentVec = pin.wPos - ptPos; ptIncidentVec = normalize(ptIncidentVec);    
    float3 diffusePtLig = CalcLambertFromLight(ptIncidentVec, ptCol, pin.normal); float3 specularPtLig = CalcPhongSpecularFromLight(ptIncidentVec, ptCol, pin.wPos, pin.normal);
    float3 distance = length(pin.wPos - ptPos); float affect = 1.0f - 1.0f / ptRange * distance;
    if (affect < 0.0f) affect = 0.0f;
    affect = pow(affect, 0.5f); diffusePtLig *= affect; specularPtLig *= affect;
    return diffusePtLig + specularPtLig;
}
float3 CalcLightFromSpotLight(PS_IN pin)
{
   float3 spIncidentVec = pin.wPos - spPos; spIncidentVec = normalize(spIncidentVec);
   float3 diffuseSpLig = CalcLambertFromLight(spIncidentVec, spCol, pin.normal); float3 specularSpLig = CalcPhongSpecularFromLight(spIncidentVec, spCol, pin.wPos, pin.normal);
   float3 distance = length(pin.wPos - spPos); float affect = 1.0f - 1.0f / spRange * distance; 
   if (affect < 0.0f) affect = 0.0f; 
   affect = pow(affect, 2.0f); diffuseSpLig *= affect; specularSpLig *= affect;
   float angle = dot(spIncidentVec, spDir); angle = abs(acos(angle)); affect = 1.0f - 1.0f / spAng * angle; 
   if (affect < 0.0f) affect = 0.0f;
   affect = pow(affect, 0.5f); diffuseSpLig *= affect; specularSpLig *= affect; 
   return diffuseSpLig + specularSpLig;
}
)EOT";

	g_pGeometoryVS = new VertexShader();
	_ASSERT_EXPR(SUCCEEDED(g_pGeometoryVS->Compile(GeometoryVS)),
		L"create failed geometory vertex shader.");
	g_pGeometoryPS = new PixelShader();
	_ASSERT_EXPR(SUCCEEDED(g_pGeometoryPS->Compile(GeometoryPS)),
		L"create failed geometory pixel shader.");
}

void CreateGeometoryConstantBuffer()
{
	g_pGeometoryWVP = new ConstantBuffer();
	g_pGeometoryWVP->Create(sizeof(g_geometoryMat));
	g_geometoryTransform[0] = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_geometoryTransform[1] = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_geometoryTransform[2] = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
	UpdateGeometoryMatrix();

	g_geometoryMat[0]._11 = 1.0f;
	g_geometoryMat[0]._22 = 1.0f;
	g_geometoryMat[0]._33 = 1.0f;
	g_geometoryMat[0]._44 = 1.0f;
	g_pGeometoryColor = new ConstantBuffer();
	g_pGeometoryColor->Create(sizeof(g_geometoryColor));
	g_geometoryColor.Color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	UpdateGeometoryColor();
	g_pGeometoryLight = new ConstantBuffer();
	g_pGeometoryLight->Create(sizeof(g_geometoryLight));
	g_geometoryLight.eyePos = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_pLight->InitPtLig(g_geometoryLight);
	g_pLight->InitSpLig(g_geometoryLight);
	g_pLight->InitAmLig(g_geometoryLight);
	UpdateGeometoryLight();
}

void UpdateGeometoryMatrix()
{
	//���[���h�s��
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(
							g_geometoryTransform[0].x, g_geometoryTransform[0].y, g_geometoryTransform[0].z);	//�ړ�
	DirectX::XMMATRIX Rx = DirectX::XMMatrixRotationX(g_geometoryTransform[1].x);	//X��]
	DirectX::XMMATRIX Ry = DirectX::XMMatrixRotationY(g_geometoryTransform[1].y);	//Y��]
	DirectX::XMMATRIX Rz = DirectX::XMMatrixRotationZ(g_geometoryTransform[1].z);	//Z��]
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(
							g_geometoryTransform[2].x, g_geometoryTransform[2].y, g_geometoryTransform[2].z);	//�g�k
	DirectX::XMMATRIX mat = S * Rx * Ry * Rz * T;		//�ЂƂɂ܂Ƃ߂�i1�̍s�񂵂��n���Ȃ����߁j

	//�]�u���ăV�F�[�_�[�Ɠ������т̍s������
	mat = DirectX::XMMatrixTranspose(mat);

	//4x4�ɕϊ�����
	DirectX::XMStoreFloat4x4(&g_geometoryMat[0], mat);

	//�萔�o�b�t�@�ɏ�������
	g_pGeometoryWVP->Write(g_geometoryMat);
}

void UpdateGeometoryColor(){
	g_pGeometoryColor->Write(&g_geometoryColor);
}

void UpdateGeometoryLight(){
	g_pGeometoryLight->Write(&g_geometoryLight);
}