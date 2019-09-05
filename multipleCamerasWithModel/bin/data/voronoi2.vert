
//  simple vertex shader
//  CC II class, MA CTech
//
//  Created by @faulty_agatha on 27.06.19.
//

#version 120

void main() {
    //translate the current processed vertex position to the screen coordinate system
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}

