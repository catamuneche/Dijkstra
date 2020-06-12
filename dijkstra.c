#include <stdio.h>
#include <stdlib.h>

#define inf 30000

#define TRUE 1
#define FALSE 0

typedef int BOOL;

int n;
int v0 = 0;
int **Grafo;
BOOL *Visitados;
int *Costo;
int *NodoAnterior;

int NumeroNodosSinVisitar();
int NodoMinimoCostoSinVisitar();
void Dijkstra();
void ImprimeCaminos();
int **DaMemoriaGrafo(int n);
int *DaMemoriaArreglo(int n);
void LeeGrafo();

int NumeroNodosSinVisitar()
{
    int i, cont;

    i = 0;
    cont = 0;

    while (i < n)
    {
        if (!Visitados[i]){
            cont++;
        }
        i++;
    }
   return cont;
}
int NodoMinimoCostoSinVisitar()
{
    int i, nodo, minimo;

    i = 0;
    while (Visitados[i]){
        i++;
    }

    minimo = Costo[i];
    nodo = i;

    i++;
    while(i < n)
    {
        if (!Visitados[i])
        {
            if (Costo[i] < minimo)
            {
                minimo = Costo[i];
                nodo = i;
            }
        }
        i++;
    }
    return nodo;
}
void Dijkstra()
{
    int i, j, w=v0;

    Visitados[v0] = TRUE;
    for(i=0;i<n;i++)
    {
        if (Grafo[v0][i] == 0)
            Costo[i] = inf;
        else
            Costo[i] = Grafo[v0][i];
        NodoAnterior[i] = v0;
    }
    while (NumeroNodosSinVisitar()>1)
    {
        w = NodoMinimoCostoSinVisitar();
        Visitados[w] = TRUE;
        for(j=0;j<n;j++)
        {
            if ((Grafo[w][j] != 0) && (!Visitados[j]))
            {
                if (Costo[w] + Grafo[w][j] < Costo[j])
                {
                    NodoAnterior[j] = w;
                    Costo[j] = Costo[w] + Grafo[w][j];
                }
            }
        }
    }
}
void ImprimeCaminos()
{
    int *Camino, i, j, nodo;

    Camino = DaMemoriaArreglo(n);

    for(i=0;i<n;i++)
    {
        if (i != v0)
        {
            j = 0;
            Camino[j] = i;
            j++;
            nodo = NodoAnterior[i];
            while(nodo != v0)
            {
                Camino[j] = nodo;
                j++;
                nodo = NodoAnterior[nodo];
            }
            Camino[j] = nodo;

            printf("\n\nCamino desde %2d hasta %2d (costo:%2d): ", v0, i, Costo[i]);

            while (j >= 0)
            {
                printf("%3d", Camino[j]);
                j--;
            }
        }
    }
}
int **DaMemoriaGrafo(int n)
{
    int **aux;
    int i;

    aux = (int **)malloc(n*(sizeof(int *)));
    if (!aux)
    {
        printf("\nNo hay memoria suficiente.");
        exit(1);
    }
    for(i=0;i<n;i++)
    {
        aux[i] = (int *)malloc(n*(sizeof(int)));
        if (!aux[i])
        {
            printf("\nNo hay memoria suficiente.");
            exit(1);
        }
    }
    return aux;
}
int *DaMemoriaArreglo(int n)
{
    int *aux;
    int i;

    aux = (int *)malloc(n*(sizeof(int)));
    if (!aux)
    {
        printf("\nNo hay memoria suficiente.");
        exit(1);
    }
    for(i=0;i<n;i++)
        aux[i] = 0;

    return aux;
}
void LeeGrafo()
{
    FILE *arch;
    int i, j;

    arch = fopen("grafo.txt", "r");
    if (!arch)
    {
        printf("\nNo se puede abrir el archivo.");
        exit(1);
    }
    fscanf(arch, "%d", &n);

    Grafo = DaMemoriaGrafo(n);
    Visitados = DaMemoriaArreglo(n);
    Costo = DaMemoriaArreglo(n);
    NodoAnterior = DaMemoriaArreglo(n);

    for (i=0;i<n;i++)
    {
        for (j=0;j<n;j++)
        {
            fscanf(arch,"%d",&Grafo[i][j]);
        }
    }
    fclose(arch);
}
int main()
{
    LeeGrafo();
    Dijkstra();
    ImprimeCaminos();
    printf("\n\n\n");
    return 1;
}
