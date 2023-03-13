#include <pch.h>
#include <EditorCamera.h>

namespace Durian
{
    EditorCamera::EditorCamera(float viewportWidth, float viewportHeight)
    {
        m_Cam.Near = -1.0f;
        m_Cam.Far = 1.0f;
        OnViewportResize(viewportWidth, viewportHeight);
    }

    void EditorCamera::OnViewportResize(float width, float height)
    {
        m_Cam.xMin = -(width / 2.0f);
        m_Cam.xMax = width / 2.0f;
        m_Cam.yMin = -(height / 2.0f);
        m_Cam.yMax = height / 2.0f;
        m_Cam.UpdateMatrices();
    }
}