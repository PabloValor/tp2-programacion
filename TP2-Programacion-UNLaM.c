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

typedef struct examen{
	int dniAlumno;
	char preguntas[10][255];
	char respuestas[10][255];
	char evaluacionRespuesta[10];
	int estado; // = EXAMEN_CERRADO;
 };

typedef struct _alumno{
    char apellido[50];
    char nombre[50];
    int dni;
    int edad;
    float notas[3];
} alumno;

struct comision{
    int anio;
    char cuatrimestre;
    alumno * listaAlumnos; // = NULL;
    struct examen examenes[3];
    struct examen * examenesEntregados; // = NULL;
    char estado; // = COMISION_ABIERTA;
};

typedef alumno nodo;

void imprimirCabecera(char *);
int seleccionarPerfil();

void menuDocente(struct comision *);
int mostrarOpcionesDocente();
struct comision darDeAltaComision();
void darDeAltaAlumnos(struct comision *);
void guardarComision(struct comision *);
struct comision * buscarComision();
void menuExamenes(struct comision *);
void cerrarNotas(struct comision *);
void generarReporte(struct comision *);
void menuExamenes(struct comision *);
int mostrarOpcionesExamenes();
void iniciarExamen(struct comision *);
void finalizarExamen(struct comision *);
void corregirExazmen(struct comision *);

void menuAlumno(struct comision *);
int mostrarOpcionesAlumno();
void rendirUnExamen(struct comision *);
void consultarNota(struct comision *);

void main(void){

		int perfil;
		struct comision comisionActual;

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

void menuDocente(struct comision * comisionActual){

	int opcionIngresada = 0;

	while((opcionIngresada=mostrarOpcionesDocente()) <= SALIR){
		switch (opcionIngresada){
			case DAR_DE_ALTA_UNA_COMISION:
				(*comisionActual) = darDeAltaComision();
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

struct comision darDeAltaComision(){

    struct comision comisionNueva;
    comisionNueva.anio = 2015;
    comisionNueva.cuatrimestre = 1;
    comisionNueva.listaAlumnos = NULL;
    comisionNueva.examenesEntregados = NULL;
    comisionNueva.estado = COMISION_ABIERTA;

    printf("Se ha creado una nueva Comision");
    getche();

    return comisionNueva;
}
void darDeAltaAlumnos(struct comision * comisionActual){
	comisionActual->listaAlumnos = NULL;
	printf("Funcionalidad en mantenimiento. Regrese mas tarde por favor.");
   getche();
}

void guardarComision(struct comision * comisionActual){
	printf("Funcionalidad en mantenimiento. Regrese mas tarde por favor.");
   getche();
}

struct comision * buscarComision(){
	printf("Funcionalidad en mantenimiento. Regrese mas tarde por favor.");
   getche();
}

void cerrarNotas(struct comision * comisionActual){
	printf("Funcionalidad en mantenimiento. Regrese mas tarde por favor.");
   getche();
}

void generarReporte(struct comision * comisionActual){
	printf("Funcionalidad en mantenimiento. Regrese mas tarde por favor.");
   getche();
}

void menuExamenes(struct comision * comisionActual){

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

void iniciarExamen(struct comision * comisionActual){
	printf("Funcionalidad en mantenimiento. Regrese mas tarde por favor.");
   getche();
}
void finalizarExamen(struct comision * comisionActual){
	printf("Funcionalidad en mantenimiento. Regrese mas tarde por favor.");
   getche();
}

void corregirExazmen(struct comision * comisionActual){
	printf("Funcionalidad en mantenimiento. Regrese mas tarde por favor.");
   getche();
}

void menuAlumno(struct comision * comisionActual){

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

void rendirUnExamen(struct comision * comisionActual){
	printf("Funcionalidad en mantenimiento. Regrese mas tarde por favor.");
   getche();
}
void consultarNota(struct comision * comisionActual){
	printf("Funcionalidad en mantenimiento. Regrese mas tarde por favor.");
   getche();
}
