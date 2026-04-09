#pragma once

#include "FrostMath.h"

namespace FrostEngine
{
    class Camera2D
    {
    public:
        Camera2D();

        Camera2D(int width, int height);

        void SetPosition(const vec2 &pos) { m_Pos = pos; m_NeedsUpdate = true; }

        void SetScale(float scaleValue) { m_Scale = scaleValue; m_NeedsUpdate = true; }

        vec2 GetPosition() const { return m_Pos; }
        float GetScale() const { return m_Scale; }

        void Update();

        const mat4 &GetCameraMatrix() const { return m_CameraMatrix; }

    private:
        int m_Width;
        int m_Height;
        float m_Scale;
        vec2 m_Pos;

        mat4 m_CameraMatrix;
        mat4 m_Projection;
        bool m_NeedsUpdate;
    };
}
