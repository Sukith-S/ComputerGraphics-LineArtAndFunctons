#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>


const int MAX_ITEMS = 1000;
struct ItemData {
   double x1, y1;
   double x2, y2;
};

struct ItemData items[MAX_ITEMS]; 
int itemCt = 0;  
int width;   
int height;  
bool dragging = false;  
int dragModifiers;      
void handleStartDraw(double x, double y, int modifiers) {
   if (itemCt == MAX_ITEMS) {
      printf("Line draw limit has been reached..!\n");
      return;
   }
   dragging = true;   
   dragModifiers = modifiers;
   items[itemCt].x1 = x;   
   items[itemCt].y1 = y;   
   items[itemCt].x2 = x;   
   items[itemCt].y2 = y;   
   itemCt++;
}

void handleContinueDraw(double x, double y) {
   if (!dragging)
      return;
   int current = itemCt - 1;                         
   bool shifted = ((dragModifiers & GLUT_ACTIVE_SHIFT) != 0);
   if (shifted) {  
      if (abs(x - items[current].x1) > abs(y - items[current].y1))
         y = items[current].y1;
      else
         x = items[current].x1;
   }
   items[current].x2 = x;  
   items[current].y2 = y;
   glutPostRedisplay();    
}

void handleFinishDraw(double x, double y) {
   if (!dragging)
      return;
   dragging = false;   
   int current = itemCt - 1;  
   if (items[current].x1 == items[current].x2 &&
      items[current].y1 == items[current].y2) {
         itemCt--;
   }
   glutPostRedisplay();  
}

void menu(int op){
   if(op==1){
      itemCt--;
      glutPostRedisplay();
   }
   if(op==2){
      itemCt=0;
      glutPostRedisplay();
   }
   if(op==3)
      exit(0);
}

void menuFunction(){
    glutCreateMenu(menu);
    glutAddMenuEntry("Undo",1);
    glutAddMenuEntry("Clear",2);
    glutAddMenuEntry("Home",3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void init(){
}

void drawItems() {
   glColor3f(1,1,1);  
   for (int i = 0; i < itemCt; i++) {
      glBegin(GL_LINES);
         glVertex2f(items[i].x1, items[i].y1);
         glVertex2f(items[i].x2, items[i].y2);
      glEnd();
   }
}

void initTransformation(double x1, double x2, double y1, double y2) {
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(x1,x2,y1,y2);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}


void display(){
   glClearColor(0,0,0,1);  
   glClear(GL_COLOR_BUFFER_BIT);   
   glViewport(0,0,width-0,height);
   initTransformation(0,1,0,1);
   drawItems();
   glViewport(0,0,0,height);  
   initTransformation(0,0,0,height);
   glutSwapBuffers();  
}

void reshape(int new_width, int new_height){
   height = new_height;
   width = new_width;
   glViewport(0,0,width,height);
}

void mouse(int button, int state, int x, int y) {
   if (button == GLUT_LEFT_BUTTON) {
      double wx, wy;  
      wx = (double)(x-0)/(width-0);
      wy = (double)(height-y)/height;
      if (state == GLUT_DOWN)
         handleStartDraw(wx,wy,glutGetModifiers());
      else
         handleFinishDraw(wx,wy);
   }
}

void motion(int x, int y) {
   if (dragging) {
      double wx, wy;  
      wx = (double)(x-0)/(width-0);
      wy = (double)(height-y)/height;
      handleContinueDraw(wx,wy);      
   }
}

int main(int argc, char **argv) {
   glutInit(&argc,argv);
   glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
   glutInitWindowSize(650,700);       
   glutInitWindowPosition(300,10);    
   glutCreateWindow("CG Mini Project : Line Art"); 
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutMouseFunc(mouse);       
   glutMotionFunc(motion);     
   menuFunction();
   init();
   glutMainLoop();
}

