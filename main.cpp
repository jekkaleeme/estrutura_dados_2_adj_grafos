#include <stdio.h>
#include <stdlib.h>
#define GRAPH_H
#define true 1
#define false 0
typedef int bool;
typedef int TIPO;

typedef struct adjacencia {
    int vertice;
    TIPO peso;
    struct adjacencia *prox;
}ADJACENCIA;

typedef struct vertice {
    bool visitado;
    ADJACENCIA *cab;
}VERTICE;

typedef struct grafo {
    int vertices;
    int arestas;
    VERTICE *adj;
}GRAFO;

GRAFO *newGraph (int v){
    int i;

    GRAFO *g = (GRAFO *)malloc(sizeof(GRAFO));
    g->vertices = v;
    g->arestas = 0;
    g-> adj = (VERTICE *)malloc(v*sizeof(VERTICE));

    for(i=0; i<v; i++){
        g->adj[i].cab = NULL;
    }

    return g;
}

ADJACENCIA *newAdjacent(int v, int peso){
    ADJACENCIA *temp = (ADJACENCIA *)malloc(sizeof(ADJACENCIA));
    temp->vertice = v;
    temp->peso = peso;
    temp->prox = NULL;

    return temp;
}

void newEdge(GRAFO *gr, int vi, int vf, TIPO p){
    if(!gr){ 
        printf("Grafo nao existe.\n");
        return;
    }
    if((vf<0) || (vf >= gr->vertices)) {
        printf("Valores negativos no grafo\n");
        return;
    }
    if((vi<0) || (vf >= gr->vertices)){
        printf("Valores maiores que o numero de vertices\n");
        return;
    }

    ADJACENCIA *novo = newAdjacent(vf, p);
    
    novo->prox = gr->adj[vi].cab;
    gr->adj[vi].cab = novo;
    gr->arestas++;
    printf("Aresta v%d -> v%d e peso: %d criada.\n", vi, vf, p);
}

void output(GRAFO *gr){
    if(!gr) return;

    printf("Vertices: %d | Arestas: %d \n", gr->vertices, gr->arestas);
    int i;

    for(i=0; i<gr->vertices; i++){
        printf("%d: ", i);
        ADJACENCIA *ad = gr->adj[i].cab;
            while(ad){
                printf("%d(%d) ", ad->vertice, ad->peso);
                ad = ad->prox;
            }
        printf("\n");
    }
}

int** matrix(GRAFO *gr){
    if(!gr) return NULL;

    int i, j;
    int** M = malloc(gr->vertices * sizeof(int *));
    for (i=0; i<gr->vertices; i++)
         M[i] = malloc(gr->vertices * sizeof(int));

    for(i = 0; i < gr->vertices; i++){
        for(j = 0; j < gr->vertices; j++)
            M[i][j] = 0;
    }

    for(i=0; i < gr->vertices; i++){
        ADJACENCIA *ad = gr->adj[i].cab;
            while(ad){
                M[i][ad->vertice] = ad->peso;
                M[ad->vertice][i] = ad->peso;
                ad = ad->prox;
            }
    }
    return M;
}

void outputMatrix(GRAFO *gr){
    if(!gr) return;

    int i, j;
    int M[gr->vertices][gr->vertices];

    for(i = 0; i < gr->vertices; i++){
        for(j = 0; j < gr->vertices; j++)
            M[i][j] = 0;
    }

    for(i=0; i < gr->vertices; i++){
        ADJACENCIA *ad = gr->adj[i].cab;
            while(ad){
                M[i][ad->vertice] = ad->peso;
                M[ad->vertice][i] = ad->peso;
                ad = ad->prox;
            }
    }

    printf("     ");
    for(i = 0; i < gr->vertices; i++)
        if(i<10)
            printf("| 0%d ", i);
        else
            printf("| %d ", i);
        
    printf("\n");
    for(i = 0; i < gr->vertices; i++){
        if(i<10)
            printf("| 0%d ", i);
        else
            printf("| %d ", i);
        
        for(j = 0; j < gr->vertices; j++){
            if(M[i][j]<10)
                printf("| 0%d ", M[i][j]);
            else
                printf("| %d ", M[i][j]);
        }
        printf("\n");
    }
}

void shortest_path(GRAFO *gr, int origem, int destino){
    int i, vert, k, NovaDist, min;
    int *M, *L, *A, *caminho;
    M = (int*) malloc(gr->vertices*sizeof(int));
    L = (int*) malloc(gr->vertices*sizeof(int));
    A = (int*) malloc(gr->vertices*sizeof(int));
    caminho = (int*) malloc(gr->vertices*3*sizeof(int));
    
    int** Mat = (int**) malloc(gr->vertices*sizeof(int*));
    Mat = matrix(gr);
    
    for(i=0;i<gr->vertices;i++){
        M[i] = 0;
        L[i] = 300000;
        A[i] = -1;
    }
    vert = origem;
    L[vert] = 0;
    while (vert != destino && vert != -1){
        for(i=0;i<gr->vertices;i++)
            if(Mat[vert][i] != 0 && M[i] == 0){
                NovaDist = L[vert] + Mat[vert][i];
                if(NovaDist < L[i]){
                    L[i] = NovaDist;
                    A[i] = vert;
                }
            }
        M[vert] = 1;
        min = 300000;
        vert = -1;
        
        for(i=0;i<gr->vertices;i++)
            if(M[i]==0 && L[i] < min){
                min = L[i];
                vert = i;
            }
        
    }

    if(vert == destino){
        printf("O caminho mais curto entre v%d e v%d, tem comprimento: %d\nCaminho: ", origem, destino, L[destino]);
        caminho[0] = destino;
        k = 1;
        while(vert != origem){
            caminho[k] = A[vert];
            vert = A[vert];
            k++;
        }
        for(i=k-1;i>=0;i--){
            printf("%d", caminho[i]);
            if(i > 0)
                printf(" -> ");
        }
    }else
        printf("Nao existe caminho entre v%d e v%d", origem, destino);
}

GRAFO *newGraph (int v);

ADJACENCIA *newAdjacent(int v, int peso);

void newEdge(GRAFO *gr, int vi, int vf, TIPO p);

void output(GRAFO *gr);

void outputMatrix(GRAFO *gr);

int** matrix(GRAFO *gr);

void shortest_path(GRAFO *gr, int origem, int destino);

int main(){
    GRAFO *graph1 = NULL;
    graph1 = newGraph(6);

    newEdge(graph1, 0, 1, 1);
    newEdge(graph1, 0, 2, 4);

    newEdge(graph1, 1, 2, 4);
    newEdge(graph1, 1, 3, 2);
    newEdge(graph1, 1, 4, 7);

    newEdge(graph1, 2, 3, 3);
    newEdge(graph1, 2, 4, 5);

    newEdge(graph1, 3, 4, 4);
    newEdge(graph1, 3, 5, 6);

    newEdge(graph1, 4, 5, 7);

    printf("\n");
    output(graph1);
    printf("\n");
    outputMatrix(graph1);
    printf("\n");
    shortest_path(graph1, 0, 5);
    return 0;
}