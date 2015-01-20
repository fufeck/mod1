// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   SceneOpenGl.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ftaffore <ftaffore@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/01/20 13:06:30 by ftaffore          #+#    #+#             //
//   Updated: 2015/01/20 13:06:31 by ftaffore         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef SCENE_OPENGL_HPP
# define SCENE_OPENGL_HPP

#include <string>
#include <iostream>
#include <exception>
#include <SDL.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

class SceneOpenGl
{
private:
	std::string const &		_title;
	int 					_height;
	int 					_width;

	SDL_Window* 			_win;
	SDL_GLContext 			_contexteOpenGL;	
	SDL_Event 				_even;

	void 			draw(void);
public:
	SceneOpenGl(std::string const & title, int height, int width);
	~SceneOpenGl();

	void 			mainWhile();
};

#endif