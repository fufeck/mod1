// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   WaveScene.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ftaffore <ftaffore@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/01/22 11:34:22 by ftaffore          #+#    #+#             //
//   Updated: 2015/01/22 11:34:23 by ftaffore         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <unistd.h>
#include "WaveScene.hpp"

WaveScene::WaveScene(std::string const & str) : AScene(str) {
	for (unsigned int x = 0; x < X_MAX; x++) {
		for (unsigned int z = 0; z < Z_MAX; z++) {
			this->_water[x][z] = 0;
		}
	}
}

WaveScene::~WaveScene(void) {

}

void			WaveScene::_getColor(int x, int z) {
	double		y = this->_mapPoints[x][z].y;
	double		w = this->_water[x][z];

	if (y >= w / 2) {
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
		this->_mapPoints[x][z].r = 1 - w;
		this->_mapPoints[x][z].g = 1 - w;
		this->_mapPoints[x][z].b = 1;
	}
}

void			WaveScene::_waterCase(int x, int z, int x1, int z1) {
	double		water = this->_water[x][z];

	if (x1 >= 0 && x1 < X_MAX && z1 >= 0 && z1 < Z_MAX) {
		double		water1 = this->_water[x1][z1];
	 	if (water1 < water) {

			water1 = water1 + (water / 4.0) - this->_mapPoints[x1][z1].y / 4;
			this->_water[x1][z1] = (water1 > 1) ? (1) : (water1);
		}
	}
}

void			WaveScene::_waterDistribution(int x, int z) {

	if (this->_water[x][z] >= 0.001) {
		this->_waterCase(x, z, x - 1, z);
		this->_waterCase(x, z, x , z - 1);
		this->_waterCase(x, z, x + 1, z);
		this->_waterCase(x, z, x, z + 1);
	}
}

void			WaveScene::actualiseMap(void) {
	usleep(50);

	for (unsigned int x = 0; x < X_MAX; x++) {
		for (unsigned int z = 0; z < Z_MAX; z++) {
			if (z == 0) {
				this->_water[x][z] = 1.0;
			}
			this->_waterDistribution(x, z);
			this->_getColor(x, z);
		}
	}
}