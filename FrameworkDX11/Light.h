#pragma once

#include"DrawableGameObject.h"

class Light_Data
{
public:
	Light_Data();
	Light_Data(string Name,bool Enabled, LightType _LightType, XMFLOAT4 Pos,XMFLOAT4 Colour, float Angle, float ConstantAttenuation, float LinearAttenuation, float QuadraticAttenuation);
	Light_Data(Light LightData);
	~Light_Data();


	void update(float t, ID3D11DeviceContext* pContext);
	void draw(ID3D11DeviceContext* pContext);

	Light GetLightData();
	void SetLightData(Light LightData);
	DrawableGameObject* GetLightObject();


	string GetName();
	void setName(string name);



	void setColour(XMFLOAT4 Colour);
	void setPos(XMFLOAT4 Pos);
	void setDirection(XMFLOAT4 dir);
private:

	Light _LightData;
	DrawableGameObject* LightObject;
	string Name;

	void CleanUP();
};

