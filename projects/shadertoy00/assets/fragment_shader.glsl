#version 330 core

out vec4 FragColor;

uniform float iTime;
uniform vec2 iResolution;
uniform int iFrame;
uniform vec4 iMouse;

void mainImage( out vec4 fragColor, in vec2 fragCoord );

void main()
{
    vec2 fragCoord = gl_FragCoord.xy;
    mainImage(FragColor, fragCoord);
}
