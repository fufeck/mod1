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

#include <unistd.h>
#include "SceneOpenGl.hpp"

/************CONSTRUCTEUR***************/

SceneOpenGl::SceneOpenGl(std::string const & str, char *mode) : _height(480), _width(640), _lvlWater(0.0) {

	std::string 	m(mode);
	if (m == "WATER") {
		this->_mode = WATER;
	} else if (m == "WAVE") {
		this->_mode = WAVE;
	} else {
		std::cout << "ERROR : mode is not correct" << std::endl;
		throw std::exception();
	}
	std::ifstream   myFile(str.c_str());

	if (myFile.is_open()) {
		this->_map = new double*[X_MAX];
		for (int i = 0; i < Y_MAX; i++) {
			this->_map[i] = new double[Y_MAX];
			bzero(this->_map[i], sizeof(double) * Y_MAX);
		}
		this->_parsePoints(myFile);
		this->_createMap();
	} else {
		std::cout << "ERROR : file can't be open." << std::endl;
		throw std::exception();
	}

}

SceneOpenGl::~SceneOpenGl(void) {

}

void            		SceneOpenGl::_parsePoints(std::ifstream & myFile) {
	std::string 		line;
	std::string 		d2(")");
	std::string 		d1("(");

	while (getline(myFile, line)) {
		unsigned int    pos = 0;

		while (pos < line.size()) {
			std::stringstream   ss;
			vec3f               *vec = new vec3f;
			std::string         token = line.substr(line.find(d1) + 1, line.find(d2) - 1);
			std::replace(token.begin(), token.end(), ',', ' ');
			ss.str(token);

			ss >> vec->x;
			ss >> vec->y;
			ss >> vec->z;
			if (this->_maxZ < vec->z) {
				this->_maxZ = vec->z;
			}
			if (vec->x <= 0 || vec->y <= 0 || vec->z <= 0 || vec->x >= X_MAX || vec->y >= Y_MAX) {
				std::cout << "ERROR : points to file are incorrect." << std::endl;
				throw std::exception();
			}
			this->_points.push_back(vec);
			line = line.substr(line.find(d2) + 1);
		}
	}
	myFile.close();
}

void					SceneOpenGl::_createMap(void) {

	for (unsigned int i = 0; i < this->_points.size(); i++) {
		double			xx = (this->_points[i]->x < X_MAX / 2) ? (this->_points[i]->x) : (X_MAX - this->_points[i]->x);
		double			yy = (this->_points[i]->y < Y_MAX / 2) ? (this->_points[i]->y) : (Y_MAX - this->_points[i]->y);
		double         	domR = (xx > yy) ? (yy) : (xx);
		double			domF = 3.0 / domR;
		double 			xF = -3.0;

		for (int xR = this->_points[i]->x - domR; xR < this->_points[i]->x + domR; xR++) {
			double 		yF = -3.0;
			for (int yR = this->_points[i]->y - domR; yR < this->_points[i]->y + domR; yR++) {
				double height = exp(0 - (xF * xF) - (yF * yF));
				height = height * (this->_points[i]->z / static_cast<double>(this->_maxZ));
				if (height > this->_map[xR][yR]) {
					this->_map[xR][yR] = height;
				}
				yF += domF;
			}
			xF += domF;
		}
	}
}
double					**SceneOpenGl::getMap(void) const {
	return this->_map;
}

double					SceneOpenGl::getWater(void) {
	usleep(500);

	if (this->_lvlWater < 0.5) {
		this->_lvlWater += 0.00002;
	}
	return this->_lvlWater;
}

int                     SceneOpenGl::getHeight(void) const {
	return this->_height;
}

int                     SceneOpenGl::getWidth(void) const {
	return this->_width;
}

int                     SceneOpenGl::getMaxZ(void) const {
	return this->_maxZ;
}

int                     SceneOpenGl::getMode(void) const {
	return this->_mode;
}
