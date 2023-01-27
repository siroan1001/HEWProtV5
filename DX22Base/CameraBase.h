#ifndef _____CAMERA_BASE_H____
#define _____CAMERA_BASE_H____

#include <DirectXMath.h>
#include "Def.h"

using namespace DirectX;

//class Object;

class CameraBase
{
public:
	enum CameraAngle
	{
		E_CAM_ANGLE_PERSPECTIVEFOV = 0,
		E_CAM_ANGLE_ORTHOGRAPHIC,

		E_CAM_ANGLE_MAX
	};

public:
	CameraBase()
		:m_pos(0.0f, 0.0f, 3.0f), m_look(0.0f, 0.0f, 0.0f), m_up(0.0f, 1.0f, 0.0f)
		,m_fovy(60.0f), m_aspect(16.0f / 9.0f), m_near(0.2f), m_far(1000.0f)
		,m_radXZ(0.0f), m_radY(0.0f), m_radius(3.0f)
	{
		m_Info = { m_look, {8.0f, 4.5f, 0.0f}, {0.0f, 0.0f, 0.0f} };
	}
	virtual ~CameraBase() {};
	virtual void Update() = 0;

	void SetLook(XMFLOAT3 pod) { m_look = pod; }

	XMFLOAT3 GetPos() { return m_pos; }
	XMFLOAT3 GetLook() { return m_look; }

	XMFLOAT4X4 GetViewMatrix()
	{
		XMFLOAT4X4 mat;
		XMMATRIX view;
		view = XMMatrixLookAtLH(
			XMVectorSet(m_pos.x, m_pos.y, m_pos.z, 1.0f),
			XMVectorSet(m_look.x, m_look.y, m_look.z, 1.0f),
			XMVectorSet(m_up.x, m_up.y, m_up.z, 1.0f)
		);
		view = XMMatrixTranspose(view);
		XMStoreFloat4x4(&mat, view);
		return mat;
	}

	DirectX::XMFLOAT4X4 GetProjectionMatrix(CameraAngle angle)
	{
		XMFLOAT4X4 mat;
		XMMATRIX proj;
		switch (angle)
		{
		case CameraBase::E_CAM_ANGLE_PERSPECTIVEFOV:
			proj = XMMatrixPerspectiveFovLH(
				XMConvertToRadians(m_fovy),
				m_aspect,
				m_near,
				m_far
			);
			break;
		case CameraBase::E_CAM_ANGLE_ORTHOGRAPHIC:
			proj = XMMatrixOrthographicLH(
				XMConvertToRadians(m_fovy),
				m_aspect,
				m_near,
				m_far
			);
			proj *= XMMatrixScaling(0.1f, 0.3f, 1.0f);
			break;
		default:
			break;
		}
		
		proj = XMMatrixTranspose(proj);
		DirectX::XMStoreFloat4x4(&mat, proj);
		return mat;
	}

	Def::Info GetInfo()
	{
		return m_Info;
	}
protected:
	XMFLOAT3 m_pos, m_look, m_up;		//ビュー行列の設定に必要な変数
	float m_fovy, m_aspect, m_near, m_far;		//プロジェクション行列の設定に必要な変数
	float m_radXZ, m_radY;		//回り込みの角度
	float m_radius;		//注視点からカメラの距離
	Def::Info m_Info;
};

#endif // !_____CAMERA_BASE_H____
