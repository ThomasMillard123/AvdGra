#pragma once
#include <vector>

#include "Camera.h"

using namespace std;
class CameraController
{
public:
	CameraController();
	~CameraController();


	void AddCam(Camera* cam);
	vector<Camera*> GetCamList();

	void RemoveAllCam();
	void RemoveCam(int CamNum);

	Camera* GetCurentCam();
	Camera* GetCam(int CamNo);
	Camera* GetCam(string CamName);

	bool SetCam(int CamNo);
	bool SetCam(string CamName);

	void Update();
private:

	vector<Camera*> CamList;
	int _CurrentCamNumber;

};

