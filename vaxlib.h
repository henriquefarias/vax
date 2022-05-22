#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <string.h>


/*  Tipos booleanos.

    Em C, todo valor equivalente a NULL é falso, e tudo que não é NULL é verdadeiro.
    Antes de compilar o código, o pré-processador de C irá substituir esses valores.
    Ou seja: quando aparecer um FALSE no código, ele será substituído por (NULL).
    O uso de parênteses não é necessário em todos os casos, mas é uma boa prática que previne erros.

    (OBS: Isso não é uma solução adequada. O ideal seria usar um typedef.)

*/
#define TRUE (!NULL)
#define FALSE (NULL)


/*  Tamanho de cada campo do registro +1 para o null terminator.
    OBS: ESTES VALORES SÃO PLACEHOLDERS!
*/
#define USER_SIZE (100+1)
#define CRM_SIZE (10+1)
#define STATUS_SIZE (1+1)
#define TEST_LIST_SIZE 4


/*  AMOSTRA DOS REGISTROS EM MEDICOSCREMESP.CSV:

        053579;ACHILLES MACHADO CRUZ                     ;A;1986-03-04;    -  -  ;SAO PAULO                            ;SP;MASTOLOGIA - GINECOLOGIA E OBSTETRICIA
        192864;BIANCA ELIZA HOEKSTRA                     ;A;2018-12-12;    -  -  ;RIBEIRAO PRETO                       ;SP;
        184673;CAMILA FURLAN RODRIGUES TEIXEIRA          ;I;2016-12-20;2020-08-19;ESTANCIA VELHA                       ;RS;
        175216;DENISE AKERMAN                            ;A;2015-11-17;    -  -  ;SAO PAULO                            ;SP;CIRURGIA GERAL - MASTOLOGIA
        196406;EDINILSON BUENO                           ;A;2018-05-02;    -  -  ;AMPARO                               ;SP;
        018580;SERGIO SCHUINDT                           ;I;1973-04-24;1988-03-29;LINS                                 ;SP;

    A estrutura parece ser a seguinte:

    [CRM];[NOME];[STATUS_CRM];[EXPEDIÇÃO];[CANCELAMENTO];[MUNICIPIO];[ESTADO];[ESPECIALIDADE]

    CRM: CRM do médico.

    NOME: Nome completo do médico.

    STATUS_CRM: Indica se o CRM está [A]tivo ou [I]nativo.

    EXPEDIÇÃO: Data que o CRM foi expedido.

    CANCELAMENTO: Data que o CRM foi cancelado. Note que este valor só existe nos CRM [I]nativos.

    MUNICÍPIO: Pode ser o endereço atual do médico ou o local onde o CRM foi expedido.

    ESTADO: Idem.

    ESPECIALIDADE: Pode ser a área de especialização ou o emprego atual.

*/


/* Registro individual do médico. Usaremos apenas os campos necessários. */
typedef struct
{
    char crm[CRM_SIZE];
    char nome[USER_SIZE];
    char status_crm[STATUS_SIZE];

} MEDICO;


/*  Troca dois registros de posição. */
void swap_reg(MEDICO *med1, MEDICO *med2)
{
    MEDICO temp_med;

    temp_med = *med1;
    *med1 = *med2;
    *med2 = temp_med;
}


/* Testa se alocação de memória foi bem sucedida. Caso negativo, encerra o programa. */
void validate_allocation(void *object)
{
    if (object == NULL)
    {
        system("cls");
        printf("*** ERRO AO ALOCAR MEMÓRIA! ***");
        getch();
        exit(EXIT_FAILURE);
    }
}


/*  Ordena uma lista de médicos (por ordem crescente de CRM) usando bubble sort. */
void bubble_sort(MEDICO *lista_medicos, int tamanho_lista)
{
    int i, j, strcmp_result;

    for (i = 0; i < (tamanho_lista - 1); i++)
    {
        for (j = 0; j < (tamanho_lista - 1 - i); j++)
        {
            /* strcmp retorna um valor positivo quando a segunda é menor que a primeira. */
            // strcmp_result = strcmp(lista_medicos[j].crm, lista_medicos[j+1].crm);

            if (strcmp(lista_medicos[j].crm, lista_medicos[j+1].crm) > 0 )
                swap_reg(&lista_medicos[j], &lista_medicos[j+1]);
        }
    }
}


/*  Ordena uma lista de médicos (por ordem crescente de CRM) usando selection sort. */
void selection_sort(MEDICO *lista_medicos, int tamanho_lista)
{
    int pos_min, i, j, strcmp_result;

    for(i = 0; i < (tamanho_lista - 1); i++)
    {
        pos_min = i;

        for (j = (i + 1); j < tamanho_lista; j++)
        {
            /* strcmp retorna um valor positivo quando a segunda é menor que a primeira. */
            // strcmp_result = strcmp(lista_medicos[pos_min].crm, lista_medicos[j].crm);

            if (strcmp(lista_medicos[pos_min].crm, lista_medicos[j].crm) > 0 )
                pos_min = j; /* pos_min recebe a posição do menor valor */
        }
        /* Se a posição do menor for diferente da que está passando, ocorre a troca */
        if (pos_min != i)
             swap_reg(&lista_medicos[i], &lista_medicos[pos_min]);
    }
}


/* Retorna a quantidade de registos em um arquivo CSV. */
void csv_reg_count(char *filename)
{
    int current_char;
    int reg_count = 0;
    FILE *file = fopen(filename, "r");

    validate_allocation(file);
    current_char = getc(file);

    /*  A cada iteração desse loop, um caractere do arquivo é lido e impresso. O loop termina quando é encontrado o caractere especial EOF - End of File. */
    while(current_char != EOF)
    {
        if (current_char == '\n')
            reg_count++;
        
        current_char = getc(file);
    }
    fclose(file);
    
    /* O último registo não possui newline, portanto é preciso somar +1 ao total. */
    reg_count++;
    
    printf("Total: %d registros em %s", reg_count, filename);
}
