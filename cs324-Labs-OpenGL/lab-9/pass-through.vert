#version 120

void main(void)
{
	// transform the vertex using the modelview and projection matrix
	//gl_Position =  gl_ModelViewProjectionMatrix * (gl_Vertex + (-0.9,0.2,0.2,0.0));
	gl_Position =  gl_ModelViewProjectionMatrix * gl_Vertex + (1.5,1.5,0.5,0.0);

	//gl_FrontColor = gl_Color; // pass out the input colour to geom/frag shader
	gl_FrontColor = vec4(1.0,0.0,0.0,1.0);
}
