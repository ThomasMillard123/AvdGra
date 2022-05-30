#include "TerrainVoxel.h"

TerrainVoxel::TerrainVoxel(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext)
{
    ChunkData.resize(3);
    ChunkData[0].push_back(new Chunk(pd3dDevice, pContext));
}

TerrainVoxel::~TerrainVoxel()
{
}

void TerrainVoxel::Draw(ID3D11DeviceContext* pContext, ShaderController* ShaderControll, ConstantBuffer* buffer, ID3D11Buffer* _pConstantBuffer)
{
    for (auto x : ChunkData)
    {
        for (auto z : x)
        {
            z->Draw(pContext, ShaderControll, buffer, _pConstantBuffer);
        }
    }
}

Chunk::Chunk(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext)
{
    CubeData.resize(xSize);
    GenrateTerrain(pd3dDevice, pContext);
}

Chunk::~Chunk()
{
}

void Chunk::Draw(ID3D11DeviceContext* pContext, ShaderController* ShaderControll, ConstantBuffer* buffer, ID3D11Buffer* _pConstantBuffer)
{
    for (auto x : CubeData)
    {
        for (auto z : x)
        {
            for (auto y : z)
            {
                if (y->GetIsActive()) {
                    XMFLOAT4X4 WorldAsFloat = y->GetTransForm()->GetWorldMatrix();
                    XMMATRIX mGO = XMLoadFloat4x4(&WorldAsFloat);
                    buffer->mWorld = XMMatrixTranspose(mGO);
                    pContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, buffer, 0, 0);

                    //y->GetApparance()->SetTextures(pContext);
                    y->GetApparance()->Draw(pContext);
                }
            }
        }
    }
 


}

void Chunk::GenrateTerrain(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext)
{
    //World Creation
    FastNoiseLite noise;
    //noise.SetSeed(1338);
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    noise.SetFrequency(0.01);
    noise.SetFractalType(FastNoiseLite::FractalType::FractalType_None);
    noise.SetFractalOctaves(6);
    //noise.SetRotationType3D(FastNoiseLite::RotationType3D_ImproveXZPlanes);
    for (float x = 0; x < xSize; x++)
    {
        for (float z = 0; z < zSize; z++)
        {
            int  Active = ((noise.GetNoise(x, z)+1)/2)*10;
            //Active = 51;
            CubeData[x].resize(Active);
            for (float y = 0; y < Active; y++)
            {
                CubeData[x][y].push_back(new Block(pd3dDevice, pContext));
                CubeData[x][y][z]->SetIsActive(true);
                CubeData[x][y][z]->GetTransForm()->SetPosition(x/0.5f, y / 0.5f, z / 0.5f);
            }
        }
 
    }

    //face cube creation
    bool lDefault = false;
    for (int x = 0; x < xSize; x++) {
        for (int y = 0; y < CubeData[x].size(); y++) {
            for (int z = 0; z < xSize; z++) {
                if (CubeData[x][y][z]->GetIsActive() == false) {
                    continue;
                }
                bool lXNegative = lDefault;
                if (x > 0) lXNegative = CubeData[x - 1][y][z]->GetIsActive();

                bool lXPositive = lDefault;
                if (x < xSize - 1) lXPositive = CubeData[x + 1][y][z]->GetIsActive();

                bool lYNegative = lDefault;
                if (y > 0) lYNegative = CubeData[x][y - 1][z]->GetIsActive();

                bool lYPositive = lDefault;
                if (y < xSize - 1) lYPositive = CubeData[x][y + 1][z]->GetIsActive();

                bool lZNegative = lDefault;
                if (z > 0) lZNegative = CubeData[x][y][z - 1]->GetIsActive();

                bool lZPositive = lDefault;
                if (z < xSize - 1) lZPositive = CubeData[x][y][z + 1]->GetIsActive();
                CubeData[x][y][z]->CreatCube(lXNegative, lXPositive, lYNegative, lYPositive, lZNegative, lZPositive, pd3dDevice, pContext);
            }
        }
    }


}

Block::Block(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext)
{
    m_CubeTransform = new Transform();
    m_CubeApparace = new TerrainAppearence();
    //m_CubeApparace->initMesh(pd3dDevice, pContext);
}

Block::~Block()
{
}

void Block::CreatCube(bool lXNegative, bool lXPositive, bool lYNegative, bool lYPositive, bool lZNegative, bool lZPositive, ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext)
{
    m_CubeApparace->CreateCube(lXNegative, lXPositive, lYNegative, lYPositive, lZNegative, lZPositive, pd3dDevice, pContext);
}
