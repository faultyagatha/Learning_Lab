/* mesh deformation vertex shader
 created by @faulty_agatha on 24.07.19
 based on a workshop https://github.com/hamoid/Fun-Programming/wiki/In-the-Mood-for-Shaders
 */

#version 120


uniform float u_time;

attribute vec4 a_position;

mat2 rotation2d(float angle) {
    float s = sin(angle);
    float c = cos(angle);
    return mat2(c, -s, s, c);
}

void main() {
    vec4 pos = a_position;
    
    //deform
    pos.xz *= rotation2d(0.1 * sin(u_time * 5.0 + pos.y * 0.06));
    float amt = smoothstep(20., 50., pos.y) - smoothstep(50., 80., pos.y);
    pos.y += 20.0 * sin(u_time + pos.x * 0.1) * amt;

    gl_Position = gl_ModelViewProjectionMatrix * pos;
}
