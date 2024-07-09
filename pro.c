
#ifndef nodo_arbol_prefijo_h
#define nodo_arbol_prefijo_h
#include "nodo_arbol_prefijo.h"
#endif /* nodo_arbol_prefijo_h */

#ifndef lista_ordenada_palabras_h
#define lista_ordenada_palabras_h
#include "lista_ordenada_palabras.h"
#endif /* lista_ordenada_palabras_h */

#include <stdio.h>
#include <stdlib.h>

int main() {
    NodoArbolPrefijo *arbol = crearArchivo("tt.txt");
    ListaOrdenadaPalabras *lista = NULL;

    if (arbol != NULL) {
        lista = palabrasEnArbolOrdenadas(arbol, lista);
        liberarMemoria(arbol);
    }

    char **topDiez = darDiezDatos(lista);
    for (int i = 0; i < 10 && topDiez[i] != NULL; i++) {
        printf("%s\n", topDiez[i]);
    }

    free(topDiez);
    while (lista != NULL) {
        ListaOrdenadaPalabras *temp = lista;
        lista = lista->siguiente;
        free(temp->palabraListada);
        free(temp);
    }

    return 0;
}