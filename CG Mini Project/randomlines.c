#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
int width=650, height=700,X,Y,i=0,j=0,A,B;
void Init(){
	gluOrtho2D(0,650,0,700);
}
void menu(int op){
   if(op==1)
      exit(0);
}

void time();
void menuFunction(){
    glutCreateMenu(menu);
    glutAddMenuEntry("Home",1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
void mouse(int button, int state, int x, int y){
    int mouseX = x;
    int mouseY = 700- y;

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		glClear(GL_COLOR_BUFFER_BIT);
		glPointSize(3);
		glColor3f(1,1,1);
		glBegin(GL_POINTS);
		glVertex2i(mouseX,mouseY);
		glEnd();
		X=mouseX;
		Y=mouseY;
		A=mouseX;
		B=mouseY;
		glutTimerFunc(0,time,0);
	}
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1,1,1);
}
void time(){
	if(A>B){
		if(X==650 && Y<700){
			i=1;
		}else if(X<650 && Y==700){
			i=2;
		}else if(X==0 && Y<700){
			i=3;
		}else if(X<650 && Y==0){
			i=0;
		}
		if(i==0){
			X++;
			Y++;
		}
		else if(i==1){
			X--;
			Y++;
		}
		else if(i==2){
			X--;
			Y--;
		}
		else if(i==3){
			X++;
			Y--;
		}
		glBegin(GL_POINTS);
		glVertex2i(X,Y);
		glEnd();
	}else if(A<B){
		if(X==650 && Y<700){
			j=1;
		}else if(X<650 && Y==700){
			j=2;
		}else if(X==0 && Y<700){
			j=0;
		}else if(X<650 && Y==0){
			j=3;
		}
		if(j==0){
			X++;
			Y++;
		}else if(j==1){
			X--;
			Y--;
		}else if(j==2){
			X++;
			Y--;
		}else if(j==3){
			X--;
			Y++;
		}
		glBegin(GL_POINTS);
		glVertex2i(X,Y);
		glEnd();
	}else{
		if(X==650 && Y==700){
			X++;
			Y++;
		}
		else if(X==0 && Y==0){
			X++;
			Y++;
		}
		glBegin(GL_POINTS);
		glVertex2i(X,Y);
		glEnd();
	}
	
	glutTimerFunc(1000/360,time,0);
	glutSwapBuffers();
}
int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(650,700);
	glutInitWindowPosition(300,10);
	glutCreateWindow("CG Mini Project : Line Art");
	Init();
	glutDisplayFunc(display);
    glutMouseFunc(mouse);
	menuFunction();
	glutMainLoop();
}

