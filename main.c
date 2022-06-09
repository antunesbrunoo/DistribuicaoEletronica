#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

typedef struct{
    int numCamada;
    char strCamada;
    int numAtomico;
}camadas;

void dist(int Numatomico)
{
    int ContCamada, ContSubCamada, Cont, EletronsUltimaCamad, NumAtomicoCamada, QtdDistribuicao=0;
    //int Numatomico;
    int Numatomicofixo;
    camadas distribuicao[11] = {{1, 's', 2}, {2, 's', 2}, {2, 'p', 6}, {3, 's', 2}, {3, 'p', 6}, {4, 's', 2}, {3, 'd', 10}, {4, 'p', 6}, {5, 's', 2}, {4, 'd', 10}, {5, 'p', 6}};

    //printf("Digite o valor do numero atomico\n");
    //scanf("%d", &Numatomico);
    Numatomicofixo = Numatomico;

    for (ContSubCamada = 0; ContSubCamada < 11; ContSubCamada++){
        if ((Numatomicofixo - distribuicao[ContSubCamada].numAtomico) <0){
            EletronsUltimaCamad = Numatomicofixo;
        }
        if ((Numatomicofixo - distribuicao[ContSubCamada].numAtomico) >= 0){
            QtdDistribuicao++;
            Numatomicofixo -= distribuicao[ContSubCamada].numAtomico;
        }else{
            if (Numatomicofixo > 0){;
                QtdDistribuicao++;
            }
            ContSubCamada = 11;
        }
    }
    printf("Distribuicao eletronica: \n\n");
        if (EletronsUltimaCamad == 0){
            for (Cont = 0; Cont < QtdDistribuicao; Cont++){
                printf("%d %c %d,\n", distribuicao[Cont].numCamada, distribuicao[Cont].strCamada, distribuicao[Cont].numAtomico);
            }
        }else{
            for (Cont = 0; Cont < QtdDistribuicao; Cont++){
                if (Cont == (QtdDistribuicao-1)){
                    printf("%d %c %d,\n", distribuicao[Cont].numCamada, distribuicao[Cont].strCamada, EletronsUltimaCamad);
                }else{
                    printf("%d %c %d,\n", distribuicao[Cont].numCamada, distribuicao[Cont].strCamada, distribuicao[Cont].numAtomico);
                }
            }
        }


}

int main()
{

    FILE *arq, *arq2;
    char nome[80]="", busca[80], buscaSimb[20], op[20]="", buscaMassaA[80], buscaEnergia[80], buscaNum[80], buscaRaio[80], buscaAfinidade[80], buscaEletro[80];
    int tamanho;



    if ((arq = fopen ("Tabela.txt","r"))==NULL){
        printf ("Erro na abertura do arquivo.");
    }
    else if ((arq2 = fopen ("PotencialReducao.txt","r"))==NULL){
        printf ("Erro na abertura do arquivo 2.");
    }
    else{
        printf("Arquivo aberto com sucesso.\n");
        printf("Digite a operacao desejada entre: distribuicao eletronica, busca elemento, conversao molar e calculo pilha:\n");
        scanf("%[^\n]s", op);

        getchar();

        if(!(strcmp(op,"busca elemento"))){
            printf("Digite o nome do elemento a ser buscado no arquivo: ");
            scanf("%[^\n]s", nome);

            strcat(nome, "\n");

            tamanho = strlen(nome);

            do {
                fgets(busca, tamanho+1, arq);

                if(strcmp(busca, nome) == 0) {
                    fgets(buscaMassaA, tamanho+10, arq);
                    fgets(buscaSimb, tamanho+10, arq);
                    fgets(buscaNum, tamanho+10, arq );
                    fgets(buscaEnergia, tamanho+30, arq);
                    fgets(buscaRaio, tamanho+10, arq);
                    fgets(buscaAfinidade, tamanho+10, arq);
                    fgets(buscaEletro, tamanho+10, arq);

                    printf("Nome: %s", busca);
                    printf("Massa Atomica em u: %s", buscaMassaA);
                    printf("Simbolo: %s", buscaSimb);
                    printf("Numero Atomico: %s", buscaNum);
                    printf("Energia de ionizacao em Kj/mol: %s", buscaEnergia);
                    printf("Tamanho Raio atomico em picometros: %s", buscaRaio);
                    printf("Tamanho Afinidade eletronica em Kj/mol: %s", buscaAfinidade);
                    printf("Tamanho Eletronegatividade em picometros: %s", buscaEletro);
                    exit(1);
                }
            } while(!feof(arq));

            printf("elemento nao encontrado!");
        }

        else if(!(strcmp(op,"distribuicao eletronica"))){

            printf("Digite o nome do elemento a ser feito a distribuicao: ");
            scanf("%[^\n]s", nome);

            strcat(nome, "\n");

            tamanho = strlen(nome);

            do {
                fgets(busca, tamanho+1, arq);

                if(strcmp(busca, nome) == 0) {
                    fgets(buscaMassaA, tamanho+10, arq);
                    fgets(buscaSimb, tamanho+10, arq);
                    fgets(buscaNum, tamanho+10, arq );
                    fgets(buscaEnergia, tamanho+30, arq);
                    fgets(buscaRaio, tamanho+10, arq);
                    fgets(buscaAfinidade, tamanho+10, arq);
                    fgets(buscaEletro, tamanho+10, arq);
                    dist(atoi(buscaNum));


                    exit(1);
                }
            } while(!feof(arq));

            printf("elemento nao encontrado!");

        }
        else if(!(strcmp(op,"conversao molar"))){

            int cont=0, substancia;
            int NumAtomos = 0.0;
            int selec = 0, i = 0;
            float Nmol = 0; // N�mero de mols
            float NumG = 0.0, ResultNm = 0.0, guarda = 0.0, MassaG = 0.0, /* Massa em gramas*/ Massaatomica =0.0, Massamolar = 0.0; //Multiplicar a quantidade de �tomos do elemento pela massa atomica
            float ResultFinal = 0.0, ResultMassaG = 0.0; // Resultado da massa



            printf("                   Convers�o mol/ grama e grama/mol:\n\n");
            printf("1- Para convers�o grama/ mol de um elemento:\n");
            printf("2- Para convers�o grama/ mol de uma subst�ncia:\n");
            printf("3- Para convers�o mol/grama de um elemento:\n");
            printf("4- Para convers�o mol/grama de uma subst�ncia:\n");
            scanf("%d", &selec);
            getchar();


            switch (selec){

                case 1:

                    printf("Digite o nome do elemento: ");
                    scanf("%[^\n]s", nome);

                    strcat(nome, "\n");

                    tamanho = strlen(nome);

                    do {
                        fgets(busca, tamanho+1, arq);

                        if(strcmp(busca, nome) == 0) {
                            fgets(buscaMassaA, tamanho+10, arq);
                            fgets(buscaSimb, tamanho+10, arq);
                            fgets(buscaNum, tamanho+10, arq );
                            fgets(buscaEnergia, tamanho+30, arq);
                            fgets(buscaRaio, tamanho+10, arq);
                            fgets(buscaAfinidade, tamanho+10, arq);
                            fgets(buscaEletro, tamanho+10, arq);
                        }

                    } while(!feof(arq));

                    printf("Informe a gramas do elemento\n");
                    scanf("%f", &NumG);

                    ResultNm = NumG/atof(buscaMassaA);

                    printf("%.3f mol", ResultNm);
                    break;

                case 2:

                    printf("informe quantos elementos tem na substancia\n");
                    scanf("%d", &cont);

                    for(i = 0 ;i<cont; i++ ){
                    printf("Informe a quantidade de atomos do %d elemento \n", i+1);
                    scanf("%d", &NumAtomos);
                    getchar();
                    printf("Digite o nome do elemento: ");
                    scanf("%[^\n]s", nome);

                    strcat(nome, "\n");

                    tamanho = strlen(nome);

                    do {
                        fgets(busca, tamanho+1, arq);

                        if(strcmp(busca, nome) == 0) {
                            fgets(buscaMassaA, tamanho+10, arq);
                            fgets(buscaSimb, tamanho+10, arq);
                            fgets(buscaNum, tamanho+10, arq );
                            fgets(buscaEnergia, tamanho+30, arq);
                            fgets(buscaRaio, tamanho+10, arq);
                            fgets(buscaAfinidade, tamanho+10, arq);
                            fgets(buscaEletro, tamanho+10, arq);
                        }

                    } while(!feof(arq));


                    guarda = NumAtomos * atof(buscaMassaA);
                    Massamolar += guarda ;
                    rewind(arq);
                    }

                    printf("Informe as gramas da substancia\n");
                    scanf("%f", &NumG);

                    ResultNm = NumG/Massamolar;

                    printf("%.3f mol", ResultNm);
                    break;

                case 3:

                    printf("Informe o Numero de Mol:\n");
                    scanf("%f", &Nmol);
                    getchar();
                    printf("Digite o nome do elemento: ");
                    scanf("%[^\n]s", nome);

                    strcat(nome, "\n");

                    tamanho = strlen(nome);

                    do {
                        fgets(busca, tamanho+1, arq);

                        if(strcmp(busca, nome) == 0) {
                            fgets(buscaMassaA, tamanho+10, arq);
                            fgets(buscaSimb, tamanho+10, arq);
                            fgets(buscaNum, tamanho+10, arq );
                            fgets(buscaEnergia, tamanho+30, arq);
                            fgets(buscaRaio, tamanho+10, arq);
                            fgets(buscaAfinidade, tamanho+10, arq);
                            fgets(buscaEletro, tamanho+10, arq);
                        }

                    } while(!feof(arq));
                    ResultMassaG = (Nmol * atof(buscaMassaA));

                    printf("%.3f gramas", ResultMassaG);
                    break;

                case 4:

                    printf("Informe o Numero de Mol:\n");
                    scanf("%f", &Nmol);
                    printf("Informe o numero de elementos da subst�ncia:\n");
                    scanf("%d", &substancia);
                    getchar();
                    for(i = 0 ;i<substancia; i++){

                        printf("Digite o nome do %d elemento: ", (i+1));
                        scanf("%[^\n]s", nome);

                        strcat(nome, "\n");

                        tamanho = strlen(nome);

                        do {
                            fgets(busca, tamanho+1, arq);

                            if(strcmp(busca, nome) == 0) {
                                fgets(buscaMassaA, tamanho+10, arq);
                                fgets(buscaSimb, tamanho+10, arq);
                                fgets(buscaNum, tamanho+10, arq );
                                fgets(buscaEnergia, tamanho+30, arq);
                                fgets(buscaRaio, tamanho+10, arq);
                                fgets(buscaAfinidade, tamanho+10, arq);
                                fgets(buscaEletro, tamanho+10, arq);
                            }

                        } while(!feof(arq));

                        printf("Informe a quantidade de atomos do elemento %d\n", (i+1));
                        scanf("%d", &NumAtomos);
                        getchar();
                        Massamolar = NumAtomos * atof(buscaMassaA);
                        ResultMassaG += Massamolar;
                    rewind(arq);
                    }

                    ResultFinal = (Nmol * ResultMassaG);
                    printf("%.3f gramas", ResultFinal);
                    break;
            }
        }
        else if(!(strcmp(op,"calculo pilha"))){

            float pot1, pot2, pottotal=0.0;
            char elem1[80]={}, elem2[80]={}, buscar[80] ={};
            char buscarN1[80] = {}, buscarN2[80]={};
            int tamanho;

            printf("Calculo de Pilhas: \n");
            printf("informe os dois elementos no estado reduzido que ser�o utilizados para criar a pilha \nseparados por um espa�o: (Zn [enter] Cu[enter])\n");
            scanf("%[^\n]s", &elem1);
            getchar();
            strcat(elem1, "\n");
            tamanho = strlen(elem1);
                do{
                    fgets(buscar, tamanho+1, arq2);

                        if(strcmp(buscar, elem1) == 0){
                            fgets(buscarN1, tamanho+5, arq2);
                        }
                    } while(!feof(arq2));
            rewind(arq2);

            printf("%s", buscarN1);

            scanf("%[^\n]s", &elem2);
            getchar();

            strcat(elem2, "\n");
            tamanho = strlen(elem2);

                do{
                    fgets(buscar, tamanho+1, arq2);

                        if(strcmp(buscar, elem2) == 0){
                            fgets(buscarN2, tamanho+5, arq2);
                        }
                    } while(!feof(arq2));

            printf("%.2f\n", atof(buscarN2));
            strtok(elem1, "\n");
            strtok(elem2, "\n");

                if(atof(buscarN1) < atof(buscarN2)){
                    printf("o %s e o anodo da pilha e o %s e o catodo\n", elem1, elem2);
                    printf("o potencial da pilha e %.3f", (atof(buscarN2)- atof(buscarN1)));
                }
                else if (atof(buscarN1) > atof(buscarN2)){
                    printf("o %s e o anodo da pilha e o %s e o catodo\n", elem2, elem1);
                    printf("o potencial da pilha e %.3f", (atof(buscarN1)- atof(buscarN2)));
                }
        }
    }


    fclose(arq);

    return 0;
}





