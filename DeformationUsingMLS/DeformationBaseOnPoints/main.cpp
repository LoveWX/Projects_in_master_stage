#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/GLAux.h>
#include <gl/glut.h>
#include <iostream>
#include <vector>

#include "mObject.h"
#include "theDefinition.h"
#include "AffineDeformationFast.h"
#include "SimilarityDeformationFast.h"
#include "RigidDeformationFast.h"

//#pragma comment(lib, "openGL32.lib");
//#pragma comment(lib, "glu32.lib");
//#pragma comment(lib, "glaux.lib"); 

using namespace std;

int row,column;
int numOfControlPoint;
vector<Point> myOldControlPoint,myNewControlPoint,mycommonPoint;
vector<Point> printAffinePoint,printSimilarityPoint,printRigidPoint;

int screenWidth = 600;
int screenHeight = 600;

mVert meshPoint[100][100];
int initMark = 0;

void SaveasImage()
{
	FILE*    pDummyFile;
	FILE*    pWritingFile;
	GLubyte* pPixelData;
	GLubyte  BMP_Header[54];
	GLint    i, j;
	GLint    PixelDataLength;
	
	int WindowWidth=600;
	int WindowHeight=600;
	
	// �����������ݵ�ʵ�ʳ���
	i = WindowWidth * 3;   // �õ�ÿһ�е��������ݳ���
	while( i%4 != 0 )      // �������ݣ�ֱ��i�ǵı���
		++i;               // �������и�����㷨��
	// �������׷��ֱ�ۣ����ٶ�û��̫��Ҫ��
	PixelDataLength = i * WindowHeight;
	
	// �����ڴ�ʹ��ļ�
	pPixelData = (GLubyte*)malloc(PixelDataLength);
	if( pPixelData == 0 )
		exit(0);
	
	pDummyFile = fopen("bmphead.bmp", "rb");
	if( pDummyFile == 0 )
		exit(0);
	
	pWritingFile = fopen("result.bmp", "wb");
	if( pWritingFile == 0 )
		exit(0);
	
	// ��ȡ����
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glReadPixels(0, 0, WindowWidth, WindowHeight,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, pPixelData);
	
	// ��dummy.bmp���ļ�ͷ����Ϊ���ļ����ļ�ͷ
	fread(BMP_Header, sizeof(BMP_Header), 1, pDummyFile);
	fwrite(BMP_Header, sizeof(BMP_Header), 1, pWritingFile);
	fseek(pWritingFile, 0x0012, SEEK_SET);
	i = WindowWidth;
	j = WindowHeight;
	fwrite(&i, sizeof(i), 1, pWritingFile);
	fwrite(&j, sizeof(j), 1, pWritingFile);
	
	// д����������
	fseek(pWritingFile, 0, SEEK_END);
	fwrite(pPixelData, PixelDataLength, 1, pWritingFile);
	
	// �ͷ��ڴ�͹ر��ļ�
	fclose(pDummyFile);
	fclose(pWritingFile);
	free(pPixelData);
	
}

void ChangePointIntoMeshPoint(vector<Point> &toPrintPoint)
{
	int i,j,index=0;
	for(i=0;i<row;i++)
	{
		for(j=0;j<column;j++)
		{
			meshPoint[i][j].X=toPrintPoint[index].xx*0.5-25;
			meshPoint[i][j].Y=toPrintPoint[index].yy*0.5-25;
			meshPoint[i][j].Z=0.0;
			index++;
		}
	}
}

//�����ʼ��
void InitMesh()
{
	ChangePointIntoMeshPoint(mycommonPoint);

	initMark = 1; //��ʼ���ɹ����Ϊ1
	cout<<"�����ʼ���ɹ� "<<endl;
}

void DeformMeshAffine()
{
	ChangePointIntoMeshPoint(printAffinePoint);
	cout<<"Affine Points Deformation"<<endl;
}

void DeformMeshSimilarity()
{
	ChangePointIntoMeshPoint(printSimilarityPoint);
	cout<<"Similarity Points Deformation"<<endl;
}

void DeformMeshRigid()
{
	ChangePointIntoMeshPoint(printRigidPoint);
	cout<<"Rigid Points Deformation"<<endl;
}

void DrawMesh()//������
{
	int i,j;
	glColor3f(0.0, 0.5, 0.5);
	for (i=0; i<100; i++)
	{
		for (j=0; j<99; j++)
		{
			glBegin(GL_LINE_LOOP);
			glVertex3f(meshPoint[i][j].X, meshPoint[i][j].Y, 0);
			glVertex3f(meshPoint[i][j+1].X, meshPoint[i][j+1].Y, 0);		
			glEnd();
		}
	}

	glColor3f(0.0, 0.5, 0.5);
	for (i=0; i<99; i++)
	{
		for (j=0; j<100; j++)
		{
			glBegin(GL_LINE_LOOP);
			glVertex3f(meshPoint[i][j].X, meshPoint[i][j].Y, 0);
			glVertex3f(meshPoint[i+1][j].X, meshPoint[i+1][j].Y, 0);		
			glEnd();
		}
	}

	glColor3f(0.0, 0.5, 0.5);
	for (i=0; i<100; i++)
	{
		for (j=0; j<100; j++)
		{
			glPointSize(2.0);
			glBegin(GL_POINTS);
			glVertex3f(meshPoint[i][j].X, meshPoint[i][j].Y, 0);
			glEnd();
		}
	}
}

void displayEveryCrossCurve()
{
	glClearColor(1.0,1.0,1.0,0.0);
	//initLight();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);       //clear the screen
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);//�ر�����ӳ��ģʽ

	glEnable(GL_LINE_STIPPLE);//����㻮��ģʽ
	DrawMesh();
	glDisable(GL_LINE_STIPPLE);//�رյ㻮��ģʽ

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_TEXTURE_2D);
	/* ����������������弸������ */
	if (initMark == 1)
	{
		for (int i=0; i<99; i++)
		{
			for (int j=0; j<99; j++)
			{
				//glBegin(GL_QUADS);
				//glTexCoord2f(i*0.05, j*0.05); glVertex3f(-5.0+i*0.5, -5.0+j*0.5, 0.0);
				//glTexCoord2f(i*0.05,(j+1)*0.05); glVertex3f(-5.0+i*0.5, -5.0+(j+1)*0.5, 0.0);
				//glTexCoord2f((i+1)*0.05, (j+1)*0.05); glVertex3f(-5.0+(i+1)*0.5, -5.0+(j+1)*0.5, 0.0);
				//glTexCoord2f((i+1)*0.05, j*0.05); glVertex3f(-5+(i+1)*0.5, -5.0+j*0.5, 0.0);
				//glEnd();
				glBegin(GL_QUADS);
				glTexCoord2f(i*0.01, j*0.01); glVertex3f(meshPoint[i][j].X, meshPoint[i][j].Y, 0.0); //(-5.0+i*0.5, -5.0+j*0.5, 0.0);
				glTexCoord2f(i*0.01,(j+1)*0.01); glVertex3f(meshPoint[i][j+1].X, meshPoint[i][j+1].Y, 0.0); //(-5.0+i*0.5, -5.0+(j+1)*0.5, 0.0);
				glTexCoord2f((i+1)*0.01, (j+1)*0.01); glVertex3f(meshPoint[i+1][j+1].X, meshPoint[i+1][j+1].Y, 0.0); //(-5.0+(i+1)*0.5, -5.0+(j+1)*0.5, 0.0);
				glTexCoord2f((i+1)*0.01, j*0.01); glVertex3f(meshPoint[i+1][j].X, meshPoint[i+1][j].Y, 0.0); //(-5+(i+1)*0.5, -5.0+j*0.5, 0.0);
				glEnd();
			}
		}
	}
	for (int i=0; i<19; i++)
	{
		for (int j=0; j<19; j++)
		{
			//glBegin(GL_QUADS);
			//glTexCoord2f(i*0.05, j*0.05); glVertex3f(-5.0+i*0.5, -5.0+j*0.5, 0.0);
			//glTexCoord2f(i*0.05,(j+1)*0.05); glVertex3f(-5.0+i*0.5, -5.0+(j+1)*0.5, 0.0);
			//glTexCoord2f((i+1)*0.05, (j+1)*0.05); glVertex3f(-5.0+(i+1)*0.5, -5.0+(j+1)*0.5, 0.0);
			//glTexCoord2f((i+1)*0.05, j*0.05); glVertex3f(-5+(i+1)*0.5, -5.0+j*0.5, 0.0);
			//glEnd();
		}
	}
	//glBegin(GL_QUADS);
	//glTexCoord2f(0.4, 0.4); glVertex3f(-5.0, -5.0, 0.0);
	//glTexCoord2f(0.4, 0.5); glVertex3f(-5.0, 5.0, 0.0);
	//glTexCoord2f(0.5, 0.5); glVertex3f(5.0, 5.0, 0.0);
	//glTexCoord2f(0.5, 0.4); glVertex3f(5.0, -5.0, 0.0);
	//glEnd();

	//glDisable(GL_TEXTURE_2D);

	
	glFlush();
	//glutSwapBuffers();
}

int g_width, g_height;
void reshape_2d(int w, int h)
{
	g_width = w;
	g_height = h;

	glMatrixMode(GL_PROJECTION);  // Set "camera shape"
	glLoadIdentity();
	glViewport(0, 0, (GLsizei) g_width, (GLsizei) g_height);

	//if (model_view_mark == 1)
	//{
	//	gluPerspective(60.0f,1.0,1.0f,100);
	//}
	//GLdouble aspect_ratio = (GLdouble) w / (GLdouble) h;

	GLdouble aspect_ratio = (GLdouble) h / (GLdouble) w;
	GLdouble nRange = 30.0;
	if(w<=h)
		glOrtho(-nRange,nRange,-nRange*aspect_ratio,nRange*aspect_ratio,-2, 2);
	else
		glOrtho(-nRange*aspect_ratio,nRange*aspect_ratio,-nRange,nRange,-2, 2);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GLfloat light_position[] = {100.0f,100.0f,100.0f,1.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

/* �������� */
#define ImageWidth 64
#define ImageHeight 64
GLubyte Image[ImageWidth][ImageHeight][3];

void makeImage(void)
{
	int i, j, r,g,b;

	for (i = 0; i < ImageWidth; i++)
	{
		for (j = 0; j < ImageHeight; j++)
		{
			r=(i*j)%255;
			g=(4*i)%255;
			b=(4*j)%255;
			Image[i][j][0] = (GLubyte) r;
			Image[i][j][1] = (GLubyte) g;
			Image[i][j][2] = (GLubyte) b;
		}
	}
}

//װ��λͼ�ļ�
AUX_RGBImageRec * LoadBitmap(char *Filename)
{
	//����һ���ļ�������ڴ��ļ�
	FILE *imageFile = NULL;

	//�ļ�������Ϊ��
	if (!Filename)
	{
		return NULL;
	}

	//��ֻ���ķ�ʽ���ļ�,�������ļ��Ƿ����
	imageFile = fopen(Filename, "r"); // Check To See If The File Exists

	if (imageFile)
	{
		//���ڣ���ر��ļ�
		fclose(imageFile);         //Close The Handle
		//װ������Ѵ��ڵ��ļ�    
		return auxDIBImageLoad(Filename); //Load the Bitmap and Return A pointer
	}

	//�ļ�װ��ʧ�ܣ�����NULL
	return NULL;
}

int LoadTexture()
{
	int Status = FALSE;

	//������������ݽṹ��������glaux.h��
	AUX_RGBImageRec *pTextureImage = NULL; //Create Storage Space For The Texture

	//����pTextureImage�ڲ���Ա������
	//memset(pTextureImage, 0, sizeof(AUX_RGBImageRec)); //Set the Pointer to Null

	if (pTextureImage=LoadBitmap("1.bmp"))
	{
		Status = TRUE;

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pTextureImage->sizeX, pTextureImage->sizeY, 
			         0, GL_RGB, GL_UNSIGNED_BYTE, pTextureImage->data);

		//�ظ��ͽ�ȡ
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

		//ָ���˲���ʽ
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	}

	if (pTextureImage)
	{
		if (pTextureImage->data)
		{
			free(pTextureImage->data);
		}
		free(pTextureImage);
	}

	return Status;  //return the status
}

void init3d(void)
{
	glClearColor(0.0,0.0,0.0,1.0); // Set white background color
	//glColor3f(0.0f,0.0f,0.0f);    // Drawing color is black

	GLfloat mat_specular[]={1.0, 1.0, 0.0, 1.0};
	GLfloat mat_shininess[]={ 128 };
	GLfloat ambientLight[]={0.5f,0.0f,0.0f,1.0f};
	GLfloat diffuseLight[]={0.7f,0.7f,0.7f,1.0f};
	GLfloat lightPos[]={100.0f,100.0f,100.0f,1.0f};

	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
	glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);

	glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);
	glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambientLight);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
	//glColorMaterial(GL_BACK,GL_AMBIENT_AND_DIFFUSE);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	//��������
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	makeImage();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	/* �������� */
	glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth,
		ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, &Image[0][0][0]);

	/* �����˲� */
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	/* ˵��ӳ�䷽ʽ*/
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	/* ��������ӳ�� */
	glEnable(GL_TEXTURE_2D);

	glShadeModel(GL_FLAT);

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);
}

void myInit(void)
{
	glClearColor(0.0,0.0,0.0,1.0); // Set white background color
	//glColor3f(0.0f,0.0f,0.0f);    // Drawing color is black

	GLfloat mat_specular[]={1.0, 1.0, 1.0, 1.0};
	GLfloat mat_shininess[]={ 128 };
	GLfloat ambientLight[]={0.5f,0.5f,0.5f,1.0f};
	GLfloat diffuseLight[]={0.7f,0.7f,0.7f,1.0f};
	GLfloat lightPos[]={100.0f,100.0f,100.0f,1.0f};

	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
	glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);


	glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);
	glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambientLight);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
	glColorMaterial(GL_BACK,GL_AMBIENT_AND_DIFFUSE);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	//��������
	LoadTexture();
	glEnable(GL_TEXTURE_2D); //Enable texture Mapping
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
   // glEnable(GL_CULL_FACE);
}

void printInputInfo()
{
	cout<<endl;
	cout<<"�����ļ�in.txt��ʽ���£�"<<endl;
	cout<<"��һ��2��int������,��ʾ����ĸߺͿ�"<<endl
		<<"�ڶ���1��int������n,��ʾ�ؼ���ĸ���"<<endl
		<<"������n��ÿ��4��int������:x0,y0,x1,y1,��ʾ�ؼ���(x0,y0)�α������λ��Ϊ(x1,y1)"<<endl;
}

void keyboard_planeCrossDesign(unsigned char key, int x,int y)
{
	switch(key)
	{
	case 'i':
	case 'I':
		InitMesh();
		glutPostRedisplay();
		break;
	case 'j':
	case 'J':
		DeformMeshAffine();
		glutPostRedisplay();
		break;
	case 'k':
	case 'K':
		DeformMeshSimilarity();
		glutPostRedisplay();
		break;
	case 'l':
	case 'L':
		DeformMeshRigid();
		glutPostRedisplay();
		break;
	case 's':
	case 'S':
		SaveasImage();
		break;
	case 'h':
	case 'H':
		printInputInfo();
		break;
	default:
		break;
	}
}

void mouse(int button, int state, int mouse_x, int mouse_y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		glutPostRedisplay();
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{

	}
}

void printInfo()
{
	cout<<"��ӭʹ�û����ƶ���С���˵��α����"<<endl;
	cout<<"�����ʹ�������ļ�in.txt�еĵ�λ����Ϣ�����α�"<<endl
		<<"�����ļ������ݸ�ʽ������'h'���в鿴"<<endl;
	cout<<endl;
	cout<<"ʹ�÷���:���Ȱ�'i'����ʼ��������ʹ�ð���'j''k''l'�鿴���ַ����Ľ��"<<endl;

	cout<<"����'i':��ʼ������"<<endl;
	cout<<"����'j':��ʾ����任���"<<endl;
	cout<<"����'k':��ʾ���Ʊ任���"<<endl;
	cout<<"����'l':��ʾ���Ա任���"<<endl;
	cout<<"����'s':���浱ǰ���Ϊresult.bmp�ļ�"<<endl;
	cout<<"����'h':��ʾ�����ļ������ݸ�ʽ"<<endl;
}

void main(int argc, char** argv)
{
	int i,j;
	Point tp1,tp2;
	scanf("%d%d",&row,&column);
	scanf("%d",&numOfControlPoint);
	for(i=0;i<numOfControlPoint;i++)
	{
		scanf("%lf%lf%lf%lf",&tp1.xx,&tp1.yy,&tp2.xx,&tp2.yy);
		myOldControlPoint.push_back(tp1);
		myNewControlPoint.push_back(tp2);
	}
	mycommonPoint.clear();
	for(i=0;i<row;i++)
	{
		for(j=0;j<column;j++)
		{
			Point tempPoint;
			tempPoint.xx=i;
			tempPoint.yy=j;
			mycommonPoint.push_back(tempPoint);
		}
	}

	AffineDeformationFast myAffineDeformation(myOldControlPoint);
	myAffineDeformation.UpdateControlPoint(myNewControlPoint);
	myAffineDeformation.UpdateCommonPoint(mycommonPoint);
	myAffineDeformation.getResultofCommonPoint(printAffinePoint);
	SimilarityDeformationFast mySimilarityDeformation(myOldControlPoint);
	mySimilarityDeformation.UpdateControlPoint(myNewControlPoint);
	mySimilarityDeformation.UpdateCommonPoint(mycommonPoint);
	mySimilarityDeformation.getResultofCommonPoint(printSimilarityPoint);
	RigidDeformationFast myRigidDeformation(myOldControlPoint);
	myRigidDeformation.UpdateControlPoint(myNewControlPoint);
	myRigidDeformation.UpdateCommonPoint(mycommonPoint);
	myRigidDeformation.getResultofCommonPoint(printRigidPoint);

	glutInit(&argc, argv);  // Initialize the toolkit
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);  // Set display mode

	glutInitWindowPosition(200, 250);  // Set window pozition on screen
	glutInitWindowSize(screenWidth, screenHeight);      // Set window size
	glutCreateWindow("dispaly3dmodelwindow"); // Open the screen window

	glutDisplayFunc(displayEveryCrossCurve);
	glutReshapeFunc(reshape_2d);
	glutKeyboardFunc(keyboard_planeCrossDesign);
	glutMouseFunc(mouse);

	init3d();
	myInit();

	printInfo();

	glutMainLoop();  // Go into a perpetual loop
}
