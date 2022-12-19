#include "Game3D.h"
#include "Geometory.h"
#include "Input.h"
#include "CameraBase.h"
#include "CameraDebug.h"
//#include "CameraPlayer.h"
//#include "CameraEvent.h"
#include "CameraMain.h"
#include "Stage.h"
#include "ShadowBlock.h"
#include "Light.h"
#include "Collision.h"
#include "Fade.h"

Fade* g_pFade;

Game3D::Game3D()
	:m_cylinderFlag(false)
{
	//ステージの生成
	m_pStage = new Stage;

	//プレイヤーの生成
	m_pPlayer = new Player;

	g_pFade = new Fade;

	m_mainCamera = E_CAM_MAIN;
	m_pCamera[E_CAM_MAIN] = new CameraMain(m_pPlayer);
	m_pCamera[E_CAM_DEBUG] = new CameraDebug;

	m_pShadowBlock = new ShadowBlock;
	Stage::Info info = { {0.0f, 0.5f, 0.0f}, {1.0f, 1.5f, 1.0f}, {0.0f, 0.0f, 0.0f} };
	m_pShadowBlock->SetShadowBlock(info);

	m_pLight = new Light;

	m_pPlayer->SetCamera(m_pCamera[m_mainCamera]);
	m_pPlayer->InitDirection(m_pStage->GetNum() + m_pShadowBlock->GetNum());

	// 画像合成方法の設定
	m_pBlend = new BlendState;

	D3D11_RENDER_TARGET_BLEND_DESC blend = {};
	blend.BlendEnable = TRUE;
	blend.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	blend.SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blend.SrcBlendAlpha = D3D11_BLEND_ONE;
	blend.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blend.DestBlendAlpha = D3D11_BLEND_ONE;
	blend.BlendOp = D3D11_BLEND_OP_ADD;
	blend.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	m_pBlend->Create(blend);
	m_pBlend->Bind();

}
Game3D::~Game3D()
{
	delete m_pBlend;
	delete g_pFade;
	//ステージの終了
	//delete m_pStage;
	delete m_pPlayer;
	delete m_pLight;
	delete m_pShadowBlock;

	//カメラの終了
	for (int i = 0; i < E_CAM_MAX; i++)
	{
		delete m_pCamera[i];
	}

}
void Game3D::Update()
{
	if (IsKeyPress('0'))
	{
		g_pFade->StartOut();
	}
	g_pFade->Update();

	//カメラの更新
	m_pCamera[m_mainCamera]->Update();

	m_pShadowBlock->Update();
	m_pLight->Update();
	m_pShadowBlock->Update();

	//プレイヤーの更新
	//カメラがPlayerCameraの場合のみ処理する
	if(m_mainCamera == E_CAM_MAIN)	m_pPlayer->Update();

	//カメラの切り替え
	CameraKind camera = m_mainCamera;
	if (IsKeyPress('C'))
	{
		if (IsKeyTrigger('1'))	camera = E_CAM_DEBUG;
		if (IsKeyTrigger('2'))	camera = E_CAM_MAIN;
	}
	if (m_mainCamera != camera)
	{
		m_mainCamera = camera;
		m_pPlayer->SetCamera(m_pCamera[m_mainCamera]);
	}

	if (IsKeyTrigger('P'))
	{
		m_cylinderFlag ^= 1;
	}

	CheckCollision();
}
void Game3D::Draw()
{
	//ジオメトリーのビュー行列とプロジェクション行列を設定する
	SetGeometoryVPMatrix(m_pCamera[m_mainCamera]->GetViewMatrix(), m_pCamera[m_mainCamera]->GetProjectionMatrix(CameraBase::CameraAngle::E_CAM_ANGLE_PERSPECTIVEFOV));
	
	//ステージの描画
	m_pStage->Draw();

	//プレイヤーの描画
	m_pPlayer->Draw();

	//シャドウブロックの描画
	m_pShadowBlock->Draw();

	//ライトの描画
	m_pLight->Draw(); 
	
	g_pFade->Draw();

	
}

void Game3D::CheckCollision()
{
	
	//ShadowBlockとLigthの判定
	std::vector<std::vector<ShadowBlock::SmallBlockTemp>>* block = m_pShadowBlock->GetInfo();	//シャドウブロックの情報

	for (std::vector<std::vector<ShadowBlock::SmallBlockTemp>>::iterator it = block->begin(); it != block->end(); ++it)
	{
		for (std::vector<ShadowBlock::SmallBlockTemp>::iterator init = it->begin(); init != it->end(); ++init)
		{
			if (Collision::RectAndCircle(init->Info, m_pLight->GetInfo(), m_pLight->GetRadius()))
			{
				init->life -= m_pLight->GetPower();		//シャドウブロックのライフを削る
				if (init->life <= 0.0f)
				{//ライフが０を下回ったら
					init->life = 0.0f;	//０以下にならないように補正
					init->use = false;	//使用してない状態にする
				}
			}
		}
	}

	int num = 0;		//プレイヤーとブロックの当たり判定が何個目かを入れる（前フレームのどの方向に当たったかを確認するのに使う）

	//PlayerとStageの当たり判定
	for (num = 0; num < m_pStage->GetNum(); num++)
	{
		//当たり判定に使う要素
		Stage::Info stage = m_pStage->GetInfo(num);		//ステージブロックの情報
		Stage::Info player = m_pPlayer->GetInfo();		//プレイヤーの情報（プレイヤーの中心をposとする）
		Stage::Info Oplayer = m_pPlayer->GetOldInfo();	//プレイヤーの前フレームの情報
		player.pos.y += player.size.y / 2.0f;		//座標が足元にあるため中心になるように補正
		Oplayer.pos.y += player.size.y / 2.0f;		//座標が足元にあるため中心になるように補正
		

		//どの方向に当たったかを確認する
		if (Collision::Direction dire = Collision::RectAndRectDirection(player, Oplayer, stage, m_pPlayer->GetDirection(num)))
		{
			//補正用pos(足元)
			XMFLOAT3 pos = m_pPlayer->GetInfo().pos;

			switch (dire)
			{//当たった方向に応じての処理
			case Collision::E_DIRECTION_L:	//左
				pos.x = stage.pos.x + stage.size.x / 2.0f + player.size.x / 2.0f;
				break;
			case Collision::E_DIRECTION_R:	//右
				pos.x = stage.pos.x - stage.size.x / 2.0f - player.size.x / 2.0f;
				break;
			case Collision::E_DIRECTION_U:	//上
				pos.y = stage.pos.y + stage.size.y / 2.0f;
				m_pPlayer->ResetMove();		//重力をリセットする
				break;
			case Collision::E_DIRECTION_D:	//下
				pos.y = stage.pos.y - stage.size.y / 2.0f - player.size.y;
				m_pPlayer->ResetMove();
				break;
			default:
				break;
			}
			m_pPlayer->SetPos(pos);		//補正した値をプレイヤーに反映
			m_pPlayer->SetDirection(dire, num);		//どの方向に当たったかを保持する
			
		}
	}

	//PlayerとShadowBloackの当たり判定
	for (std::vector<std::vector<ShadowBlock::SmallBlockTemp>>::iterator it = block->begin(); it != block->end(); ++it)
	{
		for (std::vector<ShadowBlock::SmallBlockTemp>::iterator init = it->begin(); init != it->end(); ++init, num++)
		{
			Stage::Info shadow = init->Info;		//シャドウブロックの情報
			Stage::Info player = m_pPlayer->GetInfo();		//プレイヤーの情報
			player.pos.y += player.size.y / 2.0f;		//座標が足元にあるため中心になるように補正

			if (init->use)
			{//存在する（引き戻しの処理）
				Stage::Info Oplayer = m_pPlayer->GetOldInfo();		//前フレームの情報
				Oplayer.pos.y += player.size.y / 2.0f;		//座標が足元にあるため中心になるように補正

				if (Collision::Direction dire = Collision::RectAndRectDirection(player, Oplayer, shadow, m_pPlayer->GetDirection(num)))
				{
					//補正用pos
					XMFLOAT3 pos = m_pPlayer->GetInfo().pos;
					switch (dire)
					{
					case Collision::E_DIRECTION_L:		//左
					case Collision::E_DIRECTION_R:		//右
						Stage::Info PlayerBot;
						Stage::Info PlayerTop;
						PlayerBot = PlayerTop = m_pPlayer->GetInfo();
						PlayerBot.size.y = 0.1f;		//足元の大きさ
						PlayerBot.pos.y += PlayerBot.size.y / 2.0f;		//プレイヤーの元の座標から足元の大きさ分ずらす
						PlayerTop.size.y -= PlayerBot.size.y;		//体の大きさ（プレイヤー全体から足元の大きさを引いた大きさ）
						PlayerTop.pos.y += PlayerBot.size.y + PlayerTop.size.y / 2.0f;	//プレイヤーの元の座標から足元の大きさ分と体の半分ずらす
						{
							bool bTop = Collision::RectAndRect(PlayerTop, shadow);		//体がブロックと当たっているか
							bool bBot = Collision::RectAndRect(PlayerBot, shadow);		//足元がブロックと当たっているか
							if (bBot && !bTop)		//足元は当たっていて体は当たっていない場合段差を無視する
							{//上
								pos.y = shadow.pos.y + shadow.size.y / 2.0f;		//ブロックの上に補正
								m_pPlayer->ResetMove();		//重力をリセット
							}
							else
							{//横
								if (player.pos.x < shadow.pos.x)
								{//右
									pos.x = shadow.pos.x - shadow.size.x / 2.0f - player.size.x / 2.0f;
								}
								else if (player.pos.x >= shadow.pos.x)
								{//左
									pos.x = shadow.pos.x + shadow.size.x / 2.0f + player.size.x / 2.0f;
								}
							}
						}
						break;
					case Collision::E_DIRECTION_U:		//上
						pos.y = shadow.pos.y + shadow.size.y / 2.0f;
						m_pPlayer->ResetMove();
						break;	
					case Collision::E_DIRECTION_D:		//下
						pos.y = shadow.pos.y - shadow.size.y / 2.0f - player.size.y;
						m_pPlayer->ResetMove();
						break;
					default:
						continue;
						break;
					}
					m_pPlayer->SetPos(pos);		//プレイヤーに反映
					m_pPlayer->SetDirection(dire, num);		//当たった方向を保持
				}
			}
			else if (!init->use)
			{//存在しない（消し続ける処理）
				if (Collision::RectAndRect(player, shadow))		//プレイヤーとブロックが当たっているか
				{
					init->life -= m_pLight->GetPower();		
					if (init->life <= 0.0f)
					{
						init->life = 0.0f;
						init->use = false;
					}
				}
			}			
		}
	}
}
