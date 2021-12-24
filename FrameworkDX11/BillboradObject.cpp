#include "BillboradObject.h"

BillboardObject::BillboardObject(string TexName, int numberToCreate, ID3D11Device* _pd3dDevice)
{
    SetTexture(TexName, _pd3dDevice);
    CreatBillboard(numberToCreate, _pd3dDevice);

}

BillboardObject::~BillboardObject()
{
    CleanUp();
}

void BillboardObject::CreatBillboard(int Number, ID3D11Device* _pd3dDevice)
{
    HRESULT hr;

    
    NumberOfBillBoards = Number;

    Positions.resize(NumberOfBillBoards);
    Positions[0].Pos = XMFLOAT3(0, 0, 0);
    Positions[1].Pos = XMFLOAT3(0, 10, 0);

    D3D11_BUFFER_DESC instBuffDesc;
    ZeroMemory(&instBuffDesc, sizeof(instBuffDesc));

    instBuffDesc.Usage = D3D11_USAGE_DEFAULT;
    instBuffDesc.ByteWidth = sizeof(SimpleVertexBill) * NumberOfBillBoards;
    instBuffDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    instBuffDesc.CPUAccessFlags = 0;
    instBuffDesc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA instData;
    ZeroMemory(&instData, sizeof(instData));
    instData.pSysMem = &Positions[0];
    instData.SysMemPitch = 0;
    instData.SysMemSlicePitch = 0;


    hr = _pd3dDevice->CreateBuffer(&instBuffDesc, &instData, &BillboardInstanceBuff);



    // Create the vertex buffer we will send to the shaders for the billboard data. We are going to use
    // the instancing technique for the billboards, and our billboard geometry shader only requires a single
    // point to be an input, so all we need to do is create a buffer that stores a single point!
    D3D11_BUFFER_DESC billboardBufferDesc;
    ZeroMemory(&billboardBufferDesc, sizeof(billboardBufferDesc));

    billboardBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    billboardBufferDesc.ByteWidth = sizeof(SimpleVertexBill);
    billboardBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    billboardBufferDesc.CPUAccessFlags = 0;
    billboardBufferDesc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA ginitData;

    // Create a single vertex at the point 0,0,0. None of the other members will be used for billboarding
    SimpleVertexBill gv;
    gv.Pos = XMFLOAT3(0.0f, 0.0f, 0.0f);

    ginitData.pSysMem = &gv;
    _pd3dDevice->CreateBuffer(&billboardBufferDesc, &ginitData, &BillboardVertBuff);
}

void BillboardObject::Draw(ID3D11DeviceContext* pContext, ShaderData Shader, ConstantBuffer* cb, ID3D11Buffer* _pConstantBuffer)
{
    pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
    pContext->IASetInputLayout(Shader._pVertexLayout);
    UINT strides[2] = { sizeof(SimpleVertexBill), sizeof(SimpleVertexBill) };
    UINT offsets[2] = { 0, 0 };
    
    cb->mWorld = XMMatrixIdentity();
    pContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, cb, 0, 0);

    ID3D11Buffer* vertBillInstBuffers[2] = { BillboardVertBuff, BillboardInstanceBuff };
    pContext->IASetVertexBuffers(0, 2, vertBillInstBuffers, strides, offsets);

    
    pContext->VSSetShader(Shader._pVertexShader, nullptr, 0);
    pContext->VSSetConstantBuffers(0, 1, &_pConstantBuffer);
    pContext->GSSetShader(Shader._pGeometryShader, nullptr, 0);
    pContext->GSSetConstantBuffers(0, 1, &_pConstantBuffer);
    pContext->PSSetShaderResources(0, 1, &m_pDiffuseResourceView);
    pContext->PSSetShader(Shader._pPixelShader, nullptr, 0);
    pContext->DrawInstanced(1, NumberOfBillBoards, 0, 0);


    //reset buffers
    pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    pContext->GSSetShader(nullptr, nullptr, 0);
}

void BillboardObject::SetTexture(string TexName, ID3D11Device* _pd3dDevice)
{
    wstring tex = std::wstring(TexName.begin(), TexName.end());
    const wchar_t* widecstr = tex.c_str();
    HRESULT hr = CreateDDSTextureFromFile(_pd3dDevice, widecstr, nullptr, &m_pDiffuseResourceView);
    if (FAILED(hr))
        return;
}

void BillboardObject::UpdatePositions(ID3D11DeviceContext* pContext)
{
    pContext->UpdateSubresource(BillboardInstanceBuff, 0, NULL, &Positions[0], 0, 0);
}

void BillboardObject::CleanUp()
{
    if (BillboardInstanceBuff) {
        BillboardInstanceBuff->Release();
    }

    if (BillboardVertBuff) {
        BillboardVertBuff->Release();
    }

    if (m_pDiffuseResourceView) {
        m_pDiffuseResourceView->Release();
    }
}
