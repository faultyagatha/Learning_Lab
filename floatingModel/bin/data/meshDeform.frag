/*
 mesh deform fragment shader
 implemented: @faulty_agatha
 */

#version 120

//TODO: write an interesting fragment shader
//void main() {
//    gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
//}

uniform float u_time;
uniform float u_scale;
uniform float u_cell_size;
uniform vec2 u_resolution;

float rand(vec2 pos) {
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
    vec2 pos = (gl_FragCoord.xy / u_resolution.xy) * u_scale - 1.0;
    pos.x *= u_resolution.x / u_resolution.y;
    
    float offset = voronoi(pos * u_cell_size - vec2(u_time * 0.5));
    //main line: generates floating circles
    float r = voronoi(pos + sin(pos.y + u_time));
    float g = voronoi(pos) * u_cell_size + u_time;
    
    gl_FragColor = vec4(r, 1.0-offset, 1.0-r, 1.0);
}
