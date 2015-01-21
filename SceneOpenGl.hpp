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

#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <exception>
#include <sstream>
#include <SDL.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>


struct vec3f {
	int		x;
	int		y;
	int		z;
};

enum Mode {
	WATER,
	WAVE
};

#define			X_MAX		500
#define			Y_MAX		500
#define			MUL			100
#define			PAS			0.01

class SceneOpenGl
{

#define 		DELIM		','

private:
	std::vector<vec3f *>	_points;
	int 					_height;
	int 					_width;
	double 					_lvlWater;
	int						_maxZ;
	double					**_map;
	int						_mode;

	
	void					_createMap(void);
	void 					_parsePoints(std::ifstream &myFile);
public:
	SceneOpenGl(std::string const & str, char *mode);
	~SceneOpenGl();

	double					**getMap(void) const;
	double					getWater(void);
	int						getHeight(void) const;
	int						getWidth(void) const;
	int						getMaxZ(void) const;
	int						getMode(void) const;

};

#endif