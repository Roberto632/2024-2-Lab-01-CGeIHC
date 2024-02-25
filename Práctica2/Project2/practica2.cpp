//Práctica 2 semestre 2024-2: índices, mesh, proyecciones, transformaciones geométricas
#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
#include <glew.h>
#include <glfw3.h>
//glm
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
//clases para dar orden y limpieza al código
#include"Mesh.h"
#include"Shader.h"
#include"Window.h"
//Dimensiones de la ventana
const float toRadians = 3.14159265f/180.0; //grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<MeshColor*> meshColorList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";
//Nuevos shader
static const char* vShaderCuboRojo = "shaders/shaderCuboRojo.vert";
static const char* vShaderPiramideAzul = "shaders/shaderPiramideAzul.vert";
static const char* vShaderCuboCafe = "shaders/shaderCuboCafe.vert";
static const char* vShaderPiramideVerde = "shaders/shaderPiramideVerde.vert";
static const char* vShaderCuboVerde = "shaders/shaderCuboVerde.vert";

float angulo = 0.0f;

//color café en RGB : 0.478, 0.255, 0.067

//Pirámide triangular regular
void CreaPiramide()
{
	unsigned int indices[] = { 
		0,1,2,
		1,3,2,
		3,0,2,
		1,0,3
		
	};
	GLfloat vertices[] = {
		-0.5f, -0.5f,0.0f,	//0
		0.5f,-0.5f,0.0f,	//1
		0.0f,0.5f, -0.25f,	//2
		0.0f,-0.5f,-0.5f,	//3

	};
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);
}

//Vértices de un cubo
void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

GLfloat cubo_vertices[] = {
	// front
	-0.5f, -0.5f,  0.5f,
	0.5f, -0.5f,  0.5f,
	0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	// back
	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f
};
Mesh *cubo = new Mesh();
cubo->CreateMesh(cubo_vertices, cubo_indices,24, 36);
meshList.push_back(cubo);
}

void CrearLetrasyFiguras()
{	
	//0
	GLfloat vertices_letras[] = {	
			//X			Y			Z			R		G		B
			//Letra P
			-0.85f,		0.6f,	0.0f,			0.0f,	0.5f,	1.0f,
			-0.85f,		-0.4f,	0.0f,			0.0f,	0.5f,	1.0f,
			-0.75f,		-0.4f,	0.0f,			0.0f,	0.5f,	1.0f,
			-0.85f,		0.6f,	0.0f,			0.0f,	0.5f,	1.0f,
			-0.75f,		0.6f,	0.0f,			0.0f,	0.5f,	1.0f,
			-0.75f,		-0.4f,	0.0f,			0.0f,	0.5f,	1.0f,
			-0.75f,		0.1f,	0.0f,			0.0f,	0.5f,	1.0f,
			-0.55f,		0.1f,	0.0f,			0.0f,	0.5f,	1.0f,
			-0.75f,		0.2f,	0.0f,			0.0f,	0.5f,	1.0f,
			-0.75f,		0.2f,	0.0f,			0.0f,	0.5f,	1.0f,
			-0.55f,		0.2f,	0.0f,			0.0f,	0.5f,	1.0f,
			-0.55f,		0.1f,	0.0f,			0.0f,	0.5f,	1.0f,
			-0.75f,		0.6f,	0.0f,			0.0f,	0.5f,	1.0f,
			-0.55f,		0.6f,	0.0f,			0.0f,	0.5f,	1.0f,
			-0.55f,		0.5f,	0.0f,			0.0f,	0.5f,	1.0f,
			-0.75f,		0.6f,	0.0f,			0.0f,	0.5f,	1.0f,
			-0.75f,		0.5f,	0.0f,			0.0f,	0.5f,	1.0f,
			-0.55f,		0.5f,	0.0f,			0.0f,	0.5f,	1.0f,
			-0.55f,		0.6f,	0.0f,			0.0f,	0.5f,	1.0f,
			-0.45f,		0.6f,	0.0f,			0.0f,	0.5f,	1.0f,
			-0.45f,		0.1f,	0.0f,			0.0f,	0.5f,	1.0f,
			-0.55f,		0.6f,	0.0f,			0.0f,	0.5f,	1.0f,
			-0.55,		0.1f,	0.0f,			0.0f,	0.5f,	1.0f,
			-0.45f,		0.1f,	0.0f,			0.0f,	0.5f,	1.0f,

			//Letra A
			-0.2f,		0.5f,	0.0f,			0.3f,	0.7f,	0.3f,
			-0.32f,		-0.4f,	0.0f,			0.3f,	0.7f,	0.3f,
			-0.22f,		-0.4f,	0.0f,			0.3f,	0.7f,	0.3f,
			-0.2f,		0.5f,	0.0f,			0.3f,	0.7f,	0.3f,
			-0.1f,		0.5f,	0.0f,			0.3f,	0.7f,	0.3f,
			-0.22f,		-0.4f,	0.0f,			0.3f,	0.7f,	0.3f,
			0.0f,		0.5f,	0.0f,			0.3f,	0.7f,	0.3f,
			0.15f,		-0.4f,	0.0f,			0.3f,	0.7f,	0.3f,
			0.25f,		-0.4f,	0.0f,			0.3f,	0.7f,	0.3f,
			0.0f,		0.5f,	0.0f,			0.3f,	0.7f,	0.3f,
			0.1f,		0.5f,	0.0f,			0.3f,	0.7f,	0.3f,
			0.25f,		-0.4f,	0.0f,			0.3f,	0.7f,	0.3f,
			-0.18f,		0.6f,	0.0f,			0.3f,	0.7f,	0.3f,
			-0.2f,		0.5f,	0.0f,			0.3f,	0.7f,	0.3f,
			0.1f,		0.5f,	0.0f,			0.3f,	0.7f,	0.3f,
			-0.19f,		0.6f,	0.0f,			0.3f,	0.7f,	0.3f,
			0.08f,		0.6f,	0.0f,			0.3f,	0.7f,	0.3f,
			0.1f,		0.5f,	0.0f,			0.3f,	0.7f,	0.3f,
			-0.17f,		0.2f,	0.0f,			0.3f,	0.7f,	0.3f,
			-0.18f,		0.1f,	0.0f,			0.3f,	0.7f,	0.3f,
			0.13f,		0.1f,	0.0f,			0.3f,	0.7f,	0.3f,
			-0.17f,		0.2f,	0.0f,			0.3f,	0.7f,	0.3f,
			0.13f,		0.1f,	0.0f,			0.3f,	0.7f,	0.3f,
			0.12f,		0.2f,	0.0f,			0.3f,	0.7f,	0.3f,
			
			//Letra R
			0.45f,		0.6f,	0.0f,			0.9f,	0.7f,	0.2f,
			0.45f,		-0.4f,	0.0f,			0.9f,	0.7f,	0.2f,
			0.55f,		-0.4f,	0.0f,			0.9f,	0.7f,	0.2f,
			0.45f,		0.6f,	0.0f,			0.9f,	0.7f,	0.2f,
			0.55f,		0.6f,	0.0f,			0.9f,	0.7f,	0.2f,
			0.55f,		-0.4f,	0.0f,			0.9f,	0.7f,	0.2f,
			0.55f,		0.6f,	0.0f,			0.9f,	0.7f,	0.2f,
			0.55f,		0.5f,	0.0f,			0.9f,	0.7f,	0.2f,
			0.75f,		0.5f,	0.0f,			0.9f,	0.7f,	0.2f,
			0.55f,		0.6f,	0.0f,			0.9f,	0.7f,	0.2f,
			0.75f,		0.6f,	0.0f,			0.9f,	0.7f,	0.2f,
			0.75f,		0.5f,	0.0f,			0.9f,	0.7f,	0.2f,
			0.75f,		0.6f,	0.0f,			0.9f,	0.7f,	0.2f,
			0.85f,		0.6f,	0.0f,			0.9f,	0.7f,	0.2f,
			0.85f,		0.1f,	0.0f,			0.9f,	0.7f,	0.2f,
			0.75f,		0.6f,	0.0f,			0.9f,	0.7f,	0.2f,
			0.75f,		0.1f,	0.0f,			0.9f,	0.7f,	0.2f,
			0.85f,		0.1f,	0.0f,			0.9f,	0.7f,	0.2f,
			0.55f,		0.2f,	0.0f,			0.9f,	0.7f,	0.2f,
			0.55f,		0.1f,	0.0f,			0.9f,	0.7f,	0.2f,
			0.75f,		0.1f,	0.0f,			0.9f,	0.7f,	0.2f,
			0.55f,		0.2f,	0.0f,			0.9f,	0.7f,	0.2f,
			0.75f,		0.2f,	0.0f,			0.9f,	0.7f,	0.2f,
			0.75f,		0.1f,	0.0f,			0.9f,	0.7f,	0.2f,
			0.6f,		0.1f,	0.0f,			0.9f,	0.7f,	0.2f,
			0.75f,		-0.4f,	0.0f,			0.9f,	0.7f,	0.2f,
			0.85,		-0.4f,	0.0f,			0.9f,	0.7f,	0.2f,
			0.55f,		0.0f,	0.0f,			0.9f,	0.7f,	0.2f,
			0.6f,		0.1f,	0.0f,			0.9f,	0.7f,	0.2f,
			0.75f,		-0.4f,	0.0f,			0.9f,	0.7f,	0.2f,
			0.55f,		0.1f,	0.0f,			0.9f,	0.7f,	0.2f,
			0.55f,		0.0f,	0.0f,			0.9f,	0.7f,	0.2f,
			0.6f,		0.1f,	0.0f,			0.9f,	0.7f,	0.2f
	};
	MeshColor *letras = new MeshColor();
	letras->CreateMeshColor(vertices_letras,486);
	meshColorList.push_back(letras);

	//1
	GLfloat vertices_triangulorojo[] = {
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.0f,	1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		
	};

	MeshColor* triangulorojo = new MeshColor();
	triangulorojo->CreateMeshColor(vertices_triangulorojo, 81);
	meshColorList.push_back(triangulorojo);

	//2
	GLfloat vertices_cuadradoverde[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,

	};

	MeshColor* cuadradoverde = new MeshColor();
	cuadradoverde->CreateMeshColor(vertices_cuadradoverde, 36);
	meshColorList.push_back(cuadradoverde);
	
	//3
	//triangulo azul
	GLfloat vertices_trianguloAzul[] = {
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
		1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
		0.0f,	1.0f,		0.5f,			0.0f,	0.0f,	1.0f,

	};

	MeshColor* trianguloAzul = new MeshColor();
	trianguloAzul->CreateMeshColor(vertices_trianguloAzul, 18);
	meshColorList.push_back(trianguloAzul);

	//4
	//triangulo verde 0, 0.5, 0
	GLfloat vertices_trianguloVerdeCinco[] = {
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			0.0f,	0.5f,	0.0f,
		1.0f,	-1.0f,		0.5f,			0.0f,	0.5f,	0.0f,
		0.0f,	1.0f,		0.5f,			0.0f,	0.5f,	0.0f,

	};

	MeshColor* trianguloVerdeCinco = new MeshColor();
	trianguloVerdeCinco->CreateMeshColor(vertices_trianguloVerdeCinco, 18);
	meshColorList.push_back(trianguloVerdeCinco);

	//5
	//cuadrado rojo
	GLfloat vertices_cuadradoRojo[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.5f,	-0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		-0.5f,	-0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		-0.5f,	0.5f,		0.5f,			1.0f,	0.0f,	0.0f,

	};

	MeshColor* cuadradoRojo = new MeshColor();
	cuadradoRojo->CreateMeshColor(vertices_cuadradoRojo, 36);
	meshColorList.push_back(cuadradoRojo);

	//6
	//cuadrado cafe
	GLfloat vertices_cuadradoCafe[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			0.478f,	0.255f,	0.067f,
		0.5f,	-0.5f,		0.5f,			0.478f,	0.255f,	0.067f,
		0.5f,	0.5f,		0.5f,			0.478f,	0.255f,	0.067f,
		-0.5f,	-0.5f,		0.5f,			0.478f,	0.255f,	0.067f,
		0.5f,	0.5f,		0.5f,			0.478f,	0.255f,	0.067f,
		-0.5f,	0.5f,		0.5f,			0.478f,	0.255f,	0.067f,

	};

	MeshColor* cuadradoCafe = new MeshColor();
	cuadradoCafe->CreateMeshColor(vertices_cuadradoCafe, 36);
	meshColorList.push_back(cuadradoCafe);

}


void CreateShaders()
{
	Shader* shader1 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);

	Shader* shader2 = new Shader();//shader para usar color como parte del VAO: letras 
	shader2->CreateFromFiles(vShaderColor, fShaderColor);
	shaderList.push_back(*shader2);

	Shader* shader3 = new Shader();
	shader3->CreateFromFiles(vShaderCuboRojo, fShaderColor);
	shaderList.push_back(*shader3);

	Shader* shader4 = new Shader();
	shader4->CreateFromFiles(vShaderPiramideAzul, fShaderColor);
	shaderList.push_back(*shader4);

	Shader* shader5 = new Shader();
	shader5->CreateFromFiles(vShaderCuboCafe, fShaderColor);
	shaderList.push_back(*shader5);

	Shader* shader6 = new Shader();
	shader6->CreateFromFiles(vShaderPiramideVerde, fShaderColor);
	shaderList.push_back(*shader6);

	Shader* shader7 = new Shader();
	shader7->CreateFromFiles(vShaderCuboVerde, fShaderColor);
	shaderList.push_back(*shader7);
}


int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();
	CreaPiramide(); //índice 0 en MeshList
	CrearCubo();//índice 1 en MeshList
	CrearLetrasyFiguras(); //usa MeshColor, índices en MeshColorList
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	//Projection: Matriz de Dimensión 4x4 para indicar si vemos en 2D( orthogonal) o en 3D) perspectiva
	glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
	//glm::mat4 projection = glm::perspective(glm::radians(30.0f)	,mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
	
	//Model: Matriz de Dimensión 4x4 en la cual se almacena la multiplicación de las transformaciones geométricas.
	glm::mat4 model(1.0); //fuera del while se usa para inicializar la matriz con una identidad
	
	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(1.0f,1.0f,1.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad
		
		/*
		//Iniciales PAR (Pérez Aguilar Roberto
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[0]->RenderMeshColor();
		*/

		//*
		//CUBO ROJO
		shaderList[2].useShader();
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();
		angulo += 0.01;
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.5f, -5.0f));
		model = glm::scale(model, glm::vec3(0.8f, 1.3f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//PIRAMIDE AZUL
		shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();
		angulo += 0.01;
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.50f, -5.0f));
		model = glm::scale(model, glm::vec3(1.0f, 0.7f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		//CUBO CAFE
		shaderList[4].useShader();
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();
		angulo += 0.01;
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.7f, -0.9f, -5.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.3f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//CUBO CAFE
		shaderList[4].useShader();
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();
		angulo += 0.01;
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.7f, -0.9f, -5.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.3f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//PIRAMIDDE VERDE
		shaderList[5].useShader();
		uniformModel = shaderList[5].getModelLocation();
		uniformProjection = shaderList[5].getProjectLocation();
		angulo += 0.01;
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.7f, -0.4f, -5.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.7f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		//PIRAMIDDE VERDE
		shaderList[5].useShader();
		uniformModel = shaderList[5].getModelLocation();
		uniformProjection = shaderList[5].getProjectLocation();
		angulo += 0.01;
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.7f, -0.4f, -5.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.7f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		//CUBO VERDE
		shaderList[6].useShader();
		uniformModel = shaderList[6].getModelLocation();
		uniformProjection = shaderList[6].getProjectLocation();
		angulo += 0.01;
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.2f, -0.2f, -4.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.3f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//CUBO VERDE
		shaderList[6].useShader();
		uniformModel = shaderList[6].getModelLocation();
		uniformProjection = shaderList[6].getProjectLocation();;
		angulo += 0.01;
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.2f, -0.2f, -4.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.3f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//CUBO VERDE
		shaderList[6].useShader();
		uniformModel = shaderList[6].getModelLocation();
		uniformProjection = shaderList[6].getProjectLocation();
		angulo += 0.01;
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.78f, -4.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.6f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//*/

		glUseProgram(0);
		mainWindow.swapBuffers();

	}
	return 0;
}
// inicializar matriz: glm::mat4 model(1.0);
// reestablecer matriz: model = glm::mat4(1.0);
//Traslación
//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
//////////////// ROTACIÓN //////////////////
//model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
////////////////  ESCALA ////////////////
//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
///////////////////// T+R////////////////
/*model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
*/
/////////////R+T//////////
/*model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
*/