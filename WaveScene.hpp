// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   WaveScene.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ftaffore <ftaffore@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/01/22 11:34:27 by ftaffore          #+#    #+#             //
//   Updated: 2015/01/22 11:34:28 by ftaffore         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef WAVE_SCENE_HPP
# define WAVE_SCENE_HPP

#include "AScene.hpp"

class WaveScene : public AScene
{
private:
	double 					_water[X_MAX][Z_MAX];

	void					_getColor(int x, int z);
	void					_waterCase(int x, int z, int x1, int z1);
	void					_waterDistribution(int x, int z);
public:
	WaveScene(std::string const & str);
	virtual ~WaveScene();
	
	virtual void			actualiseMap(void);
};

#endif