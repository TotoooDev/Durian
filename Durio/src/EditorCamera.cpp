#include <pch.h>
#include <Durian/Core/Application.h>
#include <EditorCamera.h>
#include <glm/gtc/matrix_transform.hpp>

namespace Durian
{
    EditorCamera::EditorCamera(float viewportWidth, float viewportHeight, glm::vec3 pos)
        : m_Pos(pos), m_Speed(100.0f)
    {
        Application::Get().GetEventBus()->Subscribe(this, &EditorCamera::OnMouseButtonDown);
        Application::Get().GetEventBus()->Subscribe(this, &EditorCamera::OnMouseButtonUp);
        Application::Get().GetEventBus()->Subscribe(this, &EditorCamera::OnMouseScrolled);
        Application::Get().GetEventBus()->Subscribe(this, &EditorCamera::OnMouseMoved);
        Application::Get().GetEventBus()->Subscribe(this, &EditorCamera::OnKeyDown);
        Application::Get().GetEventBus()->Subscribe(this, &EditorCamera::OnKeyUp);

        m_Cam.Near = -1.0f;
        m_Cam.Far = 1.0f;
        OnViewportResize(viewportWidth, viewportHeight);
        UpdateViewMatrix();
    }

    void EditorCamera::OnUpdate(double timestep)
    {
        if (m_Inputs.Up)
            m_Pos.y -= m_Speed * timestep;
        if (m_Inputs.Down)
            m_Pos.y += m_Speed * timestep;
        if (m_Inputs.Right)
            m_Pos.x += m_Speed * timestep;
        if (m_Inputs.Left)
            m_Pos.x -= m_Speed * timestep;
        
        bool changed = m_Inputs.Up || m_Inputs.Down || m_Inputs.Left || m_Inputs.Right;
        if (changed)
            UpdateViewMatrix();
    }

    void EditorCamera::OnViewportResize(float width, float height)
    {
        m_AspectRatio = width / height;
        m_Cam.xMin = 0.0f;
        m_Cam.xMax = width;
        m_Cam.yMin = 0.0f;
        m_Cam.yMax = height;
        m_Cam.UpdateMatrices();
    }

    void EditorCamera::UpdateViewMatrix()
    {
        m_View = glm::lookAt(m_Pos, m_Pos + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
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
            // m_Cam.xMin += event->yOffset * 5.0f * m_AspectRatio;
            // m_Cam.xMax -= event->yOffset * 5.0f;
            // m_Cam.yMin -= event->yOffset * 5.0f;
            // m_Cam.yMax += event->yOffset * 5.0f * m_AspectRatio;
            // m_Cam.UpdateMatrices();

            float zoomLevel = event->yOffset * 0.01f + 1.0f;
            m_View = glm::scale(m_View, glm::vec3(zoomLevel, zoomLevel, 0.0f));
        }
    }
    void EditorCamera::OnMouseMoved(MouseMovedEvent* event)
    {
        if (m_Inputs.MiddleButton && Hovered)
        {
            glm::vec2 movement(m_LastMousePos.x - event->x, m_LastMousePos.y - event->y);
            m_Pos.x += m_LastMousePos.x - event->x;
            m_Pos.y += m_LastMousePos.y - event->y;
            // UpdateViewMatrix();
            m_View = glm::translate(m_View, glm::vec3(m_LastMousePos.x - event->x, m_LastMousePos.y - event->y, 0.0f));
        }
        m_LastMousePos = glm::vec2(event->x, event->y);
    }
    void EditorCamera::OnKeyDown(KeyDownEvent* event)
    {
        if (Hovered)
        {
            if (event->Keycode == DURIAN_SCANCODE_UP)
                m_Inputs.Up = true;
            if (event->Keycode == DURIAN_SCANCODE_DOWN)
                m_Inputs.Down = true;
            if (event->Keycode == DURIAN_SCANCODE_LEFT)
                m_Inputs.Left = true;
            if (event->Keycode == DURIAN_SCANCODE_RIGHT)
                m_Inputs.Right = true;
        }
    }
    void EditorCamera::OnKeyUp(KeyUpEvent* event)
    {
        if (event->Keycode == DURIAN_SCANCODE_UP)
            m_Inputs.Up = false;
        if (event->Keycode == DURIAN_SCANCODE_DOWN)
            m_Inputs.Down = false;
        if (event->Keycode == DURIAN_SCANCODE_LEFT)
            m_Inputs.Left = false;
        if (event->Keycode == DURIAN_SCANCODE_RIGHT)
            m_Inputs.Right = false;
    }
}