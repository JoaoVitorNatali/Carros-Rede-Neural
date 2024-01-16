#define QTD_CARROS 1000
#define QTD_SPRITES_CARROS  5
#define ALTURA_CENARIO 820
#define LARGURA_CENARIO 820
#define ALTURA_CARRO 20
#define LARGURA_CARRO 42
#define MODO_DUELO 1
#define MODO_EVOLUCAO 2
#define MODO_TESTE 3
#define MODO_JOGO MODO_EVOLUCAO

#define EXIBIR_ANIMACAO 1

double getRandomValue(){
    return (rand()%20001/10.0) - 1000.0;
}

double degToRad(){
    return M_PI / 180;
}

void getXYRotacionado(double *X, double *Y, double xCentro, double yCentro, double Angulo){
    /**
        x' = h + (x-h)*cos(A)-(y-k)*sin(A)
        y' = k + (x-h)*sin(A)+(y-k)*cos(A)
        onde:

        (x', y') = são as novas coordenadas após a rotação
        (x, y) = são as coordenadas originais do ponto
        (h, k) = são as coordenadas do centro de rotação
        A = é o ângulo de rotação em radianos

    **/

    double X1 = *X;
    double Y1 = *Y;
    double H = xCentro;
    double K = yCentro;
    double AnguloRad = degToRad()*Angulo;
    double xLinha = H + (X1 - H) * cos(AnguloRad) - (Y1 - K) * sin(AnguloRad);
    double yLinha = K + (X1 - H) * sin(AnguloRad) + (Y1 - K) * cos(AnguloRad);

    *X = xLinha;
    *Y = yLinha;
}
