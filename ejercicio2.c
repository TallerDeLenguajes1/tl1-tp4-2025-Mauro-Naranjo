#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    int TareaId;
    char *Descripcion;
    int Duracion;
}Tarea;

typedef struct Nodo
{
    Tarea T;
    struct Nodo *Siguiente;
}Nodo;

Nodo * CrearListaVacia();
Nodo * CrearNodo (char *buff, int duracion, int ID);
void InsertarNodo (Nodo ** start, Nodo * Nodo);
Nodo * QuitarNodo (Nodo ** start, int ID);
void MostrarLista (Nodo ** start);
Nodo * BuscarDatoAId (Nodo ** start, int idAbuscar);
Nodo * BuscarDatoConPalabra (Nodo ** start, char* palabra);
void MostrarTarea (Nodo * tarea);
void LiberarLista(Nodo ** start);

int main ()
{
    char buff[50];
    char opcion, palabra[15];
    int duracion, ID = 1000, idBuscado, busqueda, idABuscar;
    Nodo * listaPendientes = CrearListaVacia();
    Nodo * listaRealizadas = CrearListaVacia();
    
    do {
        fflush(stdin);
        printf("ingrese la tarea pendiente a realizar: ");
        gets(buff);
        fflush(stdin);
        printf("ingrese la duracion de la tarea entre 10 y 100: ");
        scanf("%d", &duracion);
        Nodo * nuevoNodo = CrearNodo(buff, duracion, ID);
        ID++;
        InsertarNodo(&listaPendientes, nuevoNodo);
        
        fflush(stdin);
        printf("\nDesea agregar otra tarea? (s/n): ");
        scanf("%c", &opcion);
    } while (opcion == 's' || opcion == 'S');
    
    do {
        printf("ingrese el ID de la tarea que fue realizada: ");
        scanf("%d", &idBuscado);
        Nodo * nodoQuitado = QuitarNodo(&listaPendientes, idBuscado);
        InsertarNodo(&listaRealizadas, nodoQuitado);
        
        fflush(stdin);
        printf("\nDesea pasar otra tarea a realizada? (s/n): ");
        scanf("%c", &opcion);
    } while (opcion == 's' || opcion == 'S');
    
    puts("\nLista de tareas pendientes\n");
    MostrarLista(&listaPendientes);
    puts("\nLista de tareas realizadas\n");
    MostrarLista(&listaRealizadas);
    
    printf("Desea buscar por id(1) o por palabra clave(2):");
    scanf("%d", &busqueda);
    
    if (busqueda == 1)
    {
        printf("\nIngrese el id de la tarea a buscar: ");
        scanf("%d", &idABuscar);
        Nodo * TareaBuscada;
        TareaBuscada = BuscarDatoAId(&listaPendientes, idABuscar);
        if (TareaBuscada != NULL)
        {
            printf("Tarea encontrada en pendientes:");
            MostrarTarea(TareaBuscada);
        }
        TareaBuscada = BuscarDatoAId(&listaRealizadas, idABuscar);
        if (TareaBuscada != NULL)
        {
            printf("Tarea encontrada en realizadas: ");
            MostrarTarea(TareaBuscada);
        }
        
        
    } else if (busqueda == 2)
    {
        printf("\nIngrese la palabra de la tarea a buscar: ");
        fflush(stdin);
        gets(palabra);
        Nodo * TareaBuscada;
        TareaBuscada = BuscarDatoConPalabra(&listaPendientes, palabra);
        if (TareaBuscada != NULL)
        {
            printf("Tarea encontrada en pendientes: ");
            MostrarTarea(TareaBuscada);
        }
        TareaBuscada = BuscarDatoConPalabra(&listaRealizadas, palabra);
        if (TareaBuscada != NULL)
        {
            printf("Tarea encontrada en realizadas: ");
            MostrarTarea(TareaBuscada);
        } /*else {
            printf("La palabra ingresada no fue encontrada");
        }*/
    } else
    {
        printf("\nopcion no valida");
    }
    
    LiberarLista(&listaPendientes);
    LiberarLista(&listaRealizadas);
    
    return 0;
}

Nodo * CrearListaVacia()
{
    return NULL;
}

Nodo * CrearNodo(char *buff, int duracion ,int ID)
{
    Nodo * nuevoNodo = (Nodo *) malloc(sizeof(Nodo));
    nuevoNodo->T.TareaId = ID;
    nuevoNodo->T.Descripcion = (char *)malloc((strlen(buff)+1)*sizeof(char));
    strcpy(nuevoNodo->T.Descripcion, buff);
    
    nuevoNodo->T.Duracion = duracion;
    nuevoNodo->Siguiente = NULL;
    
    return nuevoNodo;
}

void InsertarNodo(Nodo ** start, Nodo * Nodo)
{
    Nodo->Siguiente = *start;
    *start = Nodo;
}

Nodo * QuitarNodo (Nodo ** start, int ID)
{
    Nodo ** aux = start;
    while (aux != NULL && (*aux)->T.TareaId != ID)
    {
        aux = &(*aux)->Siguiente;
    }
    if (*aux)
    {
        Nodo * temp = *aux;
        *aux = (*aux)->Siguiente;
        temp->Siguiente = NULL;
        return temp;
    }
    return NULL;
}

void MostrarLista (Nodo ** start)
{
    Nodo * Aux = *start;
    while (Aux)
    {
        MostrarTarea(Aux);
        Aux = Aux->Siguiente;
    }
}

Nodo * BuscarDatoAId (Nodo ** start, int idAbuscar)
{
    Nodo * Aux = *start;
    while (Aux && Aux->T.TareaId != idAbuscar)
    {
        Aux = Aux->Siguiente;
    }
    return Aux;
}

Nodo * BuscarDatoConPalabra (Nodo ** start, char* palabra)
{
    Nodo * Aux = *start;
    while (Aux && strstr(Aux->T.Descripcion, palabra) == NULL)
    {
        Aux = Aux->Siguiente;
    }
    return Aux;
}

void MostrarTarea (Nodo * tarea)
{
    if (tarea != NULL)
    {
        printf("\n");
        printf("ID de la tarea: %d\n", tarea->T.TareaId);
        printf("Descripcion de la tarea: %s\n", tarea->T.Descripcion);
        printf("Duracion de la tarea: %d\n", tarea->T.Duracion);
    }
    
}

void LiberarLista(Nodo ** start)
{
    Nodo *actual = *start;
    Nodo *temp;

    while (actual != NULL)
    {
        temp = actual;
        actual = actual->Siguiente;

        free(temp->T.Descripcion);
        free(temp);
    }
    *start = NULL;
}