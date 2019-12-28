#version 330 core
in vec3 Color;
in vec2 TexCoord;
in vec3 Pos;
in vec3 Normal;

out vec4 FragColor;

uniform sampler2D Texture1;
uniform vec3 cameraPos;

const float SRGB_GAMMA = 1.0 / 2.2;
const float SRGB_INVERSE_GAMMA = 2.2;
const float SRGB_ALPHA = 0.055;

float linear_to_srgb(float channel) {
    if(channel <= 0.0031308)
        return 12.92 * channel;
    else
        return (1.0 + SRGB_ALPHA) * pow(channel, 1.0/2.4) - SRGB_ALPHA;
}

// Converts a single srgb channel to rgb
float srgb_to_linear(float channel) {
    if (channel <= 0.04045)
        return channel / 12.92;
    else
        return pow((channel + SRGB_ALPHA) / (1.0 + SRGB_ALPHA), 2.4);
}

// Converts a linear rgb color to a srgb color (exact, not approximated)
vec3 rgb_to_srgb(vec3 rgb) {
    return vec3(
        linear_to_srgb(rgb.r),
        linear_to_srgb(rgb.g),
        linear_to_srgb(rgb.b)
    );
}

// Converts a srgb color to a linear rgb color (exact, not approximated)
vec3 srgb_to_rgb(vec3 srgb) {
    return vec3(
        srgb_to_linear(srgb.r),
        srgb_to_linear(srgb.g),
        srgb_to_linear(srgb.b)
    );
}


void main()
{
    // point light
    vec3 lightPos = vec3(cameraPos);
    vec3 lightDir = lightPos - Pos;
    float lightDistSquared = dot(lightDir, lightDir);
    float lightIntensity = 5.0 / lightDistSquared;
    lightDir /= sqrt(lightDistSquared);

    // vec3 lightDir = normalize(vec3(1.0)); // directional light
    // float lightIntensity = 1.0;
    float lighting = dot(normalize(Normal), lightDir) * lightIntensity;
    FragColor = texture(Texture1, TexCoord) * lighting;
    //FragColor = vec4(Pos * 0.5f + 0.5f, 1.0f);
    //FragColor = vec4(Normal * 0.5f + 0.5f, 1.0f);
    FragColor = vec4(rgb_to_srgb(FragColor.rgb), 1.0);
}