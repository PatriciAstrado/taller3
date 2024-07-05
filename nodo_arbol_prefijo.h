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
    struct  NodoArbolPrefijo *rama[26];
    char *palabra;
    int frecuencia;
} NodoArbolPrefijo;

void liberarMemoria(NodoArbolPrefijo *arbol);
ListaOrdenadaPalabras *palabrasEnArbolOrdenadas(NodoArbolPrefijo *arbol);

int posicion_letra (char letra){
    
    int letra_pos= (letra-'0')-97;          //a = 0, z= 25 rango de letras para aceder
    if(letra_pos >25 || letra_pos < 0){
        return -1;
    }
    
    return letra_pos;
}

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

NodoArbolPrefijo* avanzaEnArbol(NodoArbolPrefijo *inicio, char caracter) {
    int pos = posicion_letra(caracter); // dado caracter pasado a valor ASCII tomamos posición
    if (pos == -1) {
        return NULL; // letra no válida
    }
    if (inicio->rama[pos] == NULL) { // si la rama en la posición actual no existe se crea
        inicio->rama[pos] = crearRamaVacia();
    }
    return inicio->rama[pos]; // avanzamos por la rama y devolvemos rama avanzada
}



NodoArbolPrefijo *creaArbolPrefijoDesdeArchivo(char *nombreArchivoPalabras) {
    FILE *archivo = fopen(nombreArchivoPalabras, "r");
   

    NodoArbolPrefijo *arbol = crearRamaVacia();
    char *linea;

    while (fgets(linea, sizeof(linea), archivo)) {//leemos la linea comleta hasta que llegemos al final del archivo
        char *palabra = strtok(linea, "\t"); //separamos los strings respecto /t
        char *frecuenciaStr = strtok(NULL, "\n");//separamos desde el anterior string hasta /n

        if (palabra && frecuenciaStr) { //preguntamos si existen las variables
            int frecuencia = atoi(frecuenciaStr); // str ->int conversion
            NodoArbolPrefijo *ramaActual = arbol;

            for (int i = 0; palabra[i] != '\0'; i++) {//leemos caracter por caracter le la palabra hasta su final
                ramaActual = avanzaEnArbol(ramaActual,palabra[i]); //avanzamos por la rama
            }
            //al terminar la palabra asignamos las variables corespondientes.
            ramaActual->palabra = strdup(palabra);
            ramaActual->frecuencia = frecuencia;
        }
    }

    fclose(archivo);
}


void liberarMemoria (NodoArbolPrefijo *Arbol){
    while (Arbol != NULL){
        for(int i=0;i<26;i++){
            if(Arbol->rama[i]!= NULL){
                liberarMemoria(Arbol->rama[i]);
            }
        }
        free(&Arbol->palabra);
        free(&Arbol->frecuencia);
        free(Arbol);
    }

}


 ListaOrdenadaPalabras *palabrasEnArbolOrdenadas(NodoArbolPrefijo *arbol){
    ListaOrdenadaPalabras *lista = crearLista();
    for(int i=0;i<26;i++){
        if(arbol->rama[i]!= NULL){
            palabrasEnArbolOrdenadas(arbol->rama[i]);
        }   
        lista= ingresarDato(arbol->frecuencia,arbol->palabra,lista);
    }


    return lista;



















































 }
 
  //char ListaOrdenada[10];

 /*
    for(int j = 0; j<10;j++){
        ListaOrdenada[j] = lista->palabra;
        lista = lista->siguiente;
    }*/
