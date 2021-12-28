#pragma once

#include<vector>
#include<string>

#include"RenderTargetTextureClass.h"
using namespace std;
class RenderTargetControll
{
public:
	RenderTargetControll();
	~RenderTargetControll();

	RenderTargetTextureClass* GetRenderTarget(int Number);
	RenderTargetTextureClass* GetRenderTarget(string Name);

	void CreatRenderTarget(string name, UINT width, UINT Hight, ID3D11Device* _pd3dDevice);

	
private:
	vector<RenderTargetTextureClass*> TargetTexture;

	void CleanUP();
};

