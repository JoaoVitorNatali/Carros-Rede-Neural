

void desenharPista(){
    MoveSprite(spritePista, 0, 0);
    DesenhaSprite(spritePista);
}

void desenharPontosDeColisaoCarro(int i){
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

    DesenhaRetangulo(x1, y1, 2, 2, AZUL);
    DesenhaRetangulo(x2, y2, 2, 2, VERDE);
    DesenhaRetangulo(x3, y3, 2, 2, AMARELO);
    DesenhaRetangulo(x4, y4, 2, 2, ROXO);
}

void desenharSensoresCarro(int i){
    Carro *carro = &carros[i];
    aplicarSensores(carro, NULL);
    return;

    double X,Y;
    double X1 = carro->X + (LARGURA_CARRO/2);
    double Y1 = carro->Y + (ALTURA_CARRO/2);

    for(int i=0; i<CAR_BRAIN_QTD_INPUT-1; i++){
        X = X1 + carro->DistanciaSensores[i]*cos(degToRad()*(carro->Angulo - 90.0 + ((180.0/(CAR_BRAIN_QTD_INPUT-2))*i)));
        Y = Y1 + carro->DistanciaSensores[i]*sin(degToRad()*(carro->Angulo - 90.0 + ((180.0/(CAR_BRAIN_QTD_INPUT-2))*i)));

        DesenhaLinhaSimples(X1,Y1,X,Y,AZUL);
    }

}

void desenharCarros(){
    double X,Y;
    for(int i = 0; i < QTD_CARROS; i++){
        if(carros[i].Colidiu == 0)
        {
            X = carros[i].X;
            Y = carros[i].Y;

            MoveSprite(carros[i].Sprite, X, Y);
            SetAnguloSprite(carros[i].Sprite, carros[i].Angulo);
            DesenhaSprite(carros[i].Sprite);

            if(meuTeclado[PIG_TECLA_v])
                desenharPontosDeColisaoCarro(i);

            if(meuTeclado[PIG_TECLA_b])
                desenharSensoresCarro(i);
        }
    }
}

void desenharSensoresMelhorCarro(){
    int indice = buscarMelhorCarroVivo();
    desenharSensoresCarro(indice);
}

void desenharMatrizDistancias(){
    for(int i=0; i<LARGURA_CENARIO; i++){
        for(int j=0; j<ALTURA_CENARIO; j++){

            double distancia = distancias[i][j];
            SDL_Color cor = AZUL;

            if(distancia == -1) cor = BRANCO;
            else if(distancia == 0) cor = AMARELO;
            else {
                int aux = ((int) distancia /1000) %5;

                if(aux == 0) cor = VERDE;
                else if(aux == 1) cor = AZUL;
                else if (aux == 2) cor = ROXO;
                else if (aux == 3) cor = VERMELHO;
                else if (aux == 4) cor = LARANJA;
            }

            DesenhaRetangulo(i, j, 1, 1, cor);
        }
    }
}
