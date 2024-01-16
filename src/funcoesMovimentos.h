#include <cmath>

PIG_Cor getPixelColor(int objeto, int coluna, int linha){
    PIG_Cor cor;
    int largura, altura;

    GetDimensoesOriginaisSprite(objeto, &altura, &largura);

    int colunaProporcional = (coluna * largura)/LARGURA_CENARIO;
    int linhaProporcional = (linha * altura)/ALTURA_CENARIO;

    cor.a = 255;
    cor.r = CPIGGerenciadorSprites::GetSprite(objeto)->GetPixels()[altura-1-linhaProporcional][colunaProporcional].r;
    cor.g = CPIGGerenciadorSprites::GetSprite(objeto)->GetPixels()[altura-1-linhaProporcional][colunaProporcional].g;
    cor.b = CPIGGerenciadorSprites::GetSprite(objeto)->GetPixels()[altura-1-linhaProporcional][colunaProporcional].b;

    return cor;
}

/**
void setPixelColor(int objeto, int coluna, int linha, PIG_Cor cor)
{
    int largura = PegarLargura(objeto);
    int altura = PegarAltura(objeto);

    CPIGGerenciadorObjetos::objetos[objeto]->pixels[altura-1-linha][coluna].r = cor.r;
    CGerenciadorObjetos::objetos[objeto]->pixels[altura-1-linha][coluna].g = cor.g;
    CGerenciadorObjetos::objetos[objeto]->pixels[altura-1-linha][coluna].b = cor.b;
    CGerenciadorObjetos::objetos[objeto]->pixels[altura-1-linha][coluna].a = 255;
}
**/

void getXYCentralDaLargada(double *X, double *Y){
    int x1, y1, x2, y2;
    int flag = 0;

    for(int i = 0; i < LARGURA_CENARIO; i ++){
        for(int j = 0; j < ALTURA_CENARIO; j++){
            if(chegada[i][j] == 2){
                if(flag == 0){
                    x1 = i;
                    y1 = j;
                    flag = 1;
                }
                x2 = i;
                y2 = j;
            }
        }
    }

    *X = (x1 + x2) / 2;
    *Y = (y1 + y2) / 2;
}

void preencherMatrizColisao(){
    PIG_Cor cor;
    for(int i=0; i<LARGURA_CENARIO; i++){
        for(int j=0; j<ALTURA_CENARIO; j++){
            cor = getPixelColor(spritePistaMolde, i, j);
            if(cor.r == 110 && cor.g == 110 && cor.b == 110 && cor.a == 255){ ///cinza
                cenario[i][j] = 1;
                chegada[i][j] = 1;
            }
            else if(cor.r == 255 && cor.g == 255 && cor.b == 0){ /// amarelo linha de chegada
                cenario[i][j] = 1;
                chegada[i][j] = 0;
            }
            else if(cor.r == 0 && cor.g == 255 && cor.b == 0){ /// verde linha de inicio
                cenario[i][j] = 1;
                chegada[i][j] = 2;
            }
            else{
                cenario[i][j] = 0;
                chegada[i][j] = 1;
            }
        }
    }
}

int valorMenorVizinho(int i, int j){
    int vizinhos[8];

    vizinhos[0] = distancias[i-1][j+1];
    vizinhos[1] = distancias[i][j+1];
    vizinhos[2] = distancias[i+1][j+1];
    vizinhos[3] = distancias[i-1][j];

    vizinhos[4] = distancias[i+1][j];
    vizinhos[5] = distancias[i-1][j-1];
    vizinhos[6] = distancias[i][j-1];
    vizinhos[7] = distancias[i+1][j-1];

    int Menor = 9999999;

    if(i < 0 || j < 0 || i > (LARGURA_CENARIO-1) || j > (LARGURA_CENARIO - 1)){
        return Menor;
    }

    for(int k=0; k<8; k++){
        if(vizinhos[k] < Menor && vizinhos[k] >= 0){
            Menor = vizinhos[k];
        }
    }
    return Menor;
}

int buscarMaiorDistancia(){
    int maior = 0;
    int indicek = 0, indicem = 0;
    for(int k=0; k<LARGURA_CENARIO; k++){
        for(int m=0; m<ALTURA_CENARIO; m++){
            if(cenario[k][m] == 1){
                if(distancias[k][m] > maior && distancias[k][m] != 9999999){
                    maior = distancias[k][m];
                    indicek = k;
                    indicem = m;
                }
            }
        }
    }

    return maior;
}

void zerarLinhaChegada(){
    for(int i=0; i<LARGURA_CENARIO; i++){
        for(int j=0; j<ALTURA_CENARIO; j++){
            if(chegada[i][j] == 0){
                distancias[i][j] = 0;
            }
        }
    }
}

void preencherMatrizDistancias(){
    int novo;

    for(int i=0; i<LARGURA_CENARIO; i++){
        for(int j=0; j<ALTURA_CENARIO; j++){
            distancias[i][j] = 9999999;
        }
    }

    zerarLinhaChegada();

    while(1){
        int mudancas = 0;

        for(int k=0; k<LARGURA_CENARIO; k++){
            for(int m=0; m<ALTURA_CENARIO; m++){
                if(cenario[k][m] == 1 && chegada[k][m] == 1){
                    novo = 1 + valorMenorVizinho(k,m);
                    if(novo < distancias[k][m]){
                        distancias[k][m] = novo;
                        mudancas++;
                    }
                }
            }
        }

        if(mudancas == 0){
            break;
        }
    }

    for(int i=0; i<LARGURA_CENARIO; i++){
        for(int j=0; j<ALTURA_CENARIO; j++){
            if(cenario[i][j] == 0){
                distancias[i][j] = -1;
            }
            else if(chegada[i][j] == 0){
                distancias[i][j] = 0;
            }
        }
    }

    maiorDistancia = buscarMaiorDistancia();
}

bool colisaoComParede(int x, int y, char matriz[LARGURA_CENARIO][ALTURA_CENARIO]) {
    if(matriz[x][y] == 0) return true;
    return false;
}

bool verificarColisao(char matriz[LARGURA_CENARIO][ALTURA_CENARIO], int i){

    double x1, y1, x2, y2, x3, y3, x4, y4, xCentro, yCentro, angulo;
    x1 = carros[i].X;
    y1 = carros[i].Y;
    x2 = carros[i].X + LARGURA_CARRO;
    y2 = carros[i].Y;
    x3 = carros[i].X;
    y3 = carros[i].Y + ALTURA_CARRO;
    x4 = carros[i].X + LARGURA_CARRO;
    y4 = carros[i].Y + ALTURA_CARRO;
    angulo = carros[i].Angulo;
    xCentro = carros[i].X + (LARGURA_CARRO/2);
    yCentro = carros[i].Y + (ALTURA_CARRO/2);

    getXYRotacionado(&x1, &y1, xCentro, yCentro, angulo);
    getXYRotacionado(&x2, &y2, xCentro, yCentro, angulo);
    getXYRotacionado(&x3, &y3, xCentro, yCentro, angulo);
    getXYRotacionado(&x4, &y4, xCentro, yCentro, angulo);

    return colisaoComParede(x1, y1, matriz) ||
           colisaoComParede(x2, y2, matriz) ||
           colisaoComParede(x3, y3, matriz) ||
           colisaoComParede(x4, y4, matriz);
}

void movimentarCarros(){
    for(int i=0; i<QTD_CARROS; i++){
        if(carros[i].Colidiu == 0 && carros[i].Finalizou == 0){
            double TempVelocidade = carros[i].Velocidade;

            carros[i].VX = TempVelocidade*cos(degToRad()*carros[i].Angulo);
            carros[i].VY = TempVelocidade*sin(degToRad()*carros[i].Angulo);

            if(verificarColisao(cenario, i)){
                carros[i].Colidiu = 1;
                carrosColididos++;
            } else if(verificarColisao(chegada, i)){
                carros[i].Finalizou = 1;
                carros[i].Colocacao = Colocacao;
                Colocacao ++;
            } else {
                carros[i].X = carros[i].X + carros[i].VX;
                carros[i].Y = carros[i].Y + carros[i].VY;
            }

            if(carros[i].Velocidade > 0){
                carros[i].Velocidade = carros[i].Velocidade - 0.1;
                if(carros[i].Velocidade < 0)
                    carros[i].Velocidade = 0;
            }

            if(carros[i].Velocidade < 0){
                carros[i].Velocidade = carros[i].Velocidade + 0.1;
            }
        }
    }
}

void verificarInteracaoJogador(){
    if(MODO_JOGO == MODO_EVOLUCAO) return;

    double velMax = 4;
    if(meuTeclado[PIG_TECLA_CIMA]){
        carros[0].Velocidade = carros[0].Velocidade + 0.2;
        if(carros[0].Velocidade > velMax) carros[0].Velocidade = velMax;
    }
    if(meuTeclado[PIG_TECLA_BAIXO]){
        carros[0].Velocidade = carros[0].Velocidade - 0.2;
        if(carros[0].Velocidade < -velMax) carros[0].Velocidade = -velMax;
    }
    if(meuTeclado[PIG_TECLA_ESQUERDA]){
        carros[0].Angulo = carros[0].Angulo + 4.0;
    }
    if(meuTeclado[PIG_TECLA_DIREITA]){
        carros[0].Angulo = carros[0].Angulo - 4.0;
    }
}

double DistanciaEntrePontos(double x, double y, double x1, double y1) {
    double distancia;
    distancia = sqrt(pow((x1 - x), 2) + pow((y1 - y), 2));
    return distancia;
}

void aplicarSensores(Carro* carro, double* entrada){
    int i;
    for(i=0; i<CAR_BRAIN_QTD_INPUT-1; i++)
    {
        double X1 = carro->X + (LARGURA_CARRO/2);
        double Y1 = carro->Y + (ALTURA_CARRO/2);
        double centroX = X1;
        double centroY = Y1;
        double Angulo = carro->Angulo - 90.0 + ((double)i)*180.0/((double)(CAR_BRAIN_QTD_INPUT-2));

        double Adjacente = 1*(cos(Angulo*degToRad()));
        double Oposto = 1*(sin(Angulo*degToRad()));

        while(1){
            X1 = X1 + Adjacente;
            Y1 = Y1 + Oposto;

            if(cenario[(int)X1][(int)Y1] == 0){
                X1 = X1 - Adjacente;
                Y1 = Y1 - Oposto;

                double dist = DistanciaEntrePontos(centroX, centroY, X1, Y1);

                DesenhaLinhaSimples(centroX, centroY, X1, Y1, AZUL);

                if(entrada != NULL){
                    entrada[i] = dist;
                }
                carro->DistanciaSensores[i] = dist;
                break;
            }
        }
    }
    if(entrada != NULL){
        entrada[i] = carro->Velocidade;
    }
}

void aplicarSaida(Carro* carro, double* saida){
    if(saida[0] > 0)
    {
        carro->Velocidade = carro->Velocidade + 0.2;
    }
    if(saida[1] > 0)
    {
        carro->Velocidade = carro->Velocidade - 0.2;
        if(carro->Velocidade < -4)
        {
            carro->Velocidade = -4;
        }
    }
    if(saida[2] > 0)
    {
        carro->Angulo = carro->Angulo + 4.0;
    }
    if(saida[3] > 0)
    {
        carro->Angulo = carro->Angulo - 4.0;
    }
}

void controlarCarros(){
    double Saida[CAR_BRAIN_QTD_OUTPUT];
    double Entrada[CAR_BRAIN_QTD_INPUT];

    int inicio = 0;
    if(MODO_JOGO != MODO_EVOLUCAO) inicio = 1;

    for(int i = inicio; i<QTD_CARROS; i++)
    {
        if(carros[i].Colidiu == 0)
        {
            aplicarSensores(&carros[i], Entrada);

            RNA_CopiarParaEntrada(carros[i].Cerebro, Entrada);
            RNA_CalcularSaida(carros[i].Cerebro);
            RNA_CopiarDaSaida(carros[i].Cerebro, Saida);

            if(carros[i].Colidiu == 0 && carros[i].Finalizou == 0){
                aplicarSaida(&carros[i], Saida);
            }
        }
    }
}

void movimentarCamera(){

    double CameraZoom = GetAfastamentoCamera();
    int CameraPosX,CameraPosY;
    GetXYCamera(&CameraPosX, &CameraPosY);

    double A = 10.0/(CameraZoom+1);
    if(meuTeclado[PIG_TECLA_w] == 1){
        CameraPosY += A;
    }
    if(meuTeclado[PIG_TECLA_s] == 1){
        CameraPosY -= A;
    }
    if(meuTeclado[PIG_TECLA_a] == 1){
        CameraPosX -= A;
    }
    if(meuTeclado[PIG_TECLA_d] == 1){
        CameraPosX += A;
    }

    double B = 0.02;

    if(meuTeclado[PIG_TECLA_q] == 1){
        CameraZoom -= B;
        if(CameraZoom >= 50) CameraZoom = 50;
    }
    if(meuTeclado[PIG_TECLA_e] == 1){
        CameraZoom += B;
        if(CameraZoom <= -0.9999) CameraZoom = -0.9999;
    }

    SetAfastamentoCamera(CameraZoom);
    MoveCamera(CameraPosX, CameraPosY);
}
