#pragma once

// Include standard headers
#include <chrono>
#include <iostream>

// Include GLEW. Always include it before gl.h and glfw.h, since it's a bit magic.
#include <GL/glew.h>

// Include SFML.
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

// Include GLM.
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
//using namespace glm;

#include "SFMLGame.h"
#include "RenderUtil.h"
#include "Vertex.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"
#include "Quaternion.h"
#include "custom_typedef.h"

class SampleGame : public sfml_game::SFMLGame
{
	typedef sfml_game::rendering_sys::Mesh MeshObject;
	typedef sfml_game::rendering_sys::Shader ShaderObject;
	typedef sfml_game::rendering_sys::Texture TextureObject;
	typedef sfml_game::rendering_sys::Camera CameraObject;

public:
	SampleGame() : SFMLGame("OpenGL Practice", 1800, 920, sf::Style::Default, sf::ContextSettings(32,0,0,3,0)) {}
	virtual ~SampleGame() {}

protected:	// Protected member functions
	void init() override 
	{
		using namespace glm;

		// Initialize GLEW
		glewExperimental = GL_TRUE; // Needed in core profile
		if (glewInit() != GLEW_OK) 
			std::cerr << "Failed to initialize GLEW\n" << std::endl;			

		sfml_game::utils::initGraphics();
		sfml_game::rendering_sys::Vertex v[] =
		{
			{vec3(-0.5, -0.5, 0), vec2(0.0, 0.0), vec3(0.0, 0.0, -1.0)},
			{vec3(0, 0.5, 0), vec2(0.5, 1.0), vec3(0.0, 0.0, -1.0)},
			{vec3(0.5, -0.5, 0), vec2(1.0, 0.0), vec3(0.0, 0.0, -1.0)}
		};

		uint32 indices[] = 	{ 0, 1, 2 };

		m_mesh = new MeshObject(v, sizeof(v)/sizeof(v[0]), indices, sizeof(indices)/sizeof(indices[0]));
		m_monkeyModel = new MeshObject("./res/models/monkey3.obj");
		m_shader = new ShaderObject("./res/shaders/basicShader");
		m_texture = new TextureObject("./res/textures/bricks.jpg");

		float _aspectRatio = (float)m_window.getSize().x / (float)m_window.getSize().y;
		m_camera = new CameraObject(glm::vec3(0.0f, 0.0f, -4.0f), 70.0f, _aspectRatio, 0.01f, 100.0f);

		m_counter = 0.0f;
		m_lightFadeCounter = 0.0f;
		m_lightRotCounter = 0.0f;
		m_objectRotCounter = 0.0f;
		m_lightColourCounter = 0.0f;

		m_lightFadeToggle = false;
		m_lightRotToggle = false;
		m_objectRotToggle = false;
		m_lightColourToggle = false;
	}
	void dispose() override 
	{
		delete m_mesh; 
		delete m_monkeyModel;
		delete m_shader; 
		delete m_texture; 
		delete m_camera;
	}
	void render() override 
	{
		sfml_game::Transform _trans;

		glm::vec3 colour(1.0f, 1.0f, 1.0f);
		glm::vec3 dir(0.0f, 0.0f, 1.0f);
		float intensity = 1.0f;

		sfml_game::rendering_sys::Light _light(dir, colour, intensity);


		// Object Rotation
		_trans.GetRotation().y = glm::radians(180.0f); // Rotate to face mesh to camera
		_trans.GetRotation().x += glm::radians(m_objectRotCounter);

		// Light Fade In/Out
		float sinCounter = sinf(m_lightFadeCounter);
		_light.setIntensity(sinCounter * sinCounter);
		//_light.setIntensity(1.0f);

		// Light Direction Rotation
		glm::mat4x4 lightRotMat = glm::rotate(glm::radians(m_lightRotCounter), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::vec4 lightRotate = lightRotMat * glm::vec4(_light.getDirection(), 1.0f);
		_light.setDirection(glm::vec3(lightRotate.x, lightRotate.y, lightRotate.z));

		// Light Colour Change (by rotating colour vec4)
		glm::mat4x4 lightColMat = glm::rotate(glm::radians(m_lightColourCounter), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::vec4 colourRotate = lightColMat * glm::vec4(_light.getColour(), 1.0f);
		_light.setColour(glm::vec3(colourRotate.x, colourRotate.y, colourRotate.z));

		sfml_game::utils::clearScreen();

		m_shader->Bind();
		m_texture->Bind();
		m_shader->Update(_trans, (*m_camera), _light);
		m_monkeyModel->Draw();
		//m_mesh->Draw();
	}
	void update(sf::Time deltaTime) override 
	{
		float seconds = float(deltaTime.asMilliseconds())/1000.0f;

		if(m_input.getKeyDown(sf::Keyboard::F))		// Toggles light fading
		{
			m_lightFadeToggle = !m_lightFadeToggle;
			std::cout << "Light Fade Toggle: " << (m_lightFadeToggle ? "True" : "False") << std::endl;
		}
		if(m_input.getKeyDown(sf::Keyboard::L))		// Toggles light rotation
		{
			m_lightRotToggle = !m_lightRotToggle;
			std::cout << "Light Rotation Toggle: " << (m_lightRotToggle ? "True" : "False") << std::endl;
		}
		if(m_input.getKeyDown(sf::Keyboard::O))		// Toggles object rotation
		{
			m_objectRotToggle = !m_objectRotToggle;
			std::cout << "Object Rotation Toggle: " << (m_objectRotToggle ? "True" : "False") << std::endl;
		}
		if(m_input.getKeyDown(sf::Keyboard::C))		// Toggles light colours
		{
			m_lightColourToggle = !m_lightColourToggle;
			std::cout << "Light Colour Toggle: " << (m_lightColourToggle ? "True" : "False") << std::endl;
		}

		if(m_lightFadeToggle) m_lightFadeCounter += seconds;
		if(m_lightRotToggle) m_lightRotCounter += seconds * 20;
		if(m_lightColourToggle) m_lightColourCounter += seconds * 20;
		if(m_objectRotToggle) m_objectRotCounter += seconds * 10;

		m_counter += 0.01f;
	}

private:	// Private member variables
	MeshObject * m_mesh;
	MeshObject * m_monkeyModel;
	ShaderObject * m_shader;
	TextureObject * m_texture;
	CameraObject * m_camera;

	float m_counter;
	float m_lightFadeCounter;
	float m_lightRotCounter;
	float m_lightColourCounter;
	float m_objectRotCounter;

	bool m_lightFadeToggle;
	bool m_lightRotToggle;
	bool m_lightColourToggle;
	bool m_objectRotToggle;
};

