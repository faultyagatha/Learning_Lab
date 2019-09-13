/* vertex shader
 created by @faulty_agatha on 24.08.19
 based on https://subscription.packtpub.com/book/game_development/9781849695046/1/ch01lvl1sec12/doing-a-ripple-mesh-deformer-using-the-vertex-shader
 */

#version 120

uniform float u_time;
uniform float u_scale;
uniform float u_cell_size;
uniform float u_mouse_x; //test uniform

attribute vec4 a_position;

//const float amp = 0.125;
//const float freq = 0.2;
//const float PI = 3.14159;

mat2 rotation2d(float angle) {
    float s = sin(angle);
    float c = cos(angle);
    return mat2(c, -s, s, c);
}

void main() {
    vec4 pos = a_position;
    float dist = length(pos)*u_scale;
    float z = u_scale * sin(0.1 * dist * u_cell_size + u_time);
    
    gl_Position = gl_ModelViewProjectionMatrix * vec4(pos.x, pos.y, z, 1);
}
