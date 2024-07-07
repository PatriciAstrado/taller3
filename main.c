
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
   NodoArbolPrefijo *RR = crearArchivo("tt.txt");
    if (RR == NULL) {
        fprintf(stderr, "Error creating the prefix tree from the file.\n");
        return 1;
    }

    ListaOrdenadaPalabras *LL = palabrasEnArbolOrdenadas(RR);
    if(LL == NULL) {
        fprintf(stderr, "Error creating the prefix tree from the file.\n");
        return 1;
    }
    
    char **diesPalabras = darDiezDatos(LL);
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    //nonl();
    
    int ventana_ppal_tam_x, ventana_ppal_tam_y;
    getmaxyx(stdscr, ventana_ppal_tam_y, ventana_ppal_tam_x);
    printw("%d %d", ventana_ppal_tam_y, ventana_ppal_tam_x);
    refresh();            /* Print it on to the real screen */
    curs_set(0);

    WINDOW *ventana_izquierda = newwin(ventana_ppal_tam_y-1, ventana_ppal_tam_x/2, 1, 0);
    box(ventana_izquierda, 0 , 0);
    wprintw(ventana_izquierda,"Esta es la ventana izquierda");
    wrefresh(ventana_izquierda);

    WINDOW *ventana_derecha = newwin(ventana_ppal_tam_y-1, ventana_ppal_tam_x/2, 1, ventana_ppal_tam_x/2);
    box(ventana_derecha, 0 , 0);
    wprintw(ventana_derecha,"Esta es la ventana derecha");
    wrefresh(ventana_derecha);
    
    int a = 'a';
    int fila_izq = 1, col_izq = 1;
    int fila_der = 1, col_der = 1;
    int fila_izqC = 1, col_izqC = 1;
    int fila_derC = 1, col_derC = 1;
    //wmove(ventana_izquierda, 1,1);
    //wmove(ventana_derecha, 1,1);

    while((a=getch())!= '0'){
        if ((a>='a')&&(a<='z')){
            mvwprintw(ventana_izquierda, fila_izqC, col_izqC, "%c",a);
            wrefresh(ventana_izquierda);
            wrefresh(ventana_derecha);
            for(int i=0;i<10;i++){
            mvwprintw(ventana_derecha, fila_der, col_der, "La letra ingresada es %s",diesPalabras[i]);
            wrefresh(ventana_derecha);
            fila_izq+=1;
            fila_der+=1;
            }
            col_izqC++;
        }else if(a==' ' || a=='\n'){
            mvwprintw(ventana_izquierda, fila_izqC, col_izqC, " ",a);
            col_izqC++;
            wrefresh(ventana_izquierda);
            mvwprintw(ventana_derecha, fila_der, col_der, "La letra ingresada es espacio",a);
            wrefresh(ventana_derecha);
            fila_izq+=1;
            fila_der+=1;
        }else{
            switch(a){
                case KEY_LEFT:
                    wclear(ventana_izquierda);
                    box(ventana_izquierda, 0 , 0);
                    wprintw(ventana_izquierda,"Esta es la ventana izquierda");
                    wrefresh(ventana_izquierda);
                    fila_izq = 1;
                    col_izq = 1;
                    break;
                case KEY_RIGHT:
                    wclear(ventana_derecha);
                    box(ventana_derecha, 0 , 0);
                    wprintw(ventana_derecha,"Esta es la ventana derecha");
                    wrefresh(ventana_derecha);
                    fila_der = 1;
                    col_der = 1;
                    break;
                case KEY_UP:
                    fila_der-=1;
                    fila_izq-=1;
                    mvwprintw(ventana_izquierda, fila_izq, col_izq, "                      ",a);
                    wrefresh(ventana_izquierda);
                    mvwprintw(ventana_derecha, fila_der, col_der, "                        ",a);
                    wrefresh(ventana_derecha);
                    break;
                case KEY_DOWN:
                    //
                    //
                    break;
                }
        }
    }

    endwin();           
    //
    liberarMemoria(RR);
    return 0;

}