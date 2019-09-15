/* worley algorithm, a variation of a cellular noise
 algorithm: https://thebookofshaders.com/12/
 implemented: @faulty_agatha
 */


#version 120

uniform float u_time;
uniform float u_scale;
uniform float u_cell_size;
uniform vec2 u_resolution;

vec2 random2(vec2 p) {
    return fract(sin(vec2(dot(p,vec2(127.1,311.7)),
                          dot(p,vec2(269.5,183.3))))*43758.5453);
}

void main() {
    vec2 pos = gl_FragCoord.xy / u_resolution.xy;
    pos.x *= u_resolution.x / u_resolution.y;

    pos *= u_scale; //scale the canvas [3.0]

    //tile the space
    vec2 i_pos= floor(pos); //tile coordinates stored as integer
    vec2 f_pos = fract(pos); //pixel coordinates stored as float

    // //example: check for each tile
    // vec2 point = random2(i_pos); //for each tile get a feature point randomly
    // vec2 d = point - f_pos; //difference between each pixel and random f.point
    // float dist = length(d); //get the distance to the f.points in each tile

    //2.check beween tiles
    //iterate through the neighbouring tiles: from -1 (left) to 1 (right)
    //tile in x axis and -1 (bottom) to 1 (top) in y axis
    float min_dist = 1.0;
    for(int y=-1; y<=1; y++) {
        for(int x=-1; x<=1; x++) {
            vec2 neighbour = vec2(float(x), float(y));
            //compute the random position of the points on each one of the
            //neighbours by adding the neighbour offset
            vec2 point = random2(i_pos + neighbour);
            //animate the points
            point = 0.5 + 0.5*sin(u_time + 6.2831*point);
            vec2 d = neighbour + point - f_pos; //difference between each pixel and random f.point
            float dist = length(d); //distance to the point
            min_dist = min(min_dist, dist); //get the closest distance
        }
    }
    //colour manipulation with helper functions
    float r = length(pos) * 2.0;
    float a = atan(pos.y, pos.x);

    float f = cos(a*3.0);
    // f = abs(cos(a*3.0));
    // f = abs(cos(a*2.5))*0.5+0.3;
    // f = abs(cos(a*12.0)*sin(a*3.0))*0.8+0.1;
    // f = smoothstep(-0.5, 1.0, cos(a*10.0))*0.2+0.5;
    f = abs(cos(a) * sin(a*3.0));


    vec3 colour = vec3(min_dist);
    //draw cell center
    colour.r += step(sin(f), min_dist) * 0.7;
    colour.g += step(f*0.1, min_dist) * 0.3;
    colour.b += step(cos(f*0.2), min_dist) * 0.2;

    gl_FragColor = vec4(vec3(colour.r, colour.g, colour.b), 1.0);
}
