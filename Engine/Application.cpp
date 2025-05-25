////////////////////////////////////////////////////////////////////////////////
// Filename: Application.cpp
////////////////////////////////////////////////////////////////////////////////
#include "Application.h"


CApplication::CApplication()
{
	m_direct3D = 0;
	m_camera = 0;
	m_model = 0;
	m_lightShader = 0;
	m_light = 0;
}


CApplication::CApplication(const CApplication& other)
{
}


CApplication::~CApplication()
{
}


bool CApplication::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	char modelFilename[128];
	char textureFilename[128];
	bool result;


	// Create and initialize the Direct3D object.
	m_direct3D = new Cd3D;

	result = m_direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_camera = new CCamera;

	// Set the initial position of the camera.
	m_camera->SetPosition(0.0f, 0.0f, -5.0f);

	// Set the file name of the model.
	strcpy_s(modelFilename, "../Engine/models/sphere.txt");

	// Create and initialize the model object.
	m_model = new CModel;

	// Set the name of the texture file that we will be loading.
	strcpy_s(textureFilename, "../Engine/textures/stone01.tga");

	result = m_model->Initialize(m_direct3D->GetDevice(), m_direct3D->GetDeviceContext(), modelFilename, textureFilename);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create and initialize the light shader object.
	m_lightShader = new CLightShader;

	result = m_lightShader->Initialize(m_direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create and initialize the light object.
	m_light = new CLight;

	m_light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_light->SetDirection(0.0f, -1.0f, 1.0f);
	m_light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_light->SetSpecularPower(32.0f);

	return true;
}


void CApplication::Shutdown()
{
	// Release the light object.
	if (m_light)
	{
		delete m_light;
		m_light = 0;
	}

	// Release the light shader object.
	if (m_lightShader)
	{
		m_lightShader->Shutdown();
		delete m_lightShader;
		m_lightShader = 0;
	}

	// Release the model object.
	if (m_model)
	{
		m_model->Shutdown();
		delete m_model;
		m_model = 0;
	}

	// Release the camera object.
	if (m_camera)
	{
		delete m_camera;
		m_camera = 0;
	}

	// Release the Direct3D object.
	if (m_direct3D)
	{
		m_direct3D->Shutdown();
		delete m_direct3D;
		m_direct3D = 0;
	}

	return;
}


bool CApplication::Frame()
{
	static float rotation = 0.0f;
	bool result;

	// Update the rotation variable each frame.
	rotation -= 0.0174532925f * 0.9f;
	if (rotation < 0.0f)
	{
		rotation += 360.0f;
	}

	// Render the graphics scene.
	result = Render(rotation);
	if (!result)
	{
		return false;
	}

	return true;
}


bool CApplication::Render(float rotation)
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, rotateMatrix, translateMatrix, scaleMatrix, srMatrix;
	bool result;


	// Clear the buffers to begin the scene.
	m_direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_direct3D->GetWorldMatrix(worldMatrix);
	m_camera->GetViewMatrix(viewMatrix);
	m_direct3D->GetProjectionMatrix(projectionMatrix);

	rotateMatrix = XMMatrixRotationY(rotation);  // Build the rotation matrix.
	translateMatrix = XMMatrixTranslation(0.0f, 0.0f, 0.0f);  // Build the translation matrix.

	// Multiply them together to create the final world transformation matrix.
	worldMatrix = XMMatrixMultiply(rotateMatrix, translateMatrix);

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_model->Render(m_direct3D->GetDeviceContext());

	// Render the model using the light shader.
	result = m_lightShader->Render(m_direct3D->GetDeviceContext(), m_model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_model->GetTexture(),
		m_light->GetDirection(), m_light->GetAmbientColor(), m_light->GetDiffuseColor(),
		m_camera->GetPosition(), m_light->GetSpecularColor(), m_light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	// Present the rendered scene to the screen.
	m_direct3D->EndScene();

	return true;
}