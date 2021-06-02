#version 330 core

//in vec3 fcolor;

in vec3 matambFrag;
in vec3 matdiffFrag;
in vec3 matspecFrag;
in float matshinFrag;

in vec3 colFocusFrag;
in vec3 llumAmbientFrag;
in vec3 posFocusFrag;

in mat4 viewmatrix;
in mat4 transmatrix;

in vec3 NormalSCOF;
in vec3 vertexSCOF;


uniform bool tipoFoco;
uniform vec3 posFSecu;
uniform vec3 colFSecu;

out vec4 FragColor;


vec3 Lambert (vec3 NormSCO, vec3 L) 
{
    // S'assumeix que els vectors que es reben com a paràmetres estan normalitzats

    // Inicialitzem color a component ambient
    vec3 colRes = llumAmbientFrag * matambFrag;

    // Afegim component difusa, si n'hi ha
    if (dot (L, NormSCO) > 0)
      if(tipoFoco)
        colRes = colRes + colFocusFrag * matdiffFrag * dot (L, NormSCO);
      else 
        colRes = colRes + colFSecu * matdiffFrag * dot (L, NormSCO);
    return (colRes);
}

vec3 Phong (vec3 NormSCO, vec3 L, vec4 vertSCO) 
{
    // Els vectors estan normalitzats

    // Inicialitzem color a Lambert
    vec3 colRes = Lambert (NormSCO, L);

    // Calculem R i V
    if ((dot(NormSCO,L) < 0) || (matshinFrag == 0))
      return colRes;  // no hi ha component especular

    vec3 R = reflect(-L, NormSCO); // equival a: 2.0*dot(NormSCO,L)*NormSCO - L;
    vec3 V = normalize(-vertSCO.xyz); // perquè la càmera està a (0,0,0) en SCO

    if (dot(R, V) < 0)
      return colRes;  // no hi ha component especular
    
    float shine = pow(max(0.0, dot(R, V)), matshinFrag);
    if(tipoFoco)
      return (colRes + matspecFrag * colFocusFrag * shine);
    else 
       return (colRes + matspecFrag * colFSecu * shine);
}

void main()
{	
	vec3 NormalSCO = normalize(NormalSCOF);
  vec4 focusSCO;
  if(tipoFoco)
	  focusSCO = viewmatrix*vec4(posFocusFrag,1.0);
  else
    focusSCO = viewmatrix*vec4(posFSecu,1.0);
	vec3 LSCO = normalize(focusSCO.xyz - vertexSCOF);
  
  
	vec3 color = Phong(NormalSCO, LSCO, vec4(vertexSCOF, 1.0));
	FragColor = vec4(color,1);	
}
