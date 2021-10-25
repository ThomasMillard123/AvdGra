#pragma once
#include <directxmath.h>
#include <d3d11_1.h>
#include <string>
#include "DDSTextureLoader.h"
#include"Structures.h"


using namespace DirectX;
using namespace std;

#define NUM_VERTICES 36

struct SimpleVertex
{
	XMFLOAT3 Pos;
	XMFLOAT3 Normal;
	XMFLOAT2 TexCoord;
	XMFLOAT3 tangent;
	XMFLOAT3 biTangent;
};

/// <summary>
/// class to hold apperance data of an object
/// </summary>
class Appearance
{
public:

	Appearance();
	~Appearance();
	HRESULT	initMesh(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext);
	//sets
	void SetTextureRV(ID3D11ShaderResourceView* textureRV) { m_pTextureResourceView = textureRV; }
	void SetNormalRV(ID3D11ShaderResourceView* textureRV) { m_pNormalMapResourceView = textureRV; }
	
	//gets
	ID3D11Buffer* getVertexBuffer() { return m_pVertexBuffer; }
	ID3D11Buffer* getIndexBuffer() { return m_pIndexBuffer; }
	ID3D11ShaderResourceView** getTextureResourceView() { return &m_pTextureResourceView; }
	ID3D11ShaderResourceView** getNormalMapResourceView() { return &m_pNormalMapResourceView; }
	ID3D11SamplerState** getTextureSamplerState() { return &m_pSamplerLinear; }
	ID3D11Buffer* getMaterialConstantBuffer() { return m_pMaterialConstantBuffer; }
	
	MaterialPropertiesConstantBuffer getMaterialPropertiesConstantBuffer() { return m_material; }
	void SetMaterial(MaterialPropertiesConstantBuffer material) { m_material = material; }



	bool HasTexture() const { return m_pTextureResourceView ? true : false; }


	void Update(ID3D11DeviceContext* pContext);
	void Draw(ID3D11DeviceContext* pImmediateContext);


private:
	//data
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11Buffer* m_pIndexBuffer;
	ID3D11ShaderResourceView* m_pTextureResourceView;
	ID3D11SamplerState* m_pSamplerLinear;
	MaterialPropertiesConstantBuffer	m_material;
	ID3D11Buffer* m_pMaterialConstantBuffer = nullptr;

	
	ID3D11ShaderResourceView* m_pNormalMapResourceView;

	void CleanUp();
};





