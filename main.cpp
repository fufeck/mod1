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


#include <string>
#include <iostream>
#include <exception>
#include <SDL.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include "unistd.h"
void InitGL() {

}

void Reshape(int width, int height) {

	glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, float(width) / float(height), 0.1, 100);
	glMatrixMode(GL_MODELVIEW);
}	 

int 			map[20000][20000];
std::vector<vec3>	points;
float			heightMax;

void		createMap(void) {
	for (int x = 0; x < 20000; x++) {
		for (int y = 0; y < 20000; y++) {
			map[x][y] = 0;
			for (int i = 0; i < points.size; i++) {
				float dist = square(((x - points[i].x) * (y - points[i].y)) + ((y - points[i].y) * (y - points[i].y)));
				float height = points[i].z / dist;
				if (height > map[x][y]) {
					map[x][y] = height;
				}
			}
		}
	}
}

void Draw()
{	
	glClear(GL_COLOR_BUFFER_BIT);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(25,20,25, 0, -20, 0, 0, 1, 0);

	glBegin(GL_LINES);
	glVertex2i(0,0);glVertex2i(0,50);
	glVertex2i(0,0);glVertex2i(50,0);
	glVertex2i(0,0);glVertex3i(0,0,50);
	glEnd();

	for (float x = 0; x < 20.0; x += 0.01) {
		glBegin(GL_TRIANGLE_STRIP);
		for (float z = 0; z < 20.0; z += 0.01) {

			glColor3d(map[x][z] / heightMax, 1, 0);
			glVertex3f(x, 0.0, z);
			glVertex3f(x + 0.01, 0.0 ,z);

		}
		glEnd();
	}
/*	glColor3d(1,1,0);
	glVertex3i(0,0,0);

	glColor3d(1,0,0);
	glVertex3i(0,0,1);

	glColor3d(1,0,1);
	glVertex3i(1,0,0);

	glColor3d(0,1,1);
	glVertex3i(1,0,1);
*/
	glutSwapBuffers();

}

int main( int argc, char **argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(640,480);
	glutCreateWindow("Ma première fenêtre OpenGL !");

	glutReshapeFunc(Reshape);
	glutDisplayFunc(Draw);
	InitGL();
	glutMainLoop();
	return 0;
}
