/* voronoi
 algorithm: http://iquilezles.org/www/articles/smoothvoronoi/smoothvoronoi.htm
 implemented: @faulty_agatha
 Voronoi computes the distance to the closest feature point;
 we need 2 parameters:
 - 1. controls the amount of jittering of the feature points (the grid control parameter u)
 - 2. controls the metric (the metric controler v)
 */

#version 120
#extension GL_ARB_texture_rectangle : enable
#extension GL_EXT_gpu_shader4 : enable

uniform float u_time;
uniform float u_scale;
uniform float u_cell_size;
uniform vec2 u_resolution;
uniform sampler2DRect u_texture0;

float rand(vec2 pos){
    return fract(sin(dot(pos.xy ,vec2(12.9898,78.233))) * 43758.5453);
}


float voronoi(vec2 pos) {
    vec2 p = floor(pos);
    vec2 f = fract(pos);
    
    float dist = 8.0; //dist = distance to closest feature point
    for(int j=-1; j<=1; j++) {
        for(int i=-1; i<=1; i++) {
            vec2 lat = vec2(i, j); //lst = lattice point
            vec2  r = vec2(lat) - f + rand(p + lat);
            float d = dot(r, r); //d = current distance
            
            dist = min(dist, d);
        }
    }
    return sqrt(dist);
}

void main() {
    
    vec2 uv = (gl_FragCoord.xy / u_resolution.xy) * u_scale - 1.0;
    uv.x *= u_resolution.x / u_resolution.y;
    
    float offset = voronoi(uv * u_cell_size - vec2(u_time * 0.5));
    //main line: generates floating circles
    float r = voronoi(uv + sin(uv.y + u_time));
    
    gl_FragColor = vec4(r, 0., offset, 1.0);
}
