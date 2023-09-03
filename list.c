#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH 1024
#define MAX_FIELDS 8
#define MAX_LIBROS 50
typedef struct {
  char titulo[MAX_LINE_LENGTH];
  char autor[MAX_LINE_LENGTH];
  char genero[MAX_LINE_LENGTH];
  char isbn[MAX_LINE_LENGTH];
  char ubicacion[MAX_LINE_LENGTH];
  char estado[MAX_LINE_LENGTH];
  char reserva1[MAX_LINE_LENGTH];
  char reserva2[MAX_LINE_LENGTH];
} Libro;
int contador_libros = 0; 
void mostrarMenu() {
  printf("Menú de la biblioteca:\n");
  printf("1. Registrar libro\n");
  printf("2. Mostrar datos de un libro\n");
  printf("3. Mostrar todos los libros\n");
  printf("4. Reservar libro\n");
  printf("5. Cancelar reserva\n");
  printf("6. Retirar libro\n");
  printf("7. Devolución libro\n");
  printf("8. Mostrar libros prestados\n");
  printf("9. Importar libros desde archivo CSV\n");
  printf("10. Exportar libros a archivo CSV\n");
  printf("0. Salir\n");
}
void registrarLibro(Libro libros[]) {
  if (contador_libros < MAX_LIBROS) {
    Libro nuevoLibro;
    printf("Ingrese el título del libro: ");
    scanf(" %[^\n]", nuevoLibro.titulo); 
    printf("Ingrese el autor del libro: ");
    scanf(" %[^\n]", nuevoLibro.autor);
    printf("Ingrese el género del libro: ");
    scanf(" %[^\n]", nuevoLibro.genero);
    printf("Ingrese el ISBN del libro: ");
    scanf(" %[^\n]", nuevoLibro.isbn);
    printf("Ingrese la ubicación del libro: ");
    scanf(" %[^\n]", nuevoLibro.ubicacion);
    printf("Ingrese el estado del libro (Disponible, Prestado, etc.): ");
    scanf(" %[^\n]", nuevoLibro.estado);
    libros[contador_libros] = nuevoLibro;
    contador_libros++;
    printf("Libro registrado con éxito.\n");
  } else {
    printf("La biblioteca está llena. No es posible registrar más libros.\n");
  }
}
void mostrarDatosLibro() {
  char isbnBuscado[MAX_LINE_LENGTH];
  printf("\nIngrese el ISBN del libro que desea buscar: ");
  scanf("%s", isbnBuscado);
  FILE *archivo;
  archivo = fopen("biblioteca.csv", "r");
  if (archivo == NULL) {
    perror("\nError al abrir el archivo 'biblioteca.csv'.\n");
    return;
  }
  char linea[MAX_LINE_LENGTH];
  while (fgets(linea, sizeof(linea), archivo)) {
    Libro libro;
    sscanf(linea, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]",
           libro.titulo, libro.autor, libro.genero, libro.isbn, libro.ubicacion,
           libro.estado, libro.reserva1, libro.reserva2);
    if (strcmp(libro.isbn, isbnBuscado) == 0) {
      printf("\nDatos del Libro:\n");
      printf("\tTítulo: %s\n", libro.titulo);
      printf("\tAutor: %s\n", libro.autor);
      printf("\tGénero: %s\n", libro.genero);
      printf("\tISBN: %s\n", libro.isbn);
      printf("\tUbicación: %s\n", libro.ubicacion);
      printf("\tEstado: %s\n", libro.estado);
      if (strlen(libro.reserva1) > 0)
        printf("\tReserva 1: %s\n", libro.reserva1);
      if (strlen(libro.reserva2) > 0)
        printf("\tReserva 2: %s\n", libro.reserva2);
      fclose(archivo);
      return;
    }
  }
  fclose(archivo);
  printf("\nEl ISBN ingresado no corresponde a ningún libro en la biblioteca.\n");
}
void mostrarTodosLosLibros() {
  FILE *archivo;
  archivo = fopen("biblioteca.csv", "r");
  if (archivo == NULL) {
    perror("\nError al abrir el archivo 'biblioteca.csv'.\n");
    return;
  }
  char linea[MAX_LINE_LENGTH];
  printf("\nListado de todos los libros:\n\n");
  while (fgets(linea, sizeof(linea), archivo)) {
    Libro libro;
    sscanf(linea, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]",
           libro.titulo, libro.autor, libro.genero, libro.isbn, libro.ubicacion,
           libro.estado, libro.reserva1, libro.reserva2);
    printf("\tTítulo: %s\n", libro.titulo);
    printf("\tAutor: %s\n", libro.autor);
    printf("\tGénero: %s\n", libro.genero);
    printf("\tISBN: %s\n", libro.isbn);
    printf("\tUbicación: %s\n", libro.ubicacion);
    printf("\tEstado: %s\n", libro.estado);
    if (strlen(libro.reserva1) > 0)
      printf("\tReserva 1: %s\n", libro.reserva1);
    if (strlen(libro.reserva2) > 0)
      printf("\tReserva 2: %s\n", libro.reserva2);
    printf("\n");
  }
  fclose(archivo);
}
void reservarLibro() {
  char nombreLibro[MAX_LINE_LENGTH];
  char nombreUsuario[MAX_LINE_LENGTH];
  printf("\nIngrese el nombre del libro que desea reservar: ");
  scanf(" %[^\n]", nombreLibro);
  printf("Ingrese su nombre: ");
  scanf(" %[^\n]", nombreUsuario);
  FILE *archivo;
  FILE *temporal;
  archivo = fopen("biblioteca.csv", "r");
  temporal = fopen("temporal.csv", "w");
  if (archivo == NULL || temporal == NULL) {
    perror("\nError al abrir los archivos.\n");
    return;
  }
  char linea[MAX_LINE_LENGTH];
  int encontrado = 0; // Bandera para indicar si se encontró el libro
  while (fgets(linea, sizeof(linea), archivo)) {
    Libro libro;
    sscanf(linea, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]",
           libro.titulo, libro.autor, libro.genero, libro.isbn, libro.ubicacion,
           libro.estado, libro.reserva1, libro.reserva2);
    if (strcmp(libro.titulo, nombreLibro) == 0) {
      encontrado = 1; // Se encontró el libro
      if (strcmp(libro.estado, "Disponible") == 0) {
        strcpy(libro.estado, "Reservado");
        strcpy(libro.reserva1, nombreUsuario);
        printf("\nEl libro %s ha sido reservado para usted.\n", nombreLibro);
      } else if (strlen(libro.reserva1) > 0 && strlen(libro.reserva2) == 0) {
        if (strcmp(libro.reserva1, nombreUsuario) == 0) {
          printf("\nUsted ya tiene la reserva del libro %s.\n", nombreLibro);
        } else {
          strcpy(libro.reserva2, nombreUsuario);
          printf("\nEl libro %s ha sido reservado para usted.\n", nombreLibro);
        }
      } else {
        printf("\nEl libro %s no se puede reservar en este momento.\n",
               nombreLibro);
      }
    }
    fprintf(temporal, "%s,%s,%s,%s,%s,%s,%s,%s\n", libro.titulo, libro.autor,
            libro.genero, libro.isbn, libro.ubicacion, libro.estado,
            libro.reserva1, libro.reserva2);
  }
  fclose(archivo);
  fclose(temporal);
  remove("biblioteca.csv");
  rename("temporal.csv", "biblioteca.csv");
  if (encontrado == 0) {
    printf("\nEl nombre del libro ingresado no corresponde a ningún libro en ""la biblioteca.\n");
  }
}
void cancelarReserva() {
  char nombreLibro[MAX_LINE_LENGTH];
  char nombreUsuario[MAX_LINE_LENGTH];
  printf("\nIngrese el nombre del libro que desea cancelar la reserva: ");
  scanf(" %[^\n]", nombreLibro); // Lee el nombre hasta que se presione Enter
  printf("Ingrese su nombre: ");
  scanf(" %[^\n]", nombreUsuario);
  FILE *archivo;
  FILE *temporal;
  archivo = fopen("biblioteca.csv", "r");
  temporal = fopen("temporal.csv", "w");
  if (archivo == NULL || temporal == NULL) {
    perror("\nError al abrir los archivos.\n");
    return;
  }
  char linea[MAX_LINE_LENGTH];
  int encontrado = 0; // Bandera para indicar si se encontró el libro
  while (fgets(linea, sizeof(linea), archivo)) {
    Libro libro;
    sscanf(linea, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]",
           libro.titulo, libro.autor, libro.genero, libro.isbn, libro.ubicacion,
           libro.estado, libro.reserva1, libro.reserva2);
    if (strcmp(libro.titulo, nombreLibro) == 0) {
      encontrado = 1; // Se encontró el libro
      if (strcmp(libro.reserva1, nombreUsuario) == 0) {
        strcpy(libro.reserva1, "");
        if (strlen(libro.reserva2) > 0) {
          strcpy(libro.reserva1, libro.reserva2);
          strcpy(libro.reserva2, "");
        } else {
          strcpy(libro.estado, "Disponible");
        }
        printf("\nSu reserva del libro %s ha sido cancelada.\n", nombreLibro);
      } else if (strcmp(libro.reserva2, nombreUsuario) == 0) {
        strcpy(libro.reserva2, "");
        printf("\nSu reserva del libro %s ha sido cancelada.\n", nombreLibro);
      } else {
        printf("\nUsted no tiene ninguna reserva del libro %s.\n", nombreLibro);
      }
    }
    fprintf(temporal, "%s,%s,%s,%s,%s,%s,%s,%s\n", libro.titulo, libro.autor,
            libro.genero, libro.isbn, libro.ubicacion, libro.estado,
            libro.reserva1, libro.reserva2);
  }
  fclose(archivo);
  fclose(temporal);
  remove("biblioteca.csv");
  rename("temporal.csv", "biblioteca.csv");

  if (encontrado == 0) {
    // No se encontró el libro por su título
    printf("\nEl nombre del libro ingresado no corresponde a ningún libro en "
           "la biblioteca.\n");
  }
}
void retirarLibro() {
  char isbnBuscado[MAX_LINE_LENGTH];
  char usuario[MAX_LINE_LENGTH];
  printf("\nIngrese el ISBN del libro que desea retirar: ");
  scanf("%s", isbnBuscado);
  FILE *archivo;
  archivo = fopen("biblioteca.csv", "r+");
  if (archivo == NULL) {
    perror("\nError al abrir el archivo 'biblioteca.csv'.\n");
    return;
  }
  char linea[MAX_LINE_LENGTH];
  int encontrado = 0;
  while (fgets(linea, sizeof(linea), archivo)) {
    Libro libro;
    sscanf(linea, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]",
           libro.titulo, libro.autor, libro.genero, libro.isbn, libro.ubicacion,
           libro.estado, libro.reserva1, libro.reserva2);
    if (strcmp(libro.isbn, isbnBuscado) == 0) {
      encontrado = 1;
      if (strcmp(libro.estado, "Disponible") == 0) {
        strcpy(libro.estado, "Prestado");
        printf("Ingrese su nombre de usuario: ");
        scanf("%s", usuario);
        strcpy(libro.reserva1,
               usuario); 
        fseek(archivo, -strlen(linea),
              SEEK_CUR); // Retroceder al inicio de la línea
        fprintf(archivo, "%s,%s,%s,%s,%s,%s,%s,%s\n", libro.titulo, libro.autor,
                libro.genero, libro.isbn, libro.ubicacion, libro.estado,
                libro.reserva1, libro.reserva2);
        printf("Libro retirado con éxito.\n");
      } else if (strcmp(libro.estado, "Prestado") == 0) {
        if (strcmp(libro.reserva1, usuario) == 0) {
          // Retirar el libro
          strcpy(libro.estado, "Prestado");
          // Actualizar el archivo
          fseek(archivo, -strlen(linea),
                SEEK_CUR); // Retroceder al inicio de la línea
          fprintf(archivo, "%s,%s,%s,%s,%s,%s,%s,%s\n", libro.titulo,
                  libro.autor, libro.genero, libro.isbn, libro.ubicacion,
                  libro.estado, libro.reserva1, libro.reserva2);
          printf("Libro retirado con éxito.\n");
        } else {
          // Mostrar aviso
          printf("\nEl libro está prestado y usted no tiene prioridad para "
                 "retirarlo.\n");
        }
      } else {
        // Mostrar aviso
        printf("\nEl libro no está disponible para ser retirado.\n");
      }
      break;
    }
  }
  fclose(archivo);
  if (encontrado == 0) {
    printf("\nEl ISBN ingresado no corresponde a ningún libro en la ""biblioteca.\n");
  }
}
void devolverLibro() {
  char isbnBuscado[MAX_LINE_LENGTH];
  char usuario[MAX_LINE_LENGTH];
  printf("\nIngrese el ISBN del libro que desea devolver: ");
  scanf("%s", isbnBuscado);
  FILE *archivo;
  archivo = fopen("biblioteca.csv", "r+");
  if (archivo == NULL) {
    perror("\nError al abrir el archivo 'biblioteca.csv'.\n");
    return;
  }
  char linea[MAX_LINE_LENGTH];
  int encontrado = 0;
  while (fgets(linea, sizeof(linea), archivo)) {
    Libro libro;
    sscanf(linea, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]",
           libro.titulo, libro.autor, libro.genero, libro.isbn, libro.ubicacion,
           libro.estado, libro.reserva1, libro.reserva2);
    if (strcmp(libro.isbn, isbnBuscado) == 0) {
      encontrado = 1;
      if (strcmp(libro.estado, "Prestado") == 0) {
        // Devolver el libro
        strcpy(libro.estado, "Disponible");
        printf("Ingrese su nombre de usuario: ");
        scanf("%s", usuario);
        if (strcmp(libro.reserva1, usuario) == 0) {
          // El usuario que devuelve el libro es el mismo que lo retiró
          strcpy(libro.reserva1,
                 ""); // Borrar el usuario de la cola de reservas
          if (strlen(libro.reserva2) > 0) {
            // Hay otro usuario en la cola de reservas
            strcpy(libro.reserva1, libro.reserva2); // Pasar al primer lugar
            strcpy(libro.reserva2, "");             // Borrar el segundo lugar
            printf("El libro ha sido reservado por otro usuario: %s\n",
                   libro.reserva1);
          }
        } else {
          // El usuario que devuelve el libro no es el mismo que lo retiró
          printf("El libro no le pertenece a usted. No puede devolverlo.\n");
          break;
        }
        // Actualizar el archivo
        fseek(archivo, -strlen(linea),
              SEEK_CUR); // Retroceder al inicio de la línea
        fprintf(archivo, "%s,%s,%s,%s,%s,%s,%s,%s\n", libro.titulo, libro.autor,
                libro.genero, libro.isbn, libro.ubicacion, libro.estado,
                libro.reserva1, libro.reserva2);
        printf("Libro devuelto con éxito.\n");
      } else {
        // Mostrar aviso
        printf("\nEl libro no está prestado. No puede devolverlo.\n");
      }
      break;
    }
  }
  fclose(archivo);
  if (encontrado == 0) {
    // Si llega aquí, significa que el ISBN no se encontró en el archivo
    printf("\nEl ISBN ingresado no corresponde a ningún libro en la "
           "biblioteca.\n");
  }
}
void mostrarLibrosPrestados() {
  FILE *archivo;
  archivo = fopen("biblioteca.csv", "r");
  if (archivo == NULL) {
    perror("\nError al abrir el archivo 'biblioteca.csv'.\n");
    return;
  }
  char linea[MAX_LINE_LENGTH];
  printf("\nListado de todos los libros prestados:\n\n");
  while (fgets(linea, sizeof(linea), archivo)) {
    Libro libro;
    sscanf(linea, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]",
           libro.titulo, libro.autor, libro.genero, libro.isbn, libro.ubicacion,
           libro.estado, libro.reserva1, libro.reserva2);
    if (strcmp(libro.estado, "Prestado") == 0) {
      printf("\tTítulo: %s\n", libro.titulo);
      printf("\tAutor: %s\n", libro.autor);
      printf("\tGénero: %s\n", libro.genero);
      printf("\tISBN: %s\n", libro.isbn);
      printf("\tUbicación: %s\n", libro.ubicacion);
      printf("\tEstado: %s\n", libro.estado);
      if (strlen(libro.reserva1) > 0)
        printf("\tReserva 1: %s\n", libro.reserva1);
      if (strlen(libro.reserva2) > 0)
        printf("\tReserva 2: %s\n", libro.reserva2);
    }
  }
  fclose(archivo);
}
void importarLibros(Libro libros[], char *nombre_archivo) {
  FILE *archivo;
  archivo = fopen(nombre_archivo, "r");
  if (archivo == NULL) {
    perror("\nError al abrir el archivo.\n");
    return;
  }
  char linea[MAX_LINE_LENGTH];
  while (fgets(linea, sizeof(linea), archivo)) {
    Libro libro;
    sscanf(linea, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]",
           libro.titulo, libro.autor, libro.genero, libro.isbn, libro.ubicacion,
           libro.estado, libro.reserva1, libro.reserva2);
    libros[contador_libros] = libro;
    contador_libros++;
  }
  fclose(archivo);
}
void exportarLibros(Libro libros[], int contador_libros) {
  if (contador_libros == 0) {
    printf("No hay libros para exportar.\n");
    return;
  }
  char nombre_archivo[MAX_LINE_LENGTH];
  printf("Ingrese el nombre del archivo CSV de destino: ");
  scanf("%s", nombre_archivo);
  FILE *archivo = fopen(nombre_archivo, "w");
  if (archivo == NULL) {
    perror("\nError al abrir el archivo de destino.\n");
    return;
  }
  fprintf(archivo, "Título,Autor,Género,ISBN,Ubicación,Estado,Reserva1,Reserva2\n");
  for (int i = 0; i < contador_libros; i++) {
    fprintf(archivo, "%s,%s,%s,%s,%s,%s,%s,%s\n", libros[i].titulo, libros[i].autor,
            libros[i].genero, libros[i].isbn, libros[i].ubicacion, libros[i].estado,
            libros[i].reserva1, libros[i].reserva2);
  }
  fclose(archivo);
  printf("Libros exportados exitosamente a %s.\n", nombre_archivo);
}
int main() {
  int opcion;
  Libro libros[MAX_LIBROS];
  do {
    mostrarMenu();
    scanf("%d", &opcion);
    switch (opcion) {
    case 1:
      registrarLibro(libros);
      break;
    case 2:
      mostrarDatosLibro();
      break;
    case 3:
      mostrarTodosLosLibros();
      break;
    case 4:
      reservarLibro();
      break;
    case 5:
      cancelarReserva();
      break;
    case 6:
      retirarLibro();
      break;
    case 7:
      devolverLibro();
      break;
    case 8:
     mostrarLibrosPrestados();
      break;
    case 9:
    printf("Ingrese el nombre del archivo: ");
      char nombre_archivo[MAX_LINE_LENGTH];
      scanf("%s", nombre_archivo);
      importarLibros(libros, nombre_archivo);
      break;
    case 10:
  exportarLibros(libros, contador_libros);
  break;
    }
  } while (opcion != 0);
  return 0;
}
