// Defina aquí una estructura de datos apropiada para contener
// una lista de palabras ordenada por frecuencia.
// Para que funcionen las prueba automáticas, el tipo de datos 
// se debe llamar ListaOrdenadaPalabras


typedef struct ListaOrdenadaPalabras{
    int frecuenciaListada;
    char *palabraListada;
    struct ListaOrdenadaPalabras *siguiente;

}ListaOrdenadaPalabras;
//ListaOrdenadaPalabras *lista = (ListaOrdenadaPalabras*)malloc(sizeof(ListaOrdenadaPalabras));

char **darDiezDatos(ListaOrdenadaPalabras *lista) {
    ListaOrdenadaPalabras *actual = lista;
    char **datos = (char **)malloc(10 * sizeof(char *));

    for (int i = 0; i < 10; i++) {
        if (actual == NULL) {
            printf("!!!NULL");
            //datos[i] = NULL; // If there are less than 10 nodes, fill remaining with NULL
        } else {
            datos[i] = actual->palabraListada;
            actual = actual->siguiente;
        }
    }
    return datos;
}

ListaOrdenadaPalabras *ingresarDato(int Entradafrecuencia, char *Entradapalabra, ListaOrdenadaPalabras *lista) {
    ListaOrdenadaPalabras *nuevo = (ListaOrdenadaPalabras*)malloc(sizeof(ListaOrdenadaPalabras));
    nuevo->frecuenciaListada = Entradafrecuencia;
    nuevo->palabraListada = Entradapalabra;
    nuevo->siguiente = NULL;

    if (lista == NULL || lista->frecuenciaListada <= Entradafrecuencia) {
        nuevo->siguiente = lista;
        return nuevo;
    }
    
    ListaOrdenadaPalabras *actual = lista;
    while (actual->siguiente != NULL && actual->siguiente->frecuenciaListada > Entradafrecuencia) {
        actual = actual->siguiente;
    }
    
    nuevo->siguiente = actual->siguiente;
    actual->siguiente = nuevo;
    
    return lista;
}