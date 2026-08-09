#version 300 es
layout(location = 0) in vec4 VertexPosition;
layout(location = 1) in vec4 VertexColor;

uniform float RadianAngle;

out vec4 TriangleColor;

void main()
{
    float c = cos(RadianAngle);
    float s = sin(RadianAngle);

    // 2D rotation matrix applied to XY, Z and W pass through
    vec2 rotated = mat2(c, s, -s, c) * VertexPosition.xy;
    gl_Position   = vec4(rotated, 0.0, 1.0);
    TriangleColor = VertexColor;
}
