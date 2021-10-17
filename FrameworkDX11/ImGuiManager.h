#pragma once

#include<Windows.h>
#include "imgui.h"
#include "backends/imgui_impl_dx11.h"
#include "backends/imgui_impl_win32.h"

#include"CameraController.h";

class DrawableGameObject;
class LightControll;

class ImGuiManager
{
public:
	ImGuiManager();
	~ImGuiManager();

	void BeginRender();
	void EndRender();
	void Initialize(HWND hWnd, ID3D11Device* device, ID3D11DeviceContext* context);


	//menus
	void DrawCamMenu(CameraController* Cams);
	void ShaderMenu();
	void ObjectControl(DrawableGameObject* GameObject);
	void LightControl(LightControll* LightControl);


private:
	void SetBlackGoldStyle();

};

