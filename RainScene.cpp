// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   RainScene.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ftaffore <ftaffore@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/01/22 12:07:15 by ftaffore          #+#    #+#             //
//   Updated: 2015/01/22 12:07:15 by ftaffore         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <unistd.h>
#include "RainScene.hpp"

RainScene::RainScene(std::string const & str) : AScene(str), _lvlWater(0.0) {

}

RainScene::~RainScene(void) {

}

void			RainScene::_getColor(int x, int z) {
	double		y = this->_mapPoints[x][z].y;

	if (y >= this->_lvlWater) {
		if (y < 0.5) {
			this->_mapPoints[x][z].r = y * 2;
			this->_mapPoints[x][z].g = 0.6 - y * 2;
			this->_mapPoints[x][z].b = 0;
		}
		else {
			this->_mapPoints[x][z].r = 1;
			this->_mapPoints[x][z].g = (y - 0.5) * 2;
			this->_mapPoints[x][z].b = (y - 0.5) * 2;
		}
	} else {
		this->_mapPoints[x][z].r = 1 - ((this->_lvlWater - y) * 1000);
		this->_mapPoints[x][z].g = 1 - ((this->_lvlWater - y) * 1000);
		this->_mapPoints[x][z].b = 1;
	}
}

void			RainScene::actualiseMap(void) {
	usleep(500);

	if (this->_lvlWater < 0.5) {
		this->_lvlWater += 0.00002;
	}
	for (unsigned int x = 0; x < X_MAX; x++) {
		for (unsigned int z = 0; z < Z_MAX; z++) {
			this->_getColor(x, z);
		}
	}
}