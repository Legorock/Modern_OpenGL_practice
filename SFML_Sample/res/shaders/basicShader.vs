#version 330

struct Light
{
	vec3 direction;
	vec3 colour;
	float intensity;
};

in vec3 position;
in vec2 texCoord;
in vec3 normal;

out vec2 texCoord0;
out vec3 normal0;
out vec3 position0;
out Light light0;
out vec3 viewPos0;

uniform mat4 transform;
uniform vec3 viewPos;

// light
uniform Light light;

void main()
{
	gl_Position = transform * vec4(position, 1.0);
	texCoord0 = texCoord;
	light0.direction = light.direction;
	light0.colour = light.colour;
	light0.intensity = light.intensity;
	normal0 = (transform * vec4(normal, 0.0)).xyz;
	position0 = position;
	viewPos0 = viewPos;
}