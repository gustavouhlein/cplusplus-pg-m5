#version 400

in vec3 vertexColor;
in vec2 texcoord;
uniform sampler2D texBuffer;
uniform vec2 offset;
uniform float frameWidth;
out vec4 color;

void main()
{
    vec2 texCoords = texcoord * vec2(frameWidth, 1.0) + offset;
    color = texture(texBuffer, texCoords);
}
