#include "Model.h"
#include "DirectXTex/Texture.h"
//#include "WinDialog.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

VertexShader* Model::m_pDefVS = nullptr;
PixelShader* Model::m_pDefPS = nullptr;
unsigned int Model::m_shaderRef = 0;

//--- プロトタイプ宣言
void MakeModelDefaultShader(VertexShader** vs, PixelShader** ps);

Model::Model()
	: m_modelScale(1.0f), m_isModelFlip(false)
	, m_pMeshes(nullptr), m_meshNum(0)
	, m_pMaterials(nullptr), m_materialNum(0)
	, m_playNo(ANIME_NONE), m_blendNo(ANIME_NONE)
	, m_blendTime(0.0f), m_blendTotalTime(0.0f)
	, m_parametric{ ANIME_NONE, ANIME_NONE }, m_parametricBlend(0.0f)
{
	if (m_shaderRef == 0)
	{
		MakeModelDefaultShader(&m_pDefVS, &m_pDefPS);
	}
	m_pVS = m_pDefVS;
	m_pPS = m_pDefPS;
	++m_shaderRef;

	m_pBones = new ConstantBuffer;
	m_pBones->Create(sizeof(DirectX::XMFLOAT4X4) * MAX_BONE);

}
Model::~Model()
{
	delete m_pBones;
	for (unsigned int i = 0; i < m_meshNum; ++i)
	{
		if (m_pMeshes[i].pBones)
			delete[] m_pMeshes[i].pBones;
		delete[] m_pMeshes[i].pVertices;
		delete[] m_pMeshes[i].pIndices;
		delete m_pMeshes[i].pMesh;
	}
	if (m_pMeshes) {
		delete[] m_pMeshes;
	}
	for (unsigned int i = 0; i < m_materialNum; ++i)
	{
		if (m_pMaterials[i].pTexture)
			m_pMaterials[i].pTexture->Release();
	}
	if (m_pMaterials) {
		delete[] m_pMaterials;
	}

	--m_shaderRef;
	if (m_shaderRef <= 0)
	{
		delete m_pDefPS;
		delete m_pDefVS;
	}
}

void Model::SetVertexShader(VertexShader* vs)
{
	m_pVS = vs;
}
void Model::SetPixelShader(PixelShader* ps)
{
	m_pPS = ps;
}
const Model::Mesh* Model::GetMesh(unsigned int index)
{
	if (index >= GetMeshNum())
	{
		return &m_pMeshes[index];
	}
	return nullptr;
}
uint32_t Model::GetMeshNum()
{
	return m_meshNum;
}



Model::AnimeNo Model::AddAnimation(const char* file)
{
	// assimpの設定
	Assimp::Importer importer;
	int flag = 0;
	if (m_isModelFlip) flag |= aiProcess_MakeLeftHanded;
	// assimpで読み込み
	const aiScene* pScene = importer.ReadFile(file, flag);
	if (!pScene) {
		MessageBox(nullptr, importer.GetErrorString(), "assimp Anime Error", MB_OK);
		return ANIME_NONE;
	}

	// アニメーションチェック
	if (!pScene->HasAnimations())
	{
		return ANIME_NONE;
	}

	// アニメーションデータ領域追加
	aiAnimation* pAnime = pScene->mAnimations[0];
	m_animes.push_back(Animation());
	Animation& anime = m_animes.back();

	// アニメーション設定
	anime.totalTime = pAnime->mDuration / pAnime->mTicksPerSecond;
	anime.channels.resize(pAnime->mNumChannels);
	std::vector<Channel>::iterator channelIt = anime.channels.begin();
	while (channelIt != anime.channels.end())
	{
		// チャンネル(ボーン)別にデータを設定
		int channelIdx = channelIt - anime.channels.begin();
		aiNodeAnim* pChannel = pAnime->mChannels[channelIdx];
		Mapping::iterator mappingIt = m_boneMapping.find(pChannel->mNodeName.data);
		if (mappingIt == m_boneMapping.end())
		{
			channelIt->index = INDEX_NONE;
			channelIt++;
			continue;
		}

		// 各キーの値を設定
		channelIt->index = mappingIt->second;
		// 移動
		channelIt->pos.resize(pChannel->mNumPositionKeys);
		for (int i = 0; i < channelIt->pos.size(); ++i)
		{
			aiVector3D val = pChannel->mPositionKeys[i].mValue;
			channelIt->pos[i].value = DirectX::XMFLOAT3(val.x * m_modelScale, val.y * m_modelScale, val.z * m_modelScale);
			channelIt->pos[i].time = pChannel->mPositionKeys[i].mTime / pAnime->mTicksPerSecond;
		}
		// 回転
		channelIt->quat.resize(pChannel->mNumRotationKeys);
		for (int i = 0; i < channelIt->quat.size(); ++i)
		{
			aiQuaternion val = pChannel->mRotationKeys[i].mValue;
			channelIt->quat[i].value = DirectX::XMFLOAT4(val.x, val.y, val.z, val.w);
			channelIt->quat[i].time = pChannel->mRotationKeys[i].mTime / pAnime->mTicksPerSecond;
		}
		// 拡縮
		channelIt->scale.resize(pChannel->mNumScalingKeys);
		for (int i = 0; i < channelIt->scale.size(); ++i)
		{
			aiVector3D val = pChannel->mScalingKeys[i].mValue;
			channelIt->scale[i].value = DirectX::XMFLOAT3(val.x, val.y, val.z);
			channelIt->scale[i].time = pChannel->mScalingKeys[i].mTime / pAnime->mTicksPerSecond;
		}

		channelIt++;
	}

	return m_animes.size() - 1;
}

void Model::Step(float tick)
{
	if (m_playNo == ANIME_NONE) { return; }

	if (m_playNo == ANIME_PARAMETRIC || m_blendNo == ANIME_PARAMETRIC)
	{
		CalcAnime(ANIME_TRANSFORM_PARAMETRIC0, m_parametric[0]);
		CalcAnime(ANIME_TRANSFORM_PARAMETRIC1, m_parametric[1]);
	}
	if (m_playNo != ANIME_NONE && m_playNo != ANIME_PARAMETRIC)
	{
		CalcAnime(ANIME_TRANSFORM_MAIN, m_playNo);
	}
	if (m_blendNo != ANIME_NONE && m_blendNo != ANIME_PARAMETRIC)
	{
		CalcAnime(ANIME_TRANSFORM_BLEND, m_blendNo);
	}

	CalcBones(0, DirectX::XMMatrixIdentity());

	// アニメーション時間更新
	UpdateAnime(m_playNo, tick);
	if (m_blendNo != ANIME_NONE)
	{
		UpdateAnime(m_blendNo, tick);
		m_blendTime += tick;
		if (m_blendTotalTime <= m_blendTime)
		{
			m_blendTime = 0.0f;
			m_blendTotalTime = 0.0f;
			m_playNo = m_blendNo;
			m_blendNo = ANIME_NONE;
		}
	}
	if (m_playNo == ANIME_PARAMETRIC || m_blendNo == ANIME_PARAMETRIC)
	{
		UpdateAnime(m_parametric[0], tick);
		UpdateAnime(m_parametric[1], tick);
	}
}

void Model::Play(AnimeNo no, bool loop)
{
	if (!AnimeNoCheck(no)) { return; }
	if (m_playNo == no) { return; }
	if (no != ANIME_PARAMETRIC)
	{
		InitAnime(no);
		m_animes[no].isLoop = loop;
	}
	else
	{
		InitAnime(m_parametric[0]);
		InitAnime(m_parametric[1]);
		m_animes[m_parametric[0]].isLoop = loop;
		m_animes[m_parametric[1]].isLoop = loop;
	}
	m_playNo = no;
}
void Model::PlayBlend(AnimeNo no, float blendTime, bool loop)
{
	if (!AnimeNoCheck(no)) { return; }
	if (no != ANIME_PARAMETRIC)
	{
		InitAnime(no);
		m_animes[no].isLoop = loop;
	}
	else
	{
		InitAnime(m_parametric[0]);
		InitAnime(m_parametric[1]);
		m_animes[m_parametric[0]].isLoop = loop;
		m_animes[m_parametric[1]].isLoop = loop;
	}
	m_blendTime = 0.0f;
	m_blendTotalTime = blendTime;
	m_blendNo = no;
}
void Model::SetParametric(AnimeNo no1, AnimeNo no2)
{
	if (!AnimeNoCheck(no1)) { return; }
	if (!AnimeNoCheck(no2)) { return; }
	m_parametric[0] = no1;
	m_parametric[1] = no2;
	SetParametricBlend(0.0f);
}
void Model::SetParametricBlend(float blendRate)
{
	if (m_parametric[0] == ANIME_NONE || m_parametric[1] == ANIME_NONE) return;
	Animation& anime1 = m_animes[m_parametric[0]];
	Animation& anime2 = m_animes[m_parametric[1]];
	m_parametricBlend = blendRate;
	float blendTotalTime = anime1.totalTime * (1.0f - m_parametricBlend) + anime2.totalTime * m_parametricBlend;
	anime1.speed = anime1.totalTime / blendTotalTime;
	anime2.speed = anime2.totalTime / blendTotalTime;
}
bool Model::IsPlay(AnimeNo no)
{
	if (!AnimeNoCheck(no)) { return false; }
	if (no == ANIME_PARAMETRIC) { no = m_parametric[0]; }
	if (m_animes[no].totalTime < m_animes[no].time) { return false; }

	if (m_playNo == no) { return true; }
	if (m_blendNo == no) { return true; }
	if (m_playNo == ANIME_PARAMETRIC || m_blendNo == ANIME_PARAMETRIC)
	{
		if (m_parametric[0] == no) { return true; }
		if (m_parametric[1] == no) { return true; }
	}
	return false;
}
Model::AnimeNo Model::GetPlayNo()
{
	return m_playNo;
}
Model::AnimeNo Model::GetBlendNo()
{
	return m_blendNo;
}
float Model::GetRemainingTime(AnimeNo no)
{
	if (!AnimeNoCheck(no)) { return 0.0f; }
	return max(m_animes[no].totalTime - m_animes[no].time, 0.0f);
}

void Model::MakeNodes(const void* pScene)
{
	std::function<NodeIndex(aiNode*, NodeIndex)> AssimpNodeConvert =
		[&AssimpNodeConvert, this](aiNode* pNode, NodeIndex parent)
	{
		// Assimpのノードを変換
		Node node;
		node.name = pNode->mName.data;
		node.parent = parent;
		node.children.resize(pNode->mNumChildren);
		aiMatrix4x4 mat = pNode->mTransformation;
		DirectX::XMStoreFloat4x4(&node.offset,
			DirectX::XMMatrixSet(
				mat.a1, mat.b1, mat.c1, mat.d1,
				mat.a2, mat.b2, mat.c2, mat.d2,
				mat.a3, mat.b3, mat.c3, mat.d3,
				mat.a4 * m_modelScale, mat.b4 * m_modelScale, mat.c4 * m_modelScale, mat.d4)
		);
		node.mat = DirectX::XMLoadFloat4x4(&node.offset);
		m_nodes.push_back(node);

		// ノード名に基づく参照リスト作成
		NodeIndex index = m_nodes.size() - 1;
		m_boneMapping.insert(MappingKey(node.name, index));

		// 子要素に関しても変換
		for (int i = 0; i < pNode->mNumChildren; ++i)
		{
			m_nodes[index].children[i] = AssimpNodeConvert(pNode->mChildren[i], index);
		}
		return index;
	};

	// ノード作成
	m_nodes.clear();
	m_boneMapping.clear();
	AssimpNodeConvert(reinterpret_cast<const aiScene*>(pScene)->mRootNode, -1);
	// ノード数に基づいて、アニメーションデータ作成
	for (int i = 0; i < MAX_ANIME_TRANSFORM; ++i)
	{
		m_animeTransform[i].resize(m_nodes.size());
		for (NodeTransforms::iterator it = m_animeTransform[i].begin(); it != m_animeTransform[i].end(); ++it)
		{
			it->translate = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
			it->quaternion = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
			it->scale = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
		}
	}
}
void Model::MakeBoneWeight(const void* scene, int i)
{
	const aiScene* pScene = reinterpret_cast<const aiScene*>(scene);

	// メッシュに対応するボーン番号
	if (pScene->mMeshes[i]->HasBones())
	{
		m_pMeshes[i].boneNum = pScene->mMeshes[i]->mNumBones;
		m_pMeshes[i].pBones = new Bone[m_pMeshes[i].boneNum];
		for (unsigned int j = 0; j < m_pMeshes[i].boneNum; ++j)
		{
			std::string name = pScene->mMeshes[i]->mBones[j]->mName.data;
			auto it = m_boneMapping.find(name);
			if (it != m_boneMapping.end())
			{
				m_pMeshes[i].pBones[j].index = it->second;
				aiMatrix4x4 mat = pScene->mMeshes[i]->mBones[j]->mOffsetMatrix;
				m_pMeshes[i].pBones[j].invOffset = DirectX::XMFLOAT4X4(
					mat.a1, mat.b1, mat.c1, mat.d1,
					mat.a2, mat.b2, mat.c2, mat.d2,
					mat.a3, mat.b3, mat.c3, mat.d3,
					mat.a4 * m_modelScale, mat.b4 * m_modelScale, mat.c4 * m_modelScale, mat.d4
				);

				// ウェイト
				unsigned int weightNum = pScene->mMeshes[i]->mBones[j]->mNumWeights;
				for (int k = 0; k < weightNum; ++k)
				{
					aiVertexWeight weight = pScene->mMeshes[i]->mBones[j]->mWeights[k];
					for (int l = 0; l < 4; ++l)
					{
						if (m_pMeshes[i].pVertices[weight.mVertexId].weight[l] <= 0.0f)
						{
							m_pMeshes[i].pVertices[weight.mVertexId].index[l] = j;
							m_pMeshes[i].pVertices[weight.mVertexId].weight[l] = weight.mWeight;
							break;
						}
					}
				}
			}
			else
			{
				m_pMeshes[i].pBones[j].index = -1;
			}
		}
	}
	else
	{
		std::map<std::string, int>::iterator it = m_boneMapping.find(pScene->mMeshes[i]->mName.data);
		if (it != m_boneMapping.end())
		{
			// メッシュでない親ノードを探索
			std::function<int(int)> FindNodeFunc = [&FindNodeFunc, this, pScene](int index)
			{
				//////////////////////////////
				if (index == -1)
					return 0;

				std::string name = m_nodes[index].name;
				for (int i = 0; i < pScene->mNumMeshes; ++i)
					if (name == pScene->mMeshes[i]->mName.data)
					{
						return FindNodeFunc(m_nodes[index].parent);
					}
				return index;
			};
			// ノードまでの行列を計算
			std::function<DirectX::XMMATRIX(int, DirectX::XMMATRIX)> CalcNodeFunc =
				[&CalcNodeFunc, this](int index, DirectX::XMMATRIX mat)
			{
				if (index == -1) return mat;
				mat = mat * DirectX::XMLoadFloat4x4(&m_nodes[index].offset);
				return CalcNodeFunc(m_nodes[index].parent, mat);
			};

			m_pMeshes[i].boneNum = 1;
			m_pMeshes[i].pBones = new Bone[1];
			m_pMeshes[i].pBones->index = FindNodeFunc(m_nodes[it->second].parent);
			DirectX::XMStoreFloat4x4(&m_pMeshes[i].pBones->invOffset, DirectX::XMMatrixInverse(nullptr,
				CalcNodeFunc(m_pMeshes[i].pBones->index, DirectX::XMMatrixIdentity())
			));
			for (unsigned int j = 0; j < m_pMeshes[i].vertexNum; ++j)
			{
				m_pMeshes[i].pVertices[j].weight[0] = 1.0f;
			}
		}
		else
		{
			m_pMeshes[i].boneNum = 0;
			m_pMeshes[i].pBones = nullptr;
		}
	}
}
void Model::UpdateBoneMatrix(int i)
{
	DirectX::XMFLOAT4X4 boneMat[MAX_BONE];
	int j;
	for (j = 0; j < m_pMeshes[i].boneNum && j < MAX_BONE; ++j)
	{
		DirectX::XMStoreFloat4x4(&boneMat[j],
			DirectX::XMMatrixTranspose(
				DirectX::XMLoadFloat4x4(&m_pMeshes[i].pBones[j].invOffset) *
				m_nodes[m_pMeshes[i].pBones[j].index].mat
			));
	}
	for (; j < MAX_BONE; ++j)
	{
		DirectX::XMStoreFloat4x4(&boneMat[j], DirectX::XMMatrixIdentity());
	}
	m_pBones->Write(boneMat);
	m_pBones->BindVS(1);
}
bool Model::AnimeNoCheck(AnimeNo no)
{
	if (no == ANIME_PARAMETRIC)
		return m_parametric[0] != ANIME_NONE && m_parametric[1] != ANIME_NONE;
	else
		return 0 <= no && no < m_animes.size();
}
void Model::InitAnime(AnimeNo no)
{
	if (no == ANIME_NONE || no == ANIME_PARAMETRIC) { return; }

	Animation& anime = m_animes[no];
	anime.time = 0.0f;
	anime.speed = 1.0f;
	anime.isLoop = false;
}
void Model::UpdateAnime(AnimeNo no, float tick)
{
	if (no == ANIME_PARAMETRIC) { return; }
	Animation& anime = m_animes[no];
	anime.time += anime.speed * tick;
	if (anime.isLoop)
		while (anime.time >= anime.totalTime)
			anime.time -= anime.totalTime;
}
void Model::CalcBones(NodeIndex index, DirectX::XMMATRIX parent)
{
	//--- アニメーションごとのパラメータを合成
	Transform transform;
	// パラメトリックブレンド
	if (m_playNo == ANIME_PARAMETRIC || m_blendNo == ANIME_PARAMETRIC)
	{
		Transform& parametric0 = m_animeTransform[ANIME_TRANSFORM_PARAMETRIC0][index];
		Transform& parametric1 = m_animeTransform[ANIME_TRANSFORM_PARAMETRIC1][index];
		transform.translate = Lerp(parametric0.translate, parametric1.translate, m_parametricBlend);
		transform.quaternion = Lerp(parametric0.quaternion, parametric1.quaternion, m_parametricBlend);
		transform.scale = Lerp(parametric0.scale, parametric1.scale, m_parametricBlend);
		if (m_playNo == ANIME_PARAMETRIC)
			m_animeTransform[ANIME_TRANSFORM_MAIN][index] = transform;
		if (m_blendNo == ANIME_PARAMETRIC)
			m_animeTransform[ANIME_TRANSFORM_BLEND][index] = transform;
	}
	// モーションブレンド
	if (m_blendNo != ANIME_NONE)
	{
		Transform& anime0 = m_animeTransform[ANIME_TRANSFORM_MAIN][index];
		Transform& anime1 = m_animeTransform[ANIME_TRANSFORM_BLEND][index];
		float rate = m_blendTime / m_blendTotalTime;
		transform.translate = Lerp(anime0.translate, anime1.translate, rate);
		transform.quaternion = Lerp(anime0.quaternion, anime1.quaternion, rate);
		transform.scale = Lerp(anime0.scale, anime1.scale, rate);
	}
	else
	{
		transform = m_animeTransform[ANIME_TRANSFORM_MAIN][index];
	}

	// ノードごとの姿勢行列を計算
	Node& node = m_nodes[index];
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(transform.translate.x, transform.translate.y, transform.translate.z);
	DirectX::XMVECTOR Q = DirectX::XMLoadFloat4(&transform.quaternion);
	DirectX::XMMATRIX R = DirectX::XMMatrixRotationQuaternion(Q);
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(transform.scale.x, transform.scale.y, transform.scale.z);
	DirectX::XMMATRIX mat = S * R * T;
	node.mat = mat * parent;

	// 子要素の姿勢を更新
	Children::iterator it = node.children.begin();
	while (it != node.children.end())
	{
		CalcBones(*it, node.mat);
		++it;
	}
}
void Model::CalcAnime(AnimeTransformKind kind, AnimeNo no)
{
	Animation& anime = m_animes[no];
	Channels::iterator channelIt = anime.channels.begin();
	while (channelIt != anime.channels.end())
	{
		// 一致するボーンがなければスキップ
		if (channelIt->index == INDEX_NONE)
		{
			++channelIt;
			continue;
		}

		// 座標
		DirectX::XMFLOAT3 pos;
		if (anime.time <= channelIt->pos[0].time) { pos = channelIt->pos[0].value; }
		else if (channelIt->pos.back().time <= anime.time) { pos = channelIt->pos.back().value; }
		else
		{
			for (int i = 0; i < channelIt->pos.size() - 1; ++i)
			{
				if (channelIt->pos[i].time < anime.time && anime.time <= channelIt->pos[i + 1].time)
				{
					float timeLen = channelIt->pos[i + 1].time - channelIt->pos[i].time;
					float rate = (anime.time - channelIt->pos[i].time) / timeLen;
					pos = Lerp(channelIt->pos[i].value, channelIt->pos[i + 1].value, rate);
					break;
				}
			}
		}
		// 回転
		DirectX::XMFLOAT4 quat;
		if (anime.time <= channelIt->quat[0].time) { quat = channelIt->quat[0].value; }
		else if (channelIt->quat.back().time <= anime.time) { quat = channelIt->quat.back().value; }
		else
		{
			for (int i = 0; i < channelIt->quat.size() - 1; ++i)
			{
				if (channelIt->quat[i].time < anime.time && anime.time <= channelIt->quat[i + 1].time)
				{
					float timeLen = channelIt->quat[i + 1].time - channelIt->quat[i].time;
					float rate = (anime.time - channelIt->quat[i].time) / timeLen;
					quat = Lerp(channelIt->quat[i].value, channelIt->quat[i + 1].value, rate);
					break;
				}
			}
		}
		// 拡大縮小
		DirectX::XMFLOAT3 scale;
		if (anime.time <= channelIt->scale[0].time) { scale = channelIt->scale[0].value; }
		else if (channelIt->scale.back().time <= anime.time) { scale = channelIt->scale.back().value; }
		else
		{
			for (int i = 0; i < channelIt->scale.size() - 1; ++i)
			{
				if (channelIt->scale[i].time < anime.time && anime.time <= channelIt->scale[i + 1].time)
				{
					float timeLen = channelIt->scale[i + 1].time - channelIt->scale[i].time;
					float rate = (anime.time - channelIt->scale[i].time) / timeLen;
					scale = Lerp(channelIt->scale[i].value, channelIt->scale[i + 1].value, rate);
					break;
				}
			}
		}

		m_animeTransform[kind][channelIt->index].translate = pos;
		m_animeTransform[kind][channelIt->index].quaternion = quat;
		m_animeTransform[kind][channelIt->index].scale = scale;
		channelIt++;
	}
}

DirectX::XMFLOAT3 Model::Lerp(DirectX::XMFLOAT3& a, DirectX::XMFLOAT3& b, float rate)
{
	DirectX::XMFLOAT3 out;
	DirectX::XMVECTOR vA = DirectX::XMLoadFloat3(&a);
	DirectX::XMVECTOR vB = DirectX::XMLoadFloat3(&b);
	DirectX::XMStoreFloat3(&out, DirectX::XMVectorAdd(
		DirectX::XMVectorScale(vA, 1.0f - rate), DirectX::XMVectorScale(vB, rate)
	));
	return out;
}
DirectX::XMFLOAT4 Model::Lerp(DirectX::XMFLOAT4& a, DirectX::XMFLOAT4& b, float rate)
{
	DirectX::XMFLOAT4 out;
	DirectX::XMVECTOR vA = DirectX::XMLoadFloat4(&a);
	DirectX::XMVECTOR vB = DirectX::XMLoadFloat4(&b);
	DirectX::XMStoreFloat4(&out, DirectX::XMVector4Normalize(
		DirectX::XMQuaternionSlerp(vA, vB, rate)
	));
	return out;
}

void MakeModelDefaultShader(VertexShader** vs, PixelShader** ps)
{
	const char* ModelVS = R"EOT(
struct VS_IN {
	float3 pos : POSITION0;
	float3 normal : NORMAL0;
	float2 uv : TEXCOORD0;
};
struct VS_OUT {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
};
VS_OUT main(VS_IN vin) {
	VS_OUT vout;
	vout.pos = float4(vin.pos, 1.0f);
	vout.pos.z += 0.5f;
	vout.pos.y -= 0.8f;
	vout.uv = vin.uv;
	return vout;
})EOT";
	const char* ModelPS = R"EOT(
struct PS_IN {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
};
Texture2D tex : register(t0);
SamplerState samp : register(s0);
float4 main(PS_IN pin) : SV_TARGET
{
	return tex.Sample(samp, pin.uv);
})EOT";
	*vs = new VertexShader();
	(*vs)->Compile(ModelVS);
	*ps = new PixelShader();
	(*ps)->Compile(ModelPS);
}