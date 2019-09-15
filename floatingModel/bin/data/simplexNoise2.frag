/*  simplex noise
 by @faulty_agatha
 based on functions from
 http://patriciogonzalezvivo.com
 and https://github.com/ashima/webgl-noise
 */

#version 120

uniform vec2 u_resolution;
uniform float u_time;
uniform float u_scale;

//helper functions
vec3 mod289(vec3 x) { return x - floor(x * (1.0/289.0)) * 289.0; }
vec2 mod289(vec2 x) { return x - floor(x * (1.0/289.0)) * 289.0; }
vec3 permute(vec3 x) { return mod289(((x * 34.0) + 1.0) * x); }

//simplex noise
float snoise(vec2 v) {
    const vec4 C = vec4(0.211324865405187,  // (3.0-sqrt(3.0))/6.0
                        0.366025403784439,  // 0.5*(sqrt(3.0)-1.0)
                        -0.577350269189626,  // -1.0 + 2.0 * C.x
                        0.024390243902439); // 1.0 / 41.0
    //first corner
    vec2 i  = floor(v + dot(v, C.yy));
    vec2 x0 = v -   i + dot(i, C.xx);
    
    //other corners
    vec2 i1;
    i1 = (x0.x > x0.y) ? vec2(1.0, 0.0) : vec2(0.0, 1.0);
    vec4 x12 = x0.xyxy + C.xxzz;
    x12.xy -= i1;
    
    //permutations
    i = mod289(i); //avoid truncation effects in permutation
    vec3 p = permute(permute(i.y + vec3(0.0, i1.y, 1.0 ))
                     + i.x + vec3(0.0, i1.x, 1.0 ));
    
    vec3 m = max(0.5 - vec3(dot(x0,x0), dot(x12.xy,x12.xy), dot(x12.zw,x12.zw)), 0.0);
    m = m*m ;
    m = m*m ;
    
    //gradients: 41 points uniformly over a line, mapped onto a diamond.
    //the ring size 17*17 = 289 is close to a multiple of 41 (41*7 = 287)
    vec3 x = 2.0 * fract(p * C.www) - 1.0;
    vec3 h = abs(x) - 0.5;
    vec3 ox = floor(x + 0.5);
    vec3 a0 = x - ox;
    
    //normalise gradients implicitly by scaling m
    //approximation of: m *= inversesqrt( a0*a0 + h*h );
    m *= 1.79284291400159 - 0.85373472095314 * (a0*a0 + h*h);
    
    //compute final noise value at P
    vec3 g;
    g.x  = a0.x  * x0.x  + h.x  * x0.y;
    g.yz = a0.yz * x12.xz + h.yz * x12.yw;
    return 130.0 * dot(m, g);
}

float fbm_5oct(vec2 p) {
    float f = 0.0;
    f += 0.50000*snoise( p ); p = p*2.02;
    f += 0.25000*snoise( p ); p = p*2.03;
    f += 0.12500*snoise( p ); p = p*2.01;
    f += 0.06250*snoise( p ); p = p*2.04;
    // f += 0.03125*snoise( p );
    return f/0.984375;
}

float fbm(vec2 P, float lacunarity, float gain) {
    const int octaves = 10;
    float sum = 0.0;
    float amp = 1.0;
    vec2 pp = P;
    
    for( int i = 0; i < octaves; i+=1) {
        amp *= gain;
        sum += amp * snoise(pp);
        pp *= lacunarity;
    }
    return sum;
}

vec3 rgb2hsb(vec3 c){
    vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    vec4 p = mix(vec4(c.bg, K.wz),
                 vec4(c.gb, K.xy),
                 step(c.b, c.g));
    vec4 q = mix(vec4(p.xyw, c.r),
                 vec4(c.r, p.yzx),
                 step(p.x, c.r));
    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;
    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)),
                d / (q.x + e),
                q.x);
}

void main() {
    vec2 pos = gl_FragCoord.xy/u_resolution.xy;
    pos.x *= u_resolution.x/u_resolution.y;
    vec3 color = vec3(0.0);
    vec2 p = vec2(pos*u_scale);
    
    float DF = 0.0;
    
    //add a random position
    float a = 0.0;
    vec2 vel = vec2(u_time*.1);
    // DF += snoise(pos+vel)*.25+.25; //optional result
    DF += fbm_5oct(pos+vel)*0.25+0.25;
    
    //add a random position
    // a = snoise(pos*vec2(cos(u_time*0.15),sin(u_time*0.1))*0.1)*3.1415;
    // a = fbm_5oct(pos*vec2(cos(u_time*0.15),sin(u_time*0.1))*0.1)*3.1415;
    a = fbm(pos, cos(u_time*0.15), sin(u_time*0.1));
    vel = vec2(cos(a), sin(a));
    DF += snoise(pos+vel)*0.25+0.25;
    
    // color.r = smoothstep(0.3, 0.75, fract(DF * u_time * 0.1)); //75. [10, 75]
    // color.b = smoothstep(0.3, 0.75, fract(DF)); //75. [10, 75]
    // color.g = step(DF, DF * 0.1); //abs(DF * 0.1); //0.1 [0.1., 0.5]
    
    gl_FragColor = vec4(color.r, color.g, 1.0-color.b, 1.0);
    
    //2d version
    float at = atan(pos.y,pos.x);
    float f = smoothstep(-.5,1., cos(a*10.))*0.2+0.5;
    color = rgb2hsb(vec3(f));
    
    color.r += smoothstep(0.3, f*0.5, fract(f*DF)); //75. [10, 75]
    color.b += smoothstep(0.7, f, fract(DF*2.0)); //75. [10, 75]
    color.g += smoothstep(0.3, f*0.1, fract(f));//step(f, f * 0.3);
    
    gl_FragColor = vec4(color.r, color.g, color.b, 1.0);
}

