#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct pessoa
{
    int tipo;
    void *info;
    struct pessoa *prox;
} Pessoa;

typedef struct aluno
{
    int matricula;
    int anoIngresso;
    char nome[50];
    char curso[30];
} Aluno;

typedef struct professor
{
    int matricula;
    float salario;
    char nome[50];
} Professor;

void imprimirLista(Pessoa *p)
{
    int i = 0;
    while (p != NULL)
    {
        if (p->tipo == 2)
        {
            Aluno *a = (Aluno *)p->info;
            printf("Pos:%d  Nome:%s  Matricula:%d  Curso:%s  Ano de Ingresso: %d\n", i, a->nome, a->matricula, a->curso, a->anoIngresso);
        }
        else
        {
            Professor *m = (Professor *)p->info;
            printf("Pos:%d  Nome:%s  Matricula:%d  Salario:%.2f\n", i, m->nome, m->matricula, m->salario);
        }
        p = p->prox;
        i++;
    }
}

Pessoa *inserir(Pessoa *p, int tipo, void *info)
{
    Pessoa *novo = (Pessoa *)malloc(sizeof(Pessoa));

    novo->tipo = tipo;
    novo->info = info;
    novo->prox = NULL;

    if (p == NULL)
    {
        return novo;
    }
    else
    {
        Pessoa *aux = p;
        while (aux->prox != NULL)
        {
            aux = aux->prox;
        }
        aux->prox = novo;
        return p;
    }
}

Pessoa *remover(Pessoa *p, int matricula)
{
    Pessoa *anterior = NULL;
    Pessoa *atual = p;

    while (atual != NULL)
    {
        if (atual->tipo == 2)
        {
            Aluno *a = (Aluno *)atual->info;
            if (a->matricula == matricula)
            {
                if (anterior == NULL)
                {
                    p = atual->prox;
                }
                else
                {
                    anterior->prox = atual->prox;
                }
                free(atual->info);
                free(atual);
                return p;
            }
        }
        else if (atual->tipo == 1)
        {
            Professor *m = (Professor *)atual->info;
            if (m->matricula == matricula)
            {
                if (anterior == NULL)
                {
                    p = atual->prox;
                }
                else
                {
                    anterior->prox = atual->prox;
                }
                free(atual->info);
                free(atual);
                return p;
            }
        }
        anterior = atual;
        atual = atual->prox;
    }
    return p;
}

void imprimirPorMatricula(Pessoa *p, int matricula)
{
    while (p != NULL)
    {
        if (p->tipo == 2)
        {
            Aluno *a = (Aluno *)p->info;
            if (a->matricula == matricula)
            {
                printf("\nNome:%s  Matricula:%d  Curso:%s  Ano de Ingresso:%d\n", a->nome, a->matricula, a->curso, a->anoIngresso);
                break;
            }
        }
        else if (p->tipo == 1)
        {
            Professor *m = (Professor *)p->info;
            if (m->matricula == matricula)
            {
                printf("\nNome:%s  Matricula:%d  Salario:%f\n", m->nome, m->matricula, m->salario);
                break;
            }
        }
        p = p->prox;
    }
}

void imprimirPorCurso(Pessoa *p, char curso[30])
{
    while (p != NULL)
    {
        if (p->tipo == 2)
        {
            Aluno *a = (Aluno *)p->info;
            if (strcmp(strlwr(curso), strlwr(a->curso)) == 0)
            {
                printf("\nNome:%s  Matricula:%d  Curso:%s  Ano de Ingresso:%d\n", a->nome, a->matricula, a->curso, a->anoIngresso);
            }
        }
        p = p->prox;
    }
}

void imprimirMaioresSalarios(Pessoa *p)
{
    int salario = 0;
    Pessoa *aux = p;
    while (aux != NULL)
    {
        if (aux->tipo == 1)
        {
            Professor *m = (Professor *)aux->info;
            if (m->salario > salario)
            {
                salario = m->salario;
            }
        }
        aux = aux->prox;
    }
    while (p != NULL)
    {
        if (p->tipo == 1)
        {
            Professor *m = (Professor *)p->info;
            if (m->salario == salario)
            {
                printf("\nNome:%s  Matricula:%d  Salario:%.2f\n", m->nome, m->matricula, m->salario);
            }
        }
        p = p->prox;
    }
}

int main()
{

    Pessoa *p = NULL;
    Aluno *a;
    Professor *m;

    int opc = 0, x = 0, tipo = 0;

    while (opc != 6)
    {
        printf("\n1-Inserir\n2-Remover\n3-Imprimir pela matricula\n4-Imprimir por curso\n5-Imprimir maiores salarios\n6-Sair\n");
        scanf("%d", &opc);
        getchar();

        switch (opc)
        {
        case 1:
            printf("\n1-Professor\n2-Aluno:\n");
            scanf("%d", &tipo);
            getchar();

            if (tipo == 2)
            {
                a = (Aluno *)malloc(sizeof(Aluno));

                printf("Digite nome:\n");
                fgets(a->nome, sizeof(a->nome), stdin);
                a->nome[strcspn(a->nome, "\n")] = '\0';

                printf("Digite curso:\n");
                fgets(a->curso, sizeof(a->curso), stdin);
                a->curso[strcspn(a->curso, "\n")] = '\0';

                printf("Digite matricula:\n");
                scanf("%d", &a->matricula);
                getchar();

                printf("Digite ano de ingresso:\n");
                scanf("%d", &a->anoIngresso);
                getchar();

                p = inserir(p, tipo, a);
            }
            else if (tipo == 1)
            {
                m = (Professor *)malloc(sizeof(Professor));

                printf("Digite nome:\n");
                fgets(m->nome, sizeof(m->nome), stdin);
                m->nome[strcspn(m->nome, "\n")] = '\0';

                printf("Digite matricula:\n");
                scanf("%d", &m->matricula);

                printf("Digite o salario:\n");
                scanf("%f", &m->salario);
                getchar();

                p = inserir(p, tipo, m);
            }
            else
            {
                printf("Tipo invalido!");
            }
            break;
        case 2:
            printf("Matricula:");
            scanf("%d", &x);
            p = remover(p, x);
            break;
        case 3:
            printf("Matricula:");
            scanf("%d", &x);

            imprimirPorMatricula(p, x);

            break;
        case 4:
            char curso[30];
            // getchar();
            printf("Digite curso:\n");

            fgets(curso, sizeof(curso), stdin);
            curso[strcspn(curso, "\n")] = '\0';

            imprimirPorCurso(p, curso);
            break;
        case 5:
            imprimirMaioresSalarios(p);
            break;
        case 6:
            printf("Saindo..");
            break;
        /*case 7:
            imprimirLista(p);
            break;
            */
        default:
            break;
        }
    }
    free(a);
    return 0;
}