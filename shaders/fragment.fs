#version 330 core
in vec3 Color;
in vec2 TexCoord;
in vec3 Pos;
in vec3 Normal;

out vec4 FragColor;

uniform sampler2D Texture1;
//uniform sampler2D Texture2;

void main()
{
//  FragColor = texture(Texture1, TexCoord) * texture(Texture2, TexCoord);
   // vec4 texel2 = texture(Texture2, TexCoord);
    //if(texel2.a == 0)
    //{
    //    FragColor = texture(Texture1, TexCoord);
    //}
    //else
    //{
     //   FragColor = texture(Texture1, TexCoord) * texture(Texture2, TexCoord);
    //}
//	FragColor = mix(texture(Texture1, TexCoord), texel2, texel2.a);
//  FragColor = texture(Texture1, TexCoord) + vec4(Color, 1);

    vec3 lightDir = normalize(vec3(1.0));
    float lighting = 1; //dot(normalize(Normal), lightDir);
    FragColor = texture(Texture1, TexCoord) * lighting;

    //FragColor = vec4(Pos * 0.5f + 0.5f, 1.0f);
    //FragColor = vec4(Normal * 0.5f + 0.5f, 1.0f);
}