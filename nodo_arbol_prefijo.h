// IMPORTANTE: para que las pruebas puedan funcionar 
// las siguientes funciones deben estar presentes en 
// la implementación del árbol de prefijos:
// -Requisito 2
//  NodoArbolPrefijo *creaArbolPrefijoDesdeArchivo(char *nombreArchivoPalabras) check-pv
// -Requisito 3
//  NodoArbolPrefijo *avanzaEnArbol(NodoArbolPrefijo *arbol, char letra) check-pv
//  ListaOrdenadaPalabras *palabrasEnArbolOrdenadas(NodoArbolPrefijo *arbol)
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef lista_ordenada_palabras_h
#define lista_ordenada_palabras_h
#include "lista_ordenada_palabras.h"
#endif /* lista_ordenada_palabras_h */

typedef struct NodoArbolPrefijo {
    struct NodoArbolPrefijo *rama[26];
    char *palabra;
    int frecuencia;
} NodoArbolPrefijo;

NodoArbolPrefijo* crearRamaVacia() {
    NodoArbolPrefijo *rama = (NodoArbolPrefijo*)malloc(sizeof(NodoArbolPrefijo));
    if (rama != NULL) {
        for (int i = 0; i < 26; i++) {
            rama->rama[i] = NULL;
        }
        rama->palabra = NULL;
        rama->frecuencia = 0;
    }
    return rama;
}

NodoArbolPrefijo* avanzaEnArbol(NodoArbolPrefijo* arbol, int indice) {
    if (arbol->rama[indice] == NULL) {
        arbol->rama[indice] = crearRamaVacia();
    }
    return arbol->rama[indice];
}

void insertarPalabra(NodoArbolPrefijo *raiz, char *palabra, int frecuencia) {
    NodoArbolPrefijo *actual = raiz;
    char *originalPalabra = palabra; // Store the original pointer
    while (*palabra) {
        int pos = *palabra - 'a';
        if (pos < 0 || pos >= 26) {
            palabra++;
            continue;
        }
        if (actual->rama[pos] == NULL) {
            actual->rama[pos] = crearRamaVacia();
        }
        actual = avanzaEnArbol(actual, pos);
        palabra++;
    }
    actual->palabra = strdup(originalPalabra); // Use the original pointer
    actual->frecuencia = frecuencia;
}

NodoArbolPrefijo* crearArchivo(char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return NULL;
    }

    NodoArbolPrefijo *raiz = crearRamaVacia();
    if (raiz == NULL) {
        printf("RAIZ NULL ERROR");
        fclose(archivo);
        return NULL;
    }

    char palabra[256];
    int frecuencia;
    
    while (fscanf(archivo, "%s %d", palabra, &frecuencia) != EOF) {
        insertarPalabra(raiz, palabra, frecuencia);
    }

    fclose(archivo);
    return raiz;
}

void liberarMemoria(NodoArbolPrefijo *nodo) {
    if (nodo == NULL) {
        return;
    }
    for (int i = 0; i < 26; i++) {
        liberarMemoria(nodo->rama[i]);
    }
    if (nodo->palabra != NULL) {
        free(nodo->palabra);
    }
    free(nodo);
}


ListaOrdenadaPalabras* palabrasEnArbolOrdenadas(NodoArbolPrefijo *arbol, ListaOrdenadaPalabras *lista) {
    if (arbol == NULL) {
        return lista;
    }
    for (int i = 0; i < 26; i++) {
        lista = palabrasEnArbolOrdenadas(arbol->rama[i], lista);
    }
    if (arbol->palabra != NULL) {
        lista = ingresarDato(arbol->frecuencia, arbol->palabra, lista);
    }
    return lista;
}