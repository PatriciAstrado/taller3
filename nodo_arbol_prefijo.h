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

typedef struct NodoArbolPrefijo {//est-datos de prefijos
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

NodoArbolPrefijo* avanzaEnArbol(NodoArbolPrefijo* arbol, int indice) {//dado un numero indice avanza en dicha direccion
    if (arbol->rama[indice] == NULL) {
        arbol->rama[indice] = crearRamaVacia();
    }
    return arbol->rama[indice];
}

void insertarPalabra(NodoArbolPrefijo *raiz, char *palabra, int frecuencia) {//guarda palabra en arbol
    NodoArbolPrefijo *actual = raiz;
    char *originalPalabra = palabra;
    while (*palabra) {//mientras no sea el final de la palabra
        int pos = *palabra - 'a';//tomamos posicion actual de la palabra y pasamos a valos ASCII

        if (pos < 0 || pos >= 26) {//si NO esta en el rango del ABC pasamos de largo
            palabra++;//podriamos cambiarlo para que lea todo
            continue;//porque en caso de la é se la saltara
        }

        if (actual->rama[pos] == NULL) { //si la rama no existe en esa dirrecion la crea
            actual->rama[pos] = crearRamaVacia();
        }
        actual = avanzaEnArbol(actual, pos);//avanzamos por el arbol en dada dirrecion 
        palabra++;//tomamos siguiente letra de palabra dada
    }
    actual->palabra = strdup(originalPalabra); //guardamos duplicando la palabra dada en la ultima posicion del arbol en la que nos encontramos
    actual->frecuencia = frecuencia;//junto su frecuecia
}

NodoArbolPrefijo* crearArchivo(char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {//caso error problema de lectura de archivo
        perror("Error al abrir el archivo");
        return NULL;
    }

    NodoArbolPrefijo *raiz = crearRamaVacia();
    if (raiz == NULL) {//caso error problema al crear la rama de raiz
        printf("RAIZ NULL ERROR");
        fclose(archivo);
        return NULL;
    }

    char palabra[256];
    int frecuencia;
    
    while (fscanf(archivo, "%s %d", palabra, &frecuencia) != EOF) {//lee los datos seung PALABRA y NUMERO hasta terminar el archivo completo
        insertarPalabra(raiz, palabra, frecuencia);//los va guardando en el arbol
    }

    fclose(archivo);//cerramos archivo
    return raiz;//devolvemos arbol 
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


ListaOrdenadaPalabras* palabrasEnArbolOrdenadas(NodoArbolPrefijo *arbol, ListaOrdenadaPalabras *lista) {//creamos una lista de datos respecto el arbol dado y una lista dada preveriblemente vacia si no la actualizara con datos dados nomas
    if (arbol == NULL) {//si el arbol no existe devolvemos lista original
        return lista;
    }
    for (int i = 0; i < 26; i++) {//llamamos misma funcion en todas las dirreciones de la posicion actual del arbol llendo rama por rama hasta el final
        lista = palabrasEnArbolOrdenadas(arbol->rama[i], lista);
    }
    if (arbol->palabra != NULL) {//cuando llama todo el arbol lee desde abajo hacia arriba, si no esta vacia
        lista = ingresarDato(arbol->frecuencia, arbol->palabra, lista);//guardamos el dato completo en la lista
    }
    return lista;//devolvemos lista
}