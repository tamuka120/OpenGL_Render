#version 330 core


in vec4 gl_FragCoord;


in vec2 texCoords;
uniform sampler2D ourTexture;
uniform float color_intensity;

out vec4 FragColor;

float near = 0.1; 

float far  = 100.0; 
float getDepthNDC()
{
	// From 0 to 1
	float depth  = gl_FragCoord.z;
	return depth * 2 - 1; 
}

float getDepthSansProjectionTransformation()
{
	float ndc = getDepthNDC();

	float a = far + near - ndc * (far - near);
	float b = 2.0 * near * far;
	return a / b;
	
}

void main()
{
	float linearDepth = getDepthSansProjectionTransformation();
	FragColor = vec4(vec3(linearDepth / near), 1.0);
	// vec4 tex = texture(ourTexture, texCoords);
	// tex.xyz *= vec3(texCoords, 0.5f) * color_intensity;
	// FragColor = tex;

}
