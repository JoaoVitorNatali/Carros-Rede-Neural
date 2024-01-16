
void salvarRedeNeuralArquivo(){
    double Maior = 0;
    int Indice = 0;

    if(MODO_JOGO != MODO_DUELO){
        for(int i=0; i<QTD_CARROS; i++){
            if(carros[i].Fitness > Maior){
                Maior = carros[i].Fitness;
                Indice = i;
            }
        }

        FILE* f = fopen("RedeNeuralFile","wb");
        fwrite(&carros[Indice].TamanhoDNA, 1, sizeof(int), f);
        fwrite(carros[Indice].DNA, carros[Indice].TamanhoDNA, sizeof(double), f);
        fclose(f);
    }
}

void carregarRedeNeural(){
    FILE* f = fopen("RedeNeuralFile","rb");

    if(f != NULL){
        fread(&carros[1].TamanhoDNA, 1, sizeof(int), f);
        fread(carros[1].DNA, carros[1].TamanhoDNA, sizeof(double), f);
        fclose(f);
    }
}
