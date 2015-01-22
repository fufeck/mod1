// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AScene.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ftaffore <ftaffore@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/01/20 13:10:38 by ftaffore          #+#    #+#             //
//   Updated: 2015/01/20 13:10:38 by ftaffore         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <unistd.h>
#include "AScene.hpp"

/************CONSTRUCTEUR***************/

AScene::AScene(std::string const & str) {

	std::ifstream   myFile(str.c_str());

	if (myFile.is_open()) {
		this->_mapPoints = new point4f*[X_MAX];

		for (int i = 0; i < Z_MAX; i++) {

			this->_mapPoints[i] = new point4f[Z_MAX];
			bzero(this->_mapPoints[i], sizeof(point4f) * Z_MAX);
		}
		this->_parsePoints(myFile);
		this->_createMap();
	} else {
		std::cout << "ERROR : file can't be open." << std::endl;
		throw std::exception();
	}

}

AScene::~AScene(void) {

}

void            		AScene::_parsePoints(std::ifstream & myFile) {
	std::string 		line;
	std::string 		d2(")");
	std::string 		d1("(");

	while (getline(myFile, line)) {
		unsigned int    pos = 0;

		while (pos < line.size()) {
			std::stringstream   ss;
			vec3i               *vec = new vec3i;
			std::string         token = line.substr(line.find(d1) + 1, line.find(d2) - 1);
			std::replace(token.begin(), token.end(), ',', ' ');
			ss.str(token);

			ss >> vec->x;
			ss >> vec->y;
			ss >> vec->z;
			if (this->_maxZ < vec->z) {
				this->_maxZ = vec->z;
			}
			if (vec->x <= 0 || vec->y <= 0 || vec->z <= 0 || vec->x >= X_MAX || vec->y >= Z_MAX) {
				std::cout << "ERROR : points to file are incorrect." << std::endl;
				throw std::exception();
			}
			this->_points.push_back(vec);
			line = line.substr(line.find(d2) + 1);
		}
	}
	myFile.close();
}

void					AScene::_createMap(void) {

	for (unsigned int i = 0; i < this->_points.size(); i++) {
		double			xx = (this->_points[i]->x < X_MAX / 2) ? (this->_points[i]->x) : (X_MAX - this->_points[i]->x);
		double			yy = (this->_points[i]->y < Z_MAX / 2) ? (this->_points[i]->y) : (Z_MAX - this->_points[i]->y);
		double         	domR = (xx > yy) ? (yy) : (xx);
		double			domF = 3.0 / domR;
		double 			xF = -3.0;

		for (int xR = this->_points[i]->x - domR; xR < this->_points[i]->x + domR; xR++) {
			double 		yF = -3.0;
			for (int yR = this->_points[i]->y - domR; yR < this->_points[i]->y + domR; yR++) {
				double height = exp(0 - (xF * xF) - (yF * yF));
				height = height * (this->_points[i]->z / static_cast<double>(this->_maxZ));
				if (height > this->_mapPoints[xR][yR].y) {
					this->_mapPoints[xR][yR].y = height;
				}
				yF += domF;
			}
			xF += domF;
		}
	}
}
point4f					**AScene::getMapPoints(void) const {
	return this->_mapPoints;
}


