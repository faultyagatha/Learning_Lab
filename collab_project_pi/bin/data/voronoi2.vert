//
//  voronoi.cpp
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
    
    //set the built-in vertex attribute gl_TexCoord[0] equal to the texture coordinate of the bound image, held in the built-in variable gl_MultiTexCoord0. This value will be interpolated to the gl_TexCoord[0] value of each pixel incoming to the fragment shader.
//    gl_TexCoord[0] = gl_MultiTexCoord0;
    
    //gl_Color is a built-in variable that is equal to the color you set by calling the ofSetColor() function in openFrameworks code. gl_FrontColor is a built-in variable that assigns a color for the frontal faces of 3D and 2D objects.
//    gl_FrontColor = gl_Color;
}

