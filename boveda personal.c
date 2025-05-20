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

/*
Nombre: crear_archivo
Objetivo: Función para crear un archivo.
Descripción: Es el proceso para crear un archivo con el nombre que el usuario ingrese.
*/
void crear_archivo(){
	char nombre_archivo[100];
	// Entrada
	printf("--- Crear archivo ---\n");
	printf("Ingrese el nombre del archivo(incluir extensión .txt): ");
	fgets(nombre_archivo, sizeof(nombre_archivo), stdin);
	nombre_archivo[strcspn(nombre_archivo, "\n")] = '\0';
	system("cls");
	
	//Proceso
	FILE *archivo = fopen(nombre_archivo, "w");
	if (archivo != NULL) {
		//Salida
		printf("El archivo '%s' se ha creado correctamente.\n", nombre_archivo);
		printf("Presiona Enter para continuar...");
		getchar();
		system("cls");
		fclose(archivo);
		escribir_archivo(nombre_archivo);
	} else {
		//Salida
		printf("Ocurrió un error al crear el archivo.\n");
		printf("Presiona Enter para continuar...");
		getchar();
		system("cls");
	}
	
	return;
}

/*
Nombre: descifrar_archivo
Objetivo:Función para el descifrado de archivos txt.
Descripción:Es el proceso para aplicar el descifrado XOR en un archivo origen a uno nuevo.
*/
void descifrar_archivo(){
	char archivo_origen[100], archivo_cifrado[100], clave[50];
	printf("--- Descifrar archivo ---\n");
	printf("Ingrese el nombre del archivo a descifrar: ");
	fgets(archivo_origen, sizeof(archivo_origen), stdin);
	archivo_origen[strcspn(archivo_origen, "\n")] = '\0'; // Elimina el salto de línea
	
	printf("Ingrese el nombre del nuevo archivo descifrado: ");
	fgets(archivo_cifrado, sizeof(archivo_cifrado), stdin);
	archivo_cifrado[strcspn(archivo_cifrado, "\n")] = '\0'; // Elimina el salto de línea
	
	printf("Ingrese la clave de cifrado: ");
	fgets(clave, sizeof(clave), stdin);
	clave[strcspn(clave, "\n")] = '\0'; // Elimina el salto de línea
	
	printf("Presiona Enter para continuar...");
	getchar();
	system("cls");
	
	aplicar_xor(archivo_origen, archivo_cifrado, clave);
	printf("Archivo descifrado correctamente: %s\n", archivo_cifrado);
	printf("Presiona Enter para continuar...");
	getchar();
	system("cls");
	return;
}
