//
//  voronoi.cpp
//  collab_project_v2
//
//  Created by Valeriia Barvinska on 27.06.19.
//

//#version 120
//#extension GL_ARB_texture_rectangle : enable
//#extension GL_EXT_gpu_shader4 : enable

#ifdef GL_ES
precision mediump float;
#endif

uniform mat4 modelViewProjectionMatrix;
attribute vec4 position;


void main() {
    //translate the current processed vertex position to the screen coordinate system
    gl_Position = modelViewProjectionMatrix * position;
}
