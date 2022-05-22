#include "vaxlib.h"


/* ========================== FUN��ES AUXILIARES ========================== */

/*  Retorna uma lista de m�dicos com valores fixos para fins de teste. */
MEDICO *build_test_list(void)
{
    int tamanho_lista = TEST_LIST_SIZE;

    /* calloc() � mais adequada que malloc() nesse caso, pois ela inicializa a mem�ria zerada. Isso evita que lixo de mem�ria seja gravado no DAT. */
    MEDICO *lista_medicos = calloc(tamanho_lista, sizeof(MEDICO));

    strcpy(lista_medicos[0].nome, "DOUTOR ZERO");
    strcpy(lista_medicos[0].crm, "999");
    strcpy(lista_medicos[0].status_crm, "A");

    strcpy(lista_medicos[1].nome, "DOUTOR UM");
    strcpy(lista_medicos[1].crm, "888");
    strcpy(lista_medicos[1].status_crm, "A");

    strcpy(lista_medicos[2].nome, "DOUTOR DOIS");
    strcpy(lista_medicos[2].crm, "777");
    strcpy(lista_medicos[2].status_crm, "A");

    strcpy(lista_medicos[3].nome, "DOUTOR TR�S");
    strcpy(lista_medicos[3].crm, "666");
    strcpy(lista_medicos[3].status_crm, "I");

    return(lista_medicos);
}


/*  Imprime um array de m�dicos. */
void print_regs(MEDICO *lista_medicos)
{
    int i;
    for (i = 0; i < TEST_LIST_SIZE; i++)
        printf("\nNOME:   %s\tCRM: %s\tStatus: %s\n", lista_medicos[i].nome, lista_medicos[i].crm, lista_medicos[i].status_crm);
}


/*  Imprime o conte�do de um arquivo na tela.
    (OBS: A solu��o adequada seria usar um buffer maior para imprimir o arquivo em partes ao ao inv�s de char por char.) */
void print_file(char *filename)
{
    int current_char;

    FILE *file = fopen(filename, "r");
    validate_allocation(file);

    /*  A fun��o getc() l� o pr�ximo caractere do arquivo especificado e retorna seu valor. Podemos chamar getc() repetidamente para percorrer um arquivo.
        O loop termina quando � encontrado o caractere especial EOF - End of File. */
    while((current_char = getc(file)) != EOF)
        putchar(current_char);

    fclose(file);
}


/* ========================== FUN��ES DE TESTE ========================== */

/* Testa registro individual de m�dico. */
void test_reg(void)
{
    MEDICO dr_teste;

    strcpy(dr_teste.nome, "DOUTOR TESTANDO");
    strcpy(dr_teste.crm, "777");
    strcpy(dr_teste.status_crm, "A");

    printf("*** TESTANDO REGISTRO DE M�DICO ***\n\n");
    printf("\nNOME COMPLETO: %s\nCRM: %s\nStatus: %s", dr_teste.nome, dr_teste.crm, dr_teste.status_crm);
}


/* Testa bubble sort. */
void test_bubble_sort(void)
{
    int i;
    MEDICO *lista_medicos = build_test_list();

    printf("*************** TESTANDO BUBBLE SORT ***************\n");
    printf("(Os registros ser�o ordenados por odem crescente de CMR)\n\n");

    printf("Lista de registros antes do sort:\n\n");
    print_regs(lista_medicos);

    bubble_sort(lista_medicos, TEST_LIST_SIZE);

    printf("\n\nLista de registros depois do sort:\n\n");
    print_regs(lista_medicos);
}


/* Testa selection sort. */
void test_selection_sort(void)
{
    int i;
    MEDICO *lista_medicos = build_test_list();

    printf("*************** TESTANDO SELECTION SORT ***************\n");
    printf("(Os registros ser�o ordenados por ordem crescente de CMR)\n\n");

    printf("Lista de registros antes do sort:\n\n");
    print_regs(lista_medicos);

    selection_sort(lista_medicos, TEST_LIST_SIZE);

    printf("\n\nLista de registros depois do sort:\n\n");
    print_regs(lista_medicos);
}


/* Gera arquivo DAT pr�-definido para fins de teste. */
void make_test_dat(void)
{
    int i;

    MEDICO *lista_medicos = build_test_list();
    validate_allocation(lista_medicos);

    FILE *test_dat = fopen("test_meds.dat", "w");
    validate_allocation(test_dat);

    for (i = 0; i < TEST_LIST_SIZE; i++)
    {
        fwrite(&lista_medicos[i], sizeof(MEDICO), 1, test_dat);
        validate_allocation(test_dat);
    }

    fclose(test_dat);
}


/* Exibe menu com op��es de teste. */
void test_menu(void)
{
    char input;

    do
    {
        system("cls");
        printf("*************** PROJETO VAX - MENU DE TESTES ***************\n\n");
        printf("Escolha a op��o:\n\n");
        printf("1. Testar registro individual de m�dico.\n");
        printf("2. Testar bubble sort\n");
        printf("3. Testar selection sort\n");
        printf("4. Imprime conte�do do CSV amostra\n");
        printf("5. Conta o n�mero de registros no CSV amostra\n");
        printf("6. Gera arquivo DAT para teste\n");
        printf("\nx. Sair");

        fflush(stdin);
        input = getch();
        
        switch(input)
        {
            case '1':
            {
                system("cls");
                test_reg();
                getch();
                break;
            }
            
            case '2':
            {
                system("cls");
                test_bubble_sort();
                getch();
                break;
            }
            
            case '3':
            {
                system("cls");
                test_selection_sort();
                getch();
                break;
            }
            
            case '4':
            {
                system("cls");
                print_file("csv_sample.csv");
                getch();
                break;
            }
            
            case '5':
            {
                system("cls");
                csv_reg_count("csv_sample.csv");
                getch();
                break;
            }
            
            case '6':
            {
                system("cls");
                make_test_dat();
                break;
            }
            
            case 'x':
            {
                exit_program();
                // break;
            }
            
            default: continue;
        }

    } while (input != 'x');
}


void main(void)
{
    setlocale(LC_ALL, "");
    system("cls");
    test_menu();
}
