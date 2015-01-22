// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AScene.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ftaffore <ftaffore@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/01/20 13:06:30 by ftaffore          #+#    #+#             //
//   Updated: 2015/01/20 13:06:31 by ftaffore         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef A_SCENE_HPP
# define A_SCENE_HPP

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
#include "mod1.hpp"

class AScene
{

#define 		DELIM		','

protected:
	std::vector<vec3i *>	_points;
	point4f 				**_mapPoints;
	int						_maxZ;
	
	void					_createMap(void);
	void 					_parsePoints(std::ifstream &myFile);
public:
	AScene(std::string const & str);
	virtual ~AScene();

	point4f					**getMapPoints(void) const;
	virtual void			actualiseMap(void) = 0;
};

#endif