#include <time.h>
#include "PIG.h"
#include "redeNeural.c"
#include "definicoes.h"
#include "variaveis.h"
#include "carro.h"
#include "funcoesMovimentos.h"
#include "funcoesDesenhar.h"
#include "arquivo.h"


void inicializarSprites(){
    spritePista = CriaSprite("pistaReal.png", 0);
    spritePistaMolde = CriaSprite("pistaMolde.png", 0); /// pista molde possui linha de chegada e largada desenhada nela
    SetDimensoesSprite(spritePista, ALTURA_CENARIO, LARGURA_CENARIO);
    SetDimensoesSprite(spritePistaMolde, ALTURA_CENARIO, LARGURA_CENARIO);

    spriteCarros[0] = CriaSprite("carro1.png",0);
    spriteCarros[1] = CriaSprite("carro2.png",0);
    spriteCarros[2] = CriaSprite("carro3.png",0);
    spriteCarros[3] = CriaSprite("carro4.png",0);
    spriteCarros[4] = CriaSprite("carro5.png",0);

    for(int i = 0; i < QTD_SPRITES_CARROS; i++){
        SetDimensoesSprite(spriteCarros[i], ALTURA_CARRO, LARGURA_CARRO);
        SetPivoAbsolutoSprite(spriteCarros[i], LARGURA_CARRO/2, ALTURA_CARRO/2);
    }
}

void excluirSprites(){
    DestroiSprite(spritePista);
    for(int i = 0; i < QTD_SPRITES_CARROS; i++){
        DestroiSprite(spriteCarros[i]);
    }
}

void iniciarNovaPartida(){
    double X, Y;
    getXYCentralDaLargada(&X, &Y);
    for(int i=0; i<QTD_CARROS; i++){
        inicializarCarro(i, X, Y);
    }
}

void configuracoesIniciais(){
    CriaJogo("Carros IA");
    SetTamanhoJanela(ALTURA_CENARIO, LARGURA_CENARIO);

    PreparaCameraMovel();

    meuTeclado = GetTeclado();
    timerDesenho = CriaTimer();
    timerJogo = CriaTimer();
    timerAcoes = CriaTimer();

    Fonte = CriaFonteNormal("..\\fontes\\arial.ttf", 15, VERDE, 0, PRETO);

    inicializarSprites();

    criarCarros();
    carregarRedeNeural();

    preencherMatrizColisao();
    preencherMatrizDistancias();


    iniciarNovaPartida();
}

void desenhar(){
    if(EXIBIR_ANIMACAO != 1) return;
    IniciaDesenho();

    if(meuTeclado[PIG_TECLA_x])
        desenharMatrizDistancias();
    else if(!meuTeclado[PIG_TECLA_z]){
        desenharPista();
        desenharCarros();
    }

    if(meuTeclado[PIG_TECLA_k])
        desenharSensoresMelhorCarro();

    EncerraDesenho();
}

void verificarEstadoPartida(){
    if(MODO_JOGO == MODO_TESTE){
        if(carros[0].Colidiu){
            iniciarNovaPartida();
        }
    } else {
        if(carrosColididos == QTD_CARROS){
            randomMutations();
            iniciarNovaPartida();
            ReiniciaTimer(timerJogo);
        }
    }
}

void movimentarObjetos(){
    movimentarCarros();
}

bool jogoRodando(){
    return FIM_DE_JOGO == false;
}

void calcularFitnessDosCarros(){
    double dist;
    double tempo;
    for(int i=0; i<QTD_CARROS; i++)
    {
        double xCentro = carros[i].X + (LARGURA_CARRO/2);
        double yCentro = carros[i].Y + (ALTURA_CARRO/2);

        int distanciaCarro = distancias[(int)xCentro][(int)yCentro];
        dist = (double) maiorDistancia - (double) distanciaCarro;

        if(distanciaCarro == -1) printf("\nERRO");

        if(carros[i].Colidiu == 1){
            carros[i].Fitness = dist - 5;
        } else if(carros[i].Finalizou == 1){
            double pontoPorColocacao = QTD_CARROS - Colocacao;
            carros[i].Fitness = dist + pontoPorColocacao;
        } else {
            carros[i].Fitness = dist;
        }
    }
}

void finalizaPrograma(){
    calcularFitnessDosCarros();
    salvarRedeNeuralArquivo();
    excluirCarros();
    excluirSprites();
}

void verificarTeclado(){
    if(meuTeclado[SDL_SCANCODE_KP_ENTER] || meuTeclado[SDL_SCANCODE_RETURN]){
        FIM_DE_JOGO = true;
    }
}

int main( int argc, char* args[] ){
    srand(time(NULL));

    configuracoesIniciais();

    while(jogoRodando() && JogoRodando()){
        evento = GetEvento();

        if(TempoDecorrido(timerDesenho) >= 0.03){
            desenhar();
            ReiniciaTimer(timerDesenho);
        }

        if(TempoDecorrido(timerAcoes) >= 0.01){
            verificarTeclado();
            verificarInteracaoJogador();
            movimentarCamera();

            movimentarObjetos();
            controlarCarros();
            ReiniciaTimer(timerAcoes);

            if(MODO_JOGO == MODO_TESTE) verificarEstadoPartida();
        }

        if(TempoDecorrido(timerJogo) >= 20 && MODO_JOGO != MODO_TESTE){
            calcularFitnessDosCarros();
            randomMutations();
            iniciarNovaPartida();
            ReiniciaTimer(timerJogo);
        }
    }


    finalizaPrograma();
    FinalizaJogo();

    return 0;
}
