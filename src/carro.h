#define CAR_BRAIN_QTD_LAYERS   1
#define CAR_BRAIN_QTD_INPUT    18
#define CAR_BRAIN_QTD_HIDE     6
#define CAR_BRAIN_QTD_OUTPUT   4

typedef struct carro
{
    double X, Y;
    double VX, VY;
    double Angulo;
    double Velocidade;
    char Colidiu;
    char Finalizou;
    char Queimado;
    int Colocacao;

    int Sprite;
    double DistanciaSensores[CAR_BRAIN_QTD_INPUT-1];

    int TamanhoDNA;
    double* DNA;
    double Fitness;

    RedeNeural* Cerebro;

}   Carro;

std::array<Carro, QTD_CARROS> carros;

void alocarCarro(int i){
    int Tamanho;

    carros[i].Sprite = spriteCarros[rand()%QTD_SPRITES_CARROS];

    carros[i].Cerebro = RNA_CriarRedeNeural(   CAR_BRAIN_QTD_LAYERS,
                                               CAR_BRAIN_QTD_INPUT,
                                               CAR_BRAIN_QTD_HIDE,
                                               CAR_BRAIN_QTD_OUTPUT);

    Tamanho = RNA_QuantidadePesos(carros[i].Cerebro);

    carros[i].TamanhoDNA = Tamanho;
    carros[i].DNA = (double*)malloc(Tamanho*sizeof(double));

    for(int j=0; j<carros[i].TamanhoDNA; j++)
    {
        carros[i].DNA[j] = getRandomValue();
    }
}

void inicializarCarro(int i, double X, double Y){
    carros[i].Angulo = 90;
    carros[i].X = X;
    carros[i].Y = Y;
    carros[i].VX = 0;
    carros[i].VY = 0;
    carros[i].Velocidade = 0;
    carros[i].Colidiu = 0;
    carros[i].Finalizou = 0;
    carros[i].Queimado = 0;

    RNA_CopiarVetorParaCamadas(carros[i].Cerebro, carros[i].DNA);
}

void criarCarros(){
    for(int i = 0; i < QTD_CARROS; i++){
        alocarCarro(i);
    }
}

void excluirCarros(){
    for(int i = 0; i < QTD_CARROS; i++){
        free(carros[i].DNA);
        RNA_DestruirRedeNeural(carros[i].Cerebro);
    }
}

void randomMutations()
{
    static double RangeRandom = carros[0].TamanhoDNA;

    carro* Vetor[QTD_CARROS];
    carro* Temp;

    for(int i=0; i<QTD_CARROS; i++)
    {
        Vetor[i] = &carros[i];
    }

    for(int i=0; i<QTD_CARROS; i++)
    {
        for(int j=0; j<QTD_CARROS-1; j++)
        {
            if(Vetor[j]->Fitness < Vetor[j+1]->Fitness)
            {
                Temp = Vetor[j];
                Vetor[j] = Vetor[j+1];
                Vetor[j+1] = Temp;
            }
        }
    }

    int Step = 5;
    for(int i=0; i<Step; i++)  /// Clonando individuos
    {
        for(int j=Step+i; j<QTD_CARROS; j=j+Step)
        {
            for(int k=0; k<Vetor[j]->TamanhoDNA; k++)
            {
                Vetor[j]->DNA[k] = Vetor[i]->DNA[k];        /// individuo 'j' recebe dna do individuo 'i'
            }
        }
    }

    for(int j=Step; j<QTD_CARROS; j++)
    {
        int tipo;
        int mutations = (rand()%(int)RangeRandom)+1;

        for(int k=0; k<mutations; k++)
        {
            tipo = rand()%3;

            int indice = rand()%Vetor[j]->TamanhoDNA;
            switch(tipo)
            {
                case 0:
                {
                    //int mutations = 20;
                    Vetor[j]->DNA[indice] = getRandomValue();       /// Valor Aleatorio

                }   break;
                case 1:
                {
                    double number = (rand()%10001)/10000.0 + 0.5;
                    Vetor[j]->DNA[indice] = Vetor[j]->DNA[indice]*number;   /// Multiplicação aleatoria

                }   break;
                case 2:
                {
                    double number = getRandomValue()/100.0;
                    Vetor[j]->DNA[indice] = Vetor[j]->DNA[indice] + number; /// Soma aleatoria

                }   break;
            }
        }
    }


    RangeRandom = RangeRandom*0.999;
    if(RangeRandom < 15){
        RangeRandom = 15;
    }

    Geracao++;

    printf("\nGeracao %d", Geracao);
}

int buscarMelhorCarroVivo(){
    int menor = 999999;
    int indice = 0;
    for(int i=0; i<QTD_CARROS; i++){
        if(carros[i].Colidiu == 0){
            double x = carros[i].X, y = carros[i].Y;
            getXYRotacionado(&x, &y, x + (LARGURA_CARRO/2), y + (ALTURA_CARRO/2), carros[i].Angulo);

            int dist = distancias[(int)x][(int)y];

            if(dist < menor){
                menor = dist;
                indice = i;
            }
        }
    }
    return indice;
}

