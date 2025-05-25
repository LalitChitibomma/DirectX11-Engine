////////////////////////////////////////////////////////////////////////////////
// Filename: Application.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _APPLICATION_H_
#define _APPLICATION_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3Dclass.h"
#include "Camera.h"
#include "Model.h"
#include "LightShader.h"
#include "Light.h"


/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.3f;


////////////////////////////////////////////////////////////////////////////////
// Class name: CApplication
////////////////////////////////////////////////////////////////////////////////
class CApplication
{
public:
	CApplication();
	CApplication(const CApplication&);
	~CApplication();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();

private:
	bool Render(float);

private:
	Cd3D* m_direct3D;
	CCamera* m_camera;
	CModel* m_model;
	CLightShader* m_lightShader;
	CLight* m_light;

};

#endif