//
//  blood_vessels.cpp
//  collab_project_v2
//
//  Created by Valeriia Barvinska on 27.06.19.
//

#version 120
#extension GL_ARB_texture_rectangle : enable
#extension GL_EXT_gpu_shader4 : enable

void main() {
    //translate the current processed vertex position to the screen coordinate system
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}


