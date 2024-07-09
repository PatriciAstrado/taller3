
//
//  main.c
//  prueba ncurses 2024
//
//  Created by Mauro San Martín on 18-06-24.
//


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
#include <ncurses.h>
int main(int argc, const char * argv[]) {
    NodoArbolPrefijo *arbol = crearArchivo("10_formas.tsv");
    
    NodoArbolPrefijo *nodoActual = arbol; // Start at the root of the trie
    ListaOrdenadaPalabras *lista = NULL;
    char **diesPalabras = NULL;
    
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    
    int ventana_ppal_tam_x, ventana_ppal_tam_y;
    getmaxyx(stdscr, ventana_ppal_tam_y, ventana_ppal_tam_x);
    curs_set(0);

    WINDOW *ventana_izquierda = newwin(ventana_ppal_tam_y-1, ventana_ppal_tam_x/2, 1, 0);
    box(ventana_izquierda, 0 , 0);
    wprintw(ventana_izquierda,"Escribe en la ventana izquierda:");
    wrefresh(ventana_izquierda);

    WINDOW *ventana_derecha = newwin(ventana_ppal_tam_y-1, ventana_ppal_tam_x/2, 1, ventana_ppal_tam_x/2);
    box(ventana_derecha, 0 , 0);
    wprintw(ventana_derecha,"Palabras más frecuentes:");
    wrefresh(ventana_derecha);
    
    int a;
    int fila_izqC = 1, col_izqC = 1;
    int fila_derC = 1, col_derC = 1;
    
            box(ventana_izquierda, 0 , 0);
            wprintw(ventana_izquierda,"ENTRADA:");
    while((a = getch()) != '0'){
        if ((a >= 'a') && (a <= 'z')){
            nodoActual = avanzaEnArbol(nodoActual, a - 'a');//avanzamos por el arbol conforme se dan entradas
            lista = palabrasEnArbolOrdenadas(nodoActual, lista);//actualizamos lista
            diesPalabras = darDiezDatos(lista);//creamos array de diez datos
            
            col_izqC++;
            mvwprintw(ventana_izquierda, fila_izqC, col_izqC, "%c", a);
            wrefresh(ventana_izquierda);
            
            
            wrefresh(ventana_izquierda);
            wclear(ventana_derecha);
            box(ventana_derecha, 0 , 0);
            fila_derC = 1, col_derC = 1;
            wprintw(ventana_derecha,"Palabras más frecuentes:");
            fila_derC = 1;
            for(int i = 0; i < 10 && diesPalabras[i] != NULL; i++){
                mvwprintw(ventana_derecha, fila_derC++, col_derC, "%s", diesPalabras[i]);
            }
            wrefresh(ventana_derecha);
        } else if(a == ' ' || a == '\n'){
            nodoActual = arbol;//reiniciamos el punto de inicio
            mvwprintw(ventana_izquierda, fila_izqC, col_izqC, " ");
            col_izqC++;
            wrefresh(ventana_izquierda);
            wclear(ventana_derecha);
            box(ventana_derecha, 0 , 0);
            wprintw(ventana_derecha,"Palabras más frecuentes:");
            mvwprintw(ventana_derecha, fila_derC++, col_derC, "La letra ingresada es espacio");
            wrefresh(ventana_derecha);
        } else {
            switch(a){
                case KEY_LEFT:
                    wclear(ventana_izquierda);
                    box(ventana_izquierda, 0 , 0);
                    wprintw(ventana_izquierda,"Escribe en la ventana izquierda:");
                    wrefresh(ventana_izquierda);
                    col_izqC = 1;
                    nodoActual = arbol; // Reset to the root of the trie
                    break;
                case KEY_RIGHT:
                    wclear(ventana_derecha);
                    box(ventana_derecha, 0 , 0);
                    wprintw(ventana_derecha,"Palabras más frecuentes:");
                    wrefresh(ventana_derecha);
                    fila_derC = 1;
                    break;
                case KEY_UP:
                    if(fila_izqC > 1) fila_izqC--;
                    if(fila_derC > 1) fila_derC--;
                    mvwprintw(ventana_izquierda, fila_izqC, col_izqC, " ");
                    mvwprintw(ventana_derecha, fila_derC, col_derC, " ");
                    wrefresh(ventana_izquierda);
                    wrefresh(ventana_derecha);
                    break;
                case KEY_DOWN:
                    // Add any functionality for KEY_DOWN if needed
                    break;
            }
        }
    }

    endwin();           
    
    liberarMemoria(arbol);

    // Free the diesPalabras array
    free(diesPalabras);

    // Free the lista
    while (lista != NULL) {
        ListaOrdenadaPalabras *temp = lista;
        lista = lista->siguiente;
        free(temp->palabraListada);
        free(temp);
    }
    
    return 0;
}