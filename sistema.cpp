#include "sistema.h"

astros sol, mercurio, venus, terra, lua, marte, jupiter, saturno, urano, netuno, plutao;

float distanciaCamera = 10.0f;
float anguloCameraX = 0.0f;
float anguloCameraY = 0.0f;
int ultimoMouseX = 0;
int ultimoMouseY = 0;
bool estaArrastandoMouse = false;
bool estaAnimacaoPausada = false;

bool botaoPressionado = false;


int i = 0;

Planetas dados[qntdPlanetas];

void dadosplan() {
	std::ifstream arquivo("dados_planetas.txt");

	if (arquivo.is_open()) {
		int index = 0;
		std::string linha;
		while (getline(arquivo, linha)) {
			if (!linha.empty()) {
				dados[index].nome = linha;

				getline(arquivo, dados[index].temperatura);
				getline(arquivo, dados[index].massa);
				getline(arquivo, dados[index].raio);
				getline(arquivo, dados[index].gravidade);
				getline(arquivo, dados[index].idade);
				getline(arquivo, dados[index].distanciaDaTerra);

				index++;
			}
		}
		arquivo.close();
	}
	else {
		std::cerr << "Não foi possível abrir o arquivo." << std::endl;
	}
}

void exibirdadosplan()
{
	float left = 10.0f;    // Posição X à esquerda da tela
	float top = glutGet(GLUT_WINDOW_HEIGHT) - 10.0f;  // Posição Y no topo da tela


	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT));

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glColor3f(0.2f, 0.2f, 0.2f);
	glBegin(GL_QUADS);
	glVertex2f(left, top);
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);

	glRasterPos2f(left + 10.0f, top - 20.0f);

	std::string informacoes = "\n" "Planeta: " + dados[i].nome + "\n"
		"Temperatura: " + dados[i].temperatura + "\n"
		"Massa: " + dados[i].massa + "\n"
		"Raio: " + dados[i].raio + "\n"
		"Gravidade: " + dados[i].gravidade + "\n"
		"Idade: " + dados[i].idade + "\n"
		"Distância da Terra: " + dados[i].distanciaDaTerra;

	for (char c : informacoes) {
		if (c == '\n') {
			top = top - 20.0f;  // Ajuste a posição vertical para simular nova linha
			glRasterPos2f(left + 10.0f, top);
		}
		else {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
		}
	}

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

}

astros::astros() {
	distancia = 0.0f;
	raio = 0.0f;
	velocidade = 0.0f;
	angulo = 0.0f;

	for (int i = 0; i < 3; ++i) {
		cor[i] = 0.0f;
		posicao[i] = 0.0f;
	}
}

astros::~astros() {

}

void astros::definirParametros(float novaDistancia, float novoRaio, float novaVelocidade, float novoAngulo, const float novaCor[3], const float novaPosicao[3]) {
	distancia = novaDistancia;
	raio = novoRaio;
	velocidade = novaVelocidade;
	angulo = novoAngulo;

	std::copy(novaCor, novaCor + 3, cor);
	std::copy(novaPosicao, novaPosicao + 3, posicao);
}

void insere()
{
	float geral_posicao[3] = { 0.0f, 0.0f, 0.0f };

	float sol_cor[3] = { 1.0f, 1.0f, 0.0f };
	sol.definirParametros(0.0f, 3.2f, 5.0f, 0.0f, sol_cor, geral_posicao);

	float mercurio_cor[3] = { 0.8f, 0.8f, 0.8f };
	mercurio.definirParametros(5.0f, 0.3f, 1.0f, 0.0f, mercurio_cor, geral_posicao);

	float venus_cor[3] = { 0.9f, 0.5f, 0.0f };
	venus.definirParametros(8.0f, 0.5f, 0.7f, 0.0f, venus_cor, geral_posicao);

	float terra_cor[3] = { 0.1f, 0.1f, 1.0f };
	terra.definirParametros(12.0f, 0.7f, 0.5f, 0.0f, terra_cor, geral_posicao);

	float lua_cor[3] = { 0.7f, 0.7f, 0.7f };
	lua.definirParametros(1.5f, 0.2f, 1.0f, 0.0f, lua_cor, geral_posicao);

	float marte_cor[3] = { 1.0f, 0.1f, 0.1f };
	marte.definirParametros(18.0f, 0.5f, 0.3f, 0.0f, marte_cor, geral_posicao);

	float jupiter_cor[3] = { 0.7f, 0.7f, 0.7f };
	jupiter.definirParametros(35.0f, 2.0f, 0.2f, 0.0f, jupiter_cor, geral_posicao);

	float saturno_cor[3] = { 0.8f, 0.6f, 0.2f };
	saturno.definirParametros(50.0f, 1.5f, 0.1f, 0.0f, saturno_cor, geral_posicao);

	float urano_cor[3] = { 0.5f, 0.8f, 0.8f };
	urano.definirParametros(70.0f, 1.2f, 0.05f, 0.0f, urano_cor, geral_posicao);

	float netuno_cor[3] = { 0.0f, 0.0f, 0.8f };
	netuno.definirParametros(90.0f, 1.1f, 0.04f, 0.0f, netuno_cor, geral_posicao);

	float plutao_cor[3] = { 0.5f, 0.5f, 0.5f };
	plutao.definirParametros(110.0f, 0.2f, 0.03f, 0.0f, plutao_cor, geral_posicao);
}

void atualizarPosicaoCamera() {

	const float maxAnguloVertical = 89.0f;
	const float minAnguloVertical = -89.0f;

	anguloCameraX = std::min(std::max(anguloCameraX, minAnguloVertical), maxAnguloVertical);

	// Calcula a posição da câmera ao redor do planeta
	float cameraX = distanciaCamera * sin(anguloCameraY * (M_PI / 180.0f)) * cos(anguloCameraX * (M_PI / 180.0f));
	float cameraY = distanciaCamera * sin(anguloCameraX * (M_PI / 180.0f));
	float cameraZ = distanciaCamera * cos(anguloCameraY * (M_PI / 180.0f)) * cos(anguloCameraX * (M_PI / 180.0f));

	gluLookAt(cameraX, cameraY, cameraZ, 0.0f, 0.0f, 0.0f, 0.0f, 20.0f, 0.0f);
}

void teclasEspeciais(int tecla, int x, int y) {
	switch (tecla) {
	case GLUT_KEY_F1:
		estaAnimacaoPausada = !estaAnimacaoPausada;
		break;

	case GLUT_KEY_RIGHT:
		if (i < 10) {
			i++;
		}
		else if (i == 10) {
			i = 0;
		}
		std::cout << "Clicou ++" << i;
		distanciaCamera = dados[i].posicao[0] + 10.0f;
		glutPostRedisplay();
		break;

	case GLUT_KEY_LEFT:
		if (i > 0)
			i--;
		else if (i == 0) {
			i = 10;
		}
		std::cout << "Clicou --" << i;
		distanciaCamera = dados[i].posicao[0] + 10.0f;
		glutPostRedisplay();
		break;
	}
	glutPostRedisplay();
}

void mouse(int botao, int estado, int x, int y) {

	if (botao == 3) {
		// Rolar para cima
		distanciaCamera -= 1.0f;
	}
	else if (botao == 4) {
		// Rolar para baixo
		distanciaCamera += 1.0f;
	}

	distanciaCamera = std::min(std::max(distanciaCamera, 1.0f), 200.0f);

	atualizarPosicaoCamera();
	glutPostRedisplay();

	if (botao == GLUT_LEFT_BUTTON) {
		if (estado == GLUT_DOWN) {
			estaArrastandoMouse = true;
			ultimoMouseX = x;
			ultimoMouseY = y;
		}
		else if (estado == GLUT_UP) {
			estaArrastandoMouse = false;
		}
	}
}

void movimentoMouse(int x, int y) {
	if (estaArrastandoMouse) {
		int deltaX = x - ultimoMouseX;
		int deltaY = y - ultimoMouseY;
		ultimoMouseX = x;
		ultimoMouseY = y;

		anguloCameraY += deltaX * 0.6f;
		anguloCameraX += deltaY * 0.6f;

		atualizarPosicaoCamera();
		glutPostRedisplay();
	}
}

void desenharPlaneta(astros Astros) {
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Astros.cor);
	glMaterialfv(GL_FRONT, GL_AMBIENT, Astros.cor);

	GLfloat especular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, especular);
	glMaterialf(GL_FRONT, GL_SHININESS, 50.0f);

	glPushMatrix();
	glTranslatef(Astros.posicao[0], Astros.posicao[1], Astros.posicao[2]);
	glutSolidSphere(Astros.raio, 50, 50);
	glPopMatrix();
}

void desenharPlanetaComRotulo(astros Astros) {
	glPushMatrix();
	glTranslatef(Astros.posicao[0], Astros.posicao[1], Astros.posicao[2]);
	desenharPlaneta(Astros);

	float labelX = Astros.posicao[0] + Astros.raio + 0.2f;
	float labelY = Astros.posicao[1] - 0.5f;
	float labelZ = Astros.posicao[2];

	glPopMatrix();
}

void desenharOrbita(astros Astros) {
	glDisable(GL_LIGHTING);
	glColor3f(0.3f, 0.3f, 0.3f);

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++) {
		float radiano = i * (M_PI / 180.0f);
		float x = Astros.distancia * cos(radiano);
		float z = Astros.distancia * sin(radiano);
		glVertex3f(x, 0.0f, z);
	}
	glEnd();

}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	int larguraJanela = glutGet(GLUT_WINDOW_WIDTH);
	int alturaJanela = glutGet(GLUT_WINDOW_HEIGHT);
	float proporcaoAspecto = static_cast<float>(larguraJanela) / static_cast<float>(alturaJanela);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, proporcaoAspecto, 1.0f, 10000.0f);  // Ajustar a distância de renderização aqui

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	atualizarPosicaoCamera();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	desenharPlanetaComRotulo(sol);

	glPushMatrix();
	glRotatef(mercurio.angulo, 0.0f, 1.0f, 0.0f);
	glTranslatef(mercurio.distancia, 0.0f, 0.0f);
	desenharPlanetaComRotulo(mercurio);
	glPopMatrix();

	glPushMatrix();
	glRotatef(venus.angulo, 0.0f, 1.0f, 0.0f);
	glTranslatef(venus.distancia, 0.0f, 0.0f);
	desenharPlanetaComRotulo(venus);
	glPopMatrix();

	glPushMatrix();
	glRotatef(jupiter.angulo, 0.0f, 1.0f, 0.0f);
	glTranslatef(jupiter.distancia, 0.0f, 0.0f);
	desenharPlanetaComRotulo(jupiter);
	glPopMatrix();

	glPushMatrix();
	glRotatef(saturno.angulo, 0.0f, 1.0f, 0.0f);
	glTranslatef(saturno.distancia, 0.0f, 0.0f);
	desenharPlanetaComRotulo(saturno);
	glPopMatrix();

	glPushMatrix();
	glRotatef(urano.angulo, 0.0f, 1.0f, 0.0f);
	glTranslatef(urano.distancia, 0.0f, 0.0f);
	desenharPlanetaComRotulo(urano);
	glPopMatrix();

	glPushMatrix();
	glRotatef(netuno.angulo, 0.0f, 1.0f, 0.0f);
	glTranslatef(netuno.distancia, 0.0f, 0.0f);
	desenharPlanetaComRotulo(netuno);
	glPopMatrix();

	glPushMatrix();
	glRotatef(plutao.angulo, 0.0f, 1.0f, 0.0f);
	glTranslatef(plutao.distancia, 0.0f, 0.0f);
	desenharPlanetaComRotulo(plutao);
	glPopMatrix();

	glPushMatrix();
	glRotatef(terra.angulo, 0.0f, 1.0f, 0.0f);
	glTranslatef(terra.distancia, 0.0f, 0.0f);
	desenharPlanetaComRotulo(terra);
	glPushMatrix();
	glRotatef(lua.angulo, 0.0f, 1.0f, 0.0f);
	glTranslatef(lua.distancia, 0.0f, 0.0f);
	glRotatef(terra.angulo, 0.0f, 1.0f, 0.0f);
	desenharPlanetaComRotulo(lua);
	desenharOrbita(lua);
	glPopMatrix();

	glPushMatrix();
	glRotatef(marte.angulo, 0.0f, 1.0f, 0.0f);
	glTranslatef(marte.distancia, 0.0f, 0.0f);
	desenharPlanetaComRotulo(marte);
	glPopMatrix();

	desenharOrbita(mercurio);
	desenharOrbita(venus);
	desenharOrbita(terra);
	desenharOrbita(marte);
	desenharOrbita(jupiter);
	desenharOrbita(saturno);
	desenharOrbita(urano);
	desenharOrbita(netuno);
	desenharOrbita(plutao);

	exibirdadosplan();

	glutSwapBuffers();

	//atualizarPosicaoCamera();
}

void atualizar(int valor)
{
	if (!estaAnimacaoPausada) {

		exibirdadosplan();

		sol.angulo += 0.2f;
		mercurio.angulo += mercurio.velocidade;
		venus.angulo += venus.velocidade;
		terra.angulo += terra.velocidade;
		lua.angulo += lua.velocidade;
		marte.angulo += marte.velocidade;
		jupiter.angulo += jupiter.velocidade;
		saturno.angulo += saturno.velocidade;
		urano.angulo += urano.velocidade;
		netuno.angulo += netuno.velocidade;
		plutao.angulo += plutao.velocidade;

		glutPostRedisplay();
	}

	glutTimerFunc(16, atualizar, 0);

	dados[0].posicao[0] = 10.0f;

	dados[1].posicao[0] = mercurio.distancia;

	dados[2].posicao[0] = venus.distancia;

	dados[3].posicao[0] = terra.distancia;

	dados[4].posicao[0] = terra.distancia;

	dados[5].posicao[0] = marte.distancia;

	dados[6].posicao[0] = jupiter.distancia;

	dados[7].posicao[0] = saturno.distancia;

	dados[8].posicao[0] = urano.distancia;

	dados[9].posicao[0] = netuno.distancia;

	dados[10].posicao[0] = plutao.distancia;

}
