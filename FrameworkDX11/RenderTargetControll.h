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
	RenderTargetTextureClass* GetRenderTarget(string String);

	void CreatRenderTarget(string name, UINT width, UINT Hight);


private:
	vector<RenderTargetTextureClass*> TargetTexture;

	void CleanUP();
};

