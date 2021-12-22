#include "ShaderController.h"

ShaderController::ShaderController()
{
    CurrentShader = 0;
}

ShaderController::~ShaderController()
{
}

HRESULT ShaderController::NewShader(string Name,const WCHAR* szFileName, ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext)
{

    HRESULT hr = NewVertexShader(szFileName, pd3dDevice, pImmediateContext);
    if (FAILED(hr))
        return hr;
    
    hr = NewPixleShader(szFileName, pd3dDevice);
    if (FAILED(hr))
        return hr;


    ShaderData NewShaderData= ShaderData(Name,_pVertexShader, _pPixelShader, _pVertexLayout);

    _ShaderData.push_back(NewShaderData);

    return S_OK;
}

HRESULT ShaderController::NewVertexShader(const WCHAR* szFileName,ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext)
{
    // Compile the vertex shader
    ID3DBlob* pVSBlob = nullptr;
    HRESULT hr = CompileShaderFromFile(szFileName, "VS", "vs_4_0", &pVSBlob);
    if (FAILED(hr))
    {
        MessageBox(nullptr,
            L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
        return hr;
    }

    ID3D11VertexShader* pVertexShader;
    // Create the vertex shader
    hr = pd3dDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &pVertexShader);
    if (FAILED(hr))
    {
        pVSBlob->Release();
        return hr;
    }
    _pVertexShader = pVertexShader;
   
    // Define the input layout
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "tangent", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "biTangent", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
    UINT numElements = ARRAYSIZE(layout);

    // Create the input layout
     hr = pd3dDevice->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(),
        pVSBlob->GetBufferSize(), &_pVertexLayout);
    pVSBlob->Release();
    if (FAILED(hr))
        return hr;

    // Set the input layout
    pImmediateContext->IASetInputLayout(_pVertexLayout);

    return hr;
}


HRESULT ShaderController::NewPixleShader(const WCHAR* szFileName,ID3D11Device* pd3dDevice)
{
    // Compile the pixel shader
    ID3DBlob* pPSBlob = nullptr;
    HRESULT hr = CompileShaderFromFile(szFileName, "PS", "ps_4_0", &pPSBlob);
    if (FAILED(hr))
    {
        MessageBox(nullptr,
            L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
        return hr;
    }
    
    // Create the pixel shader
    hr = pd3dDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &_pPixelShader);
    pPSBlob->Release();
    if (FAILED(hr))
        return hr;

  
    return hr;
}



ShaderData ShaderController::GetShaderData()
{
    return _ShaderData[CurrentShader];
}

void ShaderController::SetShaderData(UINT ShaderSet)
{
    CurrentShader = ShaderSet;
}

ShaderData ShaderController::GetShaderByName(string Name)
{
    for (auto Shader : _ShaderData) {
        if (Shader.Name == Name) {
            return Shader;
        }
    }
    assert(false && "Shader does not exsit in list");
    return _ShaderData[0];
}

HRESULT ShaderController::NewFullScreenShader(string Name, const WCHAR* szFileName, ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext)
{




    // Compile the vertex shader
    ID3DBlob* pVSBlob = nullptr;
    HRESULT hr = CompileShaderFromFile(szFileName, "QuadVS", "vs_4_0", &pVSBlob);
    if (FAILED(hr))
    {
        MessageBox(nullptr,
            L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
        return hr;
    }

  
    // Create the vertex shader
    hr = pd3dDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &g_pQuadVS);
    if (FAILED(hr))
    {
        pVSBlob->Release();
        return hr;
    }
    

    // Define the input layout
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    
    };
    UINT numElements = ARRAYSIZE(layout);

    // Create the input layout
    hr = pd3dDevice->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(),
        pVSBlob->GetBufferSize(), &g_pQuadLayout);

    pVSBlob->Release();
    if (FAILED(hr))
        return hr;

 
    // Compile the pixel shader
    ID3DBlob* pPSBlob = nullptr;
     hr = CompileShaderFromFile(szFileName, "QuadPS", "ps_4_0", &pPSBlob);
    if (FAILED(hr))
    {
        MessageBox(nullptr,
            L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
        return hr;
    }

    // Create the pixel shader
    hr = pd3dDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &g_pQuadPS);
    pPSBlob->Release();
    if (FAILED(hr))
        return hr;


    ShaderData NewShaderData = ShaderData(Name, g_pQuadVS, g_pQuadPS, g_pQuadLayout);

    _FullScreenShaderData.push_back(NewShaderData);



    return hr;

    
}

ShaderData ShaderController::GetFullScreenShaderByName(string Name)
{

    for (auto FullShader : _FullScreenShaderData) {
        if (FullShader.Name == Name) {
            return FullShader;
        }
    }
    assert(false && "Shader does not exsit in list");
    return _FullScreenShaderData[0];
}

ShaderData ShaderController::GetFullScreenShaderByNumber(int No)
{
    return _FullScreenShaderData[No];
}

HRESULT ShaderController::CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
    HRESULT hr = S_OK;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows 
    // the shaders to be optimized and to run exactly the way they will run in 
    // the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;

    // Disable optimizations to further improve shader debugging
    dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

    ID3DBlob* pErrorBlob = nullptr;
    hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel,
        dwShaderFlags, 0, ppBlobOut, &pErrorBlob);
    if (FAILED(hr))
    {
        if (pErrorBlob)
        {
            OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
            pErrorBlob->Release();
        }
        return hr;
    }
    if (pErrorBlob) pErrorBlob->Release();

    return S_OK;
}

void ShaderController::CleanUp()
{
     _pVertexShader = nullptr;
     _pPixelShader = nullptr;
     _pVertexLayout = nullptr;

     for (auto Shader : _ShaderData) {

         Shader.CleanUp();
     }

     for (auto Shader : _FullScreenShaderData) {

         Shader.CleanUp();
     }

}
