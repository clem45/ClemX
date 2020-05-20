#include "Includes.h"
#define PI 3.1415926535

D3DXVECTOR3 ClampAngles(D3DXVECTOR3 angle)
{
    while (angle.x < -180.0f)
        angle.x += 360.0f;

    while (angle.x > 180.0f)
        angle.x -= 360.0f;

    if (angle.x > 89.0f)
        angle.x = 89.0f;

    if (angle.x < -89.0f)
        angle.x = -89.0f;

    while (angle.y < -180.0f)
        angle.y += 360.0f;

    while (angle.y > 180.0f)
        angle.y -= 360.0f;

    angle.z = 0.0f;

    return angle;
}

D3DXVECTOR3 CalcAngle(const D3DXVECTOR3 & src, const D3DXVECTOR3 & dst)
{
    //square root func faster than normal func youd use
    const auto sqrtss = [](float in)
    {
        __m128 reg = _mm_load_ss(&in);
        return _mm_mul_ss(reg, _mm_rsqrt_ss(reg)).m128_f32[0];
    };


    D3DXVECTOR3 angles;

    //getting delta between source and destination vectors
    D3DXVECTOR3 delta = src - dst;

    //finding the hypoteneuse using pythagoras theorem a squared + b squared = c squared
    //this gives us the vector to our enemy
    float hyp = sqrtss(delta.x * delta.x + delta.y * delta.y);

    //now we need to find the angle needed to aim at the vector (aim angles)
    angles.x = asinf(delta.z / hyp) * (180 / PI);
    angles.y = atanf(delta.y / delta.x) * (180 / PI) + !((*(DWORD*)&delta.x) >> 31 & 1) * 180;

    angles.z = 0;

    return angles;
}

void VectorAngles(D3DXVECTOR3 forward, D3DXVECTOR3 & angles)
{
    float yaw;
    float pitch;

    if (forward.z == 0 && forward.x == 0)
    {
        yaw = 0;
        pitch = 270;
    }
    else
    {
        float tmp;
        yaw = (atan2(forward.y, forward.x) * 180 / PI);

        if (yaw < 0)
            yaw += 360;

        tmp = sqrt(forward.x * forward.x + forward.y * forward.y);
        pitch = (atan2(-forward.z, tmp) * 180 / PI);

        if (pitch < 0)
            pitch += 360;
    }

    if (pitch > 180)
        pitch -= 360;
    else if (pitch < -180)
        pitch += 360;

    if (yaw > 180)
        yaw -= 360;
    else if (yaw < -180)
        yaw += 360;

    if (pitch > 89)
        pitch = 89;
    else if (pitch < -89)
        pitch = -89;

    if (yaw > 180)
        yaw = 180;
    else if (yaw < -180)
        yaw = -180;

    angles.x = pitch;
    angles.y = yaw;
    angles.z = 0;
}
