PIGEvento evento;
PIGTeclado meuTeclado;
double timerDesenho;
double timerAcoes;
double timerJogo;


bool FIM_DE_JOGO = false;

int spritePista, spritePistaMolde, spriteCarros[QTD_SPRITES_CARROS];
int         Fonte;

char        cenario[LARGURA_CENARIO][ALTURA_CENARIO];
char        chegada[LARGURA_CENARIO][ALTURA_CENARIO];
int         distancias[LARGURA_CENARIO][ALTURA_CENARIO];
double maiorDistancia;
int carrosColididos = 0;
int Geracao = 0;
int Colocacao = 0;
