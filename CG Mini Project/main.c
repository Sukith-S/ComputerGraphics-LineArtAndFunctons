#include <stdio.h>
#include <GL/glut.h>
#define pi 3.142
static GLfloat angle = 0;
int x=100,y=0,x11=450,y11=300,x22=600,y22=300;
int r=0,op,a,a1,a2,b,i,j,width=650,height=700,first=0;
int mouseX = 0, mouseY = 0; 
static int submenu;
static int mainmenu;
#define MAX_PTS 1000
int ptListX[MAX_PTS]; // X coordinate ot the input points 
int ptListY[MAX_PTS]; // Y coordinate of the input points
int noOfPts = 0;      // number of input points
int closed = 0;       // marke polygon "closed"

void init(){
    gluOrtho2D(-1000, 1000, -1000, 1000);
}
void drawhead(float x, float y, float z, char *string)
{
    glColor3f(1, 1, 1);
    glRasterPos3f(x, y, z);

    for (char *c = string; *c != '\0'; c++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}
void drawsubhead(float x, float y, float z, char *string)
{
    glColor3f(1, 1, 1);
    glRasterPos3f(x, y, z);

    for (char *c = string; *c != '\0'; c++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
    }
}

void mouse(int button, int state, int x, int y){
    mouseX = x;
    mouseY = y;

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        if (closed || noOfPts >= MAX_PTS - 1)
            noOfPts = 0; // restart the polygon
        closed = 0;
        ptListX[noOfPts] = mouseX; 
        ptListY[noOfPts] = mouseY;
        noOfPts ++;
    }
    if ( button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN )
        closed = 1;
}
void front(){
    char cn[] = "ST JOSEPH ENGINEERING COLLEGE";
        drawhead(-445, 800, 0, cn);
        char pn[] = "Vamanjoor, Mangaluru- 575028";
        drawsubhead(-275, 750, 0, pn);
        char dn[] = "DEPARTMENT OF COMPUTER SCIENCE & ENGINEERING";
        drawhead(-675, 550, 0, dn);
        char prn[] = "A Mini Project On";
        drawsubhead(-175, 350, 0, prn);
        char pro[] = "Line Art using OpenGL";
        drawhead(-275, 250, 0, pro);
        char pb[] = "PROJECT BY: ";
        drawhead(-715, -200, 0, pb);
        char p1[] = "Darshan Gouda";
        drawhead(-625, -350, 0, p1);
        char p1u[] = "4SO19CS181";
        drawsubhead(-625, -400, 0, p1u);
        char p2[] = "Sukith S";
        drawhead(-625, -500, 0, p2);
        char p2u[] = "4SO19CS182";
        drawsubhead(-625, -550, 0, p2u);
        char in[] = "Click right mouse button for menu";
        drawhead(-375, -800, 0, in);
}
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    // glClearColor(0, 0, 0.1, 0.9);
    if (r == 0){        //Front Page
        front();
        glutSwapBuffers();
    }
    if(r==1){
        system("./animate.out");
        r=0;     
    }
    if(r==3){ 
        system("./draw.out");
        r=0;
    }
    glutPostRedisplay();
    glutSwapBuffers();
}


void menu(int op){
    if(op==1)
        r=1;
    if(op==2)
        r=2;
    if(op==3)
        r=3;
    if(op==4)
        exit(0);
}
void menuFunction(){
    char subMenu = glutCreateMenu(menu);
    glutAddMenuEntry("Triangle", 11);
    glutAddMenuEntry("Rectangle", 12);
    glutAddMenuEntry("Square", 13);
    glutAddMenuEntry("Polygon", 14);
    glutAddMenuEntry("Blue", 15);
    glutCreateMenu(menu);
    glutAddMenuEntry("Random Lines",1);
    glutAddSubMenu("Shapes",subMenu);
    glutAddMenuEntry("Draw",3);
    glutAddMenuEntry("Exit",4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowPosition(300,10);
    glutInitWindowSize(650, 700);
    glutCreateWindow("CG Mini Project : Line Art");
    init();
    glutDisplayFunc(display);
    menuFunction();
    glutMainLoop();
    return 0;
}
