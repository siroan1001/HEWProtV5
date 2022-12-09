#include "Model.h"
#include "DirectXTex/Texture.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

bool Model::Load(const char* file, float scale, bool flip)
{
	Assimp::Importer importer;
	int flag = 0;
	flag |= aiProcess_Triangulate;
	flag |= aiProcess_PreTransformVertices;
	flag |= aiProcess_JoinIdenticalVertices;
	flag |= aiProcess_FlipUVs;
	if (flip)	flag |= aiProcess_MakeLeftHanded;
	//assimpで読み込み
	const aiScene* pScene = importer.ReadFile(file, flag);
	if (!pScene)
	{
		return false;
	}

	m_meshNum = pScene->mNumMeshes;
	m_pMeshes = new Mesh[m_meshNum];

	//メッシュごとに頂点データ、インデックスデータを読み取り
	for (unsigned int i = 0; i < m_meshNum; ++i)
	{
		//メッシュを元に頂点のデータを確保
		aiVector3D zero(0.0f, 0.0f, 0.0f);
		m_pMeshes[i].vertexNum = pScene->mMeshes[i]->mNumVertices;
		m_pMeshes[i].pVertices = new Model::Vertex[m_pMeshes[i].vertexNum];

		//メッシュ内の頂点データを読み取り
		for (unsigned int j = 0; j < m_pMeshes[i].vertexNum; ++j)
		{
			//値の吸い出し
			aiVector3D pos = pScene->mMeshes[i]->mVertices[j];
			aiVector3D uv = pScene->mMeshes[i]->HasTextureCoords(0) ? pScene->mMeshes[i]->mTextureCoords[0][j] : zero;

			//値の設定
			m_pMeshes[i].pVertices[j] = {
				DirectX::XMFLOAT3(pos.x * scale, pos.y * scale, pos.z * scale),
				DirectX::XMFLOAT2(uv.x, uv.y)
			};
		}

		//メッシュを元にインデックスのデータを確保
		//※faceはポリゴン数を表す（１ポリゴンで３インダックス
		m_pMeshes[i].indexNum = pScene->mMeshes[i]->mNumFaces * 3;
		m_pMeshes[i].pIndices = new unsigned int[m_pMeshes[i].indexNum];

		//メッシュ内のインデックスデータを読み取り
		for (unsigned int j = 0; j < pScene->mMeshes[i]->mNumFaces; ++j)
		{
			aiFace face = pScene->mMeshes[i]->mFaces[j];
			int idx = j * 3;
			m_pMeshes[i].pIndices[idx + 0] = face.mIndices[0];
			m_pMeshes[i].pIndices[idx + 1] = face.mIndices[1];
			m_pMeshes[i].pIndices[idx + 2] = face.mIndices[2];
		}

		//マテリアルの割り当て
		m_pMeshes[i].materialID = pScene->mMeshes[i]->mMaterialIndex;

		//メッシュを元に頂点バッファ作成
		MeshBuffer::Description desc = {};
		desc.pVtx = m_pMeshes[i].pVertices;
		desc.vtxSize = sizeof(Vertex);
		desc.vtxCount = m_pMeshes[i].vertexNum;
		desc.pIdx = m_pMeshes[i].pIndices;
		desc.idxSize = sizeof(unsigned int);
		desc.idxCount = m_pMeshes[i].indexNum;
		desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		m_pMeshes[i].pMesh = new MeshBuffer(desc);
	}

	//テクスチャを読み込む場所を探索
	std::string dir = file;
	dir = dir.substr(0, dir.find_last_of('/') + 1);		//読み込むファイルパスからファイル名を取り除く
														//Assets/Model/xx.fbx -> Assets/Model/

	//読み込んだデータを元にマテリアルのデータを確保
	m_materialNum = pScene->mNumMaterials;
	m_pMaterials = new Material[m_materialNum];

	//マテリアルごとにデータを読み取り
	HRESULT hr;
	for (unsigned int i = 0; i < m_materialNum; ++i)
	{
		//テクスチャの読み取り
		aiString path;
		if (pScene->mMaterials[i]->Get(AI_MATKEY_TEXTURE_DIFFUSE(0), path) == AI_SUCCESS)
		{
			//モデルファイルに記録されていたファイルパスから読み込み
			hr = LoadTextureFromFile(path.C_Str(), &m_pMaterials[i].pTexture);
			if (FAILED(hr))
			{
				//モデルと同じフォルダ内でテクスチャファイルを読み込み
				std::string file = dir;
				file += path.C_Str();
				hr = LoadTextureFromFile(file.c_str(), &m_pMaterials[i].pTexture);
			}
			if (FAILED(hr)) { return false; }
		}
		else
		{
			m_pMaterials[i].pTexture = nullptr;
		}
	}

	return true;
}

void Model::Draw()
{
	m_pVS->Bind();
	m_pPS->Bind();
	for (unsigned int i = 0; i < m_meshNum; ++i)
	{
		SetTexturePS(m_pMaterials[m_pMeshes[i].materialID].pTexture, 0);
		m_pMeshes[i].pMesh->Draw();
	}
}