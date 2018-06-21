#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#define TAM 40

float polt_ocup=0;
float polt_vazia=0;
int porcent_ocup=0;
int porcent_masc=0;
int porcent_femi=0;

struct data{
    int dia;
    int mes;
    int ano;
}dat;

struct horario{
    int hora;
    int min;
    int seg;
}horas;

struct poltrona{
    int  valid;
    int  num_pass;
    char nome_p[35];
    char sex;
}polt[40];

struct onibus{
    char    cid_orig[30];
    char    cid_dest[30];
    struct  data    dat;
    struct  horario horas;
    float   dist;
    struct  poltrona polt[40];
}bus;

void preencher_bus(void){
    int i,
        x;
    char aux;

    printf("===Cadastro do Ônibus===\n\n");

    printf("Digite a cidade de origem: ");
    fflush(stdin);
    fgets(bus.cid_orig,25,stdin);

    printf("\nDigite a cidade destido: ");
    fflush(stdin);
    fgets(bus.cid_dest,25,stdin);

    printf("\nDigite a data da partida:\n");
    printf("-Dia: ");
    scanf("%d", &bus.dat.dia);
    printf("-Mês: ");
    scanf("%d", &bus.dat.mes);
    printf("-Ano: ");
    scanf("%d", &bus.dat.ano);

    printf("\nDigite o horário de partida:\n");
    printf("-Hora: ");
    scanf("%d", &bus.horas.hora);
    printf("-Minutos: ");
    scanf("%d", &bus.horas.min);
    printf("-Segundos: ");
    scanf("%d", &bus.horas.seg);

    printf("\nDigite a distância entre a origem e o destino: (em quilômetros)\n");
    scanf("%f", &bus.dist);

    printf("\n===Poltronas===\n");
    for(i=0;i<TAM;i++){
        printf("A poltrona %d está:\n", i+1);
        printf("[1] - Ocupada\n[2] - Vazia\n");
        printf("Digite a opção desejada: ");

        do{
            scanf("%d", &x);
            switch(x){

                case 1:
                    polt_ocup++;
                    bus.polt[i].valid = 1;

                    printf("\n==Passageiro %d==\n", i+1);
                    printf("\nDigite o número da passagem: ");
                    fflush(stdin);
                    scanf("%d", &bus.polt[i].num_pass);

                    printf("\nDigite o nome do passageiro: ");
                    fflush(stdin);
                    fgets(bus.polt[i].nome_p,30,stdin);

                    do{

                        printf("\nDigite o sexo do passageiro: (M ou F)\n");
                        fflush(stdin);
                        scanf("%c", &aux);

                    }while(((aux!='m')&&(aux!='f'))&&((aux!='M')&&(aux!='F')));

                    bus.polt[i].sex = aux;
                    break;

                case 2:
                    polt_vazia++;
                    bus.polt[i].valid = 0;
                    break;

                default:
                    printf("Opção inválida.\n");
                    break;
            }
        }while((x!=1)&&(x!=2));
    }
    system("cls");
}

float estimar_horario(float x){
      float temp_estimado;

      temp_estimado = (bus.dist/80)*60;
      return temp_estimado;
}

void calcular_porcent_ocup(void){
    float total_ocup;

    total_ocup = polt_ocup + polt_vazia;
    porcent_ocup = (polt_ocup/total_ocup)*100;
}

void calcular_porcent_sex(void){
    int i;
    float masc=0,
          femi=0,
          total;

    for(i=0;i<TAM;i++){
        bus.polt[i].sex = toupper(bus.polt[i].sex);
        if(bus.polt[i].sex == 'F'){
            femi++;
        }else{
            if(bus.polt[i].sex == 'M'){
                masc++;
            }
        }
    }

    total = masc + femi;
    porcent_masc = (masc/total)*100;
    porcent_femi = (femi/total)*100;
}
int main(){
    int i,
        j,
        k=0;
    float temp_estimado;

    setlocale(LC_ALL, "Portuguese");
    system("color 17");

    preencher_bus();
    temp_estimado = estimar_horario(bus.dist);
    calcular_porcent_ocup();
    calcular_porcent_sex();

    printf("=================INFORMAÇÕES DO ÔNIBUS=================\n\n");
    printf("Cidade de Origem:.....................%s", bus.cid_orig);
    printf("Destino do Ônibus:....................%s", bus.cid_dest);
    printf("Data da partida:......................%02d/%02d/%04d\n", bus.dat.dia, bus.dat.mes, bus.dat.ano);
    printf("Horário da partida:...................%02dh%02dm%02ds\n", bus.horas.hora, bus.horas.min, bus.horas.seg);
    printf("Distância da viagem:..................%.2fkm\n", bus.dist);
    printf("Tempo estimado da viagem:.............%.1f(min)\n", temp_estimado);
    printf("Porcentagem de ocupação:..............%d\n", porcent_ocup);
    printf("Porcentagem de passageiros homens:....%d\n", porcent_masc);
    printf("Porcentagem de passageiros mulheres:..%d\n\n\n", porcent_femi);

    printf("==================OCUPAÇÃO DO ÔNIBUS==================\n\n");
    printf("\t[F]-Feminino||[M]-Masculino||[ ]-Vazia\n");
    for(i=0;i<10;i++){
        printf("\t\t");
        for(j=0;j<4;j++){
            printf("[%c]", bus.polt[k].sex);
            if((j+1)%2==0){
                printf("\t");
            }
            k++;
        }
        printf("\n");
    }
    printf("\n\n");

    printf("==============INFORMAÇÕES DOS PASSAGEIROS==============\n\n");
    for(i=0;i<TAM;i++){
        if(bus.polt[i].valid == 1){
            printf("\n====Poltrona %02d====\n", i+1);
            printf("Número da passagem:...................%d\n", bus.polt[i].num_pass);
            printf("Nome do passageiro:...................%s", bus.polt[i].nome_p);
            printf("Sexo:.................................%c\n", bus.polt[i].sex);
        }
    }

    system("pause");
    return 0;
}
