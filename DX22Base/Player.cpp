#include "Player.h"
#include "Input.h"

//using namespace DirectX;

Player::Player()
	:m_Pos{2.0f, -1.0f, 0.0f}
	,m_Rot{0.0f, -90.0f, 0.0f}
	,m_Ground(true)
	,m_Move{0.0f, 0.0f, 0.0f}
{
	//モデル読み込み
	m_pModel = new Model;
	if (!m_pModel->Load("Assets/もこ田めめめ/MokotaMememe.pmx", 0.05f))
	{
		MessageBox(NULL, "モデルの生成に失敗", "エラー", MB_OK);
	}

	//頂点シェーダ読み込み
	m_pVS = new VertexShader;
	if (FAILED(m_pVS->Load("Assets/Shader/ModelVS.cso")))
	{
		MessageBox(NULL, "プレイヤーのVS読み込み失敗", "エラー", MB_OK);
	}

	//頂点シェーダをモデルに設定
	m_pModel->SetVertexShader(m_pVS);

	//WVP生成
	m_pWVP = new ConstantBuffer;
	if (FAILED(m_pWVP->Create(sizeof(DirectX::XMFLOAT4X4) * 3)))
	{
		MessageBox(NULL, "pWVP作成失敗", "エラー", MB_OK);
	}
}

Player::~Player()
{
	delete m_pWVP;
	delete m_pVS;
	delete m_pModel;
}

void Player::Update()
{
	//定数定義
	const float PLAYER_MOVE = 0.1f;

	//ローカル変数宣言
	XMFLOAT3 CamPos = m_pCamera->GetPos();		//カメラPos
	XMFLOAT3 CamLook = m_pCamera->GetLook();	//カメラLook
	CamPos.y = CamLook.y = 0.0f;
	XMVECTOR vCamPos = XMLoadFloat3(&CamPos);	//カメラPosをVectorに置き換える
	XMVECTOR vCamLook = XMLoadFloat3(&CamLook);	//カメラLookをVectorに置き換える

	XMVECTOR vFroat;		//カメラの正面方向のベクトル
	vFroat = vCamLook - vCamPos;
	vFroat = XMVector3Normalize(vFroat);		//正規化

	XMMATRIX matRotSide = XMMatrixRotationY(XMConvertToRadians(90.0f));		//Y軸に90度（右方向）に回転する回転行列を生成
	matRotSide = XMMatrixTranspose(matRotSide);
	XMVECTOR vSide = XMVector3TransformCoord(vFroat, matRotSide);	//正面方向のベクトルを90度回転させて
																	//真横のベクトルをとる

	//XMMATRIX matRotUp = XMMatrixRotationX(XMConvertToRadians(90.0f));

	//移動量カット
	m_Move = { 0.0f, m_Move.y, 0.0f };

	//移動処理
	XMVECTOR vMove = XMVectorZero();	//初期化
	//if (IsKeyPress('W'))	vMove += vFroat;	//前
	//if (IsKeyPress('S'))	vMove -= vFroat;	//後ろ
	//if (IsKeyPress('A'))	
	//	vMove -= vSide;		//左
	//if (IsKeyPress('D'))	vMove += vSide;		//右
	vMove = XMVectorScale(vMove, 0.2f);		//定数倍かけて移動の大きさを適切にする

	XMFLOAT3 move;	//Posに反映させるための変数
	XMStoreFloat3(&move, vMove);	//XMVECTORをXMFLOAT3に置き換える

	if (IsKeyPress('D'))	m_Move.x -= 0.1f;
	if (IsKeyPress('A'))	m_Move.x += 0.1f;
/*
	m_Move.x += move.x;
	m_Move.y += move.y;
	m_Move.z += move.z;
*/
	
	//ジャンプ
	if (IsKeyTrigger(VK_SPACE))
	{
		m_Move.y += 0.5f;
		m_Ground = false;
	}

	if (!m_Ground)
	{
		m_Move.y -= 0.03f;
	}

	m_Pos.x += m_Move.x;
	m_Pos.y += m_Move.y;
	m_Pos.z += m_Move.z;

	if (m_Pos.y < -50.0f)
	{
		m_Pos.y = 5.0f;
		m_Move.y = 0.0f;
	}
}

void Player::Draw()
{
	if (!m_pCamera)	return;		//カメラが設定されてなければ処理しない
	XMFLOAT3 ConvertRot = { XMConvertToRadians(m_Rot.x), XMConvertToRadians(m_Rot.y), XMConvertToRadians(m_Rot.z) };
	XMFLOAT4X4 mat[3];
	XMMATRIX temp =	XMMatrixRotationX(ConvertRot.x) * XMMatrixRotationY(ConvertRot.y) * XMMatrixRotationZ(ConvertRot.z) * XMMatrixTranslation(m_Pos.x, m_Pos.y, m_Pos.z);
	XMStoreFloat4x4(&mat[0], XMMatrixTranspose(temp));	//ワールド行列
	mat[1] = m_pCamera->GetViewMatrix();		//ビュー行列
	mat[2] = m_pCamera->GetProjectionMatrix(CameraBase::CameraAngle::E_CAM_ANGLE_PERSPECTIVEFOV);	//プロジェクション行列
	m_pWVP->Write(mat);		//WVP設定
	m_pWVP->BindVS(0);
	m_pModel->Draw();
}

void Player::SetCamera(CameraBase* pCamera)
{
	m_pCamera = pCamera;
}

XMFLOAT3 Player::GetPos()
{
	return m_Pos;
}
