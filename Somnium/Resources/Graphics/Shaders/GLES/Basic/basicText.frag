#version 100

precision highp float;

varying vec2 texCoords;

uniform sampler2D text;
uniform vec3 textColor;

void main()
{    
    gl_FragColor = vec4(textColor, texture2D(text, texCoords).r);
}  
