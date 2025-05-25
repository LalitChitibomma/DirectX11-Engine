////////////////////////////////////////////////////////////////////////////////
// Filename: lightclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "Light.h"


CLight::CLight()
{
}


CLight::CLight(const CLight& other)
{
}


CLight::~CLight()
{
}


void CLight::SetAmbientColor(float red, float green, float blue, float alpha)
{
    m_ambientColor = XMFLOAT4(red, green, blue, alpha);
    return;
}


void CLight::SetDiffuseColor(float red, float green, float blue, float alpha)
{
    m_diffuseColor = XMFLOAT4(red, green, blue, alpha);
    return;
}


void CLight::SetDirection(float x, float y, float z)
{
    m_direction = XMFLOAT3(x, y, z);
    return;
}

void CLight::SetSpecularColor(float red, float green, float blue, float alpha)
{
    m_specularColor = XMFLOAT4(red, green, blue, alpha);
    return;
}


void CLight::SetSpecularPower(float power)
{
    m_specularPower = power;
    return;
}

XMFLOAT4 CLight::GetAmbientColor()
{
    return m_ambientColor;
}



XMFLOAT4 CLight::GetDiffuseColor()
{
    return m_diffuseColor;
}


XMFLOAT3 CLight::GetDirection()
{
    return m_direction;
}

XMFLOAT4 CLight::GetSpecularColor()
{
    return m_specularColor;
}


float CLight::GetSpecularPower()
{
    return m_specularPower;
}