#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOMBRE 50
#define MAX_CONS 20
#define FILE_USUARIOS "file_usuarios.txt"

void escribir_archivo(const char *nombre_archivo);
/*
Nombre: escribir_archivo
Objetivo: Funci�n para escribir en un archivo.
Descripci�n: Es el proceso para escribir en un archivo inmediatamente despu�s de crearlo.
*/
void escribir_archivo(const char *nombre_archivo){
	char linea[256];
	FILE *archivo = fopen(nombre_archivo, "w");
	// Proceso
	if (archivo == NULL) {
		// Salida
		perror("Error al abrir el archivo");
		printf("Presiona Enter para continuar...");
		getchar();
		system("cls");
		
		return;
	}
	
	printf("--- Importante ---\n");
	printf("Escribe lo que quieras.\n");
	printf("Cuando quieras cambiar de l�nea presiona Enter.\n");
	printf("Para salir, en una nueva l�nea escribe 'salir' y presiona Enter\n");
	printf("Contenido del archivo:\n");
	
	while (1) {
		fgets(linea, sizeof(linea), stdin);
		linea[strcspn(linea, "\n")] = '\0'; // Elimina el salto de l�nea
		
		if (strcmp(linea, "salir") == 0) { // Si el usuario escribe "salir", termina
			break;
		}
		
		fprintf(archivo, "%s\n", linea);
	}
	
	fclose(archivo);
	system("cls");
	printf("El archivo '%s' se ha guardado correctamente.\n", nombre_archivo);
	printf("Presiona Enter para continuar...");
	getchar();
	system("cls");
	
	return;
}
