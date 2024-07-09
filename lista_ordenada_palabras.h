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
    char **datos = (char **)malloc(10 * sizeof(char *));
    ListaOrdenadaPalabras *actual = lista;

    for (int i = 0; i < 10; i++) {
        if (actual == NULL) {
            datos[i] = NULL;
        } else {
            datos[i] = actual->palabraListada;
            actual = actual->siguiente;
        }
    }
    return datos;
}

ListaOrdenadaPalabras* ingresarDato(int Entradafrecuencia, char *Entradapalabra, ListaOrdenadaPalabras *lista) {
    ListaOrdenadaPalabras *nuevo = (ListaOrdenadaPalabras*)malloc(sizeof(ListaOrdenadaPalabras));
    nuevo->frecuenciaListada = Entradafrecuencia;
    nuevo->palabraListada = strdup(Entradapalabra); // Duplicate the word to store it safely
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