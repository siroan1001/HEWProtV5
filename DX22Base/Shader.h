#ifndef __SHADER_H__
#define __SHADER_H__

#include "DirectX.h"
#include <string>
#include <map>

// シェーダーの基本クラス
class Shader
{
protected:
	enum Kind
	{
		VertexShader,
		PixelShader
	};
protected:
	Shader(Kind kind);
public:
	virtual ~Shader();
public:
	// シェーダーファイル(*.cso)を読み込む処理
	HRESULT Load(const char* pFileName);
	// 文字列からシェーダをコンパイル
	HRESULT Compile(const char* pCode);

	// シェーダーを描画に使用
	virtual void Bind(void) = 0;

protected:
	// シェーダーファイルを読み込んだ後、シェーダーの種類別に処理を行う
	virtual HRESULT MakeShader(void* pData, UINT size) = 0;

private:
	Kind m_kind;
};

//----------
// 頂点シェーダ
class VertexShader : public Shader
{
private:
	using ILKey = std::pair<std::string, ID3D11InputLayout*>;
	using ILList = std::map<std::string, ID3D11InputLayout*>;
public:
	static void ReleaseInputLayout();

	VertexShader();
	~VertexShader();
	void Bind(void);
protected:
	HRESULT MakeShader(void* pData, UINT size);

private:
	static ILList m_ilList;
	ID3D11VertexShader* m_pVS;
	ID3D11InputLayout* m_pInputLayout;
};
//----------
// ピクセルシェーダ
class PixelShader : public Shader
{
public:
	PixelShader();
	~PixelShader();
	void Bind(void);
protected:
	HRESULT MakeShader(void* pData, UINT size);
private:
	ID3D11PixelShader* m_pPS;
};

//--- テクスチャ
void SetTextureVS(ID3D11ShaderResourceView* pTex, UINT slot = 0);
void SetTexturePS(ID3D11ShaderResourceView* pTex, UINT slot = 0);

#endif