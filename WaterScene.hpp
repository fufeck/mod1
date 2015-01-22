// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   WaterScene.hpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ftaffore <ftaffore@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/01/22 11:34:10 by ftaffore          #+#    #+#             //
//   Updated: 2015/01/22 11:34:11 by ftaffore         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef WATER_SCENE_HPP
# define WATER_SCENE_HPP

#include "AScene.hpp"

class WaterScene : public AScene
{
private:
	double 					_lvlWater;

	void					_getColor(int x, int z);
public:
	WaterScene(std::string const & str);
	virtual ~WaterScene();
	
	virtual void			actualiseMap(void);
};

#endif