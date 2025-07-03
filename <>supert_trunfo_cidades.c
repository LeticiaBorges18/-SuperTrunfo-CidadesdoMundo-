#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CARTAS 100

struct CartaCidade {
    char estado[30];
    int codigo;
    char nomeCidade[50];
    int populacao;
    float pib;
    float area;
    int pontosTuristicos;
    float densidadePopulacional;
    float pibPerCapita;
};

void limparBuffer() {
    while (getchar() != '\n');
}

void cadastrarCarta(struct CartaCidade *carta) {
    printf("Digite o nome do estado: ");
    scanf(" %[^\n]", carta->estado);

    printf("Digite o código da cidade: ");
    scanf("%d", &carta->codigo);

    printf("Digite o nome da cidade: ");
    scanf(" %[^\n]", carta->nomeCidade);

    printf("Digite a população da cidade: ");
    scanf("%d", &carta->populacao);

    printf("Digite o PIB da cidade (em bilhões): ");
    scanf("%f", &carta->pib);

    printf("Digite a área da cidade (em km²): ");
    scanf("%f", &carta->area);

    printf("Digite o número de pontos turísticos: ");
    scanf("%d", &carta->pontosTuristicos);

    if (carta->area > 0)
        carta->densidadePopulacional = carta->populacao / carta->area;
    else
        carta->densidadePopulacional = 0;

    if (carta->populacao > 0)
        carta->pibPerCapita = (carta->pib * 1e9) / carta->populacao;
    else
        carta->pibPerCapita = 0;
}

void mostrarCarta(struct CartaCidade carta, int indice) {
    printf("\n===== CARTA %d =====\n", indice + 1);
    printf("Estado: %s\n", carta.estado);
    printf("Código: %d\n", carta.codigo);
    printf("Cidade: %s\n", carta.nomeCidade);
    printf("População: %d habitantes\n", carta.populacao);
    printf("PIB: R$ %.2f bilhões\n", carta.pib);
    printf("Área: %.2f km²\n", carta.area);
    printf("Pontos turísticos: %d\n", carta.pontosTuristicos);
    printf("Densidade populacional: %.2f hab/km²\n", carta.densidadePopulacional);
    printf("PIB per capita: R$ %.2f\n", carta.pibPerCapita);
    printf("====================\n");
}

void compararCartas(struct CartaCidade c1, struct CartaCidade c2) {
    printf("\nComparando %s vs %s:\n", c1.nomeCidade, c2.nomeCidade);
    printf("População: %d vs %d -> %s\n", c1.populacao, c2.populacao, (c1.populacao > c2.populacao) ? c1.nomeCidade : c2.nomeCidade);
    printf("PIB: %.2f vs %.2f -> %s\n", c1.pib, c2.pib, (c1.pib > c2.pib) ? c1.nomeCidade : c2.nomeCidade);
    printf("Área: %.2f vs %.2f -> %s\n", c1.area, c2.area, (c1.area > c2.area) ? c1.nomeCidade : c2.nomeCidade);
    printf("Pontos turísticos: %d vs %d -> %s\n", c1.pontosTuristicos, c2.pontosTuristicos, (c1.pontosTuristicos > c2.pontosTuristicos) ? c1.nomeCidade : c2.nomeCidade);
}

void salvarCartas(struct CartaCidade cartas[], int quantidade) {
    FILE *f = fopen("cartas.txt", "w");
    if (!f) {
        printf("Erro ao salvar arquivo.\n");
        return;
    }
    for (int i = 0; i < quantidade; i++) {
        fprintf(f, "%s,%d,%s,%d,%.2f,%.2f,%d\n",
            cartas[i].estado, cartas[i].codigo, cartas[i].nomeCidade,
            cartas[i].populacao, cartas[i].pib, cartas[i].area,
            cartas[i].pontosTuristicos);
    }
    fclose(f);
    printf("Cartas salvas com sucesso!\n");
}

int carregarCartas(struct CartaCidade cartas[]) {
    FILE *f = fopen("cartas.txt", "r");
    if (!f) return 0;

    int i = 0;
    while (fscanf(f, " %[^,],%d,%[^,],%d,%f,%f,%d\n",
                  cartas[i].estado, &cartas[i].codigo, cartas[i].nomeCidade,
                  &cartas[i].populacao, &cartas[i].pib, &cartas[i].area,
                  &cartas[i].pontosTuristicos) == 7) {

        if (cartas[i].area > 0)
            cartas[i].densidadePopulacional = cartas[i].populacao / cartas[i].area;
        else
            cartas[i].densidadePopulacional = 0;

        if (cartas[i].populacao > 0)
            cartas[i].pibPerCapita = (cartas[i].pib * 1e9) / cartas[i].populacao;
        else
            cartas[i].pibPerCapita = 0;

        i++;
    }
    fclose(f);
    return i;
}

int main() {
    struct CartaCidade cartas[MAX_CARTAS];
    int quantidade = 0;
    int opcao;

    quantidade = carregarCartas(cartas);

    printf("Bem-vindo ao Super Trunfo - Cidades do Mundo!\n");

    do {
        printf("\nMenu:\n");
        printf("1 - Cadastrar nova carta\n");
        printf("2 - Listar cartas cadastradas\n");
        printf("3 - Comparar duas cartas\n");
        printf("4 - Salvar cartas em arquivo\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida.\n");
            limparBuffer();
            continue;
        }

        switch (opcao) {
            case 1:
                if (quantidade < MAX_CARTAS) {
                    cadastrarCarta(&cartas[quantidade]);
                    quantidade++;
                } else {
                    printf("Limite de cartas atingido!\n");
                }
                break;
            case 2:
                if (quantidade == 0) printf("Nenhuma carta cadastrada.\n");
                for (int i = 0; i < quantidade; i++) mostrarCarta(cartas[i], i);
                break;
            case 3:
                if (quantidade < 2) {
                    printf("Cadastre pelo menos duas cartas.\n");
                    break;
                }
                int i1, i2;
                printf("Escolha o índice da primeira carta (1 a %d): ", quantidade);
                scanf("%d", &i1);
                printf("Escolha o índice da segunda carta (1 a %d): ", quantidade);
                scanf("%d", &i2);
                if (i1 > 0 && i1 <= quantidade && i2 > 0 && i2 <= quantidade && i1 != i2) {
                    compararCartas(cartas[i1 - 1], cartas[i2 - 1]);
                } else {
                    printf("Índices inválidos.\n");
                }
                break;
            case 4:
                salvarCartas(cartas, quantidade);
                break;
            case 0:
                printf("Saindo do jogo. Até mais!\n");
                break;
            default:
                printf("Opção inválida.\n");
        }

    } while (opcao != 0);

    return 0;
}
