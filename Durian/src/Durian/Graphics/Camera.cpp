#include <pch.h>
#include <Graphics/Camera.h>
#include <glm/gtc/matrix_transform.hpp>

namespace Durian
{
    OrthoCamera::OrthoCamera()
    {
        UpdateMatrices();
    }

    void OrthoCamera::UpdateMatrices()
    {
        m_Projection = glm::ortho(xMin, xMax, yMin, yMax, Near, Far);
    }
}