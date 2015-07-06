#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define COMISION_ABIERTA 1
#define COMISION_CERRADA 0

#define RESPUESTA_CORRECTA 1
#define RESPUESTA_INCORRECTA 0

#define EXAMEN_ABIERTO 1
#define EXAMEN_CERRADO 0

#define SALIR 9

#define PERFIL_DOCENTE 1
#define PERFIL_ALUMNO 2

#define DAR_DE_ALTA_UNA_COMISION 1
#define DAR_DE_ALTA_ALUMNOS 2
#define GUARDAR_COMISION 3
#define BUSCAR_COMISION_PRE_EXISTENTE 4
#define GESTIONAR_EXAMENES 5
#define CERRAR_NOTAS 6
#define GENERAR_REPORTE 7

#define DAR_INICIO_EXAMEN 1
#define FINALIZAR_EXAMEN 2
#define CORREGIR_EXAMEN 3

#define RENDIR_UN_EXAMEN 1
#define CONSULTAR_NOTA 2

#define PATH "c:\\"

typedef struct {
	int dniAlumno;
	char preguntas[10][255];
	char respuestas[10][255];
	char evaluacionRespuesta[10];
	int estado; // = EXAMEN_CERRADO;
 } t_examen;

typedef struct {
    char apellido[50];
    char nombre[50];
    int dni;
    int edad;
    float notas[3];
} t_alumno;

typedef struct l_nodo {
    t_alumno alumno;
    struct l_nodo *sig;
} t_nodoLista;

typedef struct p_nodo {
    t_examen examen;
    struct p_nodo *sig;
} t_nodoPila;

typedef t_nodoPila* t_pila;
typedef t_nodoLista* t_lista;

typedef struct {
    int anio;
    char cuatrimestre;
    t_lista listaAlumnos; // = NULL;
    t_examen examenes[3];
    t_pila examenesEntregados; // = NULL;
    char estado; // = COMISION_ABIERTA;
} t_comision;


void imprimirCabecera(char *);
int seleccionarPerfil();

void menuDocente(t_comision *);
int mostrarOpcionesDocente();
t_comision darDeAltaComision();
void darDeAltaAlumnos(t_comision *);
void guardarComision(t_comision *);
t_comision buscarComision();
void menuExamenes(t_comision *);
void cerrarNotas(t_comision *);
void generarReporte(t_comision *);
void menuExamenes(t_comision *);
int mostrarOpcionesExamenes();
void iniciarExamen(t_comision *);
void finalizarExamen(t_comision *);
void corregirExamen(t_comision *);

void menuAlumno(t_comision *);
int mostrarOpcionesAlumno();
void rendirUnExamen(t_comision *);
void consultarNota(t_comision *);

/*  == FUNCIONES PRIMITIVAS DE LISTA == */
void crearLista(t_lista*);
int insertarNodoAlFinal(t_lista *, t_alumno *);

/* == FUNCIONES PRIMITIVAS DE PILA == */
int pilaVacia(t_pila *);
void crearPila(t_pila*);
int ponerEnPila(t_pila*, t_examen*);
int desapilar(t_pila*, t_examen*);


t_alumno buscarAlumnoPorDNI(t_lista*, int);
void actualizarNotaAlumno(t_lista*, int, int, float);

void main(){

		int perfil;
		t_comision comisionActual;

		while((perfil=seleccionarPerfil()) <= SALIR){
			switch (perfil){
				case PERFIL_DOCENTE:
					menuDocente(&comisionActual);
					break;
				case PERFIL_ALUMNO:
					menuAlumno(&comisionActual);
					break;
				case SALIR:
					exit(0);
					break;
				default:
					printf("Perfil desconocido\n");
               getche();
			}
		}
}

void imprimirCabecera(char *opcion){
  	system("cls");
	printf("*************************************************************\n");
  	printf("UNIVERSIDAD DE LA MATANZA - PROGRAMACION BASICA II \n");
	printf("GESTION DE ALUMNOS\n");
	printf("%s \n", opcion);
  	printf("*************************************************************\n\n");
}

int seleccionarPerfil(){

	int opcionIngresada = 0;

	while(opcionIngresada < PERFIL_DOCENTE || opcionIngresada > SALIR){
		imprimirCabecera("Seleccion del Perfil");
		printf("\n\t%d - Perfil docente", PERFIL_DOCENTE);
		printf("\n\t%d - Perfil alumno", PERFIL_ALUMNO);
		printf("\n\t%d - Salir", SALIR);

		printf("\n\nPor favor, seleccione el perfil: ");

      scanf("%d", &opcionIngresada);
      fflush(stdin);
	}
   return opcionIngresada;
}

void menuDocente(t_comision* comisionActual){

	int opcionIngresada = 0;

	while((opcionIngresada=mostrarOpcionesDocente()) <= SALIR){
		switch (opcionIngresada){
			case DAR_DE_ALTA_UNA_COMISION:
				*(comisionActual) = darDeAltaComision();
				break;
			case DAR_DE_ALTA_ALUMNOS:
				darDeAltaAlumnos(comisionActual);
				break;
			case GUARDAR_COMISION:
				guardarComision(comisionActual);
				break;
			case BUSCAR_COMISION_PRE_EXISTENTE:
				*(comisionActual) = buscarComision();
				break;
			case GESTIONAR_EXAMENES:
				menuExamenes(comisionActual);
				break;
			case CERRAR_NOTAS:
				cerrarNotas(comisionActual);
				break;
			case GENERAR_REPORTE:
				generarReporte(comisionActual);
				break;
			case SALIR:
				return;
			default:
				printf("Opcion invalida. Comunicarse con el administrador");
				break;
		}
	}
}

int mostrarOpcionesDocente(){

	int opcionIngresada = 0;

	while(opcionIngresada < DAR_DE_ALTA_UNA_COMISION || opcionIngresada > SALIR){
		imprimirCabecera("Menu docente");

		printf("\n\t%d - Dar de alta una comision", DAR_DE_ALTA_UNA_COMISION);
		printf("\n\t%d - Dar de alta alumnos", DAR_DE_ALTA_ALUMNOS);
		printf("\n\t%d - Guardar la comision actual", GUARDAR_COMISION);
		printf("\n\t%d - Buscar una comision pre-existente", BUSCAR_COMISION_PRE_EXISTENTE);
		printf("\n\t%d - Gestionar examenes", GESTIONAR_EXAMENES);
		printf("\n\t%d - Cerrar notas", CERRAR_NOTAS);
		printf("\n\t%d - Generar reporte de alumnos", GENERAR_REPORTE);
		printf("\n\t%d - Salir", SALIR);

		printf("\n\nPor favor, seleccione la opcion deseada: ");

		scanf("%d", &opcionIngresada);
		fflush(stdin);
	}
   return opcionIngresada;
}
  /** Funciones Rol: Docente **/
t_comision darDeAltaComision(){

    t_comision comisionNueva;

    printf("\nIngrese el anio de la comision:\t");
    scanf("%d", &comisionNueva.anio);
    printf("\nIngrese el numero de cuatrimestre:\t");
    scanf("%d", &comisionNueva.cuatrimestre);
    comisionNueva.listaAlumnos = NULL;
    comisionNueva.examenesEntregados = NULL;
    comisionNueva.estado = COMISION_ABIERTA;

    printf("Se ha creado una nueva Comision");
    getche();

    return comisionNueva;
}
void darDeAltaAlumnos(t_comision* comisionActual){
    t_alumno alumno;
    int opcion;
    int i;

    crearLista(&(comisionActual->listaAlumnos));
    printf("\nLista de alumnos creada con exito");
    getche();

    do {
        printf("\nIngrese Nombre de alumno: ");
        fflush(stdin);
        scanf("%s", alumno.nombre);
        printf("\nIngrese Apellido de alumno: ");
        fflush(stdin);
        scanf("%s", alumno.apellido);
        printf("\nIngrese DNI de alumno: ");
        fflush(stdin);
        scanf("%d", &alumno.dni);
        printf("\nIngrese Edad de alumno: ");
        fflush(stdin);
        scanf("%d", &alumno.edad);

        for(i = 0 ; i < 3 ; i++) {
                alumno.notas[i] = -1;   //inicialmente el alumno tiene -1 en todos examenes a modo de flag
        }

        if(insertarNodoAlFinal(&(comisionActual->listaAlumnos), &alumno) == 1) {
            printf("\nAlumno agregado con exito en la lista");
        } else {
            printf("\nERROR: El alumno no se pudo agregar a la lista");
        }

        printf("\nDesea ingresar otro alumno? (SI: 1 NO: 0):  ");
        fflush(stdin);
        scanf("%d", &opcion);
    }while(opcion);
}

void guardarComision(t_comision* comisionActual){

    FILE* pf = NULL;
    char path[80];
    //sprintf(path, "%d%cQ",&comisionActual->anio, &comisionActual->cuatrimestre);

    pf = fopen("20152Q","w+b");
    if(!pf) {
      printf("\nERROR: no se pudo guardar el archivo");
    } else {
        printf("\nEXITO: Se ha generado el archivo %s", path);
    }

    fwrite(comisionActual, sizeof(t_comision), 1, pf); //comision guardada

    fclose(pf);
    printf("\nComision guardada con exito");
    getche();
}

t_comision buscarComision(){
	FILE* pf = NULL;
	int anioComision;
	char cuatrimestre;
	t_comision comision;

	printf("\nIngrese el anio de comision:  ");
	scanf("%d", &anioComision);
	printf("\nIngrese numero de cuatrimestre:  ");
	scanf("%d", &cuatrimestre);

    pf = fopen("20152Q", "r+b");
    if (!pf) printf("\nERROR: no se encontro el archivo");

    fread(&comision, sizeof(t_comision), 1, pf);
    fclose(pf);

    printf("\nComision leida de archivo exitosamente");
    getche();
    return comision;
}

void cerrarNotas(t_comision* comisionActual){
	comisionActual->estado = CERRAR_NOTAS;
	printf("\La comision se ha cerrado");
   getche();
}

void generarReporte(t_comision* comisionActual){
	int i;
	t_lista lista = comisionActual->listaAlumnos;
	printf("\nREPORTE");

	("\n** Alumnos **");
    while(lista) {
        printf("\nNombre: %s Apellido: %s DNI: %d Edad: %d", lista->alumno.nombre, lista->alumno.apellido, lista->alumno.dni, lista->alumno.edad);
        printf("\nNotas:\n");
        for( i = 0 ; i < 3 ; i++) {
            printf(" Nota %d: %.2f ", i+1 ,lista->alumno.notas[i]);
        }
        lista = lista->sig;
    }
   getche();
}

void menuExamenes(t_comision* comisionActual){

	int opcionIngresada = 0;

   printf("Datos de la comision. Ano: %d, Cuatrimestre: %d. Estado: %d", comisionActual->anio, comisionActual->cuatrimestre, comisionActual->estado);
   getche();

	if(comisionActual->estado == COMISION_CERRADA){
		printf("Comision cerrada. Verifique el estado por favor.");
		return;
	}

	while((opcionIngresada=mostrarOpcionesExamenes()) <= SALIR){
		switch (opcionIngresada){
			case DAR_INICIO_EXAMEN:
				iniciarExamen(comisionActual);
				break;
			case FINALIZAR_EXAMEN:
				finalizarExamen(comisionActual);
				break;
			case CORREGIR_EXAMEN:
				corregirExamen(comisionActual);
				break;
			case SALIR:
				return;
				break;
			default:
				printf("Opcion invalida. Comunicarse con el administrador");
				break;
		}
	}
}

int mostrarOpcionesExamenes(){

	int opcionIngresada = 0;

	while(opcionIngresada < DAR_INICIO_EXAMEN || opcionIngresada > SALIR){
		imprimirCabecera("Gestion de examenes");

		printf("\n\t%d - Dar inicio a un examen", DAR_INICIO_EXAMEN);
		printf("\n\t%d - Finalizar un examen", FINALIZAR_EXAMEN);
		printf("\n\t%d - Corregir examen", CORREGIR_EXAMEN);
		printf("\n\t%d - Salir", SALIR);

		printf("\n\nPor favor, seleccione la opcion deseada: ");

		scanf("%d", &opcionIngresada);
		fflush(stdin);
	}

	return opcionIngresada;
}

void iniciarExamen(t_comision* comisionActual){
    int numeroExamen;
    int i;
    t_examen examenActual;

    printf("\nIngrese el numero de examen que desea INICIAR (1, 2 o 3):  ");
    fflush(stdin);
    scanf("%d", &numeroExamen);

    examenActual = comisionActual->examenes[numeroExamen - 1];

    examenActual.estado = DAR_INICIO_EXAMEN; // Se cambia el estado del examen a INICIO

    printf("\nSe ha iniciado el examen %d", numeroExamen);

    // El docente carga las 10 preguntas del examen.
    for(i = 0 ; i < 10 ; i++) {
        printf("\nIngrese la pregunta %d:  ", i+1);
        fflush(stdin);
        gets(examenActual.preguntas[i]);
    }
    comisionActual->examenes[numeroExamen -1] = examenActual;

    crearPila(&(comisionActual->examenesEntregados)); // Se inicia la pila de examenes entregados

    printf("\nEXITO: Se han cargado las preguntas para el examen %d", numeroExamen);
    getche();
}
void finalizarExamen(t_comision* comisionActual){
    int numeroExamen;

    printf("\nIngrese el numero de examen que desea terminar (1, 2 o 3):  ");
    scanf("%d", &numeroExamen);

    comisionActual->examenes[numeroExamen - 1].estado = FINALIZAR_EXAMEN;
    printf("\nSe ha terminado el examen %d", numeroExamen);
    getche();
}

void corregirExamen(t_comision* comisionActual){
    int numeroExamen;
    int i;
    t_pila pila;
    t_examen examen;
    t_alumno alumno;
    float resultadoExamen;

    printf("\nIngrese el numero de examen que desea CORREGIR (1, 2 o 3):  ");
    scanf("%d", &numeroExamen);

    comisionActual->examenes[numeroExamen - 1].estado = CORREGIR_EXAMEN; // el estado del examen pasa a corregir

    pila = comisionActual->examenesEntregados;


    while(!pilaVacia(&pila)) {
        if(desapilar(&pila, &examen)) {
            printf("\nRespuestas del alumno con DNI: %d", examen.dniAlumno);

            for( i = 0 ; i < 10 ; i++ ) {
                printf("\nRespuesta %d: %s", i+1, examen.respuestas[i]);
            }

            alumno = buscarAlumnoPorDNI(&(comisionActual->listaAlumnos), examen.dniAlumno); // busco en la lista al alumno que coincide con el dni en el examen que esta en la pila
            printf("\nLa nota para el examen %d para el alumno: %s, %s es:  ", numeroExamen, alumno.apellido, alumno.nombre);
            fflush(stdin);
            scanf("%f", &resultadoExamen);

            actualizarNotaAlumno(&(comisionActual->listaAlumnos), examen.dniAlumno, numeroExamen, resultadoExamen);

        } else {
            printf("\nNo se pudo desapilar el examen");
        }
    }

    printf("\nSe ha corregido el examen %d", numeroExamen);
    getche();
}

void menuAlumno(t_comision* comisionActual){

	int opcionIngresada = 0;

	if(comisionActual->estado == COMISION_CERRADA){
		printf("Comision cerrada. Comuniquese con su docente");
		return;
	}

	while((opcionIngresada=mostrarOpcionesAlumno()) <= SALIR){
		switch (opcionIngresada){
			case RENDIR_UN_EXAMEN:
				rendirUnExamen(comisionActual);
				break;
			case CONSULTAR_NOTA:
				consultarNota(comisionActual);
				break;
			case SALIR:
				return;
				break;
			default:
				printf("Opcion invalida. Comunicarse con el administrador");
				break;
		}
	}
}

int mostrarOpcionesAlumno(){

	int opcionIngresada = 0;

	while(opcionIngresada < RENDIR_UN_EXAMEN || opcionIngresada > SALIR){
		imprimirCabecera("Menu de alumno");

		printf("\n\t%d - Rendir examen", RENDIR_UN_EXAMEN);
		printf("\n\t%d - Consultar la nota", CONSULTAR_NOTA);
		printf("\n\t%d - Salir", SALIR);

		printf("\n\nPor favor, seleccione la opcion deseada: ");

		scanf("%d", &opcionIngresada);
		fflush(stdin);
	}

	return opcionIngresada;
}

void rendirUnExamen(t_comision* comisionActual){
    int numeroExamen;
    int i;
    t_examen examenActual;

    printf("\nIngrese el numero de examen que desea RENDIR (1, 2 o 3):  ");
    fflush(stdin);
    scanf("%d", &numeroExamen);


    examenActual = comisionActual->examenes[numeroExamen - 1];

    if(examenActual.estado != DAR_INICIO_EXAMEN) { //Valido el estado del examen
        printf("\nUsted no puede rendir el examen %d", numeroExamen);
        getche();
        return;
    }
    printf("\nSe ha iniciado el examen %d", numeroExamen);

    //el Alumno inicia el examen
    printf("\nIngrese su DNI: ");
    scanf("%d", &examenActual.dniAlumno);

    for( i = 0; i < 10 ; i++) {
        printf("\nPregunta %d: %s", i+1, examenActual.preguntas[i]);
        printf("\nRespuesta: ");
        fflush(stdin);
        gets(examenActual.respuestas[i]);
    }
    comisionActual->examenes[numeroExamen -1] = examenActual;

    if(ponerEnPila(&(comisionActual->examenesEntregados), &examenActual)) {
        printf("\nGracias. Su examen se encuentra en espera para ser corregido.");
    } else {
        printf("\nERROR: Su examen no ha podido ser cargado.");
    }
    getche();
}
void consultarNota(t_comision* comisionActual){
    int dni;
    int i;
    t_alumno alumno;

    printf("\nIngrese su numero de documento:  ");
    fflush(stdin);
    scanf("%d", &dni);

    alumno = buscarAlumnoPorDNI(&(comisionActual->listaAlumnos), dni);

    for ( i = 0 ; i < 3 ; i++) {
        if(alumno.notas[i] == -1) {
            printf("\nNota Examen %d: El examen aun no ha sido corregido", i+1);
        } else {
            printf("\nNota Examen %d: %.2f", i+1, alumno.notas[i]);
        }
    }
   getche();
}

/* == FUNCIONES DE LISTA == */

void crearLista(t_lista *p) {
    *p = NULL;
}

int insertarNodoAlFinal(t_lista *p, t_alumno *d) {
    while(*p)
        p = &(*p)->sig;

    *p = (t_nodoLista*)malloc(sizeof(t_nodoLista));

    if(*p == NULL)
        return 0;

    (*p)->alumno = *d;
    (*p)->sig = NULL;
    return 1;
}

/* == FUNCIONES DE PILA == */

void crearPila(t_pila* p) {
    *p =  NULL;
}

int ponerEnPila(t_pila *p, t_examen *d){
    t_nodoPila *nue = (t_nodoPila*)malloc(sizeof(t_nodoPila));

    if(nue == NULL)
        return 0;

    nue->examen= *d;
    nue->sig = *p;
    *p = nue;
    return 1;
}

int desapilar(t_pila *p, t_examen *d){
    t_nodoPila *aux = *p;

    if(*p == NULL)
        return 0;

    *d = (*p)->examen;
    *p=(*p)->sig;

    free(aux);

    return 1;
}
int pilaVacia(t_pila *p){
    return *p == NULL;
}


t_alumno buscarAlumnoPorDNI(t_lista *p, int dni) {
    while(*p && (dni != (*p)->alumno.dni)) {
        p = &(*p)->sig;
    }
    if(*p && dni == (*p)->alumno.dni) {
        return (*p)->alumno;
    }
}

void actualizarNotaAlumno(t_lista *p, int dni, int numeroExamen, float nota) {
    while(*p && (dni != (*p)->alumno.dni)) {
        p = &(*p)->sig;
    }
    if(*p && dni == (*p)->alumno.dni) {
        (*p)->alumno.notas[--numeroExamen] = nota;
    }
}
