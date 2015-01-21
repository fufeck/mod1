// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ftaffore <ftaffore@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/01/20 11:31:34 by ftaffore          #+#    #+#             //
//   Updated: 2015/01/20 11:31:34 by ftaffore         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <exception>
#include <unistd.h>
#include "SceneOpenGl.hpp"

SceneOpenGl				*SceneSingleton(SceneOpenGl *scene) {
	static SceneOpenGl 	*ptr;

	if (scene != NULL) {
		ptr = scene;
	}
	return ptr;
}

void 					reshape(int width, int height) {

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, double(width) / double(height) - 0.1, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);
}

void					getColor(double y, double lvlWater) {
	if (y >= lvlWater) {
		if (y < 0.5)
			glColor3d(y * 2, 0.6 - y * 2, 0);
		else
			glColor3d(1, (y - 0.5) * 2, (y - 0.5) * 2);
	} else {
		glColor3d(1 - ((lvlWater - y) * 1000), 1 - ((lvlWater - y) * 1000), 1);
	}
}

void					drawMap(double **map, double lvlWater, double xMax, double zMax) {

	for (double x = 0; x < xMax; x += PAS) {

		glBegin(GL_TRIANGLE_STRIP);
		for (double z = 0; z < zMax; z += PAS) {

			double		y = map[static_cast<int>(x * MUL)][static_cast<int>(z * MUL)];
			getColor(y, lvlWater);
			glVertex3f(x, y , z);

			y = map[static_cast<int>((x + PAS) * MUL)][static_cast<int>(z * MUL)];
			getColor(y, lvlWater);
			glVertex3f(x + PAS, y ,z);

		}
		glEnd();
	}
}

void 					draw(void) {
	static bool			ap = false;
	double 				xMax = static_cast<double>(X_MAX - 1) / MUL;
	double 				zMax = static_cast<double>(Y_MAX - 1) / MUL;
	double 				**map = SceneSingleton(NULL)->getMap();
	double 				lvlWater = SceneSingleton(NULL)->getWater();

	glClear(GL_COLOR_BUFFER_BIT);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (ap == false) {
		ap = true;
		glMatrixMode(GL_MODELVIEW);
		gluLookAt(6, 4, 6, 0, -5, 0, 0, 1, 0);
	}
	drawMap(map, lvlWater, xMax, zMax);
	glutSwapBuffers();
	glutPostRedisplay();
}

void 					initGL(void) {

}

int			main(int ac, char **av) {

	if (ac == 3) {
		try {
			SceneOpenGl		scene(av[1], av[2]);
			SceneSingleton(&scene);
			glutInit(&ac, av);
			glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
			glutInitWindowSize(scene.getWidth(), scene.getHeight());
			glutCreateWindow("Mod1");

			glutReshapeFunc(reshape);
			glutDisplayFunc(draw);
			initGL();
			glutMainLoop();

		} catch (std::exception & e) {
			return 0;
		}
	} else {
		std::cout << "ERROR : Usage => ./mod1 filename + mode" << std::endl;
		return 0;
	}
	return 1;
}