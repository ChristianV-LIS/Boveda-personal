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
Nombre : iniciar_sesion
Objetivo: Función para iniciar sesión en el programa.
Descripción: Es el proceso para leer el archivo con los usuarios y verificar los datos de inicio de sesion.
*/
void iniciar_sesion() {
	char nombre[MAX_NOMBRE], contrasena[MAX_CONS];
	
	// Entrada
	printf("--- Iniciar sesion ---\n");
	printf("Ingrese su nombre de usuario: ");
	fgets(nombre, MAX_NOMBRE, stdin);
	nombre[strcspn(nombre, "\n")] = 0; // Elimina el salto de línea del input
	
	printf("Ingrese su contraseña: ");
	fgets(contrasena, MAX_CONS, stdin);
	contrasena[strcspn(contrasena, "\n")] = 0; // Elimina el salto de línea del input
	system("cls");
	
	// Proceso
	if (verificar_usuario(nombre, contrasena)) {
		// Salida
		printf("Inicio de sesión exitoso. ¡Bienvenido(a), %s!\n", nombre);
		printf("Presiona Enter para continuar...");
		getchar();
		system("cls");
		segundo_menu(nombre);
	} else {
		// Salida
		printf("Nombre de usuario o contraseña incorrectos.\n");
		printf("Presiona Enter para continuar...");
		getchar();
		system("cls");
	}
}

/*
Nombre: segundo_menu
Onjetivo: Función para mostrar el menú al iniciar sesión.
Descripción: Es el proceso para mostrar el menu de opciones del programa después de iniciar sesión.
*/
void segundo_menu(const char *nombre) {
	int opc2;
	
	do {
		printf("--- MENU ---\n");
		printf("¡Hola, %s!\n", nombre);
		printf("1. Crear archivo txt\n");
		printf("2. Cifrar archivo txt\n");
		printf("3. Descifrar archivo txt\n");
		printf("4. Cerrar sesión\n");
		printf("Seleccione una opción: ");
		// Entrada
		scanf("%d", &opc2);
		getchar();
		system("cls");
		
		// Proceso
		switch (opc2) {
		case 1:
			// Salida
			crear_archivo();
			break;
		case 2:
			// Salida
			cifrar_archivo();
			break;
		case 3:
			// Salida
			descifrar_archivo();
			break;
		case 4:
			// Salida
			printf("Cerrando sesión...\n");
			printf("Presiona Enter para continuar...");
			getchar();
			system("cls");
			break;
		default:
			printf("Opción inválida.\n");
		}
	} while (opc2 != 4);

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
Nombre: escribir_archivo
Objetivo: Función para escribir en un archivo.
Descripción: Es el proceso para escribir en un archivo inmediatamente después de crearlo.
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
	printf("Cuando quieras cambiar de línea presiona Enter.\n");
	printf("Para salir, en una nueva línea escribe 'salir' y presiona Enter\n");
	printf("Contenido del archivo:\n");
	
	while (1) {
		fgets(linea, sizeof(linea), stdin);
		linea[strcspn(linea, "\n")] = '\0'; // Elimina el salto de línea
		
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

/*
Nombre: cifrar_archivo
Objetivo:Función para el cifrado de archivos txt.
Descripción:Es el proceso para aplicar el cifrado XOR en un archivo origen a uno nuevo.
*/
void cifrar_archivo(){
	char archivo_origen[100], archivo_cifrado[100], clave[50];
	printf("--- Cifrar archivo ---\n");
	printf("Ingrese el nombre del archivo original a cifrar: ");
	fgets(archivo_origen, sizeof(archivo_origen), stdin);
	archivo_origen[strcspn(archivo_origen, "\n")] = '\0'; // Elimina el salto de línea
	
	printf("Ingrese el nombre del nuevo archivo cifrado: ");
	fgets(archivo_cifrado, sizeof(archivo_cifrado), stdin);
	archivo_cifrado[strcspn(archivo_cifrado, "\n")] = '\0'; // Elimina el salto de línea
	
	printf("\n--- Importante ---\n");
	printf("Guarda la clave, sin ella no podrás descifrar el archivo y se perderá la información\n");
	printf("Ingrese su clave de cifrado: ");
	fgets(clave, sizeof(clave), stdin);
	clave[strcspn(clave, "\n")] = '\0'; // Elimina el salto de línea
	
	printf("Presiona Enter para continuar...");
	getchar();
	system("cls");
	
	aplicar_xor(archivo_origen, archivo_cifrado, clave);
	printf("Archivo cifrado correctamente: %s\n", archivo_cifrado);
	printf("Presiona Enter para continuar...");
	getchar();
	system("cls");
	
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

/*
Nombre: aplicar_xor
Objetivo:Función para realizar el método XOR de archivos txt.
Descripción:Es el proceso para aplicar XOR.
*/
void aplicar_xor (const char *archivo_origen, const char *archivo_cifrado, const char *clave) {
	FILE *origen = fopen(archivo_origen, "rb");
	FILE *cifrado = fopen(archivo_cifrado, "wb");
	// Proceso
	if  (origen == NULL || cifrado == NULL) {
		perror("Error al abrir los archivos");
		printf("Presiona Enter para continuar...");
		getchar();
		system("cls");
		return;
	}
	
	int clave_tamanio = strlen(clave);
	int contador = 0;
	char byte;
	
	while (fread(&byte, sizeof(byte), 1, origen) == 1) { // Lee un byte del archivo de origen hasta el final del archivo
		// Cifrado XOR para cualquier carácter ASCII
		byte ^= clave[contador % clave_tamanio]; // Se realiza el cifrado xor al byte leído, clave[contador % clave_tamaño] selecciona un carácter de clave en ciclos.
		// Salida
		fwrite(&byte, sizeof(byte), 1, cifrado); // Se escribe el byte cifrado en el archivo de salida: cifrado
		contador++;
	}
	
	fclose(origen);
	fclose(cifrado);
	
	return;
}

/*
Nombre : usuario_existe
Objetivo: Función para verificar que no existe otro usuario con el mismo nombre.
Descripción: Es el proceso para comparar los nombres en el archivo de texto con la entrada del usuario.
*/
int usuario_existe(const char *nombre) {
	// Proceso
	FILE *archivo = fopen(FILE_USUARIOS, "r");
	if (archivo == NULL) {
		// Salida
		perror("Error al abrir el archivo");
		printf("Presiona Enter para continuar...");
		getchar();
		system("cls");
		return 0;
	}
	
	char nombre_archivo[MAX_NOMBRE], contrasena[MAX_CONS];
	while (fscanf(archivo, "%s %s", nombre_archivo, contrasena) == 2) { // lee y recibe solo dos datos por línea 
		if (strcmp(nombre_archivo, nombre) == 0) { // Verifica si el nombre de usuario nuevo es el mismo que uno existente
			// Salida
			fclose(archivo);
			return 1; // Existe un usuario con el mismo nombre
		}
	}
	
	fclose(archivo);
	return 0; // El nombre de usuario es único
}

/*
Nombre : verificar_usuario
Objetivo: Función para verificar los datos en el inicio de sesión.
Descripción: Contiene el proceso para comparar el nombre y contraseña en el archivo de texto con la entrada del usuario.
*/
int verificar_usuario(const char *nombre, const char *contrasena) {
	// Proceso
	FILE *archivo = fopen(FILE_USUARIOS, "r");
	if (archivo == NULL) {
		// Salida
		perror("Error al abrir el archivo");
		printf("Presiona Enter para continuar...");
		getchar();
		system("cls");
		return 0;
	}
	
	char nombre_archivo[MAX_NOMBRE], contrasena_archivo[MAX_CONS];
	while (fscanf(archivo, "%s %s", nombre_archivo, contrasena_archivo) == 2) { // Lee y recibe solo dos datos por línea
		if (strcmp(nombre_archivo, nombre) == 0 && strcmp(contrasena_archivo, contrasena) == 0) { // Verifica si el nombre y contraseña digitados son iguales al registro
			// Salida
			fclose(archivo);
			return 1; // El nombre y contraseña existen
		}
	}
	
	fclose(archivo);
	return 0; // El nombre o contraseña son incorrectos. No existe 
}
