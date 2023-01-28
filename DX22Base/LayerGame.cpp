#include "LayerGame.h"
#include "SceneGame.h"
#include "EnemyDefault.h"
#include "EnemyRoundTrip.h"
#include <typeinfo>
#include <assert.h>
#include "Input.h"
#include "controller.h"

Def::Info g_temp;
bool g_flag;

LayerGame::LayerGame(CameraBase* camera, SceneGame::GameStatus* status, SceneGame::StageNumber stagenum)
{
	m_pCamera = camera;

	//ステージの生成(他のステージの読み込みどうしよう)
	m_pStage = new Stage();

	//プレイヤーの生成
	m_pPlayer = new Player(Collision::E_DIRECTION_L);

	EnemyDefault* EnemeyD = new EnemyDefault(Collision::E_DIRECTION_L, XMFLOAT3(-2.0f, 3.25f, 0.0f));
	EnemeyD->SetCamera(camera);
	EnemeyD->InitDirectin(m_pStage->GetStageNum() + m_pStage->GetShadowNum());
	m_pEnemy.push_back(EnemeyD);

	EnemyRoundTrip* EnemyRT = new EnemyRoundTrip(Collision::E_DIRECTION_L, { -7.0f,3.0f,0.0f }, { -4.0f, 5.0f, 0.0f }, 300);
	EnemyRT->SetCamera(camera);


	m_pLight = new Light;
	m_pLight->SetCamera(camera);

	m_pPlayer->SetCamera(camera);
	m_pPlayer->InitDirection(m_pStage->GetStageNum() + m_pStage->GetShadowNum());




	//for (int i = 0; i < m_pEnemys.size(); i++)
	//{
	//	m_pEnemys[i]->SetCamera(camera);
	//	m_pEnemys[i]->InitDirection(m_pStage->GetStageNum() + m_pStage->GetShadowNum());
	//}


	//m_pRvsBlock = new ReverseBlock;

	m_pStartObj = new StartObj;
	m_pStartObj->SetCamera(camera);

	m_pGoalObj = new GoalObj;
	m_pGoalObj->SetCamera(camera);

	m_pObstacle = new Obstacle;
	m_pObstacle->SetCamera(camera);

	m_pChasingShadow = new ChasingShadow;
	m_pChasingShadow->SetPlayer(m_pPlayer);
	m_pChasingShadow->SetCamera(camera);

	m_GameStatus = status;
	g_flag = false;
	g_temp = {};
}

LayerGame::~LayerGame()
{
	delete m_pChasingShadow;
	delete m_pObstacle;
	delete m_pGoalObj;
	delete m_pStartObj;
	//delete m_pRvsBlock;
	delete m_pLight;
	//delete m_pShadowBlock;
	/*m_pEnemys.clear();*/
	//for (int i = 0; i < E_ENEMY_KIND_MAX; i++)
	//{
	//	delete m_pEnemyBase[i];
	//}
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		delete m_pEnemy[i];
	}
	delete m_pPlayer;
	delete m_pStage;
}

void LayerGame::Update()
{
	g_flag = false;

	//m_pShadowBlock->Update();
	m_pLight->Update();

	m_pChasingShadow->Update();

	//プレイヤーの更新
	//カメラがPlayerCameraの場合のみ処理する
	//m_pPlayer->SetStatus(m_GameStatus);
	m_pPlayer->Update();

	//敵の更新

	//if (m_pEnemy->m_use)m_pEnemy->Update();
	//if (m_pBobbingEnemy->m_use)m_pBobbingEnemy->Update();

	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (!m_pEnemy[i]->GetUse())	continue;
		m_pEnemy[i]->Update();
	}

	m_pStage->Update();

	CheckCollision();

}

void LayerGame::Draw()
{
	//ステージの描画
	m_pStage->Draw();

	//プレイヤーの描画
	Object::SetObjColor(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	m_pPlayer->Draw();

	//敵の描画
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (!m_pEnemy[i]->GetUse())	continue;
		Object::SetObjColor(XMFLOAT4(50.0f, 50.0f, 50.0f, 1.0f));
		m_pEnemy[i]->Draw();
	}

	//シャドウブロックの描画
	//m_pShadowBlock->Draw();

	//m_pRvsBlock->Draw();

	//ライトの描画
	m_pLight->Draw();

	//スタートの描画
	m_pStartObj->Draw();

	//追ってくる影の描画
	Object::SetObjColor(XMFLOAT4(100.0f, 100.0f, 100.0f, 1.0f));
	m_pChasingShadow->Draw();
	
	m_pGoalObj->Draw();

}

void LayerGame::Reset()
{
	m_pPlayer->Reset();
	m_pChasingShadow->Reset();
	m_pLight->Reset();
}

Player * LayerGame::GetPlayer()
{
	return m_pPlayer;
}

void LayerGame::SetCamera(CameraBase * camera)
{
	m_pCamera = camera;
	m_pLight->SetCamera(m_pCamera);
	m_pPlayer->SetCamera(m_pCamera);
}


void LayerGame::CheckCollision()
{
	//ShadowBlockとLigthの判定
	vector<ShadowBlock*> shadow = m_pStage->GetShadowBlock();	//シャドウブロックの情報
	vector<vector<ShadowBlock::SmallBlockTemp>>* block;
	Def::Info cam = m_pCamera->GetInfo();

	for (int i = 0; i < shadow.size(); i++)
	{
		if (!Collision::RectAndRect(shadow[i]->GetInfo(), cam))	continue;

		Def::Info lightinfo = m_pLight->GetInfo();
		float lightradius = m_pLight->GetRadius();
		if (!Collision::RectAndCircle(shadow[i]->GetInfo(), lightinfo, lightradius))	continue;

		block = shadow[i]->GetSmallBlockInfo();
		for (std::vector<std::vector<ShadowBlock::SmallBlockTemp>>::iterator it = block->begin(); it != block->end(); ++it)
		{
			for (std::vector<ShadowBlock::SmallBlockTemp>::iterator init = it->begin(); init != it->end(); ++init)
			{
				if (Collision::RectAndCircle(init->Info, lightinfo, lightradius))
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
	}

	int num = 0;		//プレイヤーとブロックの当たり判定が何個目かを入れる（前フレームのどの方向に当たったかを確認するのに使う）

	//PlayerとStageの当たり判定
	for (num = 0; num < m_pStage->GetStageNum(); num++)
	{
		//当たり判定に使う要素
		Def::Info stage = m_pStage->GetInfo(num);		//ステージブロックの情報
		Def::Info player = m_pPlayer->GetInfo();		//プレイヤーの情報（プレイヤーの中心をposとする）
		Def::Info Oplayer = m_pPlayer->GetOldInfo();	//プレイヤーの前フレームの情報
		player.pos.y += player.size.y / 2.0f;		//座標が足元にあるため中心になるように補正
		Oplayer.pos.y += player.size.y / 2.0f;		//座標が足元にあるため中心になるように補正

		//どの方向に当たったかを確認する
		if (Collision::Direction dire = Collision::RectAndRectDirection(player, Oplayer, stage, m_pPlayer->GetStageCollistonDirection(num)))
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
			m_pPlayer->SetStageCollisionDirection(dire, num);		//どの方向に当たったかを保持する

		}


	}

	num--;

	

	//PlayerとShadowBloackの当たり判定
	for (int i = 0; i < shadow.size(); i++)
	{
		Def::Info shadowinfo = shadow[i]->GetInfo();
		Def::Info playerinfo = m_pPlayer->GetInfo();

		if (!Collision::RectAndRect(shadow[i]->GetInfo(), cam))	continue;
		if (!Collision::RectAndRect(shadowinfo, playerinfo))	continue;

		block = shadow[i]->GetSmallBlockInfo();

		for (std::vector<std::vector<ShadowBlock::SmallBlockTemp>>::iterator it = block->begin(); it != block->end(); ++it)
		{
			for (std::vector<ShadowBlock::SmallBlockTemp>::iterator init = it->begin(); init != it->end(); ++init, num++)
			{
				Def::Info shadow = init->Info;		//シャドウブロックの情報




				Def::Info player = m_pPlayer->GetInfo();		//プレイヤーの情報
				player.pos.y += player.size.y / 2.0f;		//座標が足元にあるため中心になるように補正




				if (init->use)
				{//存在する（引き戻しの処理）
					Def::Info Oplayer = m_pPlayer->GetOldInfo();		//前フレームの情報
					Oplayer.pos.y += player.size.y / 2.0f;		//座標が足元にあるため中心になるように補正

					if (Collision::Direction dire = Collision::RectAndRectDirection(player, Oplayer, shadow, m_pPlayer->GetStageCollistonDirection(num)))
					{
						//補正用pos
						XMFLOAT3 pos = m_pPlayer->GetInfo().pos;
						switch (dire)
						{
						case Collision::E_DIRECTION_L:		//左
						case Collision::E_DIRECTION_R:		//右
							Def::Info PlayerBot;
							Def::Info PlayerTop;
							PlayerBot = PlayerTop = m_pPlayer->GetInfo();
							PlayerBot.size.y = 0.06f;		//足元の大きさ
							PlayerBot.pos.y += PlayerBot.size.y / 2.0f;		//プレイヤーの元の座標から足元の大きさ分ずらす
							PlayerTop.size.y -= PlayerBot.size.y;		//体の大きさ（プレイヤー全体から足元の大きさを引いた大きさ）
							PlayerTop.pos.y += PlayerBot.size.y + PlayerTop.size.y / 2.0f;	//プレイヤーの元の座標から足元の大きさ分と体の半分ずらす
							{
								bool bTop = Collision::RectAndRect(PlayerTop, shadow);		//体がブロックと当たっているか
								bool bBot = Collision::RectAndRect(PlayerBot, shadow);		//足元がブロックと当たっているか
								if (bBot && !bTop)		//足元は当たっていて体は当たっていない場合段差を無視する
								{//上
									pos.y = shadow.pos.y + shadow.size.y / 2.0f;		//ブロックの上に補正		//ここ滑らかに上がるように修正
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
						m_pPlayer->SetStageCollisionDirection(dire, num);		//当たった方向を保持
					}
				}
				else if (!init->use)
				{//存在しない（消し続ける処理）
					if (Collision::RectAndRect(player, shadow))		//プレイヤーとブロックが当たっているか
					{
						//init->life -= m_pLight->GetPower();
						//if (init->life <= 0.0f)
						//{
						//	init->life = 0.0f;
						//	init->use = false;
						//}

						XMFLOAT3 pos = m_pPlayer->GetInfo().pos;
						Def::Info PlayerBot;
						//Def::Info PlayerTop;
						g_flag = true;
						PlayerBot  = m_pPlayer->GetInfo();
						PlayerBot.size.y = 0.04f;		//足元の大きさ
						//PlayerBot.pos.y -= 0f;
						g_temp = PlayerBot;
						//PlayerBot.pos.y += PlayerBot.size.y / 2.0f;		//プレイヤーの元の座標から足元の大きさ分ずらす
						//PlayerTop.size.y -= PlayerBot.size.y + 0.02f;		//体の大きさ（プレイヤー全体から足元の大きさを引いた大きさ）
						//PlayerTop.pos.y += PlayerBot.size.y + PlayerTop.size.y / 2.0f;	//プレイヤーの元の座標から足元の大きさ分と体の半分ずらす

	

						{
							//bool bTop = Collision::RectAndRect(PlayerTop, shadow);		//体がブロックと当たっているか
							bool bBot = Collision::RectAndRect(PlayerBot, shadow);		//足元がブロックと当たっているか
							if (bBot)		//足元は当たっていて体は当たっていない場合段差を無視する
							{//上
								init->life += 1.5f;
								if (init->life >= 30.0f)
								{
									init->life = 30.0f;
									init->use = true;
									pos.y += init->Info.size.y / 2.0f;
									m_pPlayer->SetPos(pos);
								}
							}
							else
							{//横
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

		}
	}

	//プレイヤーと反射板
	//for (int i = 0; i < m_pRvsBlock->GetStageNum(); i++)
	//{
	//	if (Collision::RectAndRect(m_pPlayer->GetInfo(), m_pRvsBlock->GetInfo(i)))
	//	{
	//		m_pPlayer->SetDirection(m_pRvsBlock->GetDirection(i));
	//	}
	//}

	//プレイヤーと追ってくる影
	if (*m_GameStatus == SceneGame::E_GAME_STATUS_NORMAL)
	{
		if (Collision::RectAndCircle(m_pPlayer->GetInfo(), m_pChasingShadow->GetInfo(), m_pChasingShadow->GetRadius()))
		{
			SceneGame::SetGameStatus(SceneGame::E_GAME_STATUS_GAMEOVER);
		}
	}

	//おってくる影とゴール
	if (!m_pChasingShadow->GetEndFlag())
	{
		if (Collision::RectAndRect(m_pGoalObj->GetInfo(), m_pChasingShadow->GetInfo()))
		{
			m_pChasingShadow->SetEndFlag(true);
		}
	}
	//プレイヤーとスタート板
	if (*m_GameStatus == SceneGame::E_GAME_STATUS_START)
	{
		Def::Info startInfo = m_pStartObj->GetInfo();
		if (Collision::RectAndRect(m_pPlayer->GetInfo(), startInfo))
		{
			SceneGame::SetGameStatus(SceneGame::E_GAME_STATUS_NORMAL);
		}
	}

	//プレイヤーとゴール板
	if (*m_GameStatus == SceneGame::E_GAME_STATUS_NORMAL)
	{
		Def::Info GoalInfo = m_pGoalObj->GetInfo();
		if (Collision::RectAndRect(m_pPlayer->GetInfo(), GoalInfo))
		{
			//SceneGame::SetGameStatus(SceneGame::E_GAME_STATUS_GOAL);
			*m_GameStatus = SceneGame::E_GAME_STATUS_GOAL;
		}
	}

	
	
	//てきとステージ・シャドウブロックの実装
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		Def::Info enemyinfo = m_pEnemy[i]->GetInfo();
		if (!Collision::RectAndRect(enemyinfo, cam))	continue;
		num = 0;		//敵用にリセット
		EnemyDefault* enemy = reinterpret_cast<EnemyDefault*>(m_pEnemy[i]);

		//敵とStageの当たり判定
		for (num = 0; num < m_pStage->GetStageNum(); num++)
		{
			//当たり判定に使う要素
			Def::Info stage = m_pStage->GetInfo(num);		//ステージブロックの情報
			enemyinfo = m_pEnemy[i]->GetInfo();				//敵の情報（プレイヤーの中心をposとする）
			Def::Info Oenemy = enemy->GetOldInfo();			//プレイヤーの前フレームの情報
			//enemyinfo.pos.y += enemyinfo.size.y / 2.0f;		//座標が足元にあるため中心になるように補正
			//Oenemy.pos.y += enemyinfo.size.y / 2.0f;		//座標が足元にあるため中心になるように補正

			//どの方向に当たったかを確認する
			if (Collision::Direction dire = Collision::RectAndRectDirection(enemyinfo, Oenemy, stage, enemy->GetStageCollistonDirection(num)))
			{
				//補正用pos(足元)
				XMFLOAT3 pos = m_pEnemy[i]->GetInfo().pos;

				switch (dire)
				{//当たった方向に応じての処理
				case Collision::E_DIRECTION_L:	//左
					pos.x = stage.pos.x + stage.size.x / 2.0f + enemyinfo.size.x / 2.0f;
					enemy->SetDirection(Collision::E_DIRECTION_R);
					break;
				case Collision::E_DIRECTION_R:	//右
					pos.x = stage.pos.x - stage.size.x / 2.0f - enemyinfo.size.x / 2.0f;
					enemy->SetDirection(Collision::E_DIRECTION_L);
					break;
				case Collision::E_DIRECTION_U:	//上
					pos.y = stage.pos.y + stage.size.y / 2.0f;
					enemy->ResetMove();		//重力をリセットする
					break;
				case Collision::E_DIRECTION_D:	//下
					pos.y = stage.pos.y - stage.size.y / 2.0f - enemyinfo.size.y;
					enemy->ResetMove();
					break;
				default:
					break;
				}
				enemy->SetPos(pos);		//補正した値をプレイヤーに反映
				enemy->SetStageCollisionDirection(dire, num);		//どの方向に当たったかを保持する
				m_pEnemy[i] = enemy;
			}


		}

		num--;

		//敵とShadowBloackの当たり判定
		for (int j = 0; j < shadow.size(); j++)
		{
			Def::Info shadowinfo = shadow[j]->GetInfo();
			
			if (!Collision::RectAndRect(shadow[j]->GetInfo(), cam))	continue;
			if (!Collision::RectAndRect(shadowinfo, enemyinfo))	continue;

			block = shadow[j]->GetSmallBlockInfo();

			for (std::vector<std::vector<ShadowBlock::SmallBlockTemp>>::iterator it = block->begin(); it != block->end(); ++it)
			{
				for (std::vector<ShadowBlock::SmallBlockTemp>::iterator init = it->begin(); init != it->end(); ++init, num++)
				{
					Def::Info shadowInfo = init->Info;		//シャドウブロックの情報

					enemyinfo = m_pEnemy[i]->GetInfo();
					enemyinfo.pos.y += enemyinfo.size.y / 2.0f;		//座標が足元にあるため中心になるように補正

					EnemyDefault* enemy = reinterpret_cast<EnemyDefault*>(m_pEnemy[i]);

					if (init->use)
					{//存在する（引き戻しの処理）
						Def::Info Oenemy = enemy->GetOldInfo();		//前フレームの情報
						Oenemy.pos.y += enemyinfo.size.y / 2.0f;		//座標が足元にあるため中心になるように補正

						if (Collision::Direction dire = Collision::RectAndRectDirection(enemyinfo, Oenemy, shadowInfo, enemy->GetStageCollistonDirection(num)))
						{
							//補正用pos
							XMFLOAT3 pos = m_pEnemy[i]->GetInfo().pos;
							switch (dire)
							{
							case Collision::E_DIRECTION_L:		//左
							case Collision::E_DIRECTION_R:		//右
								Def::Info EnemyBot;
								Def::Info EnemyTop;
								EnemyBot = EnemyTop = m_pEnemy[i]->GetInfo();
								EnemyBot.size.y = 0.08f;		//足元の大きさ
								EnemyBot.pos.y += EnemyBot.size.y / 2.0f;		//プレイヤーの元の座標から足元の大きさ分ずらす
								EnemyTop.size.y -= EnemyBot.size.y;		//体の大きさ（プレイヤー全体から足元の大きさを引いた大きさ）
								EnemyTop.pos.y += EnemyBot.size.y + EnemyTop.size.y / 2.0f;	//プレイヤーの元の座標から足元の大きさ分と体の半分ずらす
								{
									bool bTop = Collision::RectAndRect(EnemyTop, shadowInfo);		//体がブロックと当たっているか
									bool bBot = Collision::RectAndRect(EnemyBot, shadowInfo);		//足元がブロックと当たっているか
									if (bBot && !bTop)		//足元は当たっていて体は当たっていない場合段差を無視する
									{//上
										pos.y = shadowInfo.pos.y + shadowInfo.size.y / 2.0f;		//ブロックの上に補正
										enemy->ResetMove();		//重力をリセット
									}
									else
									{//横
										if (enemyinfo.pos.x < shadowInfo.pos.x)
										{//右
											pos.x = shadowInfo.pos.x - shadowInfo.size.x / 2.0f - enemyinfo.size.x / 2.0f;
											enemy->SetDirection(Collision::E_DIRECTION_R);
										}
										else if (enemyinfo.pos.x >= shadowInfo.pos.x)
										{//左
											pos.x = shadowInfo.pos.x + shadowInfo.size.x / 2.0f + enemyinfo.size.x / 2.0f;
											enemy->SetDirection(Collision::E_DIRECTION_L);
										}
									}
								}
								break;
							case Collision::E_DIRECTION_U:		//上
								pos.y = shadowInfo.pos.y + shadowInfo.size.y / 2.0f;
								enemy->ResetMove();
								break;
							case Collision::E_DIRECTION_D:		//下
								pos.y = shadowInfo.pos.y - shadowInfo.size.y / 2.0f - enemyinfo.size.y;
								enemy->ResetMove();
								break;
							default:
								continue;
								break;
							}
							enemy->SetPos(pos);		//プレイヤーに反映
							enemy->SetStageCollisionDirection(dire, num);		//当たった方向を保持
							m_pEnemy[i] = enemy;
						}
					}
					else if (!init->use)
					{//存在しない（消し続ける処理）
						if (Collision::RectAndRect(enemyinfo, shadowInfo))		//プレイヤーとブロックが当たっているか
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
	}
}
