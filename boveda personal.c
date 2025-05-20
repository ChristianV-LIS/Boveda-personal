#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOMBRE 50
#define MAX_CONS 20
#define FILE_USUARIOS "file_usuarios.txt"
/*
Nombre: boveda personal
Descripción: Primera versión del programa que incluye las opciones de crear cuenta
e iniciar sesión.
Autores: Diego Cerón, Christian Vargas, Guillermo Couoh
Fecha: 12/05/2025
Versión: 1.0
Compilador: ZinjaI
*/

// Funciones
void crear_cuenta();
void iniciar_sesion();
void segundo_menu(const char *nombre);
void crear_archivo();
void escribir_archivo(const char *nombre_archivo);
void cifrar_archivo();
void descifrar_archivo();
void aplicar_xor (const char *archivo_origen, const char *archivo_cifrado, const char *clave);
int usuario_existe(const char *nombre);
int verificar_usuario(const char *nombre, const char *contrasena);

/*
Nombre : main
Objetivo: Función base del programa
Descripción: Contiene el menú principal del programa.
*/
int main() {
	int opc;
	
	do {
		printf("--- MENU ---\n");
		printf("1. Crear cuenta\n");
		printf("2. Iniciar sesión\n");
		printf("3. Salir\n");
		printf("Seleccione una opción: ");
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
			printf("Opción inválida.\n");
		}
	} while (opc != 3);
	
	return 0;
}

/*
Nombre : crear_cuenta
Objetivo: Función para crear una cuenta en el programa.
Descripción: Es el proceso para crear una cuenta y guardar los datos en el archivo de texto.
*/
void crear_cuenta() {
	char nombre[MAX_NOMBRE], contrasena[MAX_CONS];
	
	// Salida
	printf("--- Crear cuenta ---\n");
	printf("Ingrese un nombre de usuario: ");
	fgets(nombre, MAX_NOMBRE, stdin);
	nombre[strcspn(nombre, "\n")] = 0; // Elimina el salto de línea del input
	
	if (usuario_existe(nombre)) {
		printf("Nombre de usuario existente. Pruebe con otro.\n");
		printf("Presiona Enter para continuar...");
		getchar();
		system("cls");
		return;
	}
	
	printf("Ingrese una contraseña: ");
	fgets(contrasena, MAX_CONS, stdin);
	contrasena[strcspn(contrasena, "\n")] = 0; // Elimina el salto de línea del input
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
