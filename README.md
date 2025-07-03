#include <stdio.h>

#define MAX_CARTAS 10

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

    // Cálculos derivados
    carta->densidadePopulacional = carta->populacao / carta->area;
    carta->pibPerCapita = carta->pib * 1000000000 / carta->populacao;
}

void mostrarCarta(struct CartaCidade carta, int indice) {
    printf("\n===== CARTA %d =====\n", indice+1);
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

int main() {
    struct CartaCidade cartas[MAX_CARTAS];
    int quantidade = 0;
    int opcao;

    printf("Bem-vindo ao Super Trunfo - Cidades do Mundo!\n");

    do {
        printf("\nMenu:\n");
        printf("1 - Cadastrar nova carta\n");
        printf("2 - Listar cartas cadastradas\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            if (quantidade < MAX_CARTAS) {
                cadastrarCarta(&cartas[quantidade]);
                quantidade++;
            } else {
                printf("Limite de cartas atingido!\n");
            }
        } else if (opcao == 2) {
            if (quantidade == 0) {
                printf("Nenhuma carta cadastrada ainda.\n");
            }
            for (int i = 0; i < quantidade; i++) {
                mostrarCarta(cartas[i], i);
            }
        }
    } while (opcao != 0);

    printf("Obrigado por jogar!\n");
    return 0;
}
