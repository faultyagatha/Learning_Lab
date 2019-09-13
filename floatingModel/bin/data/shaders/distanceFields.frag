/* distance field
 algorithm: https://thebookofshaders.com/07/
 implemented: @faulty_agatha
 */

#version 120

uniform vec2 u_resolution;
uniform float u_time;
uniform float u_scale;
uniform float u_cell_size; //here cell_size is a colour factor

void main() {
    vec2 pos = gl_FragCoord.xy/u_resolution.xy;
    pos.x *= u_resolution.x/u_resolution.y;
    vec3 colour = vec3(0.0);
    float d = 0.0;
    
    //adding some movement
    pos = pos * u_scale - u_time * 0.1;
    
    //make the distance field
    //   d = length(abs(pos) - 0.3 );
    d = length(sin(pos) - 0.3);
    //   d = length( min(abs(pos)-.3,0.) );
    //   d = length( max(abs(pos)-.3,0.) );
    
    //visualise the distance field
    colour.r = fract(d * 5.0);
    colour.g = fract(d * 0.0);
    colour.b = fract(d * u_cell_size);
    
    gl_FragColor = vec4(vec3(colour.r, colour.g, colour.b), 1.0);
}
