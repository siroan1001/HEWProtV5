#include "Game3D.h"
#include "SceneGame.h"

SceneBace* Game3D::m_pScene[];
Game3D::SceneKind Game3D::m_SceneKind;

Game3D::Game3D()
{
	m_pScene[E_SCENE_KIND_TITLE] = NULL;
	m_pScene[E_SCENE_KIND_GAME] = new SceneGame;

	m_SceneKind = E_SCENE_KIND_GAME;
}

Game3D::~Game3D()
{
	for (int i = 0; i < E_SCENE_KIND_MAX; i++)
	{
		delete m_pScene[i];
	}
}

void Game3D::Update()
{
	m_pScene[m_SceneKind]->Update();
}

void Game3D::Draw()
{
	m_pScene[m_SceneKind]->Draw();
}