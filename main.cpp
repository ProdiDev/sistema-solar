#include "sistema.h"

int main(int argc, char** argv) {

	insere();
	dadosplan();

	// Inicializa o GLUT
	glutInit(&argc, argv);

	// Define o tamanho inicial da janela (largura x altura)
	glutInitWindowSize(1500, 800);

	// Configura o modo de exibição e a criação da janela
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Sistema Solar");

	// Ativa o teste de profundidade
	glEnable(GL_DEPTH_TEST);

	// Configura as funções de callback
	glutMouseFunc(mouse);
	glutMotionFunc(movimentoMouse);
	glutSpecialFunc(teclasEspeciais);
	glutDisplayFunc(display);
	glutTimerFunc(25, atualizar, 0);

	// Inicia o loop principal do GLUT
	glutMainLoop();

	return 0;
}
