/* simple vertex shader
 created by @faulty_agatha on 24.07.19
 */

#version 120

void main() {
    //translate the current processed vertex position to the screen coordinate system
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
