#ifndef __MODEL_H__
#define __MODEL_H__

#include <DirectXMath.h>
#include <vector>
#include "Shader.h"
#include "MeshBuffer.h"
#include "ConstantBuffer.h"

class Model
{
public:
	// �萔
	using NodeIndex = int;
	using AnimeNo = int;
	static const NodeIndex		INDEX_NONE = -1;
	static const AnimeNo		ANIME_NONE = -1;
	static const AnimeNo		ANIME_PARAMETRIC = -2;
	static const unsigned int	MAX_BONE = 200; // ������ύX����ꍇ�A.hlsl���̒萔���ύX����	200
	enum AnimeTransformKind
	{
		ANIME_TRANSFORM_MAIN,
		ANIME_TRANSFORM_BLEND,
		ANIME_TRANSFORM_PARAMETRIC0,
		ANIME_TRANSFORM_PARAMETRIC1,
		MAX_ANIME_TRANSFORM
	};

	//--- �e��f�[�^��`
private:
	using Children = std::vector<NodeIndex>;
	using Mapping = std::map<std::string, NodeIndex>;
	using MappingKey = std::pair<std::string, NodeIndex>;
	// 3�l�̃A�j���[�V�����L�[
	struct Key3
	{
		float				time;
		DirectX::XMFLOAT3	value;
	};
	using KeyFrames3 = std::vector<Key3>;
	// 4�l�̃A�j���[�V�����L�[
	struct Key4
	{
		float				time;
		DirectX::XMFLOAT4	value;
	};
	using KeyFrames4 = std::vector<Key4>;
	// �A�j���[�V�����L�[�t���[��
	struct Channel
	{
		NodeIndex	index;
		KeyFrames3	pos;
		KeyFrames4	quat;
		KeyFrames3	scale;

	};
	using Channels = std::vector<Channel>;

	// �A�j���[�V�������
	struct Animation
	{
		float		time;		// ���݂̍Đ�����
		float		totalTime;	// �A�j���[�V�����̒���
		float		speed;		// �Đ����x
		bool		isLoop;		// ���[�v�ݒ�
		Channels	channels;	// �L�[�t���[�����
	};
	using Animations = std::vector<Animation>;
public:
	// 
	struct Transform
	{
		DirectX::XMFLOAT3 translate;
		DirectX::XMFLOAT4 quaternion;
		DirectX::XMFLOAT3 scale;
	};
	using NodeTransforms = std::vector<Transform>;
	// �K�w�\��
	struct Node
	{
		std::string			name;		// �m�[�h��
		NodeIndex			parent;		// �e
		Children			children;	// �q�v�f
		DirectX::XMFLOAT4X4	offset;		// �m�[�h�I�t�Z�b�g�l
		DirectX::XMMATRIX	mat;		// �v�Z�ς݃m�[�h�s��
	};
	using Nodes = std::vector<Node>;
	// ���_���
	struct Vertex
	{
		DirectX::XMFLOAT3	pos;		// ���W
		DirectX::XMFLOAT3	normal;		// �@��
		DirectX::XMFLOAT2	uv;			// �e�N�X�`�����W
		float				weight[4];	// ���_�u�����h�E�F�C�g
		unsigned int		index[4];	// ���_�u�����h�C���f�b�N�X
	};
	// �}�e���A��
	struct Material
	{
		DirectX::XMFLOAT4			diffuse;	// �g�U��
		DirectX::XMFLOAT4			ambient;	// ����
		DirectX::XMFLOAT4			specular;	// ���ʔ��ˌ�
		ID3D11ShaderResourceView*	pTexture;	// �e�N�X�`��
	};
	// 
	struct Bone
	{
		NodeIndex			index;
		DirectX::XMFLOAT4X4	invOffset;
	};
	// ���b�V�����
	struct Mesh
	{
		Vertex*			pVertices;	// ���_���
		unsigned int	vertexNum;	// ���_��
		unsigned int*	pIndices;	// �C���f�b�N�X���
		unsigned int	indexNum;	// �C���f�b�N�X��
		unsigned int	materialID;	// ���蓖�Ă�}�e���A��
		Bone*			pBones;		// �{�[�����
		unsigned int	boneNum;	// �{�[����
		MeshBuffer*		pMesh;		// ���_�o�b�t�@
	};
public:
	//===== Model.cpp
	Model();
	~Model();
	void SetVertexShader(VertexShader* vs);
	void SetPixelShader(PixelShader* ps);
	const Mesh* GetMesh(unsigned int index);
	unsigned int GetMeshNum();

	AnimeNo AddAnimation(const char* file);	//
	void Step(float tick);	//

	void Play(AnimeNo no, bool loop);	//
	void PlayBlend(AnimeNo no, float blendTime, bool loop);
	void SetParametric(AnimeNo no1, AnimeNo no2);
	void SetParametricBlend(float blendRate);

	bool IsPlay(AnimeNo no);
	AnimeNo GetPlayNo();
	AnimeNo GetBlendNo();
	float GetRemainingTime(AnimeNo no);

private:
	void MakeNodes(const void* pScene);
	void MakeBoneWeight(const void* scene, int i);
	void UpdateBoneMatrix(int i);
	bool AnimeNoCheck(AnimeNo no);
	void InitAnime(AnimeNo no);
	void UpdateAnime(AnimeNo no, float tick);
	void CalcBones(NodeIndex index, DirectX::XMMATRIX parent);
	void CalcAnime(AnimeTransformKind kind, AnimeNo no);
	DirectX::XMFLOAT3 Lerp(DirectX::XMFLOAT3& a, DirectX::XMFLOAT3& b, float rate);
	DirectX::XMFLOAT4 Lerp(DirectX::XMFLOAT4& a, DirectX::XMFLOAT4& b, float rate);

private:
	//===== Model_Contents
public:
	bool Load(const char* file, float scale = 1.0f, bool flip = false);
	void Draw();

private:
	static VertexShader* m_pDefVS;
	static PixelShader* m_pDefPS;
	static PixelShader* m_pLambertPS;
	static PixelShader* m_pPhongPS;
	static PixelShader* m_pToonPS;
	static unsigned int m_shaderRef;
private:
	float			m_modelScale;
	bool			m_isModelFlip;
	Nodes			m_nodes;
	Mapping			m_boneMapping;
	Mesh*			m_pMeshes;
	unsigned int	m_meshNum;
	Material*		m_pMaterials;
	unsigned int	m_materialNum;
	VertexShader*	m_pVS;
	PixelShader*	m_pPS;
	ConstantBuffer*	m_pBones;
	Animations		m_animes;
	AnimeNo			m_playNo;
	AnimeNo			m_blendNo;
	float			m_blendTime;
	float			m_blendTotalTime;
	AnimeNo			m_parametric[2];
	float			m_parametricBlend;
	NodeTransforms	m_animeTransform[MAX_ANIME_TRANSFORM];
};


#endif // __MODEL_H__