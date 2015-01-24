#version 150

struct Light
{
	vec3 direction;
	vec3 colour;
	float intensity;
};

in vec2 texCoord0;
in vec3 normal0;
in vec3 position0;
in Light light0;
in vec3 viewPos;

uniform sampler2D diffuse;

void main()
{		
	float scale = 2;

	gl_FragColor = texture(diffuse, texCoord0 * scale) * vec4(light0.colour,1.0)
		* clamp(dot(-light0.direction, normal0) * light0.intensity, 0.0, 1.0);			
}