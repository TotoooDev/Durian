#include <pch.h>
#include <Durian/Core/Application.h>
#include <EditorCamera.h>
#include <glm/gtc/matrix_transform.hpp>

namespace Durian
{
    EditorCamera::EditorCamera(float viewportWidth, float viewportHeight, glm::vec3 pos)
        : m_Pos(pos)
    {
        Application::Get().GetEventBus()->Subscribe(this, &EditorCamera::OnMouseButtonDown);
        Application::Get().GetEventBus()->Subscribe(this, &EditorCamera::OnMouseButtonUp);
        Application::Get().GetEventBus()->Subscribe(this, &EditorCamera::OnMouseScrolled);
        Application::Get().GetEventBus()->Subscribe(this, &EditorCamera::OnMouseMoved);

        m_Cam.Near = -1.0f;
        m_Cam.Far = 1.0f;
        OnViewportResize(viewportWidth, viewportHeight);
        m_View = glm::lookAt(m_Pos, m_Pos + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    }

    void EditorCamera::OnUpdate(double timestep)
    {

    }

    void EditorCamera::OnViewportResize(float width, float height)
    {
        m_AspectRatio = width / height;
        m_Cam.xMin = -(width / 2.0f);
        m_Cam.xMax = width / 2.0f;
        m_Cam.yMin = height / 2.0f;
        m_Cam.yMax = -(height / 2.0f);
        m_Cam.UpdateMatrices();
    }

    void EditorCamera::OnMouseButtonDown(MouseButtonDownEvent* event)
    {
        if (event->Button == DURIAN_BUTTON_LEFT)
            m_Inputs.LeftButton = true;
        if (event->Button == DURIAN_BUTTON_MIDDLE)
            m_Inputs.MiddleButton = true;
        if (event->Button == DURIAN_BUTTON_RIGHT)
            m_Inputs.RightButton = true;
    }
    void EditorCamera::OnMouseButtonUp(MouseButtonUpEvent* event)
    {
        if (event->Button == DURIAN_BUTTON_LEFT)
            m_Inputs.LeftButton = false;
        if (event->Button == DURIAN_BUTTON_MIDDLE)
            m_Inputs.MiddleButton = false;
        if (event->Button == DURIAN_BUTTON_RIGHT)
            m_Inputs.RightButton = false;
    }
    void EditorCamera::OnMouseScrolled(MouseScrolledEvent* event)
    {
        if (Hovered)
        {
            m_Cam.xMin += event->yOffset * 5.0f * -m_AspectRatio;
            m_Cam.xMax -= event->yOffset * 5.0f * m_AspectRatio;
            m_Cam.yMin -= event->yOffset * 5.0f;
            m_Cam.yMax += event->yOffset * 5.0f;
            m_Cam.UpdateMatrices();
        }
    }
    void EditorCamera::OnMouseMoved(MouseMovedEvent* event)
    {
        if (m_Inputs.MiddleButton && Hovered)
        {
            glm::vec2 movement(m_LastMousePos.x - event->x, m_LastMousePos.y - event->y);
            m_Pos.x += m_LastMousePos.x - event->x;
            m_Pos.y += m_LastMousePos.y - event->y;
            m_View = glm::lookAt(m_Pos, m_Pos + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        }
        m_LastMousePos = glm::vec2(event->x, event->y);
    }
}