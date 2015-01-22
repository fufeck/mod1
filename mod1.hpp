// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   mod1.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ftaffore <ftaffore@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/01/22 12:04:52 by ftaffore          #+#    #+#             //
//   Updated: 2015/01/22 12:04:52 by ftaffore         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef MOD_1_HPP
# define MOD_1_HPP

struct vec3i {
	int		x;
	int		y;
	int		z;
};

struct point4f {
	float	r;
	float	g;
	float	b;
	float	y;
};

#define			WIN_HEIGHT	480
#define			WIN_WIDTH	640

#define			X_MAX		500
#define			Z_MAX		500
#define			MUL			100
#define			PAS			0.01

#endif