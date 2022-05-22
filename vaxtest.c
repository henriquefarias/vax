#include "vaxlib.h"

/* Testa se o registro está funcionando. */
void test_reg(void)
{
    MEDICO dr_teste;

    strcpy(dr_teste.nome, "DOUTOR TESTANDO");
    strcpy(dr_teste.crm, "777");
    strcpy(dr_teste.status_crm, "A");

    printf("*** TESTANDO REGISTRO DE MÉDICO ***\n\n");
    printf("\nNOME COMPLETO: %s\nCRM: %s\nStatus: %s", dr_teste.nome, dr_teste.crm, dr_teste.status_crm);
}

/*  Gera uma lista com valores fixos para testes. */
MEDICO *build_test_list(void)
{
    int tamanho_lista = TEST_LIST_SIZE;

    MEDICO *lista_medicos = (MEDICO *) malloc(tamanho_lista * sizeof(MEDICO));

    strcpy(lista_medicos[0].nome, "DOUTOR ZERO");
    strcpy(lista_medicos[0].crm, "999");
    strcpy(lista_medicos[0].status_crm, "A");

    strcpy(lista_medicos[1].nome, "DOUTOR UM");
    strcpy(lista_medicos[1].crm, "888");
    strcpy(lista_medicos[1].status_crm, "A");

    strcpy(lista_medicos[2].nome, "DOUTOR DOIS");
    strcpy(lista_medicos[2].crm, "777");
    strcpy(lista_medicos[2].status_crm, "A");

    strcpy(lista_medicos[3].nome, "DOUTOR TRÊS");
    strcpy(lista_medicos[3].crm, "666");
    strcpy(lista_medicos[3].status_crm, "A");

    return(lista_medicos);
}

/*  Imprime um array de médicos. */
void print_regs(MEDICO *lista_medicos)
{
    int i;
    for (i = 0; i < TEST_LIST_SIZE; i++)
        printf("\nNOME:   %s\tCRM: %s\tStatus: %s\n", lista_medicos[i].nome, lista_medicos[i].crm, lista_medicos[i].status_crm);
}


void test_bubble_sort(void)
{
    int i;
    MEDICO *lista_medicos = build_test_list();

    printf("\n*** TESTANDO BUBBLE SORT ***\n");
    printf("(Os registros serão ordenados por odem crescente de CMR)\n\n");

    printf("Lista de registros antes do sort:\n\n");
    print_regs(lista_medicos);

    bubble_sort(lista_medicos, TEST_LIST_SIZE);

    printf("\n\nLista de registros depois do sort:\n\n");
    print_regs(lista_medicos);
}


void test_selection_sort(void)
{
    int i;
    MEDICO *lista_medicos = build_test_list();

    printf("\n*** TESTANDO SELECTION SORT ***\n");
    printf("(Os registros serão ordenados por ordem crescente de CMR)\n\n");

    printf("Lista de registros antes do sort:\n\n");
    print_regs(lista_medicos);

    selection_sort(lista_medicos, TEST_LIST_SIZE);

    printf("\n\nLista de registros depois do sort:\n\n");
    print_regs(lista_medicos);
}


/*  Imprime conteúdo de um arquivo na tela.
    (OBS: A solução adequada seria usar um buffer maior para imprimir o arquivo em pedaços ao invés de char por char.) */
void print_file(char *filename)
{
    int current_char;
    FILE *file = fopen(filename, "r");

    validate_allocation(file);
    current_char = getc(file);

    /*  A cada iteração desse loop, um caractere do arquivo é lido e impresso. O loop termina quando é encontrado o caractere especial EOF - End of File. */
    while(current_char != EOF)
    {
        putchar(current_char);
        current_char = getc(file);
    }

    fclose(file);
}


void main(void)
{
    setlocale(LC_ALL, "");
    system("cls");
    // test_reg();
    // test_bubble_sort();
    // test_selection_sort();
    // print_file("csv_sample.csv");
    // csv_reg_count("MEDICOSCREMESP.CSV");
    getch();
}
