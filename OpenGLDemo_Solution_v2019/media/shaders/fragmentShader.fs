#version 330 core
out vec4 FragColor;
in vec3 vertexcolor;
in vec2 outUV;
uniform vec4 uniformColor;
uniform sampler2D Texture;
uniform float time;
uniform float PI;
void main()
{
    //FragColor = vec4(1.0f, 1.0f, vertexcolor.gr);
    //FragColor = vec4(vertexcolor.rbg, 1.0f);
    FragColor =  texture(Texture, outUV.xy);
    //if(outUV.x > abs(sin(time*2.0f)))
    //   FragColor = vec4(0.0f, 0.2f, 0.2f, 1.0f);
    //vec2 uv1 = outUV - vec2(0.5);
    //vec2 uv2 = uv1 * vec2(abs(sin(time) / 0.5f));
    //vec2 uv3 = uv2 + vec2(0.5);
    //vec2 uvScroll = outUV + vec2(time*0.2f, 0.0f);
    //vec2 modifiedUV = outUV * vec2(2.0) - vec2(0.5);
    //vec2 invertedUV = vec2(1.0f, 1.0f) - outUV;
    //float angle = time*15.0f * 3.14f/180.0f;
    //vec2 uv4 = outUV * vec2(1.0f, 720.0f/1280.0f);
    //vec2 uv5 = uv4 - vec2(0.5f);
    //mat4 rotationMatrix = mat4(cos(angle),  sin(angle), 0.0f, 0.0f, 
    //                               -sin(angle), cos(angle), 0.0f, 0.0f, 
    //                                 0.0f, 0.0f, 1.0f, 0.0f, 
    //                               0.0f, 0.0f, 0.0f, 1.0f);
    //vec4 rotatedUV = rotationMatrix * vec4(uv5, 0.0f, 1.0f);
    //FragColor = texture(Texture, rotatedUV.xy*vec2(5.0f) - vec2(0.5));
}