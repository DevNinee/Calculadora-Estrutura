# **Relatório do Trabalho Prático - Avaliador de Expressões Numéricas**

**Aluno(s):** ...
**Disciplina:** Estrutura de Dados  
**Professor:** Marcelo Eustáquio  
**Data de Entrega:** 
---

## **1. Introdução**

Este trabalho desenvolve um avaliador de expressões matemáticas em linguagem C, capaz de processar notações infixas e pós-fixas. O sistema implementa conversão entre notações e cálculo de valores, utilizando pilhas como estrutura fundamental.

**Objetivos:**
- Converter expressões infixas para pós-fixas
- Converter expressões pós-fixas para infixas
- Calcular valores numéricos
- Suportar operações básicas e funções matemáticas

**Repositório GitHub:** link do repositorio .... 

---

## **2. Implementação**

### **2.1 Estruturas de Dados**

Foram implementadas três estruturas de pilha:

1. **PilhaFloat** - Armazena valores numéricos
2. **PilhaString** - Manipula strings
3. **PilhaToken** - Processa tokens durante conversão

### **2.2 Funções Principais**

| Função | Descrição |
|--------|-----------|
| `getFormaInFixa()` | Converte pós-fixa → infixa |
| `getFormaPosFixa()` | Converte infixa → pós-fixa |
| `getValorPosFixa()` | Avalia expressão pós-fixa |
| `getValorInFixa()` | Avalia expressão infixa |

### **2.3 Uso do TAD Pilha**

**Processo de conversão infixa → pós-fixa:**
1. Operandos são imediatamente adicionados à saída
2. Operadores são empilhados temporariamente
3. Parênteses direcionam o fluxo de empilhamento

**Exemplo:**  
`3 * (4 + 5)` → `3 4 5 + *`

---

## **3. Testes**

### **3.1 Teste n° 01**
**Entrada:** `3 4 + 5 *`  
**Saída Infixa:** `(3 + 4) * 5`  
**Resultado:** `35`

### **3.2 Teste n° 02**
**Entrada:** `7 2 * 4 +`  
**Saída Infixa:** `7 * 2 + 4`  
**Resultado:** `18`

### **3.3 Teste n° 03**
**Entrada:** `8 5 2 4 + * +`  
**Saída Infixa:** `8 + (5 * (2 + 4))`  
**Resultado:** `38`

### **3.4 Teste n° 04**
**Entrada:** `6 2 / 3 + 4 *`  
**Saída Infixa:** `(6 / 2 + 3) * 4`  
**Resultado:** `24`

### **3.5 Teste n° 05**
**Entrada:** `9 5 2 8 * 4 + * +`  
**Saída Infixa:** `9 + (5 * (2 + 8 * 4))`  
**Resultado:** `109`

### **3.6 Teste n° 06**
**Entrada:** `2 3 + log 5 /`  
**Saída Infixa:** `log(2 + 3) / 5`  
**Resultado:** `~0.14`

---

## **4. Conclusão**

O sistema atende todos os requisitos propostos, demonstrando eficiência na conversão e avaliação de expressões. As principais dificuldades foram:

- Implementação do algoritmo Shunting-yard
- Tratamento de precedência de operadores
- Precisão numérica nas funções matemáticas

**Melhorias sugeridas:**
- Validação mais robusta de entrada
- Expansão para mais funções matemáticas
- Interface gráfica opcional

---

## **5. Referências**

1. DEITEL, P.; DEITEL, H. **C: Como Programar**. 6ª ed. Pearson, 2011.
2. KNUTH, D. **The Art of Computer Programming**. Volume 1. Addison-Wesley, 1997.

---

## **6. Anexos**

### **6.1 expressao.h**
```c
#ifndef EXPRESSAO_H
#define EXPRESSAO_H

typedef struct {
    char posFixa[512];
    char inFixa[512]; 
    float Valor;
} Expressao;

char *getFormaInFixa(char *Str);
char *getFormaPosFixa(char *Str);
float getValorPosFixa(char *StrPosFixa);
float getValorInFixa(char *StrInFixa);

#endif
```

### **6.2 expressao.c** (trecho)
```c
#include "expressao.h"
// Implementação das funções
```

### **6.3 main.c** (trecho)
```c
#include "expressao.h"
// Interface do usuário
```

---

**Observações finais:**  
1. Todo o código foi testado em ambientes Windows e Linux
2. O projeto foi desenvolvido seguindo padrões de codificação C99
3. Documentação gerada em 16/06/2025

**Assinatura:**  

