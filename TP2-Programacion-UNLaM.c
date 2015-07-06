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

typedef struct s_nodo {
    t_alumno alumno;
    struct s_nodo *sig;
} t_nodo;

typedef t_nodo* t_lista;

typedef struct {
    int anio;
    char cuatrimestre;
    t_lista listaAlumnos; // = NULL;
    t_examen examenes[3];
    t_examen *examenesEntregados; // = NULL;
    char estado; // = COMISION_ABIERTA;
} t_comision;


void imprimirCabecera(char *);
int seleccionarPerfil();

void menuDocente(t_comision *);
int mostrarOpcionesDocente();
t_comision darDeAltaComision();
void darDeAltaAlumnos(t_comision *);
void guardarComision(t_comision *);
t_comision * buscarComision();
void menuExamenes(t_comision *);
void cerrarNotas(t_comision *);
void generarReporte(t_comision *);
void menuExamenes(t_comision *);
int mostrarOpcionesExamenes();
void iniciarExamen(t_comision *);
void finalizarExamen(t_comision *);
void corregirExazmen(t_comision *);

void menuAlumno(t_comision *);
int mostrarOpcionesAlumno();
void rendirUnExamen(t_comision *);
void consultarNota(t_comision *);

/*  == FUNCIONES PRIMITIVAS DE LISTA == */
//void crearLista(alumno**);

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
				comisionActual = buscarComision();
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
   //crearLista(comisionActual->listaAlumnos);
   printf("\nLista de alumnos creada con exito");
   getche();
}

void guardarComision(t_comision* comisionActual){
	printf("Funcionalidad en mantenimiento. Regrese mas tarde por favor.");
   getche();
}

t_comision* buscarComision(){
	printf("Funcionalidad en mantenimiento. Regrese mas tarde por favor.");
   getche();
}

void cerrarNotas(t_comision* comisionActual){
	printf("Funcionalidad en mantenimiento. Regrese mas tarde por favor.");
   getche();
}

void generarReporte(t_comision* comisionActual){
	printf("Funcionalidad en mantenimiento. Regrese mas tarde por favor.");
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
				corregirExazmen(comisionActual);
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
	printf("Funcionalidad en mantenimiento. Regrese mas tarde por favor.");
   getche();
}
void finalizarExamen(t_comision* comisionActual){
	printf("Funcionalidad en mantenimiento. Regrese mas tarde por favor.");
   getche();
}

void corregirExazmen(t_comision* comisionActual){
	printf("Funcionalidad en mantenimiento. Regrese mas tarde por favor.");
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
	printf("Funcionalidad en mantenimiento. Regrese mas tarde por favor.");
   getche();
}
void consultarNota(t_comision* comisionActual){
	printf("Funcionalidad en mantenimiento. Regrese mas tarde por favor.");
   getche();
}

/* == FUNCIONES DE LISTA == */

/*void crearLista(alumno **p) {
    *p = NULL;
}*/
