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
in vec3 triplanarNormal0;
in vec3 viewPos0;

uniform sampler2D diffuse;

// Based on http://gamedevelopment.tutsplus.com/articles/use-tri-planar-texture-mapping-for-better-terrain--gamedev-13821
vec4 getTriPlanarBlend(sampler2D diffuse, vec3 coord, vec3 normal)
{
	// normal is the world-space normal of the fragment
	vec3 blending = abs( normal );
	blending = max(blending, 0.000001);
	blending = normalize(blending); // Force weights to sum to 1.0
	float b = (blending.x + blending.y + blending.z);
	blending /= vec3(b, b, b);
	
	float scale = 1.0;
	
	vec4 xaxis = texture( diffuse, coord.yz * scale);
	vec4 yaxis = texture( diffuse, coord.xz * scale);
	vec4 zaxis = texture( diffuse, coord.xy * scale);
	// blend the results of the 3 planar projections.
	vec4 tex = xaxis * blending.x + yaxis * blending.y + zaxis * blending.z;
	return tex;
}

void main()
{
	vec4 texComponent = getTriPlanarBlend(diffuse, position0, triplanarNormal0);
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
		
	//gl_FragColor = getTriPlanarBlend(diffuse, position0, triplanarNormal0) * vec4(light0.colour,1.0)
	//	* clamp(dot(-light0.direction, normal0) * light0.intensity, 0.0, 1.0);			
}