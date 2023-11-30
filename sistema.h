#ifndef sistema_h
#define sistema_h

#include <GL/freeglut.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>

#define M_PI 3.14159265358979323846
#define qntdPlanetas 11

typedef struct {
	float posicao[3];
	std::string nome;
	std::string temperatura;
	std::string massa;
	std::string raio;
	std::string gravidade;
	std::string idade;
	std::string distanciaDaTerra;

}Planetas;

class astros
{
public:

	astros();
	~astros();

	void definirParametros(float novaDistancia, float novoRaio, float novaVelocidade, float novoAngulo, const float novaCor[3], const float novaPosicao[3]);

	friend void insere();
	friend void desenharPlaneta(astros Astros);
	friend void desenharPlanetaComRotulo(astros Astros);
	friend void desenharOrbita(astros Astros);
	friend void display();
	friend void atualizar(int valor);

private:

	float distancia;
	float raio;
	float velocidade;
	float angulo;
	float cor[3];
	float posicao[3];

};

extern astros sol, mercurio, venus, terra, lua, marte, jupiter, saturno, urano, netuno, plutao;

void dadosplan();
void exibirdadosplan();
void insere();
void atualizarPosicaoCamera();
void teclasEspeciais(int tecla, int x, int y);
void mouse(int botao, int estado, int x, int y);
void movimentoMouse(int x, int y);
void desenharPlaneta(astros Astros);
void desenharPlanetaComRotulo(astros Astros);
void desenharOrbita(astros Astros);
void display();
void atualizar(int valor);

#endif
