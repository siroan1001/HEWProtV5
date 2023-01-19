#include "LayerGame.h"
#include "SceneGame.h"
#include "EnemyDefault.h"
#include "EnemyRoundTrip.h"
#include <typeinfo>
#include <assert.h>
#include "Input.h"
#include "controller.h"

LayerGame::LayerGame(CameraBase* camera, SceneGame::GameStatus* status)
{
	m_pCamera = camera;

	//ステージの生成
	m_pStage = new Stage;

	//プレイヤーの生成
	m_pPlayer = new Player(Collision::E_DIRECTION_L);

	//敵の生成
	//m_pEnemy = new Enemy(Collision::E_DIRECTION_L, XMFLOAT3(-2.2f, 3.25f, 0.0f ));

	//m_pBobbingEnemy = new BobbingEnemy(Collision::E_DIRECTION_L, { -7.0f,3.0f,0.0f }, { -4.0f, 5.0f, 0.0f }, 300);

	//---------------

	//m_pEnemyBase[E_ENEMY_KIND_DEF_1] = new EnemyDefault(Collision::E_DIRECTION_L, XMFLOAT3(-2.2f, 3.25f, 0.0f));
	//m_pEnemyBase[E_ENEMY_KIND_ROUND_TRIP_1] =
	//	new EnemyRoundTrip(Collision::E_DIRECTION_L, { -7.0f,3.0f,0.0f }, { -4.0f, 5.0f, 0.0f }, 300);

	EnemyDefault* EnemeyD = new EnemyDefault(Collision::E_DIRECTION_L, XMFLOAT3(-2.0f, 3.25f, 0.0f));
	EnemeyD->SetCamera(camera);
	EnemeyD->InitDirectin(m_pStage->GetStageNum() + m_pStage->GetShadowNum());
	m_pEnemy.push_back(EnemeyD);

	EnemyRoundTrip* EnemyRT = new EnemyRoundTrip(Collision::E_DIRECTION_L, { -7.0f,3.0f,0.0f }, { -4.0f, 5.0f, 0.0f }, 300);
	EnemyRT->SetCamera(camera);
	//m_pEnemy.push_back(EnemyRT);

	//if (m_pEnemys[0] is EnemyDefault s)
	//{

	//}

	//assert(typeid(m_pEnemys[0]) == typeid(EnemyDefault));


	//-----------------

	/*m_pEnemys.push_back(new Enemy(Collision::E_DIRECTION_L, { -7.0f, 5.25f, 0.0f }));
	m_pEnemys.push_back(new Enemy(Collision::E_DIRECTION_L, { -7.0f, 5.25f, 0.0f }));
	m_pEnemys.push_back(new Enemy(Collision::E_DIRECTION_L, { -7.0f, 5.25f, 0.0f }));
	m_pEnemys.push_back(new Enemy(Collision::E_DIRECTION_L, { -7.0f, 5.25f, 0.0f }));*/

	m_pLight = new Light;
	m_pLight->SetCamera(camera);

	m_pPlayer->SetCamera(camera);
	m_pPlayer->InitDirection(m_pStage->GetStageNum() + m_pStage->GetShadowNum());




	//for (int i = 0; i < m_pEnemys.size(); i++)
	//{
	//	m_pEnemys[i]->SetCamera(camera);
	//	m_pEnemys[i]->InitDirection(m_pStage->GetStageNum() + m_pStage->GetShadowNum());
	//}


	m_pRvsBlock = new ReverseBlock;

	m_pStartObj = new StartObj;
	m_pStartObj->SetCamera(camera);

	m_pGoalObj = new GoalObj;
	m_pGoalObj->SetCamera(camera);

	m_pObstacle = new Obstacle;
	m_pObstacle->SetCamera(camera);

	m_pChasingShadow = new ChasingShadow;
	m_pChasingShadow->SetPlayer(m_pPlayer);

	m_GameStatus = status;
}

LayerGame::~LayerGame()
{
	delete m_pChasingShadow;
	delete m_pObstacle;
	delete m_pGoalObj;
	delete m_pStartObj;
	delete m_pRvsBlock;
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
	//m_pShadowBlock->Update();
	m_pLight->Update();

	m_pChasingShadow->Update();

	//プレイヤーの更新
	//カメラがPlayerCameraの場合のみ処理する
	m_pPlayer->Update();

	//敵の更新

	//if (m_pEnemy->m_use)m_pEnemy->Update();
	//if (m_pBobbingEnemy->m_use)m_pBobbingEnemy->Update();

	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (!m_pEnemy[i]->GetUse())	continue;
		m_pEnemy[i]->Update();
	}

	//for (int i = 0; i < m_pEnemy.size(); i++)
	//{
	//	m_pEnemy[i]->Update();
	//}

	//for (int i = 0; i < m_pEnemys.size(); i++)
	//{
	//	m_pEnemys[i]->Update();
	//}


	CheckCollision();
}

void LayerGame::Draw()
{
	//ステージの描画
	m_pStage->Draw();

	//プレイヤーの描画
	m_pPlayer->Draw();

	//敵の描画
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (!m_pEnemy[i]->GetUse())	continue;
		m_pEnemy[i]->Draw();
	}

	//シャドウブロックの描画
	//m_pShadowBlock->Draw();

	m_pRvsBlock->Draw();

	//ライトの描画
	m_pLight->Draw();

	//スタートの描画
	m_pStartObj->Draw();

  //追ってくる影の描画
	//m_pChasingShadow->Draw();
	
	m_pGoalObj->Draw();

	m_pObstacle->Draw();
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
							PlayerBot.size.y = 0.08f;		//足元の大きさ
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
						m_pPlayer->SetStageCollisionDirection(dire, num);		//当たった方向を保持
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

	//プレイヤーと反射板
	for (int i = 0; i < m_pRvsBlock->GetStageNum(); i++)
	{
		if (Collision::RectAndRect(m_pPlayer->GetInfo(), m_pRvsBlock->GetInfo(i)))
		{
			m_pPlayer->SetDirection(m_pRvsBlock->GetDirection(i));
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
			enemyinfo.pos.y += enemyinfo.size.y / 2.0f;		//座標が足元にあるため中心になるように補正
			Oenemy.pos.y += enemyinfo.size.y / 2.0f;		//座標が足元にあるため中心になるように補正

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

	////EnemyとStageの当たり判定
	//for (num = 0; num < m_pStage->GetStageNum(); num++)
	//{
	//	//当たり判定に使う要素
	//	Def::Info stage = m_pStage->GetInfo(num);		//ステージブロックの情報
	//	Def::Info Enemy = m_pEnemy->GetInfo();		//プレイヤーの情報（プレイヤーの中心をposとする）
	//	Def::Info OEnemy = m_pEnemy->GetOldInfo();	//プレイヤーの前フレームの情報
	//	Enemy.pos.y += Enemy.size.y / 2.0f;		//座標が足元にあるため中心になるように補正
	//	OEnemy.pos.y += Enemy.size.y / 2.0f;		//座標が足元にあるため中心になるように補正


	//	//どの方向に当たったかを確認する
	//	if (Collision::Direction dire = Collision::RectAndRectDirection(Enemy, OEnemy, stage, m_pEnemy->GetStageCollistonDirection(num)))
	//	{
	//		//補正用pos(足元)
	//		XMFLOAT3 pos = m_pEnemy->GetInfo().pos;

	//		switch (dire)
	//		{//当たった方向に応じての処理
	//		case Collision::E_DIRECTION_L:	//左
	//			pos.x = stage.pos.x + stage.size.x / 2.0f + Enemy.size.x / 2.0f;
	//			m_pEnemy->SetDirection(Collision::E_DIRECTION_R);
	//			break;
	//		case Collision::E_DIRECTION_R:	//右
	//			pos.x = stage.pos.x - stage.size.x / 2.0f - Enemy.size.x / 2.0f;
	//			m_pEnemy->SetDirection(Collision::E_DIRECTION_L);
	//			break;
	//		case Collision::E_DIRECTION_U:	//上
	//			pos.y = stage.pos.y + stage.size.y / 2.0f;
	//			m_pEnemy->ResetMove();		//重力をリセットする
	//			break;
	//		case Collision::E_DIRECTION_D:	//下
	//			pos.y = stage.pos.y - stage.size.y / 2.0f - Enemy.size.y;
	//			m_pEnemy->ResetMove();
	//			break;
	//		default:
	//			break;
	//		}
	//		m_pEnemy->SetPos(pos);		//補正した値をプレイヤーに反映
	//		m_pEnemy->SetStageCollisionDirection(dire, num);		//どの方向に当たったかを保持する

	//	}
	//}

	//num--;

	//if (m_pEnemy->m_use)
	//{
	//	//EnemyとShadowBloackの当たり判定
	//	for (int i = 0; i < shadow.size(); i++)
	//	{
	//		if (!Collision::RectAndRect(shadow[i]->GetInfo(), cam))	continue;
	//		block = shadow[i]->GetSmallBlockInfo();

	//		for (std::vector<std::vector<ShadowBlock::SmallBlockTemp>>::iterator it = block->begin(); it != block->end(); ++it)
	//		{
	//			for (std::vector<ShadowBlock::SmallBlockTemp>::iterator init = it->begin(); init != it->end(); ++init, num++)
	//			{
	//				Def::Info shadow = init->Info;		//シャドウブロックの情報




	//				Def::Info Enemy = m_pEnemy->GetInfo();		//エネミーの情報
	//				Enemy.pos.y += Enemy.size.y / 2.0f;		//座標が足元にあるため中心になるように補正



	//				if (init->use)
	//				{//存在する（引き戻しの処理）
	//					Def::Info OEnemy = m_pEnemy->GetOldInfo();		//前フレームの情報
	//					OEnemy.pos.y += Enemy.size.y / 2.0f;		//座標が足元にあるため中心になるように補正

	//					if (Collision::Direction dire = Collision::RectAndRectDirection(Enemy, OEnemy, shadow, m_pEnemy->GetStageCollistonDirection(num)))
	//					{
	//						//補正用pos
	//						XMFLOAT3 pos = m_pEnemy->GetInfo().pos;
	//						switch (dire)
	//						{
	//						case Collision::E_DIRECTION_L:		//左
	//						case Collision::E_DIRECTION_R:		//右
	//							//横
	//							if (Enemy.pos.x < shadow.pos.x)
	//							{//右
	//								pos.x = shadow.pos.x - shadow.size.x / 2.0f - Enemy.size.x / 2.0f;
	//								m_pEnemy->SetDirection(Collision::E_DIRECTION_R);
	//							}
	//							else if (Enemy.pos.x >= shadow.pos.x)
	//							{//左
	//								pos.x = shadow.pos.x + shadow.size.x / 2.0f + Enemy.size.x / 2.0f;
	//								m_pEnemy->SetDirection(Collision::E_DIRECTION_L);
	//							}
	//							break;
	//						case Collision::E_DIRECTION_U:		//上
	//							pos.y = shadow.pos.y + shadow.size.y / 2.0f;
	//							m_pEnemy->ResetMove();
	//							break;
	//						case Collision::E_DIRECTION_D:		//下
	//							pos.y = shadow.pos.y - shadow.size.y / 2.0f - Enemy.size.y;
	//							m_pEnemy->ResetMove();
	//							break;
	//						default:
	//							continue;
	//							break;
	//						}
	//						m_pEnemy->SetPos(pos);		//エネミーに反映
	//						m_pEnemy->SetStageCollisionDirection(dire, num);		//当たった方向を保持
	//					}
	//				}
	//				else if (!init->use)
	//				{//存在しない（消し続ける処理）
	//					if (Collision::RectAndRect(Enemy, shadow))		//エネミーとブロックが当たっているか
	//					{
	//						init->life -= m_pLight->GetPower();
	//						if (init->life <= 0.0f)
	//						{
	//							init->life = 0.0f;
	//							init->use = false;
	//						}
	//					}
	//				}
	//			}

	//		}

	//	}

	//	//エネミーと反射板
	//	for (int i = 0; i < m_pRvsBlock->GetStageNum(); i++)
	//	{
	//		if (Collision::RectAndRect(m_pEnemy->GetInfo(), m_pRvsBlock->GetInfo(i)))
	//		{
	//			m_pEnemy->SetDirection(m_pRvsBlock->GetDirection(i));
	//		}
	//	}

	//	//プレイヤーとエネミー
	//	Def::Info player = m_pPlayer->GetInfo();
	//	float playerT = player.pos.y - player.size.y / 2.0f;
	//	float playerB = player.pos.y + player.size.y / 2.0f;
	//	float playerR = player.pos.x - player.size.x / 2.0f;
	//	float playerL = player.pos.x + player.size.x / 2.0f;
	//	Def::Info Enemy = m_pEnemy->GetInfo();
	//	float EnemyT = Enemy.pos.y - Enemy.size.y / 2.0f;
	//	float EnemyB = Enemy.pos.y + Enemy.size.y / 2.0f;
	//	float EnemyR = Enemy.pos.x - Enemy.size.x / 2.0f;
	//	float EnemyL = Enemy.pos.x + Enemy.size.x / 2.0f;
	//	if (playerT < EnemyB && playerB > EnemyT &&
	//		playerR < EnemyL && playerL > EnemyR)
	//	{
	//		m_pPlayer->SetCollisionEnemy();
	//		m_pEnemy->SetCollisionPlayer();
	//	}

	//	Def::Info BobEnemy = m_pBobbingEnemy->GetInfo();
	//	float BobEnemyT = BobEnemy.pos.y - BobEnemy.size.y / 2.0f;
	//	float BobEnemyB = BobEnemy.pos.y + BobEnemy.size.y / 2.0f;
	//	float BobEnemyR = BobEnemy.pos.x - BobEnemy.size.x / 2.0f;
	//	float BobEnemyL = BobEnemy.pos.x + BobEnemy.size.x / 2.0f;
	//	if (playerT < BobEnemyB && playerB > BobEnemyT &&
	//		playerR < BobEnemyL && playerL > BobEnemyR)
	//	{
	//		m_pPlayer->SetCollisionEnemy();
	//		m_pBobbingEnemy->SetCollisionPlayer();
	//	}
	//	

	//	//エネミーとライト
	//	Def::Info light = m_pLight->GetInfo();
	//	float Radius = m_pLight->GetRadius();
	//	if ((light.pos.x > EnemyL - Radius) &&
	//		(light.pos.x < EnemyR + Radius) &&
	//		(light.pos.y > EnemyT - Radius) &&
	//		(light.pos.y < EnemyB + Radius))
	//	{
	//		if(m_pEnemy->m_life > 0.0f)m_pEnemy->m_life -= m_pLight->GetPower();
	//		else m_pEnemy->m_use = false;
	//	}

	//	if ((light.pos.x > BobEnemyL - Radius) &&
	//		(light.pos.x < BobEnemyR + Radius) &&
	//		(light.pos.y > BobEnemyT - Radius) &&
	//		(light.pos.y < BobEnemyB + Radius))
	//	{
	//		if(m_pBobbingEnemy->m_life > 0.0f)m_pBobbingEnemy->m_life -= m_pLight->GetPower();
	//		else m_pBobbingEnemy->m_use = false;
	//	}
	//}



	//for (int i = 0; i < m_pEnemys.size(); i++)
	//{
	//	//EnemyとStageの当たり判定
	//	for (num = 0; num < m_pStage->GetStageNum(); num++)
	//	{
	//		//当たり判定に使う要素
	//		Def::Info stage = m_pStage->GetInfo(num);		//ステージブロックの情報
	//		Def::Info Enemy = m_pEnemys[i]->GetInfo();		//プレイヤーの情報（プレイヤーの中心をposとする）
	//		Def::Info OEnemy = m_pEnemys[i]->GetOldInfo();	//プレイヤーの前フレームの情報
	//		Enemy.pos.y += Enemy.size.y / 2.0f;		//座標が足元にあるため中心になるように補正
	//		OEnemy.pos.y += Enemy.size.y / 2.0f;		//座標が足元にあるため中心になるように補正


	//		//どの方向に当たったかを確認する
	//		if (Collision::Direction dire = Collision::RectAndRectDirection(Enemy, OEnemy, stage, m_pEnemys[i]->GetStageCollistonDirection(num)))
	//		{
	//			//補正用pos(足元)
	//			XMFLOAT3 pos = m_pEnemys[i]->GetInfo().pos;

	//			switch (dire)
	//			{//当たった方向に応じての処理
	//			case Collision::E_DIRECTION_L:	//左
	//				pos.x = stage.pos.x + stage.size.x / 2.0f + Enemy.size.x / 2.0f;
	//				m_pEnemys[i]->SetDirection(Collision::E_DIRECTION_L);
	//				break;
	//			case Collision::E_DIRECTION_R:	//右
	//				pos.x = stage.pos.x - stage.size.x / 2.0f - Enemy.size.x / 2.0f;
	//				m_pEnemys[i]->SetDirection(Collision::E_DIRECTION_R);
	//				break;
	//			case Collision::E_DIRECTION_U:	//上
	//				pos.y = stage.pos.y + stage.size.y / 2.0f;
	//				m_pEnemys[i]->ResetMove();		//重力をリセットする
	//				break;
	//			case Collision::E_DIRECTION_D:	//下
	//				pos.y = stage.pos.y - stage.size.y / 2.0f - Enemy.size.y;
	//				m_pEnemys[i]->ResetMove();
	//				break;
	//			default:
	//				break;
	//			}
	//			m_pEnemys[i]->SetPos(pos);		//補正した値をプレイヤーに反映
	//			m_pEnemys[i]->SetStageCollisionDirection(dire, num);		//どの方向に当たったかを保持する

	//		}
	//	}

	//	num--;

	//	//EnemyとShadowBloackの当たり判定
	//	for (int j = 0; j < shadow.size(); j++)
	//	{
	//		if (!Collision::RectAndRect(shadow[j]->GetInfo(), cam))	continue;
	//		block = shadow[i]->GetSmallBlockInfo();

	//		for (std::vector<std::vector<ShadowBlock::SmallBlockTemp>>::iterator it = block->begin(); it != block->end(); ++it)
	//		{
	//			for (std::vector<ShadowBlock::SmallBlockTemp>::iterator init = it->begin(); init != it->end(); ++init, num++)
	//			{
	//				Def::Info shadow = init->Info;		//シャドウブロックの情報




	//				Def::Info Enemy = m_pEnemys[i]->GetInfo();		//エネミーの情報
	//				Enemy.pos.y += Enemy.size.y / 2.0f;		//座標が足元にあるため中心になるように補正



	//				if (init->use)
	//				{//存在する（引き戻しの処理）
	//					Def::Info OEnemy = m_pEnemys[i]->GetOldInfo();		//前フレームの情報
	//					OEnemy.pos.y += Enemy.size.y / 2.0f;		//座標が足元にあるため中心になるように補正

	//					if (Collision::Direction dire = Collision::RectAndRectDirection(Enemy, OEnemy, shadow, m_pEnemys[i]->GetStageCollistonDirection(num)))
	//					{
	//						//補正用pos
	//						XMFLOAT3 pos = m_pEnemys[i]->GetInfo().pos;
	//						switch (dire)
	//						{
	//						case Collision::E_DIRECTION_L:		//左
	//						case Collision::E_DIRECTION_R:		//右
	//							//横
	//							if (Enemy.pos.x < shadow.pos.x)
	//							{//右
	//								pos.x = shadow.pos.x - shadow.size.x / 2.0f - Enemy.size.x / 2.0f;
	//								m_pEnemys[i]->SetDirection(Collision::E_DIRECTION_R);
	//							}
	//							else if (Enemy.pos.x >= shadow.pos.x)
	//							{//左
	//								pos.x = shadow.pos.x + shadow.size.x / 2.0f + Enemy.size.x / 2.0f;
	//								m_pEnemys[i]->SetDirection(Collision::E_DIRECTION_L);
	//							}
	//							break;
	//						case Collision::E_DIRECTION_U:		//上
	//							pos.y = shadow.pos.y + shadow.size.y / 2.0f;
	//							m_pEnemys[i]->ResetMove();
	//							break;
	//						case Collision::E_DIRECTION_D:		//下
	//							pos.y = shadow.pos.y - shadow.size.y / 2.0f - Enemy.size.y;
	//							m_pEnemys[i]->ResetMove();
	//							break;
	//						default:
	//							continue;
	//							break;
	//						}
	//						m_pEnemys[i]->SetPos(pos);		//エネミーに反映
	//						m_pEnemys[i]->SetStageCollisionDirection(dire, num);		//当たった方向を保持
	//					}
	//				}
	//				else if (!init->use)
	//				{//存在しない（消し続ける処理）
	//					if (Collision::RectAndRect(Enemy, shadow))		//エネミーとブロックが当たっているか
	//					{
	//						init->life -= m_pLight->GetPower();
	//						if (init->life <= 0.0f)
	//						{
	//							init->life = 0.0f;
	//							init->use = false;
	//						}
	//					}
	//				}
	//			}

	//		}

	//	}

	//	//エネミーと反射板
	//	for (int j = 0; j < m_pRvsBlock->GetStageNum(); j++)
	//	{
	//		if (Collision::RectAndRect(m_pEnemys[i]->GetInfo(), m_pRvsBlock->GetInfo(j)))
	//		{
	//			m_pEnemys[i]->SetDirection(m_pRvsBlock->GetDirection(j));
	//		}
	//	}

	//	//プレイヤーとエネミー
	//	Def::Info player = m_pPlayer->GetInfo();
	//	float playerT = player.pos.y - player.size.y / 2.0f;
	//	float playerB = player.pos.y + player.size.y / 2.0f;
	//	float playerR = player.pos.x - player.size.x / 2.0f;
	//	float playerL = player.pos.x + player.size.x / 2.0f;
	//	Def::Info Enemy = m_pEnemys[i]->GetInfo();
	//	float EnemyT = Enemy.pos.y - Enemy.size.y / 2.0f;
	//	float EnemyB = Enemy.pos.y + Enemy.size.y / 2.0f;
	//	float EnemyR = Enemy.pos.x - Enemy.size.x / 2.0f;
	//	float EnemyL = Enemy.pos.x + Enemy.size.x / 2.0f;
	//	if (playerT < EnemyB && playerB > EnemyT &&
	//		playerR < EnemyL && playerL > EnemyR)
	//	{
	//		m_pPlayer->SetCollisionEnemy();
	//		m_pEnemys[i]->SetCollisionPlayer();
	//	}

	//	//エネミーとライト
	//	Def::Info light = m_pLight->GetInfo();
	//	float Radius = m_pLight->GetRadius();
	//	if ((light.pos.x > EnemyL - Radius) &&
	//		(light.pos.x < EnemyR + Radius) &&
	//		(light.pos.y > EnemyT - Radius) &&
	//		(light.pos.y < EnemyB + Radius))
	//	{
	//		m_pEnemys[i]->m_life -= m_pLight->GetPower();
	//		if (m_pEnemys[i]->m_life <= 0.0f)
	//		{
	//			m_pEnemys.erase(m_pEnemys.begin() + i);
	//		}
	//	}
	//	

	//}




	//if(*m_GameStatus == Sc)
}
