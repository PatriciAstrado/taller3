// Defina aquí una estructura de datos apropiada para contener
// una lista de palabras ordenada por frecuencia.
// Para que funcionen las prueba automáticas, el tipo de datos 
// se debe llamar ListaOrdenadaPalabras


typedef struct ListaOrdenadaPalabras{
    int frecuenciaListada;
    char *palabraListada;
    struct ListaOrdenadaPalabras *siguiente;

}ListaOrdenadaPalabras;


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

ListaOrdenadaPalabras *crearLista() {
    ListaOrdenadaPalabras *lista = (ListaOrdenadaPalabras*)malloc(sizeof(ListaOrdenadaPalabras));
    if (lista != NULL) {
        lista->frecuenciaListada = 0;  // Inicializar frecuencia
        lista->palabraListada = NULL;  // Inicializar puntero a palabra como NULL
        lista->siguiente = NULL;       // Inicializar siguiente como NULL
    }
    return lista;
}

char *darDiezDatos(ListaOrdenadaPalabras lista){
    char *stringOrdenados[10];
    ListaOrdenadaPalabras *actual = (ListaOrdenadaPalabras*)malloc(sizeof(ListaOrdenadaPalabras));
    for (int i =0;i<10;i++){
        stringOrdenados[i] = actual->palabraListada;
        actual = actual->siguiente;
    }
    return stringOrdenados;
}
