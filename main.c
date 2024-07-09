
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
    
    NodoArbolPrefijo *arbol = crearArchivo("10000_formas.tsv");//cargamos el archivo segun nombre dado y creamos un arbol de prefijos respecto esta
    NodoArbolPrefijo *nodoActual = arbol; //creamos un puntero al arbol, este sera por donde nos movemos y para no cambiar la posicion del arbol
    ListaOrdenadaPalabras *lista = NULL;
    char **diesPalabras = NULL;
    
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    
    int ventana_ppal_tam_x, ventana_ppal_tam_y;
    getmaxyx(stdscr, ventana_ppal_tam_y, ventana_ppal_tam_x);
    curs_set(0);

    WINDOW *ventana_izquierda = newwin(ventana_ppal_tam_y-1, ventana_ppal_tam_x/2, 1, 0);//medidas de pantalla
    WINDOW *ventana_derecha = newwin(ventana_ppal_tam_y-1, ventana_ppal_tam_x/2, 1, ventana_ppal_tam_x/2);

    box(ventana_derecha, 0 , 0);
    wprintw(ventana_derecha,"Palabras más frecuentes:");//nom,bre caja derecha
    wrefresh(ventana_derecha);
    
    int letra ,i;
    int fila_izqC = 1, col_izqC = 1;
    int fila_derC = 1, col_derC = 1;
    
    box(ventana_izquierda, 0 , 0);
    wprintw(ventana_izquierda,"ENTRADA:  0 para terminar programa");//nombre de caja izquierda

    while((letra = getch()) != '0'){//continua leyendo hasta entrada de 0 para terminar el programa
        if ((letra >= 'a') && (letra <= 'z')){ //rango del ABC
            for(int i = 0; i < 10; i++){//borramos texto anterior
                mvwprintw(ventana_derecha, i, col_derC, "");
                
            }
            nodoActual = avanzaEnArbol(nodoActual, letra - 'a');//avanzamos por el arbol conforme se dan entradas
            lista = NULL;//reiniciamos lista NO BORRAR
            lista = palabrasEnArbolOrdenadas(nodoActual, lista);//actualizamos lista segun posicion actual del arbol
            diesPalabras = darDiezDatos(lista);//creamos array de diez datos
            
            col_izqC++;//avanzamos en columnas
            mvwprintw(ventana_izquierda, fila_izqC, col_izqC, "%c", letra);
            wrefresh(ventana_izquierda);
    
            wclear(ventana_derecha);
            box(ventana_derecha, 0 , 0);
            wprintw(ventana_derecha,"Palabras más frecuentes:");
            for(i = 0; i < 10 && diesPalabras[i] != NULL; i++){//escribimos diez palabras mas frecuentes respecto posicion
                mvwprintw(ventana_derecha, i+1, col_derC, "-%s", diesPalabras[i]);
            }
            wrefresh(ventana_derecha);

        } else if(letra == ' '){
            nodoActual = arbol;//reiniciamos el punto de inicio
            col_izqC++;//avanzamos columna
            mvwprintw(ventana_izquierda, fila_izqC, col_izqC, " ");//ponemos espacio
            
            wrefresh(ventana_izquierda);
            wclear(ventana_derecha);
            box(ventana_derecha, 0 , 0);
            wprintw(ventana_derecha,"Palabras más frecuentes:");//mantenemos la casilla de palabras frecuentes
            wrefresh(ventana_derecha);

        }else if(letra == '\n'){
            nodoActual = arbol;//reiniciamos el punto de inicio
            fila_izqC++;//avanzamos fila
            col_izqC=1;//reiniciamos columna
            
            wrefresh(ventana_izquierda);
            wclear(ventana_derecha);
            box(ventana_derecha, 0 , 0);
            wprintw(ventana_derecha,"Palabras más frecuentes:");//mantenemos la casilla de palabras frecuentes
            
            wrefresh(ventana_derecha);

        }
    }

    endwin();           
    
    liberarMemoria(arbol);
    free(diesPalabras);
    liberarLista(lista);
    
    return 0;
}