#version 100

precision mediump float;

uniform vec2 light_position;

varying vec3 basicCol;
varying vec4 FragColor;

void main()
{
gl_FragColor = vec4(basicCol,1.0);
}
