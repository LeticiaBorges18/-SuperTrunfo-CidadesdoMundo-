#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int lerString(const char *msg, char *buffer, int tamanho) {
    printf("%s", msg);
    if (fgets(buffer, tamanho, stdin) == NULL) return 0;
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len-1] == '\n') buffer[len-1] = '\0';
    return 1;
}

int lerInt(const char *msg, int min, int max) {
    char linha[32];
    int valor, sucesso;
    do {
        printf("%s", msg);
        if (fgets(linha, sizeof(linha), stdin) == NULL) continue;
        sucesso = sscanf(linha, "%d", &valor);
        if (sucesso != 1 || valor < min || valor > max) {
            printf("Valor inválido. Tente novamente.\n");
        } else {
            break;
        }
    } while (1);
    return valor;
}

float lerFloat(const char *msg, float min) {
    char linha[32];
    float valor;
    int sucesso;
    do {
        printf("%s", msg);
        if (fgets(linha, sizeof(linha), stdin) == NULL) continue;
        sucesso = sscanf(linha, "%f", &valor);
        if (sucesso != 1 || valor < min) {
            printf("Valor inválido. Tente novamente.\n");
        } else {
            break;
        }
    } while (1);
    return valor;
}

void cadastrarCarta(struct CartaCidade *carta) {
    lerString("Digite o nome do estado: ", carta->estado, sizeof(carta->estado));
    carta->codigo = lerInt("Digite o código da cidade: ", 0, 1000000);
    lerString("Digite o nome da cidade: ", carta->nomeCidade, sizeof(carta->nomeCidade));
    carta->populacao = lerInt("Digite a população da cidade: ", 1, 100000000);
    carta->pib = lerFloat("Digite o PIB da cidade (em bilhões): ", 0);
    carta->area = lerFloat("Digite a área da cidade (em km²): ", 0.0001f);
    carta->pontosTuristicos = lerInt("Digite o número de pontos turísticos: ", 0, 1000);

    carta->densidadePopulacional = carta->populacao / carta->area;
    carta->pibPerCapita = (carta->populacao > 0) ? (carta->pib * 1e9) / carta->populacao : 0;
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

void editarCarta(struct CartaCidade *carta) {
    printf("Editando carta da cidade %s\n", carta->nomeCidade);
    cadastrarCarta(carta);
    printf("Carta editada com sucesso!\n");
}

void removerCarta(struct CartaCidade cartas[], int *quantidade, int indice) {
    for (int i = indice; i < (*quantidade) - 1; i++) {
        cartas[i] = cartas[i+1];
    }
    (*quantidade)--;
    printf("Carta removida com sucesso!\n");
}

void compararCartas(struct CartaCidade c1, struct CartaCidade c2, int atributo) {
    const char *atributos[] = {"População", "PIB", "Área", "Pontos turísticos", "Densidade populacional", "PIB per capita"};
    printf("\nComparando %s vs %s (%s):\n", c1.nomeCidade, c2.nomeCidade, atributos[atributo]);

    switch (atributo) {
        case 0:
            printf("População: %d vs %d -> %s\n", c1.populacao, c2.populacao,
                   (c1.populacao > c2.populacao) ? c1.nomeCidade : c2.nomeCidade);
            break;
        case 1:
            printf("PIB: %.2f vs %.2f -> %s\n", c1.pib, c2.pib,
                   (c1.pib > c2.pib) ? c1.nomeCidade : c2.nomeCidade);
            break;
        case 2:
            printf("Área: %.2f vs %.2f -> %s\n", c1.area, c2.area,
                   (c1.area > c2.area) ? c1.nomeCidade : c2.nomeCidade);
            break;
        case 3:
            printf("Pontos turísticos: %d vs %d -> %s\n", c1.pontosTuristicos, c2.pontosTuristicos,
                   (c1.pontosTuristicos > c2.pontosTuristicos) ? c1.nomeCidade : c2.nomeCidade);
            break;
        case 4:
            printf("Densidade populacional: %.2f vs %.2f -> %s\n", c1.densidadePopulacional, c2.densidadePopulacional,
                   (c1.densidadePopulacional > c2.densidadePopulacional) ? c1.nomeCidade : c2.nomeCidade);
            break;
        case 5:
            printf("PIB per capita: %.2f vs %.2f -> %s\n", c1.pibPerCapita, c2.pibPerCapita,
                   (c1.pibPerCapita > c2.pibPerCapita) ? c1.nomeCidade : c2.nomeCidade);
            break;
        default:
            printf("Atributo inválido.\n");
    }
}

void salvarCartas(struct CartaCidade cartas[], int quantidade) {
    FILE *f = fopen("cartas.csv", "w");
    if (!f) {
        printf("Erro ao salvar arquivo.\n");
        return;
    }
    for (int i = 0; i < quantidade; i++) {
        fprintf(f, "\"%s\",%d,\"%s\",%d,%.2f,%.2f,%d,%.2f,%.2f\n",
            cartas[i].estado, cartas[i].codigo, cartas[i].nomeCidade,
            cartas[i].populacao, cartas[i].pib, cartas[i].area,
            cartas[i].pontosTuristicos, cartas[i].densidadePopulacional, cartas[i].pibPerCapita);
    }
    fclose(f);
    printf("Cartas salvas com sucesso!\n");
}

int carregarCartas(struct CartaCidade cartas[]) {
    FILE *f = fopen("cartas.csv", "r");
    if (!f) return 0;

    int i = 0;
    while (i < MAX_CARTAS &&
           fscanf(f, " \"%[^\"]\",%d,\"%[^\"]\",%d,%f,%f,%d,%f,%f\n",
                  cartas[i].estado, &cartas[i].codigo, cartas[i].nomeCidade,
                  &cartas[i].populacao, &cartas[i].pib, &cartas[i].area,
                  &cartas[i].pontosTuristicos, &cartas[i].densidadePopulacional, &cartas[i].pibPerCapita) == 9) {
        i++;
    }
    fclose(f);
    return i;
}

void listarPorEstado(struct CartaCidade cartas[], int quantidade) {
    char estado[30];
    lerString("Digite o estado para filtrar: ", estado, sizeof(estado));
    int encontrou = 0;
    for (int i = 0; i < quantidade; i++) {
        if (strcasecmp(cartas[i].estado, estado) == 0) {
            mostrarCarta(cartas[i], i);
            encontrou = 1;
        }
    }
    if (!encontrou) printf("Nenhuma carta encontrada para o estado %s.\n", estado);
}

void listarPorPopulacao(struct CartaCidade cartas[], int quantidade) {
    int limite = lerInt("Listar cidades com população acima de: ", 1, 100000000);
    int encontrou = 0;
    for (int i = 0; i < quantidade; i++) {
        if (cartas[i].populacao > limite) {
            mostrarCarta(cartas[i], i);
            encontrou = 1;
        }
    }
    if (!encontrou) printf("Nenhuma carta encontrada com população acima de %d.\n", limite);
}

void listarCartasMenu(struct CartaCidade cartas[], int quantidade) {
    int escolha;
    printf("1 - Listar todas\n");
    printf("2 - Listar por estado\n");
    printf("3 - Listar por população mínima\n");
    printf("Escolha uma opção: ");
    scanf("%d", &escolha); limparBuffer();
    switch (escolha) {
        case 1:
            for (int i = 0; i < quantidade; i++) mostrarCarta(cartas[i], i);
            break;
        case 2:
            listarPorEstado(cartas, quantidade);
            break;
        case 3:
            listarPorPopulacao(cartas, quantidade);
            break;
        default:
            printf("Opção inválida.\n");
    }
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
        printf("2 - Listar cartas\n");
        printf("3 - Comparar duas cartas\n");
        printf("4 - Editar carta\n");
        printf("5 - Remover carta\n");
        printf("6 - Salvar cartas em arquivo\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao); limparBuffer();

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
                else listarCartasMenu(cartas, quantidade);
                break;
            case 3:
                if (quantidade < 2) {
                    printf("Cadastre pelo menos duas cartas.\n");
                    break;
                }
                {
                int i1 = lerInt("Escolha o índice da primeira carta (1 ... n): ", 1, quantidade) - 1;
                int i2 = lerInt("Escolha o índice da segunda carta (1 ... n): ", 1, quantidade) - 1;
                if (i1 == i2) {
                    printf("Escolha cartas diferentes.\n");
                    break;
                }
                printf("Atributos disponíveis para comparação:\n");
                printf("0 - População\n1 - PIB\n2 - Área\n3 - Pontos turísticos\n4 - Densidade populacional\n5 - PIB per capita\n");
                int atributo = lerInt("Informe o número do atributo: ", 0, 5);
                compararCartas(cartas[i1], cartas[i2], atributo);
                }
                break;
            case 4:
                if (quantidade == 0) { printf("Nenhuma carta cadastrada.\n"); break; }
                {
                int idx = lerInt("Informe o índice da carta para editar (1 ... n): ", 1, quantidade) - 1;
                editarCarta(&cartas[idx]);
                }
                break;
            case 5:
                if (quantidade == 0) { printf("Nenhuma carta cadastrada.\n"); break; }
                {
                int idx = lerInt("Informe o índice da carta para remover (1 ... n): ", 1, quantidade) - 1;
                removerCarta(cartas, &quantidade, idx);
                }
                break;
            case 6:
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
