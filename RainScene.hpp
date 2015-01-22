// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   RainScene.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ftaffore <ftaffore@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/01/22 12:07:06 by ftaffore          #+#    #+#             //
//   Updated: 2015/01/22 12:07:07 by ftaffore         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef RAIN_SCENE_HPP
# define RAIN_SCENE_HPP

#include "AScene.hpp"

class RainScene : public AScene
{
private:
	double 					_lvlWater;

	void					_getColor(int x, int z);
public:
	RainScene(std::string const & str);
	virtual ~RainScene();
	
	virtual void			actualiseMap(void);
};

#endif