#include "Light.h"

Light_Data::Light_Data()
{
}

Light_Data::Light_Data(string Name, bool Enabled, LightType _LightType, XMFLOAT4 Pos, XMFLOAT4 Colour, float Angle, float ConstantAttenuation, float LinearAttenuation, float QuadraticAttenuation):Name(Name)
{
	_LightData.Enabled = Enabled;
	_LightData.LightType = _LightType;
	_LightData.Position = Pos;
	_LightData.Color = Colour;
	_LightData.SpotAngle = Angle;
	_LightData.ConstantAttenuation = ConstantAttenuation;
	_LightData.LinearAttenuation = LinearAttenuation;
	_LightData.QuadraticAttenuation = QuadraticAttenuation;


	XMVECTOR LightDirection = XMVectorSet(-Pos.x, -Pos.y, -Pos.z, 0.0f);
	LightDirection = XMVector3Normalize(LightDirection);
	XMStoreFloat4(&_LightData.Direction, LightDirection);

	LightObject = new DrawableGameObject();

	LightObject->GetTransfrom()->SetScale(0.2f, 0.2f, 0.2f);
}

Light_Data::Light_Data(Light LightData): _LightData(LightData)
{
	
}

Light_Data::~Light_Data()
{
	CleanUP();
}

void Light_Data::update(float t, ID3D11DeviceContext* pContext)
{
	if (_LightData.Enabled) {
		if (LightObject->GetAppearance()) {
			LightObject->GetTransfrom()->SetPosition(_LightData.Position.x, _LightData.Position.y, _LightData.Position.z);
			LightObject->update(t, pContext);
		}
	}

}

void Light_Data::draw(ID3D11DeviceContext* pContext)
{
	if (_LightData.Enabled) {
		if (LightObject->GetAppearance()) {
			LightObject->draw(pContext);
		}
	}
}

Light Light_Data::GetLightData()
{
	return _LightData;
}

void Light_Data::SetLightData(Light LightData)
{
	_LightData = LightData;
}

DrawableGameObject* Light_Data::GetLightObject()
{
	return LightObject;
}

string Light_Data::GetName()
{
	return Name;
}

void Light_Data::setName(string name)
{
	Name = name;
}

void Light_Data::setColour(XMFLOAT4 Colour)
{
	_LightData.Color = Colour;

}

void Light_Data::setPos(XMFLOAT4 Pos)
{
	_LightData.Position = Pos;

}

void Light_Data::setDirection(XMFLOAT4 dir)
{
	XMVECTOR LightDirection = XMVectorSet(dir.x, dir.y, dir.z, 0.0f);
	LightDirection = XMVector3Normalize(LightDirection);
	XMStoreFloat4(&_LightData.Direction, LightDirection);

	
}

void Light_Data::SetEnabled(bool enabled)
{

	_LightData.Enabled = XMConvertToRadians(enabled);


}

void Light_Data::SetAttenuation(float ConstantAttenuation, float LinearAttenuation, float QuadraticAttenuation)
{
	_LightData.ConstantAttenuation = ConstantAttenuation;
	_LightData.LinearAttenuation = LinearAttenuation;
	_LightData.QuadraticAttenuation = QuadraticAttenuation;

}

void Light_Data::SetAngle(float Angle)
{
	_LightData.SpotAngle = Angle;
}

void Light_Data::CleanUP()
{

	if (LightObject)
		delete LightObject;
	LightObject = nullptr;



}
