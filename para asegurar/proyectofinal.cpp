//Semestre 2019 - 2
//************************************************************//
//************************************************************//
//************** Alumno (s): Angeles Lopez Michael Josefh*********************************//
//*************		Proyecto Final									******//
//*************											******//
//************************************************************//
//************************************************************//

#include "texture.h"
#include "figuras.h"
#include "Camera.h"

#include "cmodel/CModel.h"

//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////
static GLuint ciudad_display_list;	//Display List for the Monito


//NEW// Keyframes
//Variables de dibujo y manipulacion
float posX = 0, posY = 2.5, posZ = -3.5, rotRodIzq = 0, rotRodDer = 0, rotBraIzq = 0, rotBraDer = 0;
float giroMonito = 0;

#define MAX_FRAMES 5
int i_max_steps = 90;
int i_curr_steps = 0;

typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float incX;		//Variable para IncrementoX
	float incY;		//Variable para IncrementoY
	float incZ;		//Variable para IncrementoZ
	float rotRodIzq;
	float rotRodDer;
	float rotBraIzq;
	float rotBraDer;
	float rotInc;
	float rotInc2;
	float rotInc3;
	float rotInc4;
	float giroMonito;
	float giroMonitoInc;
	
}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex=0;			//introducir datos
bool play=false;
int playIndex=0;


//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////

int w = 500, h = 500;
int frame=0,time,timebase=0;
char s[30];

CCamera objCamera;	//Create objet Camera

GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW) 

int font=(int)GLUT_BITMAP_HELVETICA_18;


//GLfloat Diffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat Diffuse[]= { 0.5f, 0.5f, 0.5f, 1.0f };				// Diffuse Light Values
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat Position[]= { 0.0f, 7.0f, -5.0f, 0.0f };			// Light Position
GLfloat Position2[]= { 0.0f, 0.0f, -5.0f, 1.0f };			// Light Position

GLfloat m_dif1[] = { 0.0f, 0.2f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec1[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb1[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s1[] = {18};

GLfloat m_dif2[] = { 0.8f, 0.2f, 0.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec2[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb2[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s2[] = {22};

CTexture text1;
CTexture text2;
CTexture text3;	//Flecha
CTexture text4;	//Pavimento
CTexture text5;	//Pasto01
CTexture text6;	//Casa01



//NEW///////////////////////////7

CTexture textMesa;
CTexture textPata;
CTexture textWall;
CTexture textSilla;
CTexture textTecho;
CTexture textMarble;
CTexture textPiso;
CTexture textGlassWasser;
CTexture textBarrote;
CTexture textCuadro1;
CTexture textMarco;
CTexture textLibroCG;
CTexture textPB;
CTexture textPuerta;
CTexture textPuerta_princ;
CTexture textMarco_1;
CTexture textMarco_2;
CTexture textMarco_3;
CTexture textGrass;
CTexture textSky;
CTexture textLibrero;
CTexture t_fachada1;
CTexture t_fachada2;
CTexture t_fachada3;
CTexture t_fachada4;
CTexture t_fachada5;
CTexture t_piso1;
CTexture t_piso2;
CTexture t_piso3;
CTexture t_piso4;
CTexture t_paredgris1;
CTexture t_paredgris2;
CTexture t_paredamarilla;
CTexture t_parednaranja;
CTexture t_cascada;
CTexture t_techo2;
CTexture t_ven;
CTexture t_ven2;
CTexture t_ven3;
CTexture t_vidrioverde;
CTexture t_vidrioa;
CTexture t_vidrioa2;
CTexture t_puertaentrada;
CTexture t_puertaentrada2;
CTexture t_ladrillo;
CTexture t_negro;
CTexture t_noticiero;
CTexture t_noticia1;
CTexture t_bordeblanco;
CTexture t_puerta1;
CTexture t_tazon;




//***ROSE****
CTexture textAlmohada;
CTexture textColcha;
CTexture textMaderaBuro;
CTexture textMaderaCama;
CTexture textLampara;
CTexture textLaptop;
CTexture textPantalla;
CTexture textTeclado;
CTexture textTouchPad;
CTexture textGW;

//CFiguras fig1;
//CFiguras fig5;
CFiguras tablaMesa;
CFiguras pata1Mesa;
CFiguras pata2Mesa;
CFiguras pata3Mesa;
CFiguras pata4Mesa;
CFiguras asientoSilla;
CFiguras respaldoSilla1;
CFiguras respaldoSilla2;
CFiguras respaldoSilla3;
CFiguras respaldoSilla4;
CFiguras techoCasa;
CFiguras pisoCasa;
CFiguras cubo;
CFiguras sky;



//*****ROSE*****

CFiguras cama;
CFiguras buro;
CFiguras cono;
CFiguras lampara;
CFiguras laptop;

float abrirPuerta = 0;
//END NEW//////////////////////////////////////////

CFiguras fig1;
CFiguras fig2;
CFiguras fig3;
CFiguras fig4;	//Pasto01
CFiguras fig5;	//Casa01
CFiguras fig6;
CFiguras fig7;	//Para crear Monito


void saveFrame ( void )
{
	
	printf("frameindex %d\n",FrameIndex);			

	KeyFrame[FrameIndex].posX=posX;
	KeyFrame[FrameIndex].posY=posY;
	KeyFrame[FrameIndex].posZ=posZ;

	KeyFrame[FrameIndex].rotRodIzq=rotRodIzq;
	KeyFrame[FrameIndex].rotRodDer=rotRodDer;
	KeyFrame[FrameIndex].rotBraIzq = rotBraIzq;
	KeyFrame[FrameIndex].rotBraDer = rotBraDer;
	KeyFrame[FrameIndex].giroMonito=giroMonito;
			
	FrameIndex++;
}

void resetElements( void )
{
	posX=KeyFrame[0].posX;
	posY=KeyFrame[0].posY;
	posZ=KeyFrame[0].posZ;

	rotRodIzq=KeyFrame[0].rotRodIzq;
	rotRodDer=KeyFrame[0].rotRodDer;
	rotBraIzq = KeyFrame[0].rotBraIzq;
	rotBraDer = KeyFrame[0].rotBraDer;
	giroMonito=KeyFrame[0].giroMonito;

}

void interpolation ( void )
{
	KeyFrame[playIndex].incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;	
	KeyFrame[playIndex].incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;	
	KeyFrame[playIndex].incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;	

	KeyFrame[playIndex].rotInc = (KeyFrame[playIndex + 1].rotRodIzq - KeyFrame[playIndex].rotRodIzq) / i_max_steps;	
	KeyFrame[playIndex].rotInc2 = (KeyFrame[playIndex + 1].rotRodDer - KeyFrame[playIndex].rotRodDer) / i_max_steps;
	KeyFrame[playIndex].rotInc3 = (KeyFrame[playIndex + 1].rotBraIzq - KeyFrame[playIndex].rotBraIzq) / i_max_steps;
	KeyFrame[playIndex].rotInc4 = (KeyFrame[playIndex + 1].rotBraDer - KeyFrame[playIndex].rotBraDer) / i_max_steps;
	KeyFrame[playIndex].giroMonitoInc = (KeyFrame[playIndex + 1].giroMonito - KeyFrame[playIndex].giroMonito) / i_max_steps;

}


void ciudad ()
{

		glPushMatrix(); //Camino1
			glTranslatef(23.5,0.0,0.0);
			glScalef(40,0.1,7);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text4.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //Camino2
			glTranslatef(-23.5,0.0,0.0);
			glScalef(40,0.1,7);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text4.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //Pasto
			glTranslatef(0.0,0.0,-4.0);
			glScalef(87,0.1,1);
			glDisable(GL_LIGHTING);
			fig4.prisma2(text5.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //Pasto
			glTranslatef(0.0,0.0,4.0);
			glScalef(87,0.1,1);
			glDisable(GL_LIGHTING);
			fig4.prisma2(text5.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //Casa01
			glTranslatef(0.0,3.0,7.0);
			glRotatef(90,1,0,0);
			glRotatef(180,0,0,1);
			glScalef(6,5.0,6);
			glDisable(GL_LIGHTING);
			fig5.prisma2(t_fachada1.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //Casa01
			glTranslatef(0.0,3.0,-7.0);
			glRotatef(90,1,0,0);
			//glRotatef(180,0,0,1);
			glScalef(6,5.0,6);
			glDisable(GL_LIGHTING);
			fig5.prisma2(t_fachada2.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();

}

void monito()
{
	//glNewList(1, GL_COMPILE);
	glPushMatrix();//Pecho
		glScalef(0.5, 0.5, 0.5);
		fig7.prisma(2.0 ,2.0 ,1 ,text2.GLindex);

		glPushMatrix();//Cuello
			glTranslatef(0, 1.0, 0.0);
			fig7.cilindro(0.25, 0.25, 15, 0);
			glPushMatrix();//Cabeza
				glTranslatef(0, 1.0, 0);
				fig7.esfera(0.75, 15, 15, 0);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix(); //Brazo derecho-->
			glTranslatef(1.25, 0.65, 0);
			fig7.esfera(0.5, 12, 12, 0);
			glPushMatrix();
				glTranslatef(0.25, 0, 0);
				glRotatef(-45 +rotBraDer, 0, 1, 0); 
				glTranslatef(0.75, 0, 0);
				fig7.prisma(0.7, 1.5, 0.7, 0);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix(); //Brazo izquierdo <--
			glTranslatef(-1.25, 0.65, 0);
			fig7.esfera(0.5, 12, 12, 0);
			glPushMatrix();
				glTranslatef(-0.25, 0, 0);
				glRotatef(45, 0, 1, 0); 
				glRotatef(25, 0, 0, 1);
				glRotatef(25 +rotBraIzq, 1, 0, 0); 
				glTranslatef(-0.75, 0, 0);
				fig7.prisma(0.7, 1.5, 0.7, 0);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();//Cintura
			glColor3f(0, 0, 1);
			glTranslatef(0, -1.5, 0);
			fig7.prisma(1, 2, 1, 0);

			glPushMatrix(); //Pie Derecho -->
				glTranslatef(0.75, -0.5, 0);
				glRotatef(-15, 1, 0, 0);
				glTranslatef(0, -0.5, 0);
				fig7.prisma(1.0, 0.5, 1, 0);

				glPushMatrix();
					glTranslatef(0, -0.5, 0);
					glRotatef(15 + rotRodDer, 1, 0, 0);
					glTranslatef(0, -0.75, 0);
					fig7.prisma(1.5, 0.5, 1, 0);

					glPushMatrix();
						glTranslatef(0, -0.75, 0.3);
						fig7.prisma(0.2, 1.2, 1.5, 0);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();


			glPushMatrix(); //Pie Izquierdo -->
				glTranslatef(-0.75, -0.5, 0);
				glRotatef(-5, 1, 0, 0);
				glTranslatef(0, -0.5, 0);
				fig7.prisma(1.0, 0.5, 1, 0);

				glPushMatrix();
					glTranslatef(0, -0.5, 0);
					glRotatef(15+rotRodIzq, 1, 0, 0);
					glTranslatef(0, -0.75, 0);
					fig7.prisma(1.5, 0.5, 1, 0);

					glPushMatrix();
						glTranslatef(0, -0.75, 0.3);
						fig7.prisma(0.2, 1.2, 1.5, 0);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();


		glPopMatrix();


		glColor3f(1, 1, 1);
	glPopMatrix();
	//glEndList();
}



//NEW CASA//////////////////////////////////////

void dibujaLaptop(GLfloat xMadera, GLfloat yMadera, GLfloat zMadera, GLfloat xPosBuro, GLfloat yPosBuro, GLfloat zPosBuro)
{
	//	glPushMatrix();		
	//		glScalef(xMadera, yMadera, zMadera); 
	//		glTranslatef(xPosBuro, yPosBuro, zPosBuro); //figura 
			//contorno
	//		glPushMatrix();
	//			glTranslatef(7.0,0.5,0.25);
	//			glScalef(14.0,1.0,0.5);
	//			 laptop.prisma(1.0,1.0,1.0, textLaptop.GLindex);
	//		glPopMatrix();

	//		glPushMatrix();
	//			glTranslatef(7.0,11.5,0.25);
	//			glScalef(14.0,1.0,0.5);
	//			laptop.prisma(1.0,1.0,1.0, textLaptop.GLindex);
	//		glPopMatrix();

	//	glPushMatrix();
	//			glTranslatef(0.5,6.0,0.25);
	//			glScalef(1.0,10.0,0.5);
	//			laptop.prisma(1.0,1.0,1.0, textLaptop.GLindex);
	//		glPopMatrix();

	//		glPushMatrix();
	//			glTranslatef(13.5,6.0,0.25);
	//			glScalef(1.0,10.0,0.5);
	//			laptop.prisma(1.0,1.0,1.0, textLaptop.GLindex);
	//		glPopMatrix();
 //	glPushMatrix();
	//			glTranslatef(7.0,6.0,0.125);
	//			glScalef(12.0,10.0,0.25);
	//			laptop.prisma(1.0,1.0,1.0, textLaptop.GLindex);
	//		glPopMatrix();

	//		glPushMatrix();
	//			glTranslatef(7.0,6.0,0.375);
	//			glScalef(12.0,10.0,0.25);
	//			laptop.prisma(1.0,1.0,1.0, textPantalla.GLindex);
	//		glPopMatrix();

 		//teclado
	//		glPushMatrix();
	//			glTranslatef(7.0,-0.75,5.0);
	//			glScalef(14.0,0.5,10.0);
	//			laptop.prisma(1.0,1.0,1.0, textLaptop.GLindex);
	//		glPopMatrix();	

	//		glPushMatrix();
	//			glTranslatef(7.0,-0.25,0.5);
	//			glScalef(14.0,0.5,1.0);
	//			laptop.prisma(1.0,1.0,1.0, textLaptop.GLindex);
	//		glPopMatrix();	
	//		glPushMatrix();
	//			glTranslatef(7.0,-0.25,6.5);
	//			glScalef(14.0,0.5,1.0);
	//			laptop.prisma(1.0,1.0,1.0, textLaptop.GLindex);
	//		glPopMatrix();	

	//		glPushMatrix();
	//			glTranslatef(2.5,-0.25,8.0);
	//			glScalef(5.0,0.5,2.0);
	//			laptop.prisma(1.0,1.0,1.0, textLaptop.GLindex);
	//		glPopMatrix();	
	//	glPushMatrix();
	//			glTranslatef(11.5,-0.25,8.0);
	//			glScalef(5.0,0.5,2.0);
	//			laptop.prisma(1.0,1.0,1.0, textLaptop.GLindex);
//			glPopMatrix();	

	//		glPushMatrix();
	//			glTranslatef(7.0,-0.25,9.5);
	//			glScalef(14.0,0.5,1.0);
	//			laptop.prisma(1.0,1.0,1.0, textLaptop.GLindex);
	//		glPopMatrix();	
	//	glPushMatrix();
	//			glTranslatef(0.5,-0.25,5.0);
	//			glScalef(1.0,0.5,10.0);
	//			laptop.prisma(1.0,1.0,1.0, textLaptop.GLindex);
	//		glPopMatrix();	

	//		glPushMatrix();
	//			glTranslatef(13.5,-0.25,5.0);
	//			glScalef(1.0,0.5,10.0);
	//			laptop.prisma(1.0,1.0,1.0, textLaptop.GLindex);
	//		glPopMatrix();	
 		//teclas
	//		glPushMatrix();
	//			glTranslatef(7.0,-0.25,3.5);
	//			glScalef(12.0,0.5,5.0);
	//			laptop.prisma(1.0,1.0,1.0, textTeclado.GLindex);
	//		glPopMatrix();	

			//touchpad
	//		glPushMatrix();
	//			glTranslatef(7.0,-0.25,8.0);
	//			glScalef(4.0,0.5,2.0);
	//			laptop.tecla(1.0,1.0,1.0, textTouchPad.GLindex);
	//		glPopMatrix();	
	//	glPopMatrix();
}


void mesa(GLfloat xMadera, GLfloat yMadera, GLfloat zMadera, GLfloat xPosMesa, GLfloat yPosMesa, GLfloat zPosMesa){
	//mesa	
		//tabla
		//glPushMatrix();
			//glScalef(xMadera, yMadera, zMadera);
			//glTranslatef(xPosMesa, yPosMesa, zPosMesa);
			//glPushMatrix();
			//	glScalef(10,.5,5);
			//tablaMesa.prisma (1.0, 1.0, 1.0, textMarble.GLindex);
			//patas
			//glPopMatrix();
			//glPushMatrix();
				//glTranslatef(4, -2.75, 2);
				//glScalef( .5,5,.5);
				//pata1Mesa.prisma (1.0, 1.0, 1.0, textMarble.GLindex);
				//glTranslatef(0, 0, -8);
		//		pata2Mesa.prisma (1.0, 1.0, 1.0, textMarble.GLindex);
			//	glTranslatef(-16, 0, 0);
			//	pata3Mesa.prisma (1.0, 1.0, 1.0, textMarble.GLindex);
			//	glTranslatef(0, 0, 8);
			//	pata4Mesa.prisma (1.0, 1.0, 1.0, textMarble.GLindex);
		//	glPopMatrix();
//		glPopMatrix();

	//	return;
}

void silla(GLfloat xMadera, GLfloat yMadera, GLfloat zMadera, GLfloat xPosSilla, GLfloat yPosSilla, GLfloat zPosSilla){
	//	float numBarrotes = -2.9;
//	glPushMatrix();
		//posicion y tama�o
	//	glScalef(xMadera, yMadera, zMadera);
	//	glTranslatef(xPosSilla, yPosSilla, zPosSilla);
		//figura
	//	glPushMatrix();
		//	glScalef(3,.5,3);
		//	asientoSilla.prisma (1.0, 1.0, 1.0, textSilla.GLindex);//1
	//	glPopMatrix();
	//	glPushMatrix();
	//		glTranslatef(1.35, -3.25,-1.35);
	//		glScalef( .3,6,.3);
	//		pata1Mesa.prisma (1.0, 1.0, 1.0, textSilla.GLindex);
	//		glTranslatef(-9.0, 0, 0);
	//		pata2Mesa.prisma (1.0, 1.0, 1.0, textSilla.GLindex);
	//		glTranslatef(0, 0, 9);
	//		pata3Mesa.prisma (1.0, 1.0, 1.0, textSilla.GLindex);
	//		glTranslatef(9, 0, 0);
	//		pata4Mesa.prisma (1.0, 1.0, 1.0, textSilla.GLindex);
	//	glPopMatrix();
	//	glPushMatrix();
	//		glTranslatef(1.45, 4.25, -1.45);
	//		glScalef( 0.1,8.0,0.1);
	//		respaldoSilla1.prisma(1.0,1.0,1.0, textSilla.GLindex);
		//	for(int numBar = 1; numBar <= 10; numBar++){
		//		glTranslatef(numBarrotes,0,0);
		//		respaldoSilla1.prisma(1.0,1.0,1.0, textSilla.GLindex);
		//	}
	//	glPopMatrix();
	//	glPushMatrix();
	//		glTranslatef(0,1,-1.45);
	//		glScalef( 2.3,0.1,0.1);
		//	respaldoSilla1.prisma(1.0,1.0,1.0, textSilla.GLindex);
			//
		//	for(int numBar = 1; numBar <= 30; numBar++){
		//		glTranslatef(0,2,0);
		//		respaldoSilla1.prisma(1.0,1.0,1.0, textSilla.GLindex);
		//	}
		//	glTranslatef(0,12,0);
		//	glScalef( 1.5,1,1);
		//	respaldoSilla1.prisma(1.0,1.0,1.0, textSilla.GLindex);
	//	glPopMatrix();
//	glPopMatrix();

//	return;
}

void comedor(void){
	glPushMatrix();
			mesa(2,2,2,0,1,0);
	glPopMatrix();
	//SILLAS
	glPushMatrix();
		glTranslatef(0,0,-0.5);
		glRotatef(25, 0,1,0);
		glTranslatef(2,0,-0.5);
		silla(1,1,1,5,-1,-4.5);
		glPopMatrix();
		glPushMatrix();
			silla(1,1,1,-5,-1,-4.5);
		glPopMatrix();
		glPushMatrix();
			silla(1,1,1,0,-1,-4.5);
		glPopMatrix();
		//giramos con respecto Z
		glScalef(1,1,-1);
		glPushMatrix();				
		glPushMatrix();
			silla(1,1,1,5,-1,-4.5);
		glPopMatrix();
		glPushMatrix();
			silla(1,1,1,-5,-1,-4.5);
		glPopMatrix();
		glPushMatrix();
			silla(1,1,1,0,-1,-4.5);
		glPopMatrix();
	glPopMatrix();
		return;
}
void ropero(void){
	//		glPushMatrix();
	//			glTranslatef(-8,-20,50);
		//		fig5.prisma(50.0,1.0,30.0, textGW.GLindex);
		//	glPopMatrix();
		//	glPushMatrix();
		//		glTranslatef(-5.5,-20,35);
		//		glRotatef(90,1,0,0);
		//		fig5.prisma(1.0,6.0,50.0, textGW.GLindex);
		//	glPopMatrix();
		//	glPushMatrix();
		//		glTranslatef(-5.5,-20,65);
		//		glRotatef(90,1,0,0);
		//		fig5.prisma(1.0,6.0,50.0, textGW.GLindex);
		//	glPopMatrix();
		//	glPushMatrix();
		//		glTranslatef(-5.5,-20,57.5);
		//		glRotatef(90,1,0,0);
		//		fig5.prisma(0.5,6.0,50.0, textGW.GLindex);
		//	glPopMatrix();
		//	glPushMatrix();
		//		glTranslatef(-5.5,-20,42.5);
		//		glRotatef(90,1,0,0);
			//	fig5.prisma(0.5,6.0,50.0, textGW.GLindex);
		//	glPopMatrix();
		//	glPushMatrix();
//				glTranslatef(-5.5,-45,50);
	//			fig5.prisma(0.5,6.0,31.0, textGW.GLindex);
	//		glPopMatrix();
	//		glPushMatrix();
	//			glTranslatef(-5.5,5,50);
	//			fig5.prisma(0.5,6.0,31.0, textGW.GLindex);
	//		glPopMatrix();
	//		glPushMatrix();
	//			glTranslatef(-5.5,-20,50);
	//			fig5.prisma(0.5,6.0,30.0, textGW.GLindex);
	//		glPopMatrix();
	//		glPushMatrix();
		//		glTranslatef(-5.5,-30,50);
		//		fig5.prisma(0.5,6.0,30.0, textGW.GLindex);
		//	glPopMatrix();
		//	glPushMatrix();
		//		glTranslatef(-5.5,-10,39);
		//		fig5.prisma(0.5,6.0,7.5, textGW.GLindex);
		//	glPopMatrix();
		//	glPushMatrix();
		//		glTranslatef(-5.5,-10,61);
		//		fig5.prisma(0.5,6.0,7.5, textGW.GLindex);
		//	glPopMatrix();
}
void casa( void ){
//*****casa*****
	glPushMatrix(); //Creamos paredes
		glTranslatef(0,20,0);
		fig1.skybox2(60.0, 85.0, 85.0, t_paredamarilla.GLindex);
	glPopMatrix();

	//techo
	glPushMatrix();
		glTranslatef(0,50,0);
		techoCasa.prisma(1,85,85, t_techo2.GLindex);
	glPopMatrix();
	glPushMatrix();
	//piso
		glTranslatef(0,-10,0);
	
		//	pisoCasa.prisma(.1, 85, 85, t_piso1.GLindex);
		//pisoCasa.prisma(.1, 85, 85, t_piso2.GLindex);
		//pisoCasa.prisma(.1, 85, 85, t_piso3.GLindex);
		pisoCasa.prisma(.1, 85, 85, t_piso4.GLindex);

		//paredes de adentro
		//enfrente
		glPushMatrix();
		glTranslatef(0, 30.0, -41.5);
		glScalef(85.0, 60, 0.1);
		pisoCasa.prisma(1.0, 1.0, 1.0, t_paredgris2.GLindex);
		glPopMatrix();

		//detras
		glPushMatrix();
		glTranslatef(0, 30.0, 42.44);
		glScalef(85.0, 60, 0.1);
		pisoCasa.prisma(1.0, 1.0, 1.0, t_paredgris1.GLindex);
		glPopMatrix();

		//izq
		glPushMatrix();
		glRotatef(120, 1.0f, 1.0f, 1.0f);
		glTranslatef(30.0, 0.0, 42.44);
		glScalef(60.0, 85.0, 0.1);
		pisoCasa.prisma(1.0, 1.0, 1.0, t_paredgris1.GLindex);
		glPopMatrix();

		//der
		glPushMatrix();
		glRotatef(120, 1.0f, 1.0f, 1.0f);
		glTranslatef(30.0, 0.0, -42.44);
		glScalef(60.0, 85.0, 0.1);
		pisoCasa.prisma(1.0, 1.0, 1.0, t_paredgris1.GLindex);
		glPopMatrix();

		//patio
		glTranslatef(100,-3,-58);
		pisoCasa.prisma(1,433,430, textGrass.GLindex);
	glPopMatrix();

	//paredes de la entrada
	glPushMatrix();
		glTranslatef(-29.5,18,-42);
		glScalef(22.0, 55.0, 0.1);
		//pisoCasa.prisma(1,1,1, t_puertaentrada.GLindex);
		pisoCasa.prisma(1, 1, 1, t_puertaentrada2.GLindex);

		glPushMatrix();
		glPopMatrix();
		//no borrar
		glPopMatrix();


	//marco de la puerta para puertacasa
	//der
	glPushMatrix();
	//glTranslatef(-34, 10.0, -42.5);
	//glScalef(1.0, 40, 0.1);
	//pisoCasa.prisma(1.0, 1.0, 1.0, t_bordeblanco.GLindex);
	//pisoCasa.prisma(1.0, 1.0, 1.0, textGlassWasser.GLindex);
	glPopMatrix();

	
	//izq
	glPushMatrix();
	//glTranslatef(-26.5, 10.0, -42.5);
	//glScalef(1.0, 40, 0.1);
	//pisoCasa.prisma(1.0, 1.0, 1.0, t_bordeblanco.GLindex);
	//pisoCasa.prisma(1.0, 1.0, 1.0, textGlassWasser.GLindex);

	glPopMatrix();

	//arriba
	glPushMatrix();


	//glTranslatef(-30.25, 32, -42.5);//para puerta entrada
	//glScalef(8.5, 3.5,0.1);
	//pisoCasa.prisma(1.0, 1.0, 1.0, t_bordeblanco.GLindex);
	//pisoCasa.prisma(1.0, 1.0, 1.0, textGlassWasser.GLindex);
	glPopMatrix();

	//ventana blanca izq

	//izq
	glPushMatrix();
	glTranslatef(32, 18.0, -42);
	glScalef(1.0, 38, 1.0);
	pisoCasa.prisma(1.0, 1.0, 1.0, t_bordeblanco.GLindex);
	//pisoCasa.prisma(1.0, 1.0, 1.0, textGlassWasser.GLindex);
	glPopMatrix();


	//der
	glPushMatrix();
	glTranslatef(25, 18.0, -42);
	glScalef(1.0, 38, 1.0);
	pisoCasa.prisma(1.0, 1.0, 1.0, t_bordeblanco.GLindex);
	//pisoCasa.prisma(1.0, 1.0, 1.0, textGlassWasser.GLindex);
	glPopMatrix();

	//arriba
	glPushMatrix();
	glTranslatef(28.5, 35, -42);
	glScalef(6, 3.5, 1);
	pisoCasa.prisma(1.0, 1.0, 1.0, t_bordeblanco.GLindex);
	//pisoCasa.prisma(1.0, 1.0, 1.0, textGlassWasser.GLindex);
	glPopMatrix();

	//pared amarilla arriba izq

	glPushMatrix();
	glTranslatef(28.5, 41, -42);
	glScalef(8, 8, 1);
	pisoCasa.prisma(1.0, 1.0, 1.0, t_paredamarilla.GLindex);
	glPopMatrix();

	//abajo

	glPushMatrix();
	glTranslatef(28.5, .8, -42);
	glScalef(6, 3.5, 1);
	pisoCasa.prisma(1.0, 1.0, 1.0, t_bordeblanco.GLindex);
	//pisoCasa.prisma(1.0, 1.0, 1.0, textGlassWasser.GLindex);
	glPopMatrix();

	//pared amarilla abajo izq

	glPushMatrix();
	glTranslatef(28.5, -5.5, -42);
	glScalef(8, 9, 1);
	pisoCasa.prisma(1.0, 1.0, 1.0, t_paredamarilla.GLindex);
	glPopMatrix();


	//ventana blanca der

	//izq
	glPushMatrix();
	glTranslatef(12, 18.0, -42);
	glScalef(1.0, 38, 1.0);
	pisoCasa.prisma(1.0, 1.0, 1.0, t_bordeblanco.GLindex);
	//pisoCasa.prisma(1.0, 1.0, 1.0, textGlassWasser.GLindex);
	glPopMatrix();


	//der
	glPushMatrix();
	glTranslatef(5, 18.0, -42);
	glScalef(1.0, 38, 1.0);
	pisoCasa.prisma(1.0, 1.0, 1.0, t_bordeblanco.GLindex);
	//pisoCasa.prisma(1.0, 1.0, 1.0, textGlassWasser.GLindex);
	glPopMatrix();

	//arriba
	glPushMatrix();
	glTranslatef(8.5, 35, -42);
	glScalef(6, 3.5, 1);
	pisoCasa.prisma(1.0, 1.0, 1.0, t_bordeblanco.GLindex);
 //pisoCasa.prisma(1.0, 1.0, 1.0, textGlassWasser.GLindex);
	glPopMatrix();


	//pared amarilla arriba izq

	glPushMatrix();
	glTranslatef(8.5, 41, -42);
	glScalef(8, 8, 1);
	pisoCasa.prisma(1.0, 1.0, 1.0, t_paredamarilla.GLindex);
	glPopMatrix();

	//abajo

	glPushMatrix();
	glTranslatef(8.5, .8, -42);
	glScalef(6, 3.5, 1);
	pisoCasa.prisma(1.0, 1.0, 1.0, t_bordeblanco.GLindex);
	//pisoCasa.prisma(1.0, 1.0, 1.0, textGlassWasser.GLindex);
	glPopMatrix();

	//pared amarilla abajo der

	glPushMatrix();
	glTranslatef(8.5, -5.5, -42);
	glScalef(8, 9, 1);
	pisoCasa.prisma(1.0, 1.0, 1.0, t_paredamarilla.GLindex);
	glPopMatrix();

	//borde blanco arriba
	glPushMatrix();
		glTranslatef(0,48,-42);
		glScalef(85, 5, 1);
		pisoCasa.prisma(1.0, 1.0, 1.0, t_bordeblanco.GLindex);
		//cubo.prisma(1,1,1, textGlassWasser.GLindex);
	glPopMatrix();
	
	// borde derecho blanco
	glPushMatrix();
		glTranslatef(-41.5,17.5,-42);
		glScalef(2,56, 1);
		pisoCasa.prisma(1.0, 1.0, 1.0, t_bordeblanco.GLindex);
	    //cubo.prisma(1,1,1, textGlassWasser.GLindex);
	glPopMatrix();
	
	//chimenea
	glPushMatrix();
		glTranslatef(-10,17.6,-41.8);
		glScalef(17, 55, 0.1);
		cubo.prisma(1,1,1, t_ladrillo.GLindex);
	glPopMatrix();

	//chimenea adentro
	glPushMatrix();
	glTranslatef(-10, 20.0, -41.3);
	glScalef(17, 60, 0.1);
	cubo.prisma(1, 1, 1, t_ladrillo.GLindex);
	glPopMatrix();

	//puerta adentro
	glPushMatrix();
	glTranslatef(-30, 20.0, -41.3);
	glScalef(10, 60, 0.1);
	cubo.prisma(1, 1, 1, textPuerta.GLindex);
	glPopMatrix();


	//chimenea arriba
	glPushMatrix();
	glTranslatef(-10, 61.0, -41);
	glScalef(17, 20, 3);
	cubo.prisma(1, 1, 1, t_ladrillo.GLindex);
	glPopMatrix();

	//pared amarilla arriba
	glPushMatrix();
	glTranslatef(19, 55.0, -41);
	glScalef(47, 10, 1.5);
	cubo.prisma(1, 1, 1, t_paredamarilla.GLindex);
	glPopMatrix();


	//borde blanco arriba de la pared amarilla
	glPushMatrix();
	glTranslatef(19, 62.5, -41);
	glScalef(47, 5, 1);
	pisoCasa.prisma(1.0, 1.0, 1.0, t_bordeblanco.GLindex);
	//cubo.prisma(1, 1, 1, textGlassWasser.GLindex);
	glPopMatrix();



	//pared izq de la ventana izq

	glPushMatrix();
	glTranslatef(37.5, 17.6, -42);
	glScalef(10, 55, 1);
	cubo.prisma(1, 1, 1, t_paredamarilla.GLindex);
	glPopMatrix();

	//pared der de la ventana izq

	glPushMatrix();
	glTranslatef(18.5, 17.6, -42);
	glScalef(12, 55, 1);
	cubo.prisma(1, 1, 1, t_paredamarilla.GLindex);
	glPopMatrix();

	//pared der de la ventana der

	glPushMatrix();
	glTranslatef(1.5, 17.6, -42);
	glScalef(6, 55, 1);
	cubo.prisma(1, 1, 1, t_paredamarilla.GLindex);
	glPopMatrix();

	//vidrio ventana izq

	glPushMatrix();
	glTranslatef(28.5, 18.0, -42);
	glScalef(6, 30, 1);
	//cubo.prisma(1, 1, 1, t_vidrioverde.GLindex);
	//cubo.prisma(1, 1, 1, t_vidrioa.GLindex);
	cubo.prisma(1, 1, 1, t_vidrioa2.GLindex);

	glPopMatrix();
	
	//vidrio ventana der

	glPushMatrix();
	glTranslatef(8.5, 18.0, -42);
	glScalef(6, 30, 1);
	//cubo.prisma(1, 1, 1, t_vidrioverde.GLindex);
	//cubo.prisma(1, 1, 1, t_vidrioa.GLindex);
	cubo.prisma(1, 1, 1, t_vidrioa2.GLindex);
	glPopMatrix();


	return;
}

void cuadro(void){
	glPushMatrix();
		glScalef(1,1,-1);
		glTranslatef(-19,30,-42);
		cubo.prisma(16,15,.2, t_noticia1.GLindex);
		glTranslatef(0,0,-.05);
		cubo.prisma(19,16,.05, textMarco.GLindex);
	glPopMatrix();
	return;
}

//****ROSE****

void dibujaCama (GLfloat xMadera, GLfloat yMadera, GLfloat zMadera, GLfloat xPosCama, GLfloat yPosCama, GLfloat zPosCama)
{			
			glPushMatrix(); 
			glScalef(xMadera, yMadera, zMadera); //posicion y tama�o 
			glTranslatef(xPosCama, yPosCama, zPosCama); //figura 

			//dibujamos la cabecera PARTE DE ARRIBA
			glPushMatrix(); 
			glTranslatef(-29.0,30.5,0.5);
			glScalef(18.0,3.0,1.0);  //Tama�o de cabecera
			cama.prisma(1.0,1.0,1.0, t_negro.GLindex);
			glPopMatrix();

			//dibujamos la cabecera de enmedio der

			glPushMatrix();
			glTranslatef(-36.0, 18.5, 0.5);
			glScalef(4.0, 3.0, 1.0);  //Tama�o de cabecera
			cama.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
			glPopMatrix();

			//dibujamos la cabecera PARTE de enmedio izd

			glPushMatrix();
			glTranslatef(-22.0, 18.5, 0.5);
			glScalef(4.0, 3.0, 1.0);  //Tama�o de cabecera
			cama.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
			glPopMatrix();

			//CIRCULO IZQ
			glPushMatrix();
			glTranslatef(-27, 18.5, 0.5);
			glRotatef(120, 1.0f, 1.0f, 1.0f);
			cama.cilindro(3.5, 0.5, 20, t_negro.GLindex);
			glPopMatrix();

			//CIRCULO DER
			glPushMatrix();
			glTranslatef(-31, 18.5, 0.5);
			glRotatef(120, 1.0f, 1.0f, 1.0f);
			cama.cilindro(3.5, 0.5, 20, t_negro.GLindex);
			glPopMatrix();

			//pata der
			glPushMatrix();
			glTranslatef(-37.5, 22.0, 0.5);
			glScalef(1.0, 24.0, 1.0);
			cama.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
			glPopMatrix();


			//pata izq
			glPushMatrix();
			glTranslatef(-20.5, 22, 0.5);
			glScalef(1.0, 24.0, 1.0);
			cama.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
			glPopMatrix();

			//patas de abajo del circulo

			//der
			glPushMatrix();
			glTranslatef(-31.0, 12.5, 0.5);
			glScalef(1.0, 6.0, 1.0);
			cama.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
			glPopMatrix();

			//izq
			
			glPushMatrix();
			glTranslatef(-27, 12.5, 0.5);
			glScalef(1.0, 6.0, 1.0);
			cama.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
			glPopMatrix();

			//patas de arriba del circulo

			//der
			glPushMatrix();
			glTranslatef(-31.0, 25, 0.5);
			glScalef(1.0, 7.5, 1.0);
			cama.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
			glPopMatrix();

			//izq

			glPushMatrix();
			glTranslatef(-27, 25, 0.5);
			glScalef(1.0, 7.5, 1.0);
			cama.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
			glPopMatrix();

			//cuadro de la cabecera 
			
			
			glPushMatrix(); 
				glTranslatef(-29.,6.0,0.5);
				glScalef(16.0,6.0,1.0);  
				cama.prisma(1.0,1.0,1.0, t_negro.GLindex);
			glPopMatrix();


			//patas para sostener cabecera DER
			glPushMatrix();
			glTranslatef(-37.5, 6.0, 0.5);
			glScalef(1.0, 8.0, 1.0);
			cama.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
			glPopMatrix();
					

			//patas para sostener cabecera izq
			glPushMatrix(); 
				glTranslatef(-20.5,6.0,0.5);
				glScalef(1.0,8.0,1.0);
				cama.prisma(1.0,1.0,1.0, t_negro.GLindex);
			glPopMatrix();


			//inicio cabecera

			glPushMatrix();
			glTranslatef(-29.0, 9.5, 0.5);
			glScalef(18.0, 1.0, 1.0);
			cama.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
			glPopMatrix();


			//dibujamos la base de la cama
						

			glPushMatrix(); 
				glTranslatef(-29,1.0,11.0);
				glScalef(18.0,2.0,22.0);
				cama.prisma(1.0,1.0,1.0, t_negro.GLindex);
			glPopMatrix();

		
			//colchon
			glPushMatrix(); 
			glTranslatef(-29.0,3.5,11.0);
			glScalef(18.0,3.0,20.0);
			cama.prisma(1.0,1.0,1.0, textColcha.GLindex);
			glPopMatrix();

			// textura de cobija de tigre

			glPushMatrix();
			glTranslatef(-29.0, 3.5, 15);
			glScalef(18.0, 3.0, 12.0);
			cama.prisma(1.0,1.0,1.0, textColcha.GLindex);
			glPopMatrix();

			

			//almohada izquierda
			glPushMatrix(); 
				glTranslatef(-24.0,5.5,3.0);
				glScalef(8.0,1.0,4.0);
				cama.prisma(1.0,1.0,1.0, textAlmohada.GLindex);
			glPopMatrix();

			//almohada derecha
			glPushMatrix(); 
				glTranslatef(-34.0,5.5,3.0);
				glScalef(8.0,1.0,4.0);
				cama.prisma(1.0,1.0,1.0, textAlmohada.GLindex);
			glPopMatrix();


			//cabecera delgada de enfrente
			glPushMatrix(); 
				glTranslatef(-29.0,6.5,21.5);
				glScalef(16.0,1.0,1.0);
				cama.prisma(1.0,1.0,1.0, t_negro.GLindex);
			glPopMatrix();

			//tablita de enfrente
			glPushMatrix(); 
				glTranslatef(-29.0,2.5,21.5);
				glScalef(16.0,5.0,1.0);
				cama.prisma(1.0,1.0,1.0, t_negro.GLindex);
			glPopMatrix();

			//pata izq de enfrente
			glPushMatrix(); 
				glTranslatef(-20.5,4.0,21.5);
				glScalef(1.0,8.0,1.0);
				cama.prisma(1.0,1.0,1.0, t_negro.GLindex);
			glPopMatrix();

			//pata der de enfrente

			glPushMatrix(); 
				glTranslatef(-37.5,4.0,21.5);
				glScalef(1.0,8.0,1.0);
				cama.prisma(1.0,1.0,1.0, t_negro.GLindex);
			glPopMatrix();


			//patas chicas para sostener base de la cama
			glPushMatrix(); 
				glTranslatef(-20.5,-1.0,21.5);
				glScalef(1.0,2.0,1.0);
				cama.prisma(1.0,1.0,1.0, t_negro.GLindex);
			glPopMatrix();

			glPushMatrix(); 
				glTranslatef(-37.5,-1.0,21.5);
				glScalef(1.0,2.0,1.0);
				cama.prisma(1.0,1.0,1.0, t_negro.GLindex);
			glPopMatrix();

			glPushMatrix(); 
				glTranslatef(-37.5,-1.0,0.5);
				glScalef(1.0,2.0,1.0);
				cama.prisma(1.0,1.0,1.0, t_negro.GLindex);
			glPopMatrix();

			glPushMatrix(); 
				glTranslatef(-20.5,-1.0,0.5);
				glScalef(1.0,2.0,1.0);
				cama.prisma(1.0,1.0,1.0, t_negro.GLindex);
			glPopMatrix();
			glPopMatrix();




/////////////////////////////////////////////////////////////////////////////////////////////////
////// INICIO DE MESA peque�a

			//TABLA


			glPushMatrix();
			glTranslatef(-17.5, 0.7, 15.5);
			glScalef(7, .5, 5);
			cama.prisma(1.0, 1.0, 1.0, textMaderaCama.GLindex);
			glPopMatrix();
			

			//pata sup izq
			glPushMatrix();
				glTranslatef(-20.5, -2.75, 17.5);
				glScalef( .5,7.0,.5);
				cama.prisma(1.0, 1.0, 1.0, textMaderaCama.GLindex);
				glPopMatrix();

				//pata sup der
				glPushMatrix();
				glTranslatef(-20.5, -2.75, 13.5);
				glScalef(.5, 7.0, .5);
				cama.prisma(1.0, 1.0, 1.0, textMaderaCama.GLindex);
				glPopMatrix();

				//pata inf izq
				glPushMatrix();
				glTranslatef(-14.5, -2.75, 17.5);
				glScalef(.5, 7.0, .5);
				cama.prisma(1.0, 1.0, 1.0, textMaderaCama.GLindex);
				glPopMatrix();

				//pata inf der
				glPushMatrix();
				glTranslatef(-14.5, -2.75, 13.5);
				glScalef(.5, 7.0, .5);
				cama.prisma(1.0, 1.0, 1.0, textMaderaCama.GLindex);
				glPopMatrix();

			//silla
			//asiento de la silla

			glPushMatrix();
			glTranslatef(-17.5, -1.5, 20.5);
			glScalef(3,.5,3);
			cama.prisma (1.0, 1.0, 1.0, textSilla.GLindex);
			glPopMatrix();

			//respaldo 
			glPushMatrix();
			glTranslatef(-17.5, 3.2, 22.0);
			glScalef( 3.0,10.0,0.2);
			cama.prisma(1.0,1.0,1.0, textSilla.GLindex);
			glPopMatrix();

			//pata sup izq
			glPushMatrix();
			glTranslatef(-18.85, -4.75, 21.85);
			glScalef(.3, 6.0, .5);
			cama.prisma(1.0, 1.0, 1.0, textSilla.GLindex);
			glPopMatrix();

			//pata sup der
			glPushMatrix();
			glTranslatef(-18.85, -4.75, 19.5);
			glScalef(.3, 6.0, .5);
			cama.prisma(1.0, 1.0, 1.0, textSilla.GLindex);
			glPopMatrix();

			//pata inf izq
			glPushMatrix();
			glTranslatef(-16.15, -4.75, 21.85);
			glScalef(.3, 6.0, .5);
			cama.prisma(1.0, 1.0, 1.0, textSilla.GLindex);
			glPopMatrix();

			//pata inf der
			glPushMatrix();
			glTranslatef(-16.15, -4.75, 19.5);
			glScalef(.3, 6.0, .5);
			cama.prisma(1.0, 1.0, 1.0, textSilla.GLindex);
			glPopMatrix();


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////INICIO DE LA MESDA GRANDE		

				//TABLA


				glPushMatrix();
				glTranslatef(22.5, 2.0, -10.5);
				glScalef(20, 2.5, 13);
				cama.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
				glPopMatrix();

				//soporte de la mesa
				
				glPushMatrix();
				glTranslatef(22.0, -3.0, -10.6);
				glScalef(12, 7.0, 12);
				cama.prisma(1., 1.0, 1.0, t_negro.GLindex);
				glPopMatrix();
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////PLATO PARA PAPAS

				glPushMatrix();
				glTranslatef(22.5,4.5, -10);
				glScalef(3.2, -0.35, 3.2);
				lampara.cono(2.0, 0.4, 100, textMaderaBuro.GLindex);
				glPopMatrix();
				glPopMatrix();

}



void dibujaBuro(GLfloat xMadera, GLfloat yMadera, GLfloat zMadera, GLfloat xPosBuro, GLfloat yPosBuro, GLfloat zPosBuro)
{
	glPushMatrix();
	glScalef(xMadera, yMadera, zMadera);
	glTranslatef(xPosBuro, yPosBuro, zPosBuro); //figura 




	//buro pared der
	glPushMatrix();
	glTranslatef(13.5, 7.0, 5.0);
	glScalef(1.0, 16.5, 6.0);
	buro.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
	glPopMatrix();

	//buro pared enmedio
	glPushMatrix();
	glTranslatef(7.5, 8.0, 5.0);
	glScalef(1.0, 12.5, 6.0);
	buro.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
	glPopMatrix();

	//buro pared izq
	glPushMatrix();
	glTranslatef(2.5, 7.0, 5.0);
	glScalef(1.0, 16.5, 6.0);
	buro.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
	glPopMatrix();

	//pared atras
	glPushMatrix();
	glTranslatef(8.0, 7.0, 1.5);
	glScalef(12.0, 15.0, 1.0);
	buro.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
	glPopMatrix();

	//base

	glPushMatrix();
	glTranslatef(8.0, 0.0, 5.0);
	glScalef(10.0, 4.0, 6.0);
	buro.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
	glPopMatrix();


	//tablita de enmedio entre cajones nivel1 der
	glPushMatrix();
	glTranslatef(10.5, 2.5, 5.0);
	glScalef(5.0, 1.0, 6.0);
	buro.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
	glPopMatrix();


	//pata izq arriba del buro
	glPushMatrix();
	glTranslatef(5.0, 19.0, 1.5);
	glScalef(0.3, 9.0, 1.0);
	buro.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
	glPopMatrix();

	//pata der arriba del buro
	glPushMatrix();
	glTranslatef(11.0, 19.0, 1.5);
	glScalef(0.3, 9.0, 1.0);
	buro.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
	glPopMatrix();

	//dibujamos la cabecera PARTE DE ARRIBA enmedio

	glPushMatrix();
	glTranslatef(8.0, 23.5, 1.5);
	glScalef(6.25, 0.5, 1.0);  //Tama�o de cabecera
	cama.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
	glPopMatrix();

	//pata 2 izq arriba del buro
	glPushMatrix();
	glTranslatef(5.0, 28.0, 1.5);
	glScalef(0.3, 9.0, 1.0);
	cama.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
	glPopMatrix();

	//pata 2 der arriba del buro
	glPushMatrix();
	glTranslatef(11.0, 28.0, 1.5);
	glScalef(0.3, 9.0, 1.0);
	buro.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
	glPopMatrix();

	//CIRCULO IZQ buro
	glPushMatrix();
	glTranslatef(6.0, 27.5, 1.0);
	glRotatef(125, 1.0f, 1.0f, 1.0f);
	buro.cilindro(0.7, 1.0, 20, t_negro.GLindex);
	glPopMatrix();

	//CIRCULO medio izq buro
	glPushMatrix();
	glTranslatef(7.7, 27.5, 1.0);
	glRotatef(125, 1.0f, 1.0f, 1.0f);
	buro.cilindro(0.7, 1.0, 20, t_negro.GLindex);
	glPopMatrix();

	//CIRCULO medio der buro
	glPushMatrix();
	glTranslatef(8.4, 27.5, 1.0);
	glRotatef(125, 1.0f, 1.0f, 1.0f);
	buro.cilindro(0.7, 1.0, 20, t_negro.GLindex);
	glPopMatrix();

	//CIRCULO DER buro
	glPushMatrix();
	glTranslatef(10.0, 27.5, 1.0);
	glRotatef(125, 1.0f, 1.0f, 1.0f);
	buro.cilindro(0.7, 1.0, 20, t_negro.GLindex);
	glPopMatrix();


	//dibujamos la cabecera PARTE DE ARRIBA enmedio circulos 1

	glPushMatrix();
	glTranslatef(5.25, 27.5, 1.5);
	glScalef(0.5, 0.4, 1.0);  //Tama�o de cabecera
	cama.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
	glPopMatrix();

	//dibujamos la cabecera PARTE DE ARRIBA enmedio circulos 2

	glPushMatrix();
	glTranslatef(6.85, 27.5, 1.5);
	glScalef(0.6, 0.4, 1.0);  //Tama�o de cabecera
	cama.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
	glPopMatrix();

	//dibujamos la cabecera PARTE DE ARRIBA enmedio circulos 3

	glPushMatrix();
	glTranslatef(9.25, 27.5, 1.5);
	glScalef(0.5, 0.4, 1.0);  //Tama�o de cabecera
	cama.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
	glPopMatrix();


	//dibujamos la cabecera PARTE DE ARRIBA enmedio circulos 4

	glPushMatrix();
	glTranslatef(10.75, 27.5, 1.5);
	glScalef(0.5, 0.4, 1.0);  //Tama�o de cabecera
	cama.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
	glPopMatrix();

	//patas para el circulo del buro arriba 1
	glPushMatrix();
	glTranslatef(6.0, 30.0, 1.5);
	glScalef(0.2, 4.3, 1.0);
	buro.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
	glPopMatrix();


	//patas para el circulo del buro arriba 2
	glPushMatrix();
	glTranslatef(7.7, 30.0, 1.5);
	glScalef(0.2, 4.3, 1.0);
	buro.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
	glPopMatrix();


	//patas para el circulo del buro arriba 3
	glPushMatrix();
	glTranslatef(8.5, 30.0, 1.5);
	glScalef(0.2, 4.3, 1.0);
	buro.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
	glPopMatrix();



	//patas para el circulo del buro arriba 4
	glPushMatrix();
	glTranslatef(10.0, 30.0, 1.5);
	glScalef(0.2, 4.3, 1.0);
	buro.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
	glPopMatrix();

	//patas para el circulo del buro abajo 1
	glPushMatrix();
	glTranslatef(6.0, 25.2, 1.5);
	glScalef(0.2, 3.2, 1.0);
	buro.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
	glPopMatrix();


	//patas para el circulo del buro abajo 2
	glPushMatrix();
	glTranslatef(7.7, 25.2, 1.5);
	glScalef(0.2, 3.2, 1.0);
	buro.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
	glPopMatrix();


	//patas para el circulo del buro abajo 3
	glPushMatrix();
	glTranslatef(8.5, 25.2, 1.5);
	glScalef(0.2, 3.2, 1.0);
	buro.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
	glPopMatrix();


	//patas para el circulo del buro abajo 4
	glPushMatrix();
	glTranslatef(10.0, 25.2, 1.5);
	glScalef(0.2, 3.2, 1.0);
	buro.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
	glPopMatrix();


	//dibujamos la cabecera PARTE DE ARRIBA del buro

	glPushMatrix();
	glTranslatef(8.0, 32.5, 1.5);
	glScalef(6.25, 0.5, 1.0);  //Tama�o de cabecera
	buro.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
	glPopMatrix();

	//base arriba
	glPushMatrix();
	glTranslatef(8.0, 14.4, 5.0);
	glScalef(10.0, 0.3, 6.0);
	buro.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
	glPopMatrix();



	//tablita de enmedio entre cajones nivel3 izq
	glPushMatrix();
	glTranslatef(5.0, 10.5, 5.0);
	glScalef(4.0, 1.0, 6.0);
	buro.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
	glPopMatrix();



	//tablita de enmedio entre cajones nivel2 izq
	glPushMatrix();
	glTranslatef(5.0, 6.5, 5.0);
	glScalef(4.0, 1.0, 6.0);
	buro.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
	glPopMatrix();


	//tablita de enmedio entre cajones nivel1 izq

	glPushMatrix();
	glTranslatef(5.0, 2.5, 5.0);
	glScalef(4.0, 1.0, 6.0);
	buro.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
	glPopMatrix();

	//tablita de enmedio entre cajones nivel3 der
	glPushMatrix();
	glTranslatef(10.5, 10.5, 5.0);
	glScalef(5.0, 1.0, 6.0);
	buro.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
	glPopMatrix();



	//tablita de enmedio entre cajones nivel2 der
	glPushMatrix();
	glTranslatef(10.5, 6.5, 5.0);
	glScalef(5.0, 1.0, 6.0);
	buro.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
	glPopMatrix();


	//tablita de enmedio entre cajones nivel1 der
	glPushMatrix();
	glTranslatef(10.5, 2.5, 5.0);
	glScalef(5.0, 1.0, 6.0);
	buro.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
	glPopMatrix();


	//parte sup  nivel3 tabla enfrente izq
	glPushMatrix();
	glTranslatef(5.0, 12.0, 7.75);
	glScalef(4.0, 4.5, 0.5);
	buro.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
	glPopMatrix();

	//parte sup  nivel2 tabla enfrente izq
	glPushMatrix();
	glTranslatef(5.0, 8.0, 7.75);
	glScalef(4.0, 4.0, 0.5);
	buro.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
	glPopMatrix();

	//parte sup  nivel1 tabla enfrente izq
	glPushMatrix();
	glTranslatef(5.0, 4.0, 7.75);
	glScalef(4.0, 4.0, 0.5);
	buro.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
	glPopMatrix();


	//parte sup  nivel3 tabla enfrente der
	glPushMatrix();
	glTranslatef(10.5, 12.0, 7.75);
	glScalef(5.0, 4.5, 0.5);
	buro.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
	glPopMatrix();

	//parte sup  nivel2 tabla enfrente der
	glPushMatrix();
	glTranslatef(10.5, 8.0, 7.75);
	glScalef(5.0, 4.0, 0.5);
	buro.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
	glPopMatrix();

	//parte sup  nivel1 tabla enfrente der
	glPushMatrix();
	glTranslatef(10.5, 4.0, 7.75);
	glScalef(5.0, 4.0, 0.5);
	buro.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
	glPopMatrix();

	//parte inf nivel3 tabla para jalar izq
	glPushMatrix();
	glTranslatef(5.0, 11.5, 8.25);
	glScalef(2.0, 1.0, 0.5);
	buro.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
	glPopMatrix();

	//parte inf nivel2 tabla para jalar izq
	glPushMatrix();
	glTranslatef(5.0, 7.5, 8.25);
	glScalef(2.0, 1.0, 0.5);
	buro.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
	glPopMatrix();

	//parte sup  nivel1 tabla para jalar izq
	glPushMatrix();
	glTranslatef(5.0, 3.5, 8.25);
	glScalef(2.0, 1.0, 0.5);
	buro.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
	glPopMatrix();


	//parte inf nivel3 tabla para jalar der
	glPushMatrix();
	glTranslatef(10.5, 11.5, 8.25);
	glScalef(2.0, 1.0, 0.5);
	buro.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
	glPopMatrix();

	//parte inf nivel2 tabla para jalar der
	glPushMatrix();
	glTranslatef(10.5, 7.5, 8.25);
	glScalef(2.0, 1.0, 0.5);
	buro.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
	glPopMatrix();

	//parte sup  nivel1 tabla para jalar der
	glPushMatrix();
	glTranslatef(10.5, 3.5, 8.25);
	glScalef(2.0, 1.0, 0.5);
	buro.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
	glPopMatrix();
	glPopMatrix();
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //repisa o buro 

   

			//buro der
			glPushMatrix();
			glTranslatef(-37.5, -3.0, -38.0);
			glScalef(1.0, 10.5, 6.0);
			buro.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
			glPopMatrix();

			// buro pared izq
			glPushMatrix();
			glTranslatef(-30.5, -3.0, -38.0);
			glScalef(1.0, 10.5, 6.0);
			buro.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
			glPopMatrix();


			//pared atras
			glPushMatrix();
			glTranslatef(-34.0, -2.0, -40.5);
			glScalef(6.0, 8.5, 1.0);
			buro.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
			glPopMatrix();

			//base

			glPushMatrix();
			glTranslatef(-34.0, -7.0, -38.0);
			glScalef(6.0, 2.0, 6.0);
			buro.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
			glPopMatrix();

			//tabla enmedio del cajon 2

			glPushMatrix();
			glTranslatef(-34.0, -2.0, -38.0);
			glScalef(6.0, 0.5, 5.);
			buro.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
			glPopMatrix();

			// tabla de hasta arriba

				glPushMatrix();
			glTranslatef(-34.0, 2.0, -38.0);
			glScalef(6.0, 0.15, 6.);
			buro.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
			glPopMatrix();

			//parte sup  nivel2 tabla enfrente izq
			glPushMatrix();
			glTranslatef(-34.0, 0.0, -35.25);
			glScalef(6.0, 4.0, 0.5);
			buro.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
			glPopMatrix();

			//parte sup  nivel1 tabla enfrente izq
			glPushMatrix();
			glTranslatef(-34.0, -4.0, -35.25);
			glScalef(6.0, 4.0, 0.5);
			buro.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
			glPopMatrix();

			
			//parte inf nivel2 tabla para jalar izq
			glPushMatrix();
			glTranslatef(-34.0, 0.0, -35.);
			glScalef(2.0, 1.0, 0.5);
			buro.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
			glPopMatrix();

			//parte sup  nivel1 tabla para jalar izq
			glPushMatrix();
			glTranslatef(-34.0, -4, -35.);
			glScalef(2.0, 1.0, 0.5);
			buro.prisma(1.0, 1.0, 1.0, t_negro.GLindex);
			glPopMatrix();


}

void libros( void){
	//	glPushMatrix();
	//		glTranslatef(-1,-8,25);
	//		cubo.prisma(1,2,2, textLibroCG.GLindex);
	//	glPopMatrix();

	//	glPushMatrix();
	//		glRotatef(30, 0,1,0);
	//		glTranslatef(-10,-8,25);
			//cubo.prisma(.7,2,2, textPB.GLindex);
//	glPopMatrix();
//	return;
}

//END CASA////////////////////////////////////





GLuint createDL() 
{
	GLuint ciudadDL;
	//GLuint cieloDL;

	// Create the id for the list
	ciudadDL = glGenLists(1);
	// start list
	glNewList(ciudadDL,GL_COMPILE);
	// call the function that contains 
	// the rendering commands
		ciudad();
		//monito();
	// endList
	glEndList();

	return(ciudadDL);
}
			
void InitGL ( GLvoid )     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo	

	glEnable(GL_TEXTURE_2D);

	glShadeModel (GL_SMOOTH);

	glLightfv(GL_LIGHT1, GL_POSITION, Position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

    
    text1.LoadBMP("01.bmp");
	text1.BuildGLTexture();
	text1.ReleaseImage();

	text2.LoadBMP("logopumas.bmp");
	text2.BuildGLTexture();
	text2.ReleaseImage();

	text3.LoadTGA("city/arrow.tga");
	text3.BuildGLTexture();
	text3.ReleaseImage();

	text4.LoadTGA("city/pavimento.tga");
	text4.BuildGLTexture();
	text4.ReleaseImage();

	text5.LoadTGA("city/pasto01.tga");
	text5.BuildGLTexture();
	text5.ReleaseImage();

	text6.LoadTGA("city/casa01.tga");
	text6.BuildGLTexture();
	text6.ReleaseImage();


	//NEW////////////////////////////////////////////

	textMesa.LoadBMP("casa/wood_5.bmp");
	textMesa.BuildGLTexture();
	textMesa.ReleaseImage();

	textPata.LoadBMP("casa/brick_3.bmp");
	textPata.BuildGLTexture();
	textPata.ReleaseImage();

	textWall.LoadBMP("casa/brick_2.bmp");
	textWall.BuildGLTexture();
	textWall.ReleaseImage();

	textSilla.LoadBMP("casa/madera.bmp");
	textSilla.BuildGLTexture();
	textSilla.ReleaseImage();
	
	textTecho.LoadBMP("casa/brick_3.bmp");
	textTecho.BuildGLTexture();
	textTecho.ReleaseImage();

	textMarble.LoadBMP("casa/marble_2.bmp");
	textMarble.BuildGLTexture();
	textMarble.ReleaseImage();

	textPiso.LoadBMP("casa/floor-parquet.bmp");
	textPiso.BuildGLTexture();
	textPiso.ReleaseImage();

	textGlassWasser.LoadBMP("casa/glass_2.bmp");
	textGlassWasser.BuildGLTexture();
	textGlassWasser.ReleaseImage();

	textBarrote.LoadBMP("casa/brickwall.bmp");
	textBarrote.BuildGLTexture();
	textBarrote.ReleaseImage();

	textCuadro1.LoadBMP("casa/cuadro_1.bmp");
	textCuadro1.BuildGLTexture();
	textCuadro1.ReleaseImage();

	textMarco.LoadBMP("casa/burned wood.bmp");
	textMarco.BuildGLTexture();
	textMarco.ReleaseImage();

	textLibroCG.LoadBMP("casa/gc_donald.bmp");
	textLibroCG.BuildGLTexture();
	textLibroCG.ReleaseImage();

	textPuerta.LoadBMP("casa/door_3.bmp");
	textPuerta.BuildGLTexture();
	textPuerta.ReleaseImage();

	textPuerta_princ.LoadBMP("casa/door_3_4_puerta.bmp");
	textPuerta_princ.BuildGLTexture();
	textPuerta_princ.ReleaseImage();

	textMarco_1.LoadBMP("casa/door_3_1_izq.bmp");
	textMarco_1.BuildGLTexture();
	textMarco_1.ReleaseImage();

	textMarco_2.LoadBMP("casa/door_3_2_der.bmp");
	textMarco_2.BuildGLTexture();
	textMarco_2.ReleaseImage();

	textMarco_3.LoadBMP("casa/door_3_3_cen.bmp");
	textMarco_3.BuildGLTexture();
	textMarco_3.ReleaseImage();

	textGrass.LoadBMP("casa/grass_2.bmp");
	textGrass.BuildGLTexture();
	textGrass.ReleaseImage();

	textSky.LoadBMP("casa/blue-sky-texture.bmp");
	textSky.BuildGLTexture();
	textSky.ReleaseImage();

	textLibrero.LoadBMP("casa/strata.bmp");
	textLibrero.BuildGLTexture();
	textLibrero.ReleaseImage();

	textGW.LoadBMP("casa/glass window.bmp");
	textGW.BuildGLTexture();
	textGW.ReleaseImage();

	t_fachada1.LoadTGA("fachada1.tga");
	t_fachada1.BuildGLTexture();
	t_fachada1.ReleaseImage();

	t_fachada2.LoadTGA("fachada2.tga");
	t_fachada2.BuildGLTexture();
	t_fachada2.ReleaseImage();


	t_fachada3.LoadTGA("fachada3.tga");
	t_fachada3.BuildGLTexture();
	t_fachada3.ReleaseImage();

	t_fachada4.LoadTGA("fachada4.tga");
	t_fachada4.BuildGLTexture();
	t_fachada4.ReleaseImage();

	t_fachada5.LoadTGA("fachada5.tga");
	t_fachada5.BuildGLTexture();
	t_fachada5.ReleaseImage();

	t_piso1.LoadTGA("piso1.tga");
	t_piso1.BuildGLTexture();
	t_piso1.ReleaseImage();

	t_piso2.LoadTGA("piso2.tga");
	t_piso2.BuildGLTexture();
	t_piso2.ReleaseImage();

	t_piso3.LoadTGA("piso3.tga");
	t_piso3.BuildGLTexture();
	t_piso3.ReleaseImage();

	t_piso4.LoadTGA("piso4.tga");
	t_piso4.BuildGLTexture();
	t_piso4.ReleaseImage();

	t_paredgris1.LoadTGA("paredgris1.tga");
	t_paredgris1.BuildGLTexture();
	t_paredgris1.ReleaseImage();

	t_paredgris2.LoadTGA("paredgris2.tga");
	t_paredgris2.BuildGLTexture();
	t_paredgris2.ReleaseImage();


	t_paredamarilla.LoadTGA("paredamarilla.tga");
	t_paredamarilla.BuildGLTexture();
	t_paredamarilla.ReleaseImage();

	t_parednaranja.LoadTGA("parednaranja.tga");
	t_parednaranja.BuildGLTexture();
	t_parednaranja.ReleaseImage();

	t_cascada.LoadTGA("cascada.tga");
	t_cascada.BuildGLTexture();
	t_cascada.ReleaseImage();


	t_techo2.LoadTGA("techo2.tga");
	t_techo2.BuildGLTexture();
	t_techo2.ReleaseImage();

	t_ven.LoadTGA("ven.tga");
	t_ven.BuildGLTexture();
	t_ven.ReleaseImage();


	t_ven2.LoadTGA("ven2.tga");
	t_ven2.BuildGLTexture();
	t_ven2.ReleaseImage();

	t_ven3.LoadTGA("ven3.tga");
	t_ven3.BuildGLTexture();
	t_ven3.ReleaseImage();

	t_vidrioverde.LoadTGA("vidrioverde.tga");
	t_vidrioverde.BuildGLTexture();
	t_vidrioverde.ReleaseImage();

	t_vidrioa.LoadTGA("vidrioa.tga");
	t_vidrioa.BuildGLTexture();
	t_vidrioa.ReleaseImage();


	t_vidrioa2.LoadTGA("vidrioa2.tga");
	t_vidrioa2.BuildGLTexture();
	t_vidrioa2.ReleaseImage();

	t_puertaentrada.LoadTGA("puertaentrada.tga");
	t_puertaentrada.BuildGLTexture();
	t_puertaentrada.ReleaseImage();

	t_puertaentrada2.LoadTGA("puertaentrada2.tga");
	t_puertaentrada2.BuildGLTexture();
	t_puertaentrada2.ReleaseImage();

	t_ladrillo.LoadTGA("ladrillo.tga");
	t_ladrillo.BuildGLTexture();
	t_ladrillo.ReleaseImage();

	t_negro.LoadTGA("negro.tga");
	t_negro.BuildGLTexture();
	t_negro.ReleaseImage();

	t_noticia1.LoadTGA("noticia1.tga");
	t_noticia1.BuildGLTexture();
	t_noticia1.ReleaseImage();

	t_noticiero.LoadTGA("noticiero.tga");
	t_noticiero.BuildGLTexture();
	t_noticiero.ReleaseImage();

	t_bordeblanco.LoadTGA("bordeblanco.tga");
	t_bordeblanco.BuildGLTexture();
	t_bordeblanco.ReleaseImage();


	t_puerta1.LoadTGA("puerta1.tga");
	t_puerta1.BuildGLTexture();
	t_puerta1.ReleaseImage();

	t_tazon.LoadTGA("tazon.tga");
	t_tazon.BuildGLTexture();
	t_tazon.ReleaseImage();



	
	//*****ROSE******
	textAlmohada.LoadBMP("casa/almohada.bmp");
	textAlmohada.BuildGLTexture();
	textAlmohada.ReleaseImage();

	textColcha.LoadBMP("casa/colcha.bmp");
	textColcha.BuildGLTexture();
	textColcha.ReleaseImage();

	textMaderaBuro.LoadBMP("casa/buro.bmp");
	textMaderaBuro.BuildGLTexture();
	textMaderaBuro.ReleaseImage();

	textMaderaCama.LoadBMP("casa/maderaCama.bmp");
	textMaderaCama.BuildGLTexture();
	textMaderaCama.ReleaseImage();

	textLampara.LoadBMP("casa/lampara.bmp");
	textLampara.BuildGLTexture();
	textLampara.ReleaseImage();

	textLaptop.LoadBMP("casa/laptop.bmp");
	textLaptop.BuildGLTexture();
	textLaptop.ReleaseImage();

	textPantalla.LoadBMP("casa/windows.bmp");
	textPantalla.BuildGLTexture();
	textPantalla.ReleaseImage();

	textTeclado.LoadBMP("casa/tecla.bmp");
	textTeclado.BuildGLTexture();
	textTeclado.ReleaseImage();

	textTouchPad.LoadBMP("casa/touchpad.bmp");
	textTouchPad.BuildGLTexture();
	textTouchPad.ReleaseImage();

	//END NEW//////////////////////////////

	objCamera.Position_Camera(0,2.5f,3, 0,2.5f,0, 0, 1, 0);

	//NEW Crear una lista de dibujo
	ciudad_display_list = createDL();

	//NEW Iniciar variables de KeyFrames
	for(int i=0; i<MAX_FRAMES; i++)
	{
		KeyFrame[i].posX =0;
		KeyFrame[i].posY =0;
		KeyFrame[i].posZ =0;
		KeyFrame[i].incX =0;
		KeyFrame[i].incY =0;
		KeyFrame[i].incZ =0;
		KeyFrame[i].rotRodIzq =0;
		KeyFrame[i].rotRodDer = 0;
		KeyFrame[i].rotBraIzq = 0;
		KeyFrame[i].rotBraDer = 0;
		KeyFrame[i].rotInc =0;
		KeyFrame[i].rotInc2 = 0;
		KeyFrame[i].rotInc3 = 0;
		KeyFrame[i].rotInc4 = 0;
		KeyFrame[i].giroMonito =0;
		KeyFrame[i].giroMonitoInc =0;
	}
	//NEW//////////////////NEW//////////////////NEW///////////

}

void pintaTexto(float x, float y, float z, void *font,char *string)
{
  
  char *c;     //Almacena los caracteres a escribir
  glRasterPos3f(x, y, z);	//Posicion apartir del centro de la ventana
  //glWindowPos2i(150,100);
  for (c=string; *c != '\0'; c++) //Condicion de fin de cadena
  {
    glutBitmapCharacter(font, *c); //imprime
  }
}

void display ( void )   // Creamos la funcion donde se dibuja
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	glPushMatrix();
	

	glRotatef(g_lookupdown,1.0f,0,0);

		gluLookAt(	objCamera.mPos.x,  objCamera.mPos.y,  objCamera.mPos.z,	
					objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,	
					objCamera.mUp.x,   objCamera.mUp.y,   objCamera.mUp.z);
	

		glPushMatrix();		
			glPushMatrix(); //Creamos cielo
				glDisable(GL_LIGHTING);
				glTranslatef(0,60,0);
				fig1.skybox(130.0, 130.0, 130.0,text1.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix();
				glEnable ( GL_COLOR_MATERIAL );
					glColor3f(1, 1, 1);
					//glScalef(0.5, 0.5, 0.5);
					//monito();
					glCallList(ciudad_display_list);
					glTranslatef(posX, posY, posZ);
					glRotatef(giroMonito, 0, 1, 0);
					monito();
				glDisable ( GL_COLOR_MATERIAL );
			glPopMatrix();			

			glPushMatrix(); //Flecha
				glScalef(7,0.1,7);
				glDisable(GL_LIGHTING);
				fig3.prisma_anun(text3.GLindex, 0);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			//ventanas lavandose izq
			glPushMatrix(); 
			glTranslatef(21.45, 4.2, -4.43);
			glScalef(1.8, 4.5 , 0.01);
			glRotatef(120, 1.0f, 1.0f, 1.0f);
			glDisable(GL_LIGHTING);
			fig3.prisma_anun(t_vidrioa2.GLindex, 0);
			glEnable(GL_LIGHTING);
			glPopMatrix();


			//ventanas lavandose der
			glPushMatrix();
			glTranslatef(27.45, 4.2, -4.43);
			glScalef(1.8, 4.5, 0.01);
			glRotatef(120, 1.0f, 1.0f, 1.0f);
			glDisable(GL_LIGHTING);
			fig3.prisma_anun(t_vidrioa2.GLindex, 0);
			glEnable(GL_LIGHTING);
			glPopMatrix();



			//CASA///////////////////
			//�****casa*****
			glPushMatrix();
				glScalef(1.0, 0.5, 1.0);
				glTranslatef(30, 3, -17.2);
				glRotatef(180, 0, 1, 0);
				glDisable(GL_LIGHTING);
				glScalef(0.3, 0.3, 0.3);
					casa();
				
				glPushMatrix();
					//****cuadros***			
					cuadro();
					//****LIBROS****
					glPushMatrix();
						glTranslatef(26,11,4);
						libros();	
					glPopMatrix();
					//****COMEDOR***
					glPushMatrix();
						glTranslatef(-20,0,25);
						glScalef(1.3,1.3,1.3);
						comedor();
					glPopMatrix();
					//mesa y laptop
					glPushMatrix();
						glRotatef(90, 0,1,0);
						mesa(1,1.5,1,-25,1.4,24);
					glPopMatrix();
				
					glPushMatrix();
						glRotatef(90, 0,1,0);
						dibujaLaptop(.3,.3,.3,-90,9,77);
					glPopMatrix();

					glPushMatrix();
						glRotatef(280, 0,1,0);
						silla(1,1,1,29,0,-24.5);
					glPopMatrix();

					//*****ROSE*****
					glPushMatrix(); 
						glPushMatrix();
							glTranslatef(0,0,-0.5); 
							glRotatef(90, 0,1,0); 
							glTranslatef(2,0,-0.5);
							dibujaCama(1.1,1.1,1.1,14.0,-5.5,-37.0); 
						glPopMatrix();
						glPushMatrix();
							glRotatef(90, 0,1,0); 
							dibujaBuro(1,1,1,-2,-9.5,-42.0); 
						glPopMatrix();

						//LAMPARA DEL CENTRO
						glPushMatrix();
							glTranslatef(0,37,0);
							glScalef(3.2,1.2,3.2);
							lampara.cono(2.0,0.4,100,textLampara.GLindex);
						glPopMatrix();
					glPopMatrix();

					//sostener lampara
					glPushMatrix();
					glTranslatef(0, 38, 0);
					glScalef(0.1, 25.2, 0.1);
					lampara.cilindro(2.0, 0.4, 100, t_paredgris1.GLindex);
					glPopMatrix();
					glPopMatrix();


					//******JOAN*****
					//ropero
					glPushMatrix();
						glRotatef(180, 0,1,0);
						glTranslatef(-35,23,-35);
						glScalef(.7,.7,.7);
						ropero();
					glPopMatrix();
				glPopMatrix();

			glEnable(GL_LIGHTING);
			glPopMatrix();
					

			glColor3f(1.0,1.0,1.0);

		glPopMatrix();
	glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
			glColor3f(1.0,0.0,0.0);
			pintaTexto(-13.5,13.0,-14.0,(void *)font,"PROYECTO FINAL");
			pintaTexto(-11,8.5,-14,(void *)font,s);
			glColor3f(1.0,1.0,1.0);
		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);

	glutSwapBuffers ( );

}

void animacion()
{
	fig3.text_izq-= 0.001;
	fig3.text_der-= 0.001;
	if(fig3.text_izq<-1)
		fig3.text_izq=0;
	if(fig3.text_der<0)
		fig3.text_der=1;

	//Movimiento del monito
	if(play)
	{		
		
		if(	i_curr_steps >= i_max_steps) //end of animation between frames?
		{			
			playIndex++;		
			if(playIndex>FrameIndex-2)	//end of total animation?
			{
				printf("termina anim\n");
				playIndex=0;
				play=false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
				//Interpolation
				interpolation();

			}
		}
		else
		{
			//Draw animation
			posX+=KeyFrame[playIndex].incX;
			posY+=KeyFrame[playIndex].incY;
			posZ+=KeyFrame[playIndex].incZ;

			rotRodIzq+=KeyFrame[playIndex].rotInc;
			rotRodDer += KeyFrame[playIndex].rotInc2;
			rotBraIzq += KeyFrame[playIndex].rotInc3;
			rotBraDer += KeyFrame[playIndex].rotInc4;
			giroMonito+=KeyFrame[playIndex].giroMonitoInc;

			i_curr_steps++;
		}
		
	}


	glutPostRedisplay();
}

void reshape ( int width , int height )   // Creamos funcion Reshape
{
  if (height==0)										// Prevenir division entre cero
	{
		height=1;
	}

	glViewport(0,0,width,height);	

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista
	
	glFrustum (-0.1, 0.1,-0.1, 0.1, 0.1, 170.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}

void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{
	switch ( key ) {
		case 'w':   //Movimientos de camara
		case 'W':
			objCamera.Move_Camera( CAMERASPEED+0.2 );
			break;

		case 's':
		case 'S':
			objCamera.Move_Camera(-(CAMERASPEED+0.2));
			break;

		case 'a':
		case 'A':
			objCamera.Strafe_Camera(-(CAMERASPEED+0.4));
			break;

		case 'd':
		case 'D':
			objCamera.Strafe_Camera( CAMERASPEED+0.4 );
			break;

		case 'k':		//
		case 'K':
			if(FrameIndex<MAX_FRAMES)
			{
				saveFrame();
			}

			break;

		case 'l':						
		case 'L':
			if(play==false && (FrameIndex>1))
			{

				resetElements();
				//First Interpolation				
				interpolation();

				play=true;
				playIndex=0;
				i_curr_steps = 0;
			}
			else
			{
				play=false;
			}
			break;

		case 'y':						
		case 'Y':
			posZ++;
			printf("%f \n", posZ);
			break;

		case 'g':						
		case 'G':
			posX--;
			printf("%f \n", posX);
			break;

		case 'h':						
		case 'H':
			posZ--;
			printf("%f \n", posZ);
			break;

		case 'j':						
		case 'J':
			posX++;
			printf("%f \n", posX);
			break;

		case 'b':						
			rotRodIzq++;
			printf("%f \n", rotRodIzq);
			break;

		case 'B':						
			rotRodIzq--;
			printf("%f \n", rotRodIzq);
			break;

		case 'n':
			rotRodDer++;
			printf("%f \n", rotRodDer);
			break;

		case 'N':
			rotRodDer--;
			printf("%f \n", rotRodDer);
			break;


		case 'u':
			rotBraIzq++;
			printf("%f \n", rotBraIzq);
			break;

		case 'U':
			rotBraIzq--;
			printf("%f \n", rotBraIzq);
			break;



		case 'i':
			rotBraDer++;
			printf("%f \n", rotBraDer);
			break;

		case 'I':
			rotBraDer--;
			printf("%f \n", rotBraDer);
			break;


		case 'p':						
			giroMonito++;
			break;

		case 'P':						
			giroMonito--;
			break;

		case 27:        // Cuando Esc es presionado...
			exit ( 0 );   // Salimos del programa
			break;        
		default:        // Cualquier otra
			break;
  }

  glutPostRedisplay();
}

void arrow_keys ( int a_keys, int x, int y )  // Funcion para manejo de teclas especiales (arrow keys)
{
  switch ( a_keys ) {
	case GLUT_KEY_PAGE_UP:
		objCamera.UpDown_Camera(CAMERASPEED);
		break;

	case GLUT_KEY_PAGE_DOWN:
		objCamera.UpDown_Camera(-CAMERASPEED);
		break;

    case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
		g_lookupdown -= 1.0f;
		break;

    case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
		g_lookupdown += 1.0f;
		break;

	case GLUT_KEY_LEFT:
		objCamera.Rotate_View(-CAMERASPEED);
		break;

	case GLUT_KEY_RIGHT:
		objCamera.Rotate_View( CAMERASPEED);
		break;

    default:
		break;
  }
  glutPostRedisplay();
}

void menuKeyFrame( int id)
{
	switch (id)
	{
		case 0:	//Save KeyFrame
			if(FrameIndex<MAX_FRAMES)
			{
				saveFrame();
			}
			break;

		case 1:	//Play animation
			if(play==false && FrameIndex >1)
			{

				resetElements();
				//First Interpolation
				interpolation();

				play=true;
				playIndex=0;
				i_curr_steps = 0;
			}
			else
			{
				play=false;
			}
			break;


	}
}


void menu( int id)
{
	
}



int main ( int argc, char** argv )   // Main Function
{
  int submenu;
  glutInit            (&argc, argv); // Inicializamos OpenGL
  glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
  glutInitWindowSize  (500, 500);	// Tama�o de la Ventana
  glutInitWindowPosition (0, 0);	//Posicion de la Ventana
  glutCreateWindow    ("Proyecto final"); // Nombre de la Ventana
  //glutFullScreen     ( );         // Full Screen
  InitGL ();						// Parametros iniciales de la aplicacion
  glutDisplayFunc     ( display );  //Indicamos a Glut funci�n de dibujo
  glutReshapeFunc     ( reshape );	//Indicamos a Glut funci�n en caso de cambio de tamano
  glutKeyboardFunc    ( keyboard );	//Indicamos a Glut funci�n de manejo de teclado
  glutSpecialFunc     ( arrow_keys );	//Otras
  glutIdleFunc		  ( animacion );

  submenu = glutCreateMenu	  ( menuKeyFrame );
  glutAddMenuEntry	  ("Guardar KeyFrame", 0);
  glutAddMenuEntry	  ("Reproducir Animacion", 1);
  glutCreateMenu	  ( menu );
  glutAddSubMenu	  ("Animacion Monito", submenu);
 
  glutAttachMenu	  (GLUT_RIGHT_BUTTON);


  glutMainLoop        ( );          // 

  return 0;
}