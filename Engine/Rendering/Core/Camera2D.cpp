#include "Camera2D.h"

namespace FrostEngine
{
    Camera2D::Camera2D()
        : Camera2D(640, 480) {
          };

    Camera2D::Camera2D(int width, int height)
        : m_Width(width),
          m_Height(height),
          m_Scale(1.0f),
          m_Pos(0.0f, 0.0f),
          m_CameraMatrix(1.0f),
          m_Projection(1.0f),
          m_NeedsUpdate(true)
    {
        m_Projection = ortho(0.0f, (float)m_Width, (float)m_Height, 0.0f);
        // m_Projection = ortho(0.0f, (float)m_Width, 0, (float)m_Height);
        Update();
    };

    void Camera2D::Update()
    {
        if (!m_NeedsUpdate)
            return;

        mat4 translation = translate(vec3(-m_Pos.x, -m_Pos.y, 0.0f));
        mat4 scaling = scale(vec3(m_Scale, m_Scale, 1.0f));

        m_CameraMatrix = m_Projection * translation * scaling;
        m_NeedsUpdate = false;
    }

}
