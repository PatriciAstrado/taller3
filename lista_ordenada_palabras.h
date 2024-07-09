// Defina aquí una estructura de datos apropiada para contener
// una lista de palabras ordenada por frecuencia.
// Para que funcionen las prueba automáticas, el tipo de datos 
// se debe llamar ListaOrdenadaPalabras


typedef struct ListaOrdenadaPalabras{//est-datos de listas
    int frecuenciaListada;
    char *palabraListada;
    struct ListaOrdenadaPalabras *siguiente;
}ListaOrdenadaPalabras;

void liberarLista(ListaOrdenadaPalabras *lista){//libera memoria respecto listas
    while (lista != NULL) {
        ListaOrdenadaPalabras *temp = lista;
        lista = lista->siguiente;
        free(temp->palabraListada);
        free(temp);
    }
}

char **darDiezDatos(ListaOrdenadaPalabras *lista) {
    char **datos = (char **)malloc(10 * sizeof(char *));
    ListaOrdenadaPalabras *actual = lista;

    for (int i = 0; i < 10; i++) {//gasta llenar los 10 datos
        if (actual == NULL) {//si la lista esta vacia dara NULL
            datos[i] = NULL;
        } else {
            datos[i] = actual->palabraListada;//en X poscion guardamos X dato
            actual = actual->siguiente; //avazamos por la lista
        }
    }
    liberarLista(actual);//limpiamos lista ya usada
    return datos;//devolvemos datos
}

ListaOrdenadaPalabras* ingresarDato(int Entradafrecuencia, char *Entradapalabra, ListaOrdenadaPalabras *lista) {
    ListaOrdenadaPalabras *nuevo = (ListaOrdenadaPalabras*)malloc(sizeof(ListaOrdenadaPalabras));
    
    nuevo->palabraListada = strdup(Entradapalabra); //guardamos la palabra ingresada en la lista
    nuevo->frecuenciaListada = Entradafrecuencia;//junto su frecuencia
    nuevo->siguiente = NULL;

    if (lista == NULL || lista->frecuenciaListada <= Entradafrecuencia) {//si la frecuencia de entrada es mayor o igual a la guardada actual
        nuevo->siguiente = lista;//se dice que la nueva esta primero a la lista y la lista esta depues del nuevo
        return nuevo;//devolvemos nuevo
    }
    
    ListaOrdenadaPalabras *actual = lista;
    while (actual->siguiente != NULL && actual->siguiente->frecuenciaListada > Entradafrecuencia) {//mientras que la frecuencia entrada es menor a la lista actual, avanzamos por la lista
        actual = actual->siguiente;
    }
    //cuando llega al final de la lista o a una posicion valida
    nuevo->siguiente = actual->siguiente;//actualiza las posciones respectivas
    actual->siguiente = nuevo;
    return lista;
}