// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   SceneOpenGl.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ftaffore <ftaffore@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/01/20 13:10:38 by ftaffore          #+#    #+#             //
//   Updated: 2015/01/20 13:10:38 by ftaffore         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "SceneOpenGl.hpp"

SceneOpenGl::SceneOpenGl(std::string const & title, int height, int width) : _title(title), _height(height), _width(width) {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
		SDL_Quit();
		throw std::exception();
	}
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	if ((this->_win = SDL_CreateWindow("Test SDL 2.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->_height, this->_width, SDL_WINDOW_OPENGL)) == 0) {
		std::cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << std::endl;
		SDL_Quit();
		throw std::exception();
	}
	
	if ((this->_contexteOpenGL = SDL_GL_CreateContext(this->_win)) == 0) {
		std::cout << SDL_GetError() << std::endl;
		SDL_DestroyWindow(this->_win);
		SDL_Quit();
		throw std::exception();
	}
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, static_cast<double>(this->_width / this->_height), 1, 1000);
	//glEnable(GL_DEPTH_TEST);
}

SceneOpenGl::~SceneOpenGl(void) {
	SDL_GL_DeleteContext(this->_contexteOpenGL);
	SDL_DestroyWindow(this->_win);
	SDL_Quit();
}

void 			SceneOpenGl::draw(void) {
	glClear(GL_COLOR_BUFFER_BIT);

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glMatrixMode(GL_MODELVIEW);
gluLookAt(5,5,5,0,0,0,0,1,0);
glBegin(GL_QUADS);
glVertex3i(1,1,1);
glVertex3i(1,-1,1);
glVertex3i(-1,-1,1);
glVertex3i(-1,1,1);

//1 face
glVertex3i(1,1,-1);
glVertex3i(1,-1,-1);
glVertex3i(-1,-1,-1);
glVertex3i(-1,1,-1);

//2 faces
glVertex3i(1,1,1);
glVertex3i(1,-1,1);
glVertex3i(1,-1,-1);
glVertex3i(1,1,-1);

//3 faces
glVertex3i(-1,1,1);
glVertex3i(-1,-1,1);
glVertex3i(-1,-1,-1);
glVertex3i(-1,1,-1);

//4 faces
glVertex3i(-1,1,-1);
glVertex3i(-1,1,1);
glVertex3i(1,1,1);
glVertex3i(1,1,-1);

//5 faces
glVertex3i(-1,-1,-1);
glVertex3i(-1,-1,1);
glVertex3i(1,-1,1);
glVertex3i(1,-1,-1);

//6 faces
glEnd();	
//SwapBuffers(DC)

glutSwapBuffers();
glutPostRedisplay();
}


void 			SceneOpenGl::mainWhile(void) {
	bool 		terminer(false);

	while(!terminer)
	{
		SDL_WaitEvent(&(this->_even));
		
		if (this->_even.window.event == SDL_WINDOWEVENT_CLOSE) {
			terminer = 1;
		}
		
		draw();
	}
}