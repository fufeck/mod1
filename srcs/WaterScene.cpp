// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   WaterScene.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ftaffore <ftaffore@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/01/22 11:34:13 by ftaffore          #+#    #+#             //
//   Updated: 2015/01/22 11:34:14 by ftaffore         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <unistd.h>
#include "WaterScene.hpp"

WaterScene::WaterScene(std::string const & str) : AScene(str), _lvlWater(0.0) {

}

WaterScene::~WaterScene(void) {

}

void			WaterScene::_getColor(int x, int z) {
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
		this->_mapPoints[x][z].r = 1 - ((this->_lvlWater - y) * 1000) - 0.3;
		this->_mapPoints[x][z].g = 1 - ((this->_lvlWater - y) * 1000) - 0.3;
		this->_mapPoints[x][z].b = 1;
	}
}

void			WaterScene::actualiseMap(void) {
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