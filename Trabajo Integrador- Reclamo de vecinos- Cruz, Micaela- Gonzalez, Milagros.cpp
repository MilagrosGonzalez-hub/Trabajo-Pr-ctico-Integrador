#include <stdio.h>   
#include <string.h>  
#include <stdlib.h>  
#include <ctype.h>   


#define MAX_RECLAMOS 100    
#define MAX_NOMBRE 50       
#define MAX_DIRECCION 100   
#define MAX_TIPO 30         
#define MAX_FECHA 11        
#define MAX_ESTADO 15       


typedef struct {
	char nombre[MAX_NOMBRE];    
	char direccion[MAX_DIRECCION]; 
	char tipo[MAX_TIPO];       
	char fecha[MAX_FECHA];      
	char estado[MAX_ESTADO];    
} Reclamo; 


Reclamo reclamos[MAX_RECLAMOS];
int cantidad = 0;


void limpiarBuffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}


void leerCadena(char* buffer, int tamano) {
	if (fgets(buffer, tamano, stdin) != NULL) {
		
		buffer[strcspn(buffer, "\n")] = '\0';
	}
}


void guardarEnArchivo(const char* nombreArchivo) {
	FILE* f = fopen(nombreArchivo, "wb"); 
	if (f) { 
		fwrite(&cantidad, sizeof(int), 1, f); 
		fwrite(reclamos, sizeof(Reclamo), cantidad, f); 
		fclose(f); 
		printf("Datos guardados correctamente en '%s'.\n", nombreArchivo);
	} else {
		perror("Error al guardar archivo"); 
	}
}


void cargarDesdeArchivo(const char* nombreArchivo) {
	FILE* f = fopen(nombreArchivo, "rb"); 
	if (f) { 
		fread(&cantidad, sizeof(int), 1, f); 
		fread(reclamos, sizeof(Reclamo), cantidad, f); 
		fclose(f); 
		printf("Datos cargados correctamente desde '%s'.\n", nombreArchivo);
	} else {
		printf("No se encontró el archivo '%s'. Iniciando con lista de reclamos vacía.\n", nombreArchivo);
	}
}


void agregarReclamo() {
	if (cantidad >= MAX_RECLAMOS) { 
		printf("Error: No se pueden agregar más reclamos. Límite alcanzado (%d).\n", MAX_RECLAMOS);
		return; 
	}
	
	printf("\n--- Agregar Nuevo Reclamo ---\n");
	printf("Nombre del vecino (máx. %d caracteres): ", MAX_NOMBRE - 1);
	leerCadena(reclamos[cantidad].nombre, MAX_NOMBRE);
	
	printf("Dirección (máx. %d caracteres): ", MAX_DIRECCION - 1);
	leerCadena(reclamos[cantidad].direccion, MAX_DIRECCION);
	
	printf("Tipo de reclamo (máx. %d caracteres): ", MAX_TIPO - 1);
	leerCadena(reclamos[cantidad].tipo, MAX_TIPO);
	
	char fecha_temp[MAX_FECHA];
	printf("Fecha (YYYY-MM-DD): ");
	leerCadena(fecha_temp, MAX_FECHA);
	

	if (strlen(fecha_temp) == 10 && fecha_temp[4] == '-' && fecha_temp[7] == '-') {
		strcpy(reclamos[cantidad].fecha, fecha_temp);
	} else {
		printf("Advertencia: Formato de fecha inválido. Se guardará como '%s'. Formato esperado YYYY-MM-DD\n", fecha_temp);
		strcpy(reclamos[cantidad].fecha, fecha_temp); 
	}
	

	strcpy(reclamos[cantidad].estado, "pendiente"); 
	cantidad++; 
	printf("Reclamo agregado correctamente. Total de reclamos: %d\n", cantidad);
}

void buscarReclamos() {
	char criterio[20], valor[MAX_DIRECCION]; 
	int encontrados = 0;
	
	if (cantidad == 0) {
		printf("No hay reclamos para buscar.\n");
		return;
	}
	
	printf("\n--- Buscar Reclamos ---\n");
	printf("Buscar por (nombre/tipo/estado): ");
	leerCadena(criterio, sizeof(criterio));
	
	
	for(int i = 0; criterio[i]; i++){
		criterio[i] = tolower((unsigned char)criterio[i]); 
	}
	

	if (strcmp(criterio, "nombre") != 0 && strcmp(criterio, "tipo") != 0 && strcmp(criterio, "estado") != 0) {
		printf("Criterio de búsqueda inválido. Use 'nombre', 'tipo' o 'estado'.\n");
		return;
	}
	
	printf("Valor a buscar: ");
	leerCadena(valor, sizeof(valor));
	
	printf("\nResultados de la búsqueda por '%s' con valor '%s':\n", criterio, valor);

	printf("  %-4s | %-20s | %-30s | %-15s | %-10s | %-10s\n", "#", "Nombre", "Dirección", "Tipo", "Fecha", "Estado");
	printf("------------------------------------------------------------------------------------------------------\n");
	
	
	for (int i = 0; i < cantidad; i++) {
		
		if ((strcmp(criterio, "nombre") == 0 && strstr(reclamos[i].nombre, valor)) ||
			(strcmp(criterio, "tipo") == 0 && strstr(reclamos[i].tipo, valor)) ||
			(strcmp(criterio, "estado") == 0 && strstr(reclamos[i].estado, valor))) {
			printf("  %-4d | %-20s | %-30s | %-15s | %-10s | %-10s\n", 
				   i + 1, reclamos[i].nombre, reclamos[i].direccion, reclamos[i].tipo, reclamos[i].fecha, reclamos[i].estado);
			encontrados++;
		}
	}
	if (!encontrados) { 
		printf("No se encontraron reclamos que coincidan con los criterios.\n");
	}
}


void cambiarEstado() {
	int idx;
	char nuevo_estado[MAX_ESTADO];
	
	if (cantidad == 0) {
		printf("No hay reclamos para modificar.\n");
		return;
	}
	
	printf("\n--- Cambiar Estado de Reclamo ---\n");
	printf("Ingrese el número de reclamo a modificar (1 a %d): ", cantidad);
	if (scanf("%d", &idx) != 1) { 
		printf("Entrada inválida. Por favor, ingrese un número.\n");
		limpiarBuffer();
		return;
	}
	limpiarBuffer(); 
	
	if (idx < 1 || idx > cantidad) { 
		printf("indice de reclamo inválido. Debe estar entre 1 y %d.\n", cantidad);
		return;
	}
	
	
	printf("Reclamo seleccionado: %s | Dirección: %s | Tipo: %s | Fecha: %s | Estado actual: %s\n", 
		   reclamos[idx-1].nombre, reclamos[idx-1].direccion, reclamos[idx-1].tipo, reclamos[idx-1].fecha, reclamos[idx-1].estado);
	
	printf("Nuevo estado (pendiente/resuelto/en proceso): ");
	leerCadena(nuevo_estado, MAX_ESTADO);
	
	
	if (strcmp(nuevo_estado, "pendiente") == 0 ||
		strcmp(nuevo_estado, "resuelto") == 0 ||
		strcmp(nuevo_estado, "en proceso") == 0) {
		strcpy(reclamos[idx-1].estado, nuevo_estado);
		printf("Estado del reclamo %d actualizado a '%s' correctamente.\n", idx, nuevo_estado);
	} else {
		printf("Estado inválido. Solo se permiten 'pendiente', 'resuelto' o 'en proceso'. El estado no fue modificado.\n");
	}
}




int compararPorFecha(const void* a, const void* b) {
	
	const Reclamo* reclamoA = (const Reclamo*)a;
	const Reclamo* reclamoB = (const Reclamo*)b;

	return strcmp(reclamoA->fecha, reclamoB->fecha);
}


int compararPorEstado(const void* a, const void* b) {
	const Reclamo* reclamoA = (const Reclamo*)a;
	const Reclamo* reclamoB = (const Reclamo*)b;
	return strcmp(reclamoA->estado, reclamoB->estado);
}


void mostrarOrdenados() {
	char criterio[20];
	
	if (cantidad == 0) {
		printf("No hay reclamos para mostrar.\n");
		return;
	}
	
	printf("\n--- Mostrar Reclamos Ordenados ---\n");
	printf("Ordenar por (fecha/estado): ");
	leerCadena(criterio, sizeof(criterio));
	
	for(int i = 0; criterio[i]; i++){
		criterio[i] = tolower((unsigned char)criterio[i]);
	}
	
	
	Reclamo copia[MAX_RECLAMOS];
	
	memcpy(copia, reclamos, sizeof(Reclamo) * cantidad); 
	
	
	if (strcmp(criterio, "fecha") == 0) {
		
		qsort(copia, cantidad, sizeof(Reclamo), compararPorFecha);
		printf("\nReclamos ordenados por fecha:\n");
	} else if (strcmp(criterio, "estado") == 0) {
		qsort(copia, cantidad, sizeof(Reclamo), compararPorEstado);
		printf("\nReclamos ordenados por estado:\n");
	} else {
		printf("Criterio de ordenamiento inválido. Use 'fecha' o 'estado'.\n");
		return;
	}
	
	
	printf("  %-4s | %-20s | %-30s | %-15s | %-10s | %-10s\n", "#", "Nombre", "Dirección", "Tipo", "Fecha", "Estado");
	printf("------------------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < cantidad; i++) { 
		printf("  %-4d | %-20s | %-30s | %-15s | %-10s | %-10s\n", 
			   i + 1, copia[i].nombre, copia[i].direccion, copia[i].tipo, copia[i].fecha, copia[i].estado);
	}
}


int main() {
	int opcion;
	cargarDesdeArchivo("reclamos.dat"); 
	
	do { 
		printf("\n--- Menú de Gestión de Reclamos Vecinales ---\n");
		printf("1. Agregar un nuevo reclamo\n");
		printf("2. Buscar reclamos existentes\n");
		printf("3. Cambiar el estado de un reclamo\n");
		printf("4. Mostrar reclamos ordenados (por fecha o estado)\n");
		printf("5. Guardar cambios y salir del programa\n");
		printf("---------------------------------------------\n");
		printf("Por favor, ingrese su opción: ");
		
		
		if (scanf("%d", &opcion) != 1) { 
			printf("Entrada inválida. Por favor, ingrese un número.\n");
			limpiarBuffer(); 
			continue; 
		}
		limpiarBuffer(); 
		
		
		switch(opcion) {
		case 1: agregarReclamo(); break;
		case 2: buscarReclamos(); break;
		case 3: cambiarEstado(); break;
		case 4: mostrarOrdenados(); break;
		case 5: guardarEnArchivo("reclamos.dat"); break;
		default: printf("Opción no reconocida. Por favor, intente de nuevo.\n");
		}
	} while(opcion != 5);
	
	printf("\n¡Gracias por usar el sistema de gestión de reclamos!\n");
	return 0; 
}
