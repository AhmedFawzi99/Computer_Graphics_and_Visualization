#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include "glm.h"
#include "imageloader.h"
using namespace std;

static int shoulder = 0, shoulder2 = 0, elbow = 0, rhip = 0, rhip2 = 0, rknee = 0, lknee = 0, lhip = 0, lhip2 = 0;
double eye[] = { 0, 0, 5 };
double center[] = { 0, 0, 1 };
double up[] = { 0, 1, 0 };
double anglecam = (double)10 / 180;
double speed = 0.1;

int moving, startx, starty;
GLfloat angle = 0.0;   /* in degrees */
GLfloat angle2 = 0.0;   /* in degrees */
static int fingerBase = 0, fingerUp = 0, fingerBase2 = 0, fingerUp2 = 0;
static int SHOULDERRIGHT = 0, SHOULDERRIGHT2 = 0, SHOULDERRIGHTZROT = 0, SHOULDERRIGHTUPALL = 0;
static int SHOULDERLEFT = 0, SHOULDERLEFT2 = 0, SHOULDERLEFTZROT = 0, SHOULDERLEFTUPALL = 0;
static int RIGHTLEGUPALL = 0, RIGHTLEG2 = 0, RIGHTLEGSIDE = 0;
static int LEFTLEGUP = 0, LEFTLEG2 = 0, LEFTLEGSIDE = 0;
static int allbodyY = 0, allbodyZ = 0;


GLMmodel* pmodel;


GLMmodel* pmodel1;
GLMmodel* pmodel2;
GLMmodel* pmodel3;
GLMmodel* pmodel4;
GLMmodel* pmodel5;
GLMmodel* pmodel6;
GLMmodel* pmodel7;
GLMmodel* pmodel8;
GLMmodel* pmodel9;
////

// RGBA
GLfloat light_ambient[] = { 0, 0, 0, 0 };
GLfloat light_diffuse[] = { 0.5, 0.5, 0.5,1.0 };
GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
// x , y, z, w
GLfloat light_position[] = { 0.5,5.0,2.0, 1.0 };
GLfloat lightPos1[] = { -0.5,-5.0,-2.0, 0 };
// Material Properties
GLfloat mat_amb_diff[] = { 1, 1, 1, 1 };
GLfloat mat_specular[] = { 1, 1, 1, 1.0 };
GLfloat shininess[] = { 100 };




float DRot = 90;
float VRot = 0.0;

int val1 = 0; int val2 = 0; int val3 = 0; int val4 = 0; int val5 = 0; int val6 = 0; int val7 = 0; int val8 = 0; int val9 = 0; int val10 = 0;
bool move1 = true, move2 = false, move3 = false, move4 = false, move5 = false, move6 = false, pushDown = true, pushUp = false;
GLfloat angle3 = 0.0;
float Ytrans = 0;
float Xtrans = 0;
float Ztrans = 0;
float YtransB = 0;
float XtransB = 0;
float ZtransB = 0;


GLuint loadTexture(Image* image) {
    GLuint textureId;
    glGenTextures(1, &textureId); //Make room for our texture
    glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
        0,                            //0 for now
        GL_RGB,                       //Format OpenGL uses for image
        image->width, image->height,  //Width and height
        0,                            //The border of the image
        GL_RGB, //GL_RGB, because pixels are stored in RGB format
        GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                          //as unsigned numbers
        image->pixels);               //The actual pixel data
    return textureId; //Returns the id of the texture
}

GLuint _textureId; //The id of the texture
GLuint _walltextureId; //The id of the texture
GLuint _bodytextureId;


void drawmodel(void)
{
    glmUnitize(pmodel1);
    glmFacetNormals(pmodel1);
    glmVertexNormals(pmodel1, 90.0);
    glmScale(pmodel1, .15);
    glmDraw(pmodel1, GLM_SMOOTH | GLM_MATERIAL);
}

GLuint startList;
//Initializes 3D rendering
void initRendering() {






    //glLightfv(GL_LIGHT1, GL_POSITION, light_position);
    //glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
    //glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    //glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
    //glEnable(GL_LIGHT1);
    //glEnable(GL_LIGHTING);

    //glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_MODELVIEW);
    Image* image = loadBMP("floor4.bmp");
    _textureId = loadTexture(image);
    printf("_textureId");
    delete image;

    Image* image2 = loadBMP("floor5.bmp");
    _walltextureId = loadTexture(image2);
    delete image2;
    /*  glEnable(GL_DEPTH_TEST);*/
    Image* image3 = loadBMP("shirt.bmp");
    _bodytextureId = loadTexture(image3);
    delete image3;
    // Turn on the power
    glEnable(GL_LIGHTING);
    // Flip light switch
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    // assign light parameters
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
/*     Material Properties        */ 
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    GLfloat lightColor1[] = { 1.0f, 1.0f,  1.0f, 1.0f };
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor1);
    glEnable(GL_NORMALIZE);
    ////Enable smooth shading
    glShadeModel(GL_SMOOTH);
    //// Enable Depth buffer
    //glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    gluPerspective(65.0, (GLfloat)1024 / (GLfloat)869, 1.0, 60.0);


    //     	startList = glGenLists(4);
    // glNewList(startList, GL_COMPILE);
    // glRotatef(90, 0, 1, 0);
    // 	glScalef(1, 1.2, 1);
    // 	glTranslatef(1.7, -0.05, -.3);
    // pmodel1 = pmodel4;
    // drawmodel();
    // glEndList();

    // glNewList(startList + 1, GL_COMPILE);
    // 	glRotatef(270, 0, 1, 0);
    // 	glScalef(1, 1.2, 1);
    // 	glTranslatef(-1.7, -0.05, -.3);
    // pmodel1 = pmodel4;
    // drawmodel();
    // glEndList();

    // glNewList(startList + 2, GL_COMPILE);
    // glTranslatef(0.3, -.1, 0.075);
    // pmodel1 = pmodel2;
    // drawmodel();
    // glEndList();

    // glNewList(startList + 3, GL_COMPILE);
    // glTranslatef(-0.6, 0, 0.0);
    // pmodel1 = pmodel2;
    // drawmodel();	
    // glEndList();


}



void init(void)

{

    glMatrixMode(GL_PROJECTION);
    gluPerspective(65.0, (GLfloat)1024 / (GLfloat)869, 1.0, 60.0);
    gluLookAt(eye[0], eye[1], eye[2],
        center[0], center[1], center[2],
        up[0], up[1], up[2]);

    //glLightfv(GL_LIGHT1, GL_POSITION, light_position);
    //glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
    //glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    //glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
    //glEnable(GL_LIGHT1);
    //glEnable(GL_LIGHTING);

    //glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_MODELVIEW);
    Image* image = loadBMP("floor4.bmp");
    _textureId = loadTexture(image);
    printf("_textureId");
    delete image;
    /*  glEnable(GL_DEPTH_TEST);*/

}
void main_menu(int value)
{
    if (value == 1)
    {
        val1 = 1;
        glutPostRedisplay();
    }
    else if (value == 2)
    {

        val2 = 1;
        glutPostRedisplay();
    }
    else if (value == 3)
    {
        val3 = 1;
        glutPostRedisplay();
    }
    else if (value == 4)
    {
        val4 = 1;
        glutPostRedisplay();
    }
    else if (value == 5)
    {
        val5 = 1;
        glutPostRedisplay();
    }
    else if (value == 6)
    {
        val6 = 1;
        glutPostRedisplay();
    }
    else if (value == 7)
    {
        val7 = 1;
        glutPostRedisplay();
    }
    else if (value == 8)
    {
        val8 = 1;
        glutPostRedisplay();
    }
    else if (value == 9)
    {
        val9 = 1;
        glutPostRedisplay();
    }
    else if (value == 10)
    {
        val10 = 1;
        glutPostRedisplay();
    }
    else if (value == 11)
    {
        Image* image = loadBMP("floor3.bmp");
        _textureId = loadTexture(image);
        printf("_textureId2");
        delete image;
    }
    else if (value == 22)
    {
        Image* image = loadBMP("floor2.bmp");
        _textureId = loadTexture(image);
        printf("_textureId2");
        delete image;
    }
    else if (value == 33)
    {
        Image* image = loadBMP("floor.bmp");
        _textureId = loadTexture(image);
        printf("_textureId2");
        delete image;
    }
   
}



void Timer(int x) {
    // Refresh and redraw
    glutPostRedisplay();
    glutTimerFunc(50, Timer, 0);
}
void Timer1(int x) {
    // Refresh and redraw
    VRot += 5;
    if (VRot == 360)
        VRot = 0;
    glutPostRedisplay();
    glutTimerFunc(50, Timer1, 0);
}

void DTimer1(int x) {

    DRot -= 1;
    if (DRot == 0)
        return;
    glutPostRedisplay();
    glutTimerFunc(30, DTimer1, 0);


}

void DTimer2(int x) {
    DRot += 1;
    if (DRot == 90)
        return;
    glutPostRedisplay();
    glutTimerFunc(30, DTimer2, 0);
}


void crossProduct(double a[], double b[], double c[])
{
    c[0] = a[1] * b[2] - a[2] * b[1];
    c[1] = a[2] * b[0] - a[0] * b[2];
    c[2] = a[0] * b[1] - a[1] * b[0];
}

void normalize(double a[])
{
    double norm;
    norm = a[0] * a[0] + a[1] * a[1] + a[2] * a[2];
    norm = sqrt(norm);
    a[0] /= norm;
    a[1] /= norm;
    a[2] /= norm;
}

void rotatePoint(double a[], double theta, double p[])
{

    double temp[3];
    temp[0] = p[0];
    temp[1] = p[1];
    temp[2] = p[2];

    temp[0] = -a[2] * p[1] + a[1] * p[2];
    temp[1] = a[2] * p[0] - a[0] * p[2];
    temp[2] = -a[1] * p[0] + a[0] * p[1];

    temp[0] *= sin(theta);
    temp[1] *= sin(theta);
    temp[2] *= sin(theta);

    temp[0] += (1 - cos(theta)) * (a[0] * a[0] * p[0] + a[0] * a[1] * p[1] + a[0] * a[2] * p[2]);
    temp[1] += (1 - cos(theta)) * (a[0] * a[1] * p[0] + a[1] * a[1] * p[1] + a[1] * a[2] * p[2]);
    temp[2] += (1 - cos(theta)) * (a[0] * a[2] * p[0] + a[1] * a[2] * p[1] + a[2] * a[2] * p[2]);

    temp[0] += cos(theta) * p[0];
    temp[1] += cos(theta) * p[1];
    temp[2] += cos(theta) * p[2];

    p[0] = temp[0];
    p[1] = temp[1];
    p[2] = temp[2];

}

void Left()
{

    ////////////////////////////////// move the camera left around the up which is normal vector doesnot need normalization vector//////////////////
    rotatePoint(up, -anglecam, eye);
}

void Right()
{
    //////opposite of left
    rotatePoint(up, anglecam, eye);
}

void Up()
{    ////////////////////HORIZONTAL ROTATION//////////////////////
    double Changed[] = { 0,0,0 };      ////////////// A vector of zeros to add the new axis to when croos producted with the current vector
    double Current[] = { eye[0] - center[0] ,eye[1] - center[1] ,eye[2] - center[2] }; ////////////////////// CUrrent vector of distance values between the eye and center values
    crossProduct(Current, up, Changed);
    normalize(Changed);     ///// Normalizing the new vector as it is changed 
    rotatePoint(Changed, anglecam, up);          /////////////// rotation camera around the up vector 
    rotatePoint(Changed, anglecam, eye);         /////////////// rotation camera around the eye vector 
}

void Down()
{
    /////Opposite angle of up 
    double Changed[] = { 0,0,0 };
    double Current[] = { eye[0] - center[0] ,eye[1] - center[1] ,eye[2] - center[2] };
    crossProduct(Current, up, Changed);
    normalize(Changed);
    rotatePoint(Changed, -anglecam, up);
    rotatePoint(Changed, -anglecam, eye);
}


void moveForward()
{

    double Current[] = { center[0] - eye[0]  , center[1] - eye[1] , center[2] - eye[2] };  ////////////////////// CUrrent vector of distance values between the eye and center values
    center[0] += Current[0] * speed;
    center[1] += Current[1] * speed; ///////////////////change the center values when user presses 
    center[2] += Current[2] * speed;

    eye[0] += Current[0] * speed;
    eye[1] += Current[1] * speed;       ///////////////////change the eye values when user presses 
    eye[2] += Current[2] * speed;

}

void moveBack()
{
    //////////////////Opposite speed of Forward
    double Current[] = { center[0] - eye[0]  , center[1] - eye[1] , center[2] - eye[2] };
    center[0] += Current[0] * -speed;
    center[1] += Current[1] * -speed; ///////////////////change the center values when user presses 
    center[2] += Current[2] * -speed;

    eye[0] += Current[0] * -speed;
    eye[1] += Current[1] * -speed;       ///////////////////change the eye values when user presses 
    eye[2] += Current[2] * -speed;
}


void Body()
{

    glPushMatrix();

    glColor3f(255.0f, 0.0f, 0.0f);
    glScalef(0.5, 0.9, 0.3);
    glutSolidCube(1.5);
    glPopMatrix();
}

void Head()
{
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(0.0, 1.0, 0.0);
    glutWireSphere(0.25, 9, 9);
    glPopMatrix();
}

void Arms()
{
    //////////////////////////////////////////////LEFT ARM////////////////////////////////////////////////
    glPushMatrix();

    glTranslatef(-0.6, 0.55, 0.0);
    glRotatef((GLfloat)SHOULDERLEFTUPALL, 1.0, 0.0, 0.0);
    glRotatef((GLfloat)SHOULDERLEFT, 0.0, 0.0, 1.0);
    glTranslatef(0.63, -0.63, 0.0);
    glTranslatef(-0.63, 0.22, 0.0);
    glRotatef((GLfloat)SHOULDERLEFTZROT, 0.0, 1.0, 0.0);
    glTranslatef(0.63, -0.22, 0.0);
    glPushMatrix();
    glTranslatef(-0.55, 0.43, 0.0);
    glScalef(0.2, 0.5, 0.3);
    glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1.0, 0.15, 0.0);
    glRotatef((GLfloat)SHOULDERLEFT2, 1.0, 0.0, 0.0);
    glTranslatef(-1.0, -0.15, 0.0);
    glTranslatef(-0.55, -0.07, 0.0);
    glScalef(0.2, 0.5, 0.3);
    glutSolidCube(1.0);
    glRotatef(-90, 0.0, 0.0, 1.0);

    glPushMatrix();
    //Draw finger flang 1.1 
    glTranslatef(0.55, 0.15, 0.25);
    glRotatef((GLfloat)fingerBase2, 0.0, 0.0, 1.0);
    glTranslatef(0.05, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.2, 0.1, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    //Draw finger flang 1.2
    glTranslatef(0.15, 0.0, 0.0);
    glRotatef((GLfloat)fingerUp2, 0.0, 0.0, 1.0);
    glTranslatef(0.05, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.2, 0.1, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    glPopMatrix();


    glPushMatrix();
    //Draw finger flang 2.1
    glTranslatef(0.55, -0.15, -0.35);
    glRotatef((GLfloat)-fingerBase2, 0.0, 0.0, 1.0);
    glTranslatef(0.05, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.2, 0.1, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    //Draw finger flang 2.2
    glTranslatef(0.15, 0.0, 0.0);
    glRotatef((GLfloat)-fingerUp2, 0.0, 0.0, 1.0);
    glTranslatef(0.05, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.2, 0.1, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    glPopMatrix();


    glPushMatrix();
    //Draw finger flang 3.1
    glTranslatef(0.55, -0.15, -0.12);
    glRotatef((GLfloat)-fingerBase2, 0.0, 0.0, 1.0);
    glTranslatef(0.05, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.2, 0.1, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    //Draw finger flang 3.2
    glTranslatef(0.15, 0.0, 0.0);
    glRotatef((GLfloat)-fingerUp2, 0.0, 0.0, 1.0);
    glTranslatef(0.05, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.2, 0.1, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    glPopMatrix();


    glPushMatrix();
    //Draw finger flang 4.1
    glTranslatef(0.55, -0.15, 0.09);
    glRotatef((GLfloat)-fingerBase2, 0.0, 0.0, 1.0);
    glTranslatef(0.05, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.2, 0.1, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    //Draw finger flang 4.2
    glTranslatef(0.15, 0.0, 0.0);
    glRotatef((GLfloat)-fingerUp2, 0.0, 0.0, 1.0);
    glTranslatef(0.05, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.2, 0.1, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    //Draw finger flang 5.1
    glTranslatef(0.55, -0.15, 0.3);
    glRotatef((GLfloat)-fingerBase2, 0.0, 0.0, 1.0);
    glTranslatef(0.05, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.2, 0.1, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    //Draw finger flang 5.2
    glTranslatef(0.15, 0.0, 0.0);
    glRotatef((GLfloat)-fingerUp2, 0.0, 0.0, 1.0);
    glTranslatef(0.05, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.2, 0.1, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();


    //////////////////////////////////////////////RIGHT ARM////////////////////////////////////////////////
    glPushMatrix();
    glTranslatef(0.6, 0.55, 0.0);
    glRotatef((GLfloat)SHOULDERRIGHTUPALL, 1.0, 0.0, 0.0);
    glRotatef((GLfloat)SHOULDERRIGHT, 0.0, 0.0, 1.0);
    glTranslatef(-0.63, -0.63, 0.0);
    glTranslatef(0.63, 0.22, 0.0);
    glRotatef((GLfloat)SHOULDERRIGHTZROT, 0.0, 1.0, 0.0);
    glTranslatef(-0.63, -0.22, 0.0);
    glPushMatrix();
    glTranslatef(0.55, 0.43, 0.0);
    glScalef(0.2, 0.5, 0.3);
    glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-1.0, 0.15, 0.0);
    glRotatef((GLfloat)SHOULDERRIGHT2, 1.0, 0.0, 0.0);
    glTranslatef(1.0, -0.15, 0.0);
    glTranslatef(0.55, -0.07, 0.0);
    glScalef(0.2, 0.5, 0.3);
    glutSolidCube(1.0);





    glRotatef(-90, 0.0, 0.0, 1.0);

    glPushMatrix();
    //Draw finger flang 1.1 
    glTranslatef(0.55, -0.15, 0.25);
    glRotatef((GLfloat)fingerBase, 0.0, 0.0, 1.0);
    glTranslatef(0.05, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.2, 0.1, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    //Draw finger flang 1.2
    glTranslatef(0.15, 0.0, 0.0);
    glRotatef((GLfloat)fingerUp, 0.0, 0.0, 1.0);
    glTranslatef(0.05, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.2, 0.1, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    glPopMatrix();


    glPushMatrix();
    //Draw finger flang 2.1
    glTranslatef(0.55, 0.15, -0.35);
    glRotatef((GLfloat)-fingerBase, 0.0, 0.0, 1.0);
    glTranslatef(0.05, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.2, 0.1, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    //Draw finger flang 2.2
    glTranslatef(0.15, 0.0, 0.0);
    glRotatef((GLfloat)-fingerUp, 0.0, 0.0, 1.0);
    glTranslatef(0.05, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.2, 0.1, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    glPopMatrix();


    glPushMatrix();
    //Draw finger flang 3.1
    glTranslatef(0.55, 0.15, -0.12);
    glRotatef((GLfloat)-fingerBase, 0.0, 0.0, 1.0);
    glTranslatef(0.05, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.2, 0.1, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    //Draw finger flang 3.2
    glTranslatef(0.15, 0.0, 0.0);
    glRotatef((GLfloat)-fingerUp, 0.0, 0.0, 1.0);
    glTranslatef(0.05, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.2, 0.1, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    glPopMatrix();


    glPushMatrix();
    //Draw finger flang 4.1
    glTranslatef(0.55, 0.15, 0.09);
    glRotatef((GLfloat)-fingerBase, 0.0, 0.0, 1.0);
    glTranslatef(0.05, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.2, 0.1, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    //Draw finger flang 4.2
    glTranslatef(0.15, 0.0, 0.0);
    glRotatef((GLfloat)-fingerUp, 0.0, 0.0, 1.0);
    glTranslatef(0.05, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.2, 0.1, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    //Draw finger flang 5.1
    glTranslatef(0.55, 0.15, 0.3);
    glRotatef((GLfloat)-fingerBase, 0.0, 0.0, 1.0);
    glTranslatef(0.05, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.2, 0.1, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    //Draw finger flang 5.2
    glTranslatef(0.15, 0.0, 0.0);
    glRotatef((GLfloat)-fingerUp, 0.0, 0.0, 1.0);
    glTranslatef(0.05, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.2, 0.1, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();

}

void Legs()
{
    //////////////////////////////////////////////RIGHT LEG///////////////////////////////////////////////////
    glPushMatrix();
        glTranslatef(-0.1, -0.8, 0.0);
        glRotatef((GLfloat)RIGHTLEGUPALL, 1.0, 0.0, 0.0);
        glRotatef((GLfloat)RIGHTLEGSIDE, 0.0, 0.0, 1.0);
        glTranslatef(0.1, 0.8, 0.0);
        glPushMatrix();
            glTranslatef(-0.25, -1.02, 0.0);
            glScalef(0.25, 0.7, 0.3);
            glutSolidCube(1.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0.8, -1.35, 0.0);
            glRotatef((GLfloat)RIGHTLEG2, 1.0, 0.0, 0.0);
            glTranslatef(-0.8, 1.35, 0.0);
            glPushMatrix();
                glTranslatef(-0.25, -1.72, 0.0);
                glScalef(0.25, 0.7, 0.3);
                glutSolidCube(1.0);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(-0.25, -2.0, 0.0);
                glScalef(0.26, 0.2, 0.5);
                glutSolidCube(1.0);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
    //////////////////////////////////////////////LEFT LEG///////////////////////////////////////////////////
    glPushMatrix();
        glTranslatef(0.1, -0.8, 0.0);
        glRotatef((GLfloat)LEFTLEGUP, 1.0, 0.0, 0.0);
        glRotatef((GLfloat)LEFTLEGSIDE, 0.0, 0.0, 1.0);
        glTranslatef(-0.1, 0.8, 0.0);
        glPushMatrix();
            glTranslatef(0.25, -1.02, 0.0);
            glScalef(0.23, 0.7, 0.3);
            glutSolidCube(1.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0.8, -1.35, 0.0);
            glRotatef((GLfloat)LEFTLEG2, 1.0, 0.0, 0.0);
            glTranslatef(-0.8, 1.35, 0.0);
            glPushMatrix();
                glTranslatef(0.25, -1.72, 0.0);
                glScalef(0.25, 0.7, 0.3);
                glutSolidCube(1.0);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(0.25, -2.0, 0.0);
                glScalef(0.26, 0.2, 0.5);
                glutSolidCube(1.0);
            glPopMatrix();
        glPopMatrix();
        glPopMatrix();


}



void Room()
{

    glPushMatrix();
    // Draw floor
    glColor3f(0.7f, 0.5f, 0.4f);
    //glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex3f(-10.0f, -2.5f, -10.0f);
    glVertex3f(-10.0f, -2.5f, 10.0f);
    glVertex3f(10.0f, -2.5f, 10.0f);
    glVertex3f(10.0f, -2.5f, -10.0f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBegin(GL_QUADS);

    glNormal3f(0.0, -1.0, 0.0);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-10.0f, -2.5f, -10.0f);
    glTexCoord2f(1.75f, 0.0f);
    glVertex3f(-10.0f, -2.5f, 10.0f);
    glTexCoord2f(1.75f, 1.75f);
    glVertex3f(10.0f, -2.5f, 10.0f);
    glTexCoord2f(0.0f, 1.75f);
    glVertex3f(10.0f, -2.5f, -10.0f);

    glEnd();
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();


    //glPushMatrix();
    ////wall
    //glColor3f(1.0f, 0.851f, 0.702f);
    //glBegin(GL_QUADS);
    //glVertex3f(-10.0f, -2.5f, -10.0f);
    //glVertex3f(-10.0f, 10.0f, -10.0f);
    //glVertex3f(10.0f, 10.0f, -10.0f);
    //glVertex3f(10.0f, -2.5f, -10.0f);
    //glEnd();
    //glPopMatrix();

    glPushMatrix();
    //wall with door
    glColor3f(0.9f, 0.7f, 0.57f);
    glBegin(GL_QUADS);
    glVertex3f(-10.0f, -2.5f, -10.0f);
    glVertex3f(-10.0f, 8.0f, -10.0f);
    glVertex3f(-7.0f, 8.0f, -10.0f);
    glVertex3f(-7.0f, -2.5f, -10.0f);
    glEnd();

    glColor3f(0.9f, 0.7f, 0.57f);
    glBegin(GL_QUADS);
    glVertex3f(-3.0f, -2.5f, -10.0f);
    glVertex3f(-3.0f, 8.0f, -10.0f);
    glVertex3f(10.0f, 8.0f, -10.0f);
    glVertex3f(10.0f, -2.5f, -10.0f);
    glEnd();



    glColor3f(0.9f, 0.7f, 0.57f);
    glBegin(GL_QUADS);
    glVertex3f(-3.0f, 5.0f, -10.0f);
    glVertex3f(-3.0f, 8.0f, -10.0f);
    glVertex3f(-7.0f, 8.0f, -10.0f);
    glVertex3f(-7.0f, 5.0f, -10.0f);
    glEnd();

    glPopMatrix();

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _walltextureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBegin(GL_QUADS);

    glNormal3f(0.0, -1.0, 0.0);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-3.0f, 5.0f, -10.0f);
    glTexCoord2f(0.5f, 0.0f);
    glVertex3f(-3.0f, 8.0f, -10.0f);
    glTexCoord2f(0.5f, 0.5f);
    glVertex3f(-7.0f, 8.0f, -10.0f);
    glTexCoord2f(0.0f, 0.5f);
    glVertex3f(-7.0f, 5.0f, -10.0f);

    glNormal3f(0.0, -1.0, 0.0);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-3.0f, -2.5f, -10.0f);
    glTexCoord2f(0.7f, 0.0f);
    glVertex3f(-3.0f, 8.0f, -10.0f);
    glTexCoord2f(0.7f, 0.7f);
    glVertex3f(10.0f, 8.0f, -10.0f);
    glTexCoord2f(0.0f, 0.7f);
    glVertex3f(10.0f, -2.5f, -10.0f);

    glNormal3f(0.0, -1.0, 0.0);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-10.0f, -2.5f, -10.0f);
    glTexCoord2f(0.5f, 0.0f);
    glVertex3f(-10.0f, 8.0f, -10.0f);
    glTexCoord2f(0.5f, 0.5f);
    glVertex3f(-7.0f, 8.0f, -10.0f);
    glTexCoord2f(0.0f, 0.5f);
    glVertex3f(-7.0f, -2.5f, -10.0f);

    glEnd();
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();

    glPushMatrix();
    //wall
    glColor3f(0.9f, 0.7f, 0.57f);
    glBegin(GL_QUADS);
    glVertex3f(-10.0f, -2.5f, -10.0f);
    glVertex3f(-10.0f, 8.0f, -10.0f);
    glVertex3f(-10.0f, 8.0f, 10.0f);
    glVertex3f(-10.0f, -2.5f, 10.0f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _walltextureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBegin(GL_QUADS);

    glNormal3f(0.0, -1.0, 0.0);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-10.0f, -2.5f, -10.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-10.0f, 8.0f, -10.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-10.0f, 8.0f, 10.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-10.0f, -2.5f, 10.0f);

    glEnd();
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();

    glPushMatrix();
    //wall
    glColor3f(0.9f, 0.7f, 0.57f);
    glBegin(GL_QUADS);
    glVertex3f(10.0f, -2.5f, -10.0f);
    glVertex3f(10.0f, 8.0f, -10.0f);
    glVertex3f(10.0f, 8.0f, 10.0f);
    glVertex3f(10.0f, -2.5f, 10.0f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _walltextureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBegin(GL_QUADS);

    glNormal3f(0.0, -1.0, 0.0);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(10.0f, -2.5f, -10.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(10.0f, 8.0f, -10.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(10.0f, 8.0f, 10.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(10.0f, -2.5f, 10.0f);

    glEnd();
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();

    //wall
    glColor3f(0.9f, 0.7f, 0.57f);
    glBegin(GL_QUADS);
    glVertex3f(-10.0f, -2.5f, 10.0f);
    glVertex3f(-10.0f, 8.0f, 10.0f);
    glVertex3f(10.0f, 8.0f, 10.0f);
    glVertex3f(10.0f, -2.5f, 10.0f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _walltextureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBegin(GL_QUADS);

    glNormal3f(0.0, -1.0, 0.0);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-10.0f, -2.5f, 10.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-10.0f, 8.0f, 10.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(10.0f, 8.0f, 10.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(10.0f, -2.5f, 10.0f);

    glEnd();
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();

    //ceiling
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex3f(-10.0f, 8.0f, -10.0f);
    glVertex3f(10.0f, 8.0f, -10.0f);
    glVertex3f(10.0f, 8.0f, 10.0f);
    glVertex3f(-10.0f, 8.0f, 10.0f);
    glEnd();

}

void drawmodel1(void)
{

    if (val1 == 1) {
        if (!pmodel) {
            pmodel = glmReadOBJ((char*)"data/husk_armchair_OBJ.obj");

            if (!pmodel) exit(0);
            glmUnitize(pmodel);
            glmFacetNormals(pmodel);
            glmVertexNormals(pmodel, 90.0);
            glmScale(pmodel, .15);
        }
        glmDraw(pmodel, GLM_SMOOTH | GLM_MATERIAL);
    }
}

void drawmodel2(void)
{

        if (val2 == 1) {
            if (!pmodel1) {
                pmodel1 = glmReadOBJ((char*)"data/Bedcloth_72.obj");

                if (!pmodel1) exit(0);
                glmUnitize(pmodel1);
                glmFacetNormals(pmodel1);
                glmVertexNormals(pmodel1, 90.0);
                glmScale(pmodel1, .15);
            }
            glmDraw(pmodel1, GLM_SMOOTH | GLM_MATERIAL);
        }
}

void drawmodel3(void)
{

    if (val3 == 1) {
        if (!pmodel2) {
            pmodel2 = glmReadOBJ((char*)"data/Wasp.obj");

            if (!pmodel2) exit(0);
            glmUnitize(pmodel2);
            glmFacetNormals(pmodel2);
            glmVertexNormals(pmodel2, 90.0);
            glmScale(pmodel2, .15);
        }
        glmDraw(pmodel2, GLM_SMOOTH | GLM_MATERIAL);
    }
}

void drawmodel4(void)
{

    if (val4 == 1) {
        if (!pmodel3) {
            pmodel3 = glmReadOBJ((char*)"data/3d-model.obj");

            if (!pmodel3) exit(0);
            glmUnitize(pmodel3);
            glmFacetNormals(pmodel3);
            glmVertexNormals(pmodel3, 90.0);
            glmScale(pmodel3, .15);
        }
        glmDraw(pmodel3, GLM_SMOOTH | GLM_MATERIAL);
    }
}


void drawmodel5(void)
{

    if (val5 == 1) {
        if (!pmodel4) {
            pmodel4 = glmReadOBJ((char*)"data/LaptopBag.obj");

            if (!pmodel4) exit(0);
            glmUnitize(pmodel4);
            glmFacetNormals(pmodel4);
            glmVertexNormals(pmodel4, 90.0);
            glmScale(pmodel4, .15);
        }
        glmDraw(pmodel4, GLM_SMOOTH | GLM_MATERIAL);
    }
}

void drawmodel6(void)
{

    if (val6 == 1) {
        if (!pmodel5) {
            pmodel5 = glmReadOBJ((char*)"data/bookshelf_comment.obj");

            if (!pmodel5) exit(0);
            glmUnitize(pmodel5);
            glmFacetNormals(pmodel5);
            glmVertexNormals(pmodel5, 90.0);
            glmScale(pmodel5, .15);
        }
        glmDraw(pmodel5, GLM_SMOOTH | GLM_MATERIAL);
    }
}

void drawmodel7(void)
{

    if (val7 == 1) {
        if (!pmodel6) {
            pmodel6 = glmReadOBJ((char*)"data/cupboard.obj");

            if (!pmodel6) exit(0);
            glmUnitize(pmodel6);
            glmFacetNormals(pmodel6);
            glmVertexNormals(pmodel6, 90.0);
            glmScale(pmodel6, .15);
        }
        glmDraw(pmodel6, GLM_SMOOTH | GLM_MATERIAL);
    }
}

void drawmodel8(void)
{

    if (val8 == 1) {
        if (!pmodel7) {
            pmodel7 = glmReadOBJ((char*)"data/table.obj");

            if (!pmodel7) exit(0);
            glmUnitize(pmodel7);
            glmFacetNormals(pmodel7);
            glmVertexNormals(pmodel7, 90.0);
            glmScale(pmodel7, .15);
        }
        glmDraw(pmodel7, GLM_SMOOTH | GLM_MATERIAL);
    }
}

void drawmodel9(void)
{

    if (val9 == 1) {
        if (!pmodel8) {
            pmodel8 = glmReadOBJ((char*)"data/Laptop.obj");

            if (!pmodel8) exit(0);
            glmUnitize(pmodel8);
            glmFacetNormals(pmodel8);
            glmVertexNormals(pmodel8, 90.0);
            glmScale(pmodel8, .15);
        }
        glmDraw(pmodel8, GLM_SMOOTH | GLM_MATERIAL);
    }
}

void drawmodel10(void)
{

    if (val10 == 1) {
        if (!pmodel9) {
            pmodel9 = glmReadOBJ((char*)"data/portrait.obj");

            if (!pmodel9) exit(0);
            glmUnitize(pmodel9);
            glmFacetNormals(pmodel9);
            glmVertexNormals(pmodel9, 90.0);
            glmScale(pmodel9, .15);
        }
        glmDraw(pmodel9, GLM_SMOOTH | GLM_MATERIAL);
    }
}


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);
    glPushMatrix();
        glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glPopMatrix();
    //materials properties
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

    Room();
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glPushMatrix();
        glTranslatef(Xtrans, Ytrans, Ztrans);
        glRotatef(angle3, 0.0, 0.0, 1);
        glRotatef(angle, 0.0, 1.0, 0.0);
        glRotatef(angle2, 1.0, 0.0, 0.0);
        glTranslatef(XtransB, YtransB, ZtransB);
        glScalef(1.0, 1.2, 1.0);
        glRotatef((GLfloat)allbodyY, 0.0, 1.0, 0.0);
        glTranslatef(0.0, 0.0, allbodyZ);

        /////////////////////////////////////////////BODY//////////////////////////////////////////////////
        Body();
        /////////////////////////////////////////////HEAD////////////////////////////////////////////////////
        Head();
        /////////////////////////////////////////////ARMS////////////////////////////////////////////////////
        Arms();
        /////////////////////////////////////////////LEGS///////////////////////////////////////////////////
        Legs();
    glPopMatrix();

 
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glPushMatrix();

    //husk
    glPushMatrix();
 
        glTranslatef(-9.0, -2.0, -2);
        glRotatef(VRot, 0, 1, 0);
        glScalef(20, 20, 18);
        drawmodel1();
    glPopMatrix();

    //bed
    glPushMatrix();
  
        glTranslatef(7.0, -2.0, -8.25);
        glRotatef(VRot, 0, 1, 0);
        glScalef(28, 20, 30);
        drawmodel2();
    glPopMatrix();
    //insect1
    glPushMatrix();

        glTranslatef(0.55, 1.0, 0);
        glRotatef(VRot, 0, 1, 0);
        // glScalef(5, 20, 30);
        drawmodel3();
    glPopMatrix();
    //insect2
    glPushMatrix();

        glTranslatef(-5, 1.28, -2);
        glRotatef(VRot, 0, 1, 0);
        glScalef(3, 5, 2);
        drawmodel3();
    glPopMatrix();
    //tv
    glPushMatrix();

        glTranslatef(11, -2, 5);
        glRotatef(VRot, 0, 1, 0);
        glScalef(18, 15, 10);
        drawmodel4();
    glPopMatrix();

    //bag
    glPushMatrix();

        glTranslatef(-3, -2.5, 10.5);
        glRotatef(VRot, 0, 1, 0);
        glScalef(4, 4, 2);
        drawmodel5();
    glPopMatrix();
    //shelf
    glPushMatrix();

        glTranslatef(-11, 1, 9);
        glRotatef(VRot, 0, 1, 0);
        glScalef(6, 6, 4);
        drawmodel6();
    glPopMatrix();
    //cupboard
    glPushMatrix();

        glTranslatef(8, -2, 12);
        glRotatef(VRot, 0, 1, 0);
        glScalef(20, 20, 12);
        drawmodel7();
    glPopMatrix();
    //table
    glPushMatrix();
  
        glTranslatef(-8, -2, 12);
        glRotatef(VRot, 0, 1, 0);
        glScalef(30, 20, 17);
        drawmodel8();
    glPopMatrix();
    // labtop
    glPushMatrix();

        glTranslatef(-8, -2, 12);
        glRotatef(VRot, 0, 1, 0);
        glScalef(10, 8, 10);
        drawmodel9();
    glPopMatrix();

    //portrait
    glPushMatrix();

        glTranslatef(-11, 1, -6);
        glRotatef(VRot, 0, 1, 0);
        glScalef(17, 15, 12);
        drawmodel10();
    glPopMatrix();
    glPopMatrix();



    glutSwapBuffers();
}



void specialKeys(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT: Left(); break;
    case GLUT_KEY_RIGHT: Right(); break;
    case GLUT_KEY_UP:    Up(); break;
    case GLUT_KEY_DOWN:  Down(); break;


    }

    glutPostRedisplay();
}
void interact(int) {
    if (move1)
    {
        Ztrans -= 0.5;
    }
    if (Ztrans == -5 && move1)
    {
        move1 = false;
        move2 = true;
    }
    if (move2)
    {
        angle += 10;
    }
    if (angle == 90 && move2)
    {
        move2 = false;
        move3 = true;
    }
    if (move3)
    {
        //glTranslatef(7.0, -2.0, -8.25);
        Xtrans += 0.5;
    }
    if (Xtrans == 2 && move3)
    {
        move3 = false;
        move4 = true;
    }
    if (move4)
    {
        Ytrans = -1;
        YtransB = 1;
        angle2 += 10;
        SHOULDERLEFTUPALL -= 10;
        SHOULDERRIGHTUPALL -= 10;
        RIGHTLEGUPALL -= 10;
        LEFTLEGUP -= 10;
    }
    if (angle2 == 90 && move4)
    {
        move4 = false;
        move5 = true;
    }
    if (move5)
    {
        //glTranslatef(7.0, -2.0, -8.25);
        YtransB = -1;
        Xtrans = 4;
        angle2 += 10;
        SHOULDERLEFTUPALL -= 10;
        SHOULDERRIGHTUPALL -= 10;
        RIGHTLEGUPALL += 10;
        LEFTLEGUP += 10;
    }
    if (angle2 == 180 && move5)
    {
        move5 = false;
        move6 = true;
    }
    if (move6)
    {
        if (SHOULDERRIGHT2 == -90)
        {
            pushDown = false;
            pushUp = true;
        }
        if (SHOULDERRIGHT2 == 0)
        {
            pushDown = true;
            pushUp = false;
        }
        if (pushDown)
        {
            Ytrans -= 0.05;
            SHOULDERRIGHT2 -= 10;
            SHOULDERLEFT2 -= 10;
        }
        if (pushUp)
        {
            Ytrans += 0.05;
            SHOULDERRIGHT2 += 10;
            SHOULDERLEFT2 += 10;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(500, interact, 0);
}


void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'd':
        if (SHOULDERRIGHT < 115)
        {
            SHOULDERRIGHT = (SHOULDERRIGHT + 5) % 360;
            glutPostRedisplay();
        }
        if (SHOULDERLEFT > -115)
        {
            SHOULDERLEFT = (SHOULDERLEFT - 5) % 360;
            glutPostRedisplay();
        }
        break;
    case 'D':
        if (SHOULDERRIGHT > 0)
        {
            SHOULDERRIGHT = (SHOULDERRIGHT - 5) % 360;
            glutPostRedisplay();
        }
        if (SHOULDERLEFT < 0)
        {
            SHOULDERLEFT = (SHOULDERLEFT + 5) % 360;
            glutPostRedisplay();
        }
        break;
    case 'z':
        if (SHOULDERRIGHTZROT < 90)
        {
            SHOULDERRIGHTZROT = (SHOULDERRIGHTZROT + 5) % 360;
            glutPostRedisplay();
        }
        if (SHOULDERLEFTZROT > -90)
        {
            SHOULDERLEFTZROT = (SHOULDERLEFTZROT - 5) % 360;
            glutPostRedisplay();
        }
        break;
    case 'Z':
        if (SHOULDERRIGHTZROT > 0)
        {
            SHOULDERRIGHTZROT = (SHOULDERRIGHTZROT - 5) % 360;
            glutPostRedisplay();
        }
        if (SHOULDERLEFTZROT < 0)
        {
            SHOULDERLEFTZROT = (SHOULDERLEFTZROT + 5) % 360;
            glutPostRedisplay();
        }
        break;
    case 'w':
        if (SHOULDERRIGHT2 > -90)
        {
            SHOULDERRIGHT2 = (SHOULDERRIGHT2 - 5) % 360;
            glutPostRedisplay();
        }
        if (SHOULDERLEFT2 > -90)
        {
            SHOULDERLEFT2 = (SHOULDERLEFT2 - 5) % 360;
            glutPostRedisplay();
        }
        break;
    case 'W':
        if (SHOULDERRIGHT2 < 0)
        {
            SHOULDERRIGHT2 = (SHOULDERRIGHT2 + 5) % 360;
            glutPostRedisplay();
        }
        if (SHOULDERLEFT2 < 0)
        {
            SHOULDERLEFT2 = (SHOULDERLEFT2 + 5) % 360;
            glutPostRedisplay();
        }
        break;
    case 'l':
        if (RIGHTLEGUPALL > -90)
        {
            RIGHTLEGUPALL = (RIGHTLEGUPALL - 5) % 360;
            glutPostRedisplay();
        }
        break;
    case 'k':
        if (LEFTLEGUP > -90)
        {
            LEFTLEGUP = (LEFTLEGUP - 5) % 360;
            glutPostRedisplay();
        }
        break;
    case  'x':
        if (SHOULDERRIGHTUPALL > -180)
        {
            SHOULDERRIGHTUPALL = (SHOULDERRIGHTUPALL - 5) % 360;
            glutPostRedisplay();
        }
        break;
    case 'X':
        if (SHOULDERRIGHTUPALL < 0)
        {
            SHOULDERRIGHTUPALL = (SHOULDERRIGHTUPALL + 5) % 360;
            glutPostRedisplay();
        }
        break;

    case  't':
        if (SHOULDERLEFTUPALL > -180)
        {
            SHOULDERLEFTUPALL = (SHOULDERLEFTUPALL - 5) % 360;
            glutPostRedisplay();
        }
        break;
    case 'T':
        if (SHOULDERLEFTUPALL < 0)
        {
            SHOULDERLEFTUPALL = (SHOULDERLEFTUPALL + 5) % 360;
            glutPostRedisplay();
        }
        break;
    case 'L':
        if (RIGHTLEGUPALL < 65)
        {
            RIGHTLEGUPALL = (RIGHTLEGUPALL + 5) % 360;
            glutPostRedisplay();
        }
        break;
    case 'K':
        if (LEFTLEGUP < 65)
        {
            LEFTLEGUP = (LEFTLEGUP + 5) % 360;
            glutPostRedisplay();
        }
        break;
    case 'M':
        if (RIGHTLEG2 > -10)
        {
            RIGHTLEG2 = (RIGHTLEG2 - 5) % 360;
            glutPostRedisplay();
        }
        break;
    case 'N':
        if (LEFTLEG2 > -10)
        {
            LEFTLEG2 = (LEFTLEG2 - 5) % 360;
            glutPostRedisplay();
        }
        break;
    case 'm':
        if (RIGHTLEG2 < 90)
        {
            RIGHTLEG2 = (RIGHTLEG2 + 5) % 360;
            glutPostRedisplay();
        }
        break;
    case 'n':
        if (LEFTLEG2 < 90)
        {
            LEFTLEG2 = (LEFTLEG2 + 5) % 360;
            glutPostRedisplay();
        }
        break;
    case 'C':
        if (RIGHTLEGSIDE < 10)
        {
            RIGHTLEGSIDE = (RIGHTLEGSIDE + 5) % 360;
            glutPostRedisplay();
        }
        break;
    case 'c':
        if (RIGHTLEGSIDE > -85)
        {
            RIGHTLEGSIDE = (RIGHTLEGSIDE - 5) % 360;
            glutPostRedisplay();
        }
        break;
    case 'P':
        if (LEFTLEGSIDE > -10)
        {
            LEFTLEGSIDE = (LEFTLEGSIDE - 5) % 360;
            glutPostRedisplay();
        }
        break;
    case 'p':
        if (LEFTLEGSIDE < 85)
        {
            LEFTLEGSIDE = (LEFTLEGSIDE + 5) % 360;
            glutPostRedisplay();
        }
        break;
    case 'a':
        fingerBase = (fingerBase + 5);
        if (fingerBase > 90) {
            fingerBase = fingerBase - 5;
            break;
        }
        glutPostRedisplay();
        break;
    case 'A':
        fingerBase = (fingerBase - 5);
        if (fingerBase < -5) {
            fingerBase = fingerBase + 5;
            break;
        }
        glutPostRedisplay();
        break;
    case 'u':
        fingerUp = fingerUp + 5;
        if (fingerUp > 90) {
            fingerUp = fingerUp - 5;
            break;
        }
        glutPostRedisplay();
        break;
    case 'U':
        fingerUp = fingerUp - 5;
        if (fingerUp < -5) {
            fingerUp = fingerUp + 5;
            break;
        }
        glutPostRedisplay();
        break;
    case 'y':
        fingerBase2 = (fingerBase2 - 5);
        if (fingerBase2 < -90) {
            fingerBase2 = fingerBase2 + 5;
            break;
        }
        glutPostRedisplay();
        break;
    case 'Y':
        fingerBase2 = (fingerBase2 + 5);
        if (fingerBase2 > 5) {
            fingerBase2 = fingerBase2 - 5;
            break;
        }
        glutPostRedisplay();
        break;
    case 'r':
        fingerUp2 = fingerUp2 - 5;
        if (fingerUp2 < -90) {
            fingerUp2 = fingerUp2 + 5;
            break;
        }
        glutPostRedisplay();
        break;
    case 'R':
        fingerUp2 = fingerUp2 + 5;
        if (fingerUp2 > 5) {
            fingerUp2 = fingerUp2 - 5;
            break;
        }
        glutPostRedisplay();
        break;
    case '+':
        moveForward();
        glutPostRedisplay();
        break;

    case '-':
        moveBack();
        glutPostRedisplay();
        break;
    case 'o':
        interact(1);
        glutPostRedisplay();
        break;
    default:
        break;
    }
}
static void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            moving = 1;
            startx = x;
            starty = y;
        }
        if (state == GLUT_UP) {
            moving = 0;
        }
    }
}


static void motion(int x, int y)
{
    if (moving) {
        angle = angle + (x - startx);
        angle2 = angle2 + (y - starty);
        startx = x;
        starty = y;
        glutPostRedisplay();
    }
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(85.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("body");
    
    initRendering();

    glMatrixMode(GL_PROJECTION);
    gluPerspective(65.0, (GLfloat)1024 / (GLfloat)869, 1.0, 60.0);

    glutMotionFunc(motion);
    glutMouseFunc(mouse);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(specialKeys);
    glutKeyboardFunc(keyboard);
    //Timer(0);

    int menu = glutCreateMenu(main_menu);
    glutAddMenuEntry("Chair", 1);
    glutAddMenuEntry("Bed", 2);
    glutAddMenuEntry("FLies", 3);
    glutAddMenuEntry("TV", 4);
    glutAddMenuEntry("Bag", 5);
    glutAddMenuEntry("Shelf", 6);
    glutAddMenuEntry("Cupboard", 7);
    glutAddMenuEntry("Table", 8);
    glutAddMenuEntry("Labtop", 9);
    glutAddMenuEntry("Portrait", 10);
    int menu2 = glutCreateMenu(main_menu);
    glutAddMenuEntry("Floor 1", 11);
    glutAddMenuEntry("Floor 2", 22);
    glutAddMenuEntry("Floor 3", 33);
    glutCreateMenu(main_menu);
    glutAddSubMenu("Load Objects", menu);
    glutAddSubMenu("Change Texture", menu2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    //glutTimerFunc(0, Timer1, 0);
    glutMainLoop();
    return 0;
}