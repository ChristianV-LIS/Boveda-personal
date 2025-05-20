#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOMBRE 50
#define MAX_CONS 20
#define FILE_USUARIOS "file_usuarios.txt"
/*
Nombre: boveda personal
Descripci�n: Primera versi�n del programa que incluye las opciones de crear cuenta
e iniciar sesi�n.
Autores: Diego Cer�n, Christian Vargas, Guillermo Couoh
Fecha: 12/05/2025
Versi�n: 1.0
Compilador: ZinjaI
*/

// Funciones
void crear_cuenta();

/*
Nombre : main
Objetivo: Funci�n base del programa
Descripci�n: Contiene el men� principal del programa.
*/
int main() {
	int opc;
	
	do {
		printf("--- MENU ---\n");
		printf("1. Crear cuenta\n");
		printf("2. Iniciar sesi�n\n");
		printf("3. Salir\n");
		printf("Seleccione una opci�n: ");
		// Entrada
		scanf("%d", &opc);
		getchar();
		system("cls");
		
		// Proceso
		switch (opc) {
		case 1:
			crear_cuenta();
			break;
		case 2:
			iniciar_sesion();
			break;
		case 3:
			// Salida
			printf("Saliendo del programa...\n");
			break;
		default:
			printf("Opci�n inv�lida.\n");
		}
	} while (opc != 3);
	
	return 0;
}

/*
Nombre : crear_cuenta
Objetivo: Funci�n para crear una cuenta en el programa.
Descripci�n: Es el proceso para crear una cuenta y guardar los datos en el archivo de texto.
*/
void crear_cuenta() {
	char nombre[MAX_NOMBRE], contrasena[MAX_CONS];
	
	// Salida
	printf("--- Crear cuenta ---\n");
	printf("Ingrese un nombre de usuario: ");
	fgets(nombre, MAX_NOMBRE, stdin);
	nombre[strcspn(nombre, "\n")] = 0; // Elimina el salto de l�nea del input
	
	if (usuario_existe(nombre)) {
		printf("Nombre de usuario existente. Pruebe con otro.\n");
		printf("Presiona Enter para continuar...");
		getchar();
		system("cls");
		return;
	}
	
	printf("Ingrese una contrase�a: ");
	fgets(contrasena, MAX_CONS, stdin);
	contrasena[strcspn(contrasena, "\n")] = 0; // Elimina el salto de l�nea del input
	system("cls");
	
	// Proceso
	FILE *archivo = fopen(FILE_USUARIOS, "a");
	if (archivo == NULL) {
		perror("Error al abrir el archivo");
		printf("Presiona Enter para continuar...");
		getchar();
		system("cls");
		return;
	}
	
	// Salida
	fprintf(archivo, "%s %s\n", nombre, contrasena);
	fclose(archivo);
	
	printf("Cuenta creada exitosamente.\n");
	printf("Presiona Enter para continuar...");
	getchar();
	system("cls");
}
