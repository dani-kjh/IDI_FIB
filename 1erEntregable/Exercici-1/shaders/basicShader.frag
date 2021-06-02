#version 330 core

in vec3 fcolor;

out vec4 FragColor;
uniform float pintar;

void main() {
    if(pintar == 1.0){
	    if ((gl_FragCoord.x > 354 && gl_FragCoord.y < 340) || 
        (gl_FragCoord.x < 354 && gl_FragCoord.y > 340) ){
            FragColor = vec4(0, 0, 1, 1);
        }
        else{
        FragColor = vec4(fcolor, 1);
        }
    }
    else{
    FragColor = vec4(fcolor, 1);
    }
}
    

