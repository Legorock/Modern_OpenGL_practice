#version 330

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
in vec3 viewPos0;

uniform sampler2D diffuse;

void main()
{		
	float scale = 2;

	vec4 texComponent = texture(diffuse, texCoord0 * scale);
	vec4 diffuseComponent = vec4(light0.colour, 1.0) * 
							clamp(dot(-light0.direction, normal0) * 
							light0.intensity, 0.0, 1.0);
	
	// spacularHighligt
	vec3 viewDirection = normalize(position0 - viewPos0);
	vec3 reflectionDirection = reflect(-light0.direction, normal0);
	float specularPower = 32.0;
	float specular = pow(max(dot(viewDirection, reflectionDirection), 0.0), specularPower);
	vec4 specularComponent = specular * vec4(0.5) * light0.intensity; // fixed specular colour of (1.0)
	
	gl_FragColor = texComponent * (diffuseComponent + specularComponent);
	
	//gl_FragColor = texture(diffuse, texCoord0 * scale) * vec4(light0.colour,1.0)
	//	* clamp(dot(-light0.direction, normal0) * light0.intensity, 0.0, 1.0);			
}