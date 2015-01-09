
#include "SampleGame.h"

//// Include standard headers
////#include <stdio.h>
////#include <stdlib.h>
//#include <chrono>
//#include <iostream>
//
//// Include GLEW. Always include it before gl.h and glfw.h, since it's a bit magic.
//#include <GL/glew.h>
//
//// Include SFML.
//#include <SFML/System.hpp>
//#include <SFML/Window.hpp>
//#include <SFML/OpenGL.hpp>
//
//// Include GLM.
//#include <glm/glm.hpp>
//using namespace glm;
//
//#include "SFMLGame.h"
//#include "RenderUtil.h"
//#include "Vertex.h"
//#include "Mesh.h"
//#include "custom_typedef.h"
//
//
//class SampleGame : public sfml_game::SFMLGame
//{
//public:
//	SampleGame() {}
//	~SampleGame() { delete m_mesh; }
//
//protected:
//	void init() override 
//	{
//		// Initialize GLEW
//		glewExperimental=true; // Needed in core profile
//		if (glewInit() != GLEW_OK) 
//			std::cerr << "Failed to initialize GLEW\n" << std::endl;			
//
//		sfml_game::utils::initGraphics();
//		sfml_game::rendering_sys::Vertex v[] =
//		{
//			vec3(-0.5, -0.5, 0),
//			vec3(0, 0.5, 0),
//			vec3(0.5, -0.5, 0)
//		};
//
//		m_mesh = new sfml_game::rendering_sys::Mesh(v, sizeof(v)/sizeof(v[0]));
//		
//	}
//	void dispose() override {}
//	void render() override 
//	{
//		sfml_game::utils::clearScreen();
//
//		m_mesh->Draw();
//
//	}
//	void update(sf::Time deltaTime) override 
//	{
//		if(m_input.getMouse(sf::Mouse::Left))
//			std::cout << "Left Mouse" << std::endl;
//
//		if(m_input.getKeyDown(sf::Keyboard::K))
//			std::cout << "Key K Down!!" << std::endl;
//		if(m_input.getKeyUp(sf::Keyboard::K))
//			std::cout << "Key K Up!!" << std::endl;
//	}
//
//private:
//	sfml_game::rendering_sys::Mesh * m_mesh;
//};

int main()
{
	SampleGame game;
	game.start();

	return 0;
}



//int main()
//{
//	using namespace std::chrono;
//
//	// create the window
//	sf::Window window(sf::VideoMode(1024, 768), "OpenGL Game", sf::Style::Default, sf::ContextSettings(32));
//	window.setFramerateLimit(500);
//	window.setVerticalSyncEnabled(false);
//
//	// load resources, initialize the OpenGL states, ...
//
//	high_resolution_clock::time_point t1 = high_resolution_clock::now();
//	high_resolution_clock::time_point frame_disp_rate = high_resolution_clock::now();
//
//	// run the main loop
//	bool running = true;
//	while (running)
//	{
//		high_resolution_clock::time_point t2 = high_resolution_clock::now();		
//		if(duration_cast<duration<double>>(t1 - frame_disp_rate).count() > 1)
//		{
//			// frame rate calculation
//			duration<long double> time_span = duration_cast<duration<long double>>(t2 - t1);
//			long double frame_time = time_span.count();
//			std::cout << frame_time << " fps:" << (long double)(1/frame_time) << std::endl;
//			frame_disp_rate = t2;
//		}
//		t1 = t2;
//
//		// handle events
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//			{
//				// end the program
//				running = false;
//			}
//			else if (event.type == sf::Event::Resized)
//			{
//				// adjust the viewport when the window is resized
//				glViewport(0, 0, event.size.width, event.size.height);
//			}
//		}
//
//		// clear the buffers
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		// draw...
//
//		// end the current frame (internally swaps the front and back buffers)
//		window.display();
//	}
//
//	// release resources...
//
//	return 0;
//}

//#include <SFML/Graphics.hpp>
//
//int main()
//{
//    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
//    sf::CircleShape shape(100.f);
//    shape.setFillColor(sf::Color::Green);
//
//    while (window.isOpen())
//    {
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//
//        window.clear();
//        window.draw(shape);
//        window.display();
//    }
//
//    return 0;
//}