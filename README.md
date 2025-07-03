# Super Trunfo - Cidades do Mundo

Este é um exemplo simples de programa em linguagem C, inspirado no jogo **Super Trunfo**, com cartas de cidades e alguns atributos para cadastro e comparação.

## Funcionalidades

- Cadastro de cartas de cidades, informando:
  - Estado
  - Código
  - Nome da cidade
  - População
  - PIB (em bilhões)
  - Área (em km²)
  - Número de pontos turísticos
- Cálculos automáticos:
  - Densidade populacional
  - PIB per capita
- Listagem das cartas cadastradas
- Menu simples de interação

## Como compilar e executar

1. Compile o código (exemplo para GCC):
   ```
   gcc super_trunfo_cidades.c -o super_trunfo_cidades
   ```
2. Execute o programa:
   ```
   ./super_trunfo_cidades
   ```

## Exemplo de uso

```
Bem-vindo ao Super Trunfo - Cidades do Mundo!

Menu:
1 - Cadastrar nova carta
2 - Listar cartas cadastradas
0 - Sair
Escolha uma opção: 1
Digite o nome do estado: Bahia
...
```

## Possíveis melhorias

- Comparar atributos entre cartas (como no jogo Super Trunfo original)
- Salvar e carregar cartas em arquivos
- Limitar ou expandir o número máximo de cartas
- Interface gráfica

---

Feito para fins didáticos.
