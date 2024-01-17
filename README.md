# Carros-Rede-Neural

## Explicação do algorítimo utilizado:

Neste projeto, emprego uma abordagem de rede neural para controlar os carros no cenário. Em síntese, esses carros têm permissão para se locomover apenas na área cinza do cenário, com o objetivo de alcançar a linha de chegada.

Inicialmente, cerca de 1000 indivíduos são criados e, para cada um deles, redes neurais são alocadas com configurações de pesos distintas para os neurônios. A cada iteração, são selecionados os 5 melhores indivíduos, ou seja, aqueles que conseguiram percorrer a maior distância. O DNA desses melhores indivíduos é então replicado para os outros 995, estabelecendo uma base genética para a próxima geração.

Posteriormente, pequenas modificações aleatórias são introduzidas no DNA de cada indivíduo recém-gerado (random mutations). Essa abordagem visa garantir a diversidade entre as novas redes neurais, evitando a reprodução exata das gerações anteriores. Em seguida, realiza-se uma nova série de jogadas para determinar quais indivíduos conseguem avançar mais, dando continuidade ao ciclo iterativo.

O processo é repetido até que pelo menos um indivíduo alcance com sucesso a linha de chegada, representando o sucesso do treinamento e evolução dos carros no cenário. Essa metodologia de evolução artificial permite aprimorar o desempenho dos carros ao longo das gerações, adaptando-se de forma dinâmica ao ambiente de jogo.


## Imagens da evolução das IAs ao longo das gerações:

### Geração 1:
<img width="407" alt="image" src="https://github.com/JoaoVitorNatali/Carros-Rede-Neural/assets/57870382/81397b17-57cf-4162-a4af-48bb6839b62f">

### Geração 12:
<img width="415" alt="image" src="https://github.com/JoaoVitorNatali/Carros-Rede-Neural/assets/57870382/24b6bab4-8527-4eee-b575-63a7e7e10c03">

### Geração 32:
<img width="410" alt="image" src="https://github.com/JoaoVitorNatali/Carros-Rede-Neural/assets/57870382/0423a389-3ab4-4b83-a612-a0eb63248afe">

### Geração 63:
<img width="411" alt="image" src="https://github.com/JoaoVitorNatali/Carros-Rede-Neural/assets/57870382/01f6fb90-1fc6-4cb1-bcb6-392c6bdd3b8c">

A partir dessa geração as IAs ficaram presas em uma "Ótima região", na qual elas não conseguiam sair pois era a maior distancia que conseguiram chegar 5 individuos. Nesse momento foi necessário adotar outras abordagens para pontuas essas IAs a fim de evitar essa ótima região. A estratégia adotada foi "penalizar" as que conseguiam chegar muito longe porém colidiram no final, garantindo assim que outras IAs que não colidiram tivessem a chance de ser replicadas para as proximas gerações.

## Possibilidade de alterar o cenario utilizado

No projeto utilizo duas imagens, uma para detectar as colisões e outra para printar. A imagem para detectar as colisões deve possuir a cor cinza (110, 110, 110) para a pista percorrível, a cor amarelo (255, 255, 0) para a linha de chegada e a cor verde (0, 255, 0) para a linha de inicio, para que o projeto consiga identificar e preencher a matriz de distancias.
Caso deseje utilizar outra imagem como cenário, use essas especificações e crie as duas imagens, uma com o nome "pistaMolde.png" e outra "pistaReal.png". As duas devem ter as mesmas dimensões.
