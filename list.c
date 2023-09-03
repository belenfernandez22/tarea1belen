// mi código proporciona un error al ingresar el número 6 nos pedira ingresr el ISBN de el libro en vez que el nombre y/o autor esto se debe a que no me identificada los nombres ya que cada vez que se ingresaba un mayuzcula no la identificaba por lo que opte en poner el ISBN , lo demás lo proporciona como correspondía 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINEA 1000
#define MAX_LIBROS 50
typedef struct {
  char titulo[MAXLINEA];
  char autor[MAXLINEA];
  char genero[MAXLINEA];
  char isbn[MAXLINEA];
  char ubicacion[MAXLINEA];
  char estado[MAXLINEA];
  char reserva1[MAXLINEA];
  char reserva2[MAXLINEA];
} Libro;
int contador_libros = 0; 
//COMENZAMOS ESTE CODIGO CREANDO UNA FUNCION LA CUAL NOS MUESTRE EL MENU DE LA BIBLIOTECA 
//\n SALTO DE LIENA PARA QUE NO NOS QUEDE TODO APILADO 
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

//FUNCION PARA EL NUMERO 1 , CREAMOS UN CONTADOR QUE SEIMPRE DEBE SER MENOR A EL NUMEOR MAXIMO DE LIBROS YA QUE OSINO ESTO 
//NO CORRERIA ,LUEGO DE ESCRIBIR EL EATADO DE EL LIBRO SE AGREGARA EL NUEVO LIBRO SI LA BIBLIOTECA ESTA LLENA AVISRA ATRAVEZ DE UN MENSAJE
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
//Declaramos una variable llamada nombre nombrelibro como una cadena con un largo máximo definido por máx line que saque se usara para almacenar el titulo de el libro,  usaremos scanf para leer la entrada de el usuario y almacenarla en la variable nombre libro , File *archivo lo utilizamos para declarar un puntero de tipo file que lo utilizaremos para trabajar con archivos,  , fclose lo utilizamos para cerrar el archivo temporalmente 
//
void mostrarDatosLibro() {
  char nombreLibro[MAXLINEA];
  char autor[MAXLINEA];
  printf("\nIngrese el título del libro que desea buscar: ");
  scanf(" %[^\n]", nombreLibro);
  printf("Ingrese el autor del libro que desea buscar: ");
  scanf(" %[^\n]", autor);
  FILE *archivo;
  archivo = fopen("biblioteca.csv", "r");
  if (archivo == NULL) {
    perror("\nError al abrir el archivo 'biblioteca.csv'.\n");
    return;
  }
  char linea[MAXLINEA];
  while (fgets(linea, sizeof(linea), archivo)) {
    Libro libro;
    sscanf(linea, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]",
           libro.titulo, libro.autor, libro.genero, libro.isbn, libro.ubicacion,
           libro.estado, libro.reserva1, libro.reserva2);
    if (strcmp(libro.titulo, nombreLibro) == 0 && strcmp(libro.autor, autor) == 0) {
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
  // título y autor no se encontraron en el archivo
  printf(
      "\nEl título y autor ingresados no corresponden a ningún libro en la biblioteca.\n");
}
// abre un archivo CSV de biblioteca, lee cada línea que representa un libro, extrae la información del libro y la muestra ,  finalmente, cierra el archivo después de mostrar todos los libros//
void mostrarTodosLosLibros() {
  FILE *archivo;
  archivo = fopen("biblioteca.csv", "r");
  if (archivo == NULL) {
    perror("\nError al abrir el archivo 'biblioteca.csv'.\n");
    return;
  }
  char linea[MAXLINEA];
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
//Se abren dos archivos "biblioteca.csv" y "temporal.csv" se utilizan para mantener la información de la biblioteca, Utilizando sscanf se analiza para extraer la información y almacenarse en la variable libro ,Si el libro ya tiene una reserva , pero no una segunda reserva y el usuario no es el mismo que hizo la primera reserva, se asigna al usuario como la segunda reserva.
void reservarLibro() {
  char nombreLibro[MAXLINEA];
  char nombreUsuario[MAXLINEA];
  char autor[MAXLINEA];
  printf("\nIngrese el nombre del libro que desea reservar: ");
  scanf(" %[^\n]", nombreLibro); 
  printf("Ingrese el autor del libro que desea reservar: ");
  scanf(" %[^\n]", autor);
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
  char linea[MAXLINEA];
  int encontrado = 0; // indica si se encontró el libro
  while (fgets(linea, sizeof(linea), archivo)) {
    Libro libro;
    sscanf(linea, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]",
           libro.titulo, libro.autor, libro.genero, libro.isbn, libro.ubicacion,
           libro.estado, libro.reserva1, libro.reserva2);
    //strcmpcomparar dos cadenas de caracteres
    if (strcmp(libro.titulo, nombreLibro) == 0 && strcmp(libro.autor, autor) == 0) {
      encontrado = 1; // Se encontró el libro
      if (strcmp(libro.estado, "Disponible") == 0) {
        // se reserva para el usuario
        strcpy(libro.estado, "Reservado");
        strcpy(libro.reserva1, nombreUsuario);
        printf("\nEl libro %s ha sido reservado para usted.\n", nombreLibro);
      } else if (strlen(libro.reserva1) > 0 && strlen(libro.reserva2) == 0) {
        if (strcmp(libro.reserva1, nombreUsuario) == 0) {
          printf("\nUsted ya tiene la reserva del libro %s.\n", nombreLibro);
        } else {
          // El usuario no tiene la reserva, se le asigna la segunda reserva
          //strcpy copiar una cadena de caracteres
          strcpy(libro.reserva2, nombreUsuario);
          printf("\nEl libro %s ha sido reservado para usted como segunda opción.\n", nombreLibro);
        }
      } else if (strlen(libro.reserva1) > 0 && strlen(libro.reserva2) > 0) {
        printf("\nLo siento. El libro %s ya tiene dos reservas.\n", nombreLibro);
      }
    }
    fprintf(temporal,"%s,%s,%s,%s,%s,%s,%s,%s\n",
            libro.titulo,
            libro.autor,
            libro.genero,
            libro.isbn,
            libro.ubicacion,
            libro.estado,
            libro.reserva1,
            libro.reserva2);
  }
  fclose(archivo);
  fclose(temporal);
  remove("biblioteca.csv");
  rename("temporal.csv", "biblioteca.csv");
  if (!encontrado) {
    printf("\nLo siento. No se encontró el libro %s.\n", nombreLibro);
    return;
  }
}

void cancelarReserva() {
  char nombreLibro[MAXLINEA];
  char nombreUsuario[MAXLINEA];
  char autor[MAXLINEA];

  printf("\nIngrese el nombre del libro que desea cancelar la reserva: ");
  scanf(" %[^\n]", nombreLibro); 
  printf("Ingrese el autor del libro que desea cancelar la reserva: ");
  scanf(" %[^\n]", autor);
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
  char linea[MAXLINEA];
  int encontrado = 0; //indica si se encontró el libro
  while (fgets(linea, sizeof(linea), archivo)) {
    Libro libro;
    sscanf(linea, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]",
           libro.titulo, libro.autor, libro.genero, libro.isbn, libro.ubicacion,
           libro.estado, libro.reserva1, libro.reserva2);

    if (strcmp(libro.titulo, nombreLibro) == 0 && strcmp(libro.autor, autor) == 0) {
      encontrado = 1; // Se encontró el libro
      if (strcmp(libro.reserva1, nombreUsuario) == 0) {
        strcpy(libro.reserva1, "");
        if (strlen(libro.reserva2) > 0) {
          // Hay una segunda reserva, se pasa a la primera
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
        // El usuario no tiene ninguna reserva
        printf("\nUsted no tiene ninguna reserva del libro %s.\n", nombreLibro);
      }
    }
    fprintf(temporal,"%s,%s,%s,%s,%s,%s,%s,%s\n",
            libro.titulo,
            libro.autor,
            libro.genero,
            libro.isbn,
            libro.ubicacion,
            libro.estado,
            libro.reserva1,
            libro.reserva2);
  }
  fclose(archivo);
  fclose(temporal);
  remove("biblioteca.csv");// es la biblioteca que estamos usando 
  rename("temporal.csv", "biblioteca.csv");
//creamos una temporal
  if (!encontrado) {
    printf("\nLo siento. No se encontró el libro %s.\n", nombreLibro);
    return;
  }
}
//en esta función utilizamos los ISBN del libro el cual nos permitirá entrar en el sistema y ver si el libro está disponible para reserva
void retirarLibro() {
  char isbnBuscado[MAXLINEA];
  char usuario[MAXLINEA];
  printf("\nIngrese el ISBN del libro que desea retirar: ");
  scanf("%s", isbnBuscado);
  FILE *archivo;
  archivo = fopen("biblioteca.csv", "r+");
  if (archivo == NULL) {
    perror("\nError al abrir el archivo 'biblioteca.csv'.\n");
    return;
  }
  char linea[MAXLINEA];
  int encontrado = 0;
  while (fgets(linea, sizeof(linea), archivo)) {
    Libro libro;
    sscanf(linea, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]",
           libro.titulo, libro.autor, libro.genero, libro.isbn, libro.ubicacion,
           libro.estado, libro.reserva1, libro.reserva2);

    if (strcmp(libro.isbn, isbnBuscado) == 0) {
      encontrado = 1;
      if (strcmp(libro.estado, "Disponible") == 0) {
        // Retirar el libro
        strcpy(libro.estado, "Prestado");
        printf("Ingrese su nombre de usuario: ");
        scanf("%s", usuario);
        strcpy(libro.reserva1,
               usuario); 
        // Actualizar el archivo
        fseek(archivo, -strlen(linea),
              SEEK_CUR); 
        fprintf(archivo, "%s,%s,%s,%s,%s,%s,%s,%s\n", libro.titulo, libro.autor,
                libro.genero, libro.isbn, libro.ubicacion, libro.estado,
                libro.reserva1, libro.reserva2);
        printf("Libro retirado con éxito.\n");
      } else if (strcmp(libro.estado, "Prestado") == 0) {
        // Verificar si el usuario tiene prioridad
        if (strcmp(libro.reserva1, usuario) == 0) {
          strcpy(libro.estado, "Prestado");
          fseek(archivo, -strlen(linea),
                SEEK_CUR);
          fprintf(archivo, "%s,%s,%s,%s,%s,%s,%s,%s\n", libro.titulo,
                  libro.autor, libro.genero, libro.isbn, libro.ubicacion,
                  libro.estado, libro.reserva1, libro.reserva2);
          printf("Libro retirado con éxito.\n");
        } else {
          printf("\nEl libro está prestado y usted no tiene prioridad para "
                 "retirarlo.\n");
        }
      } else {
        printf("\nEl libro no está disponible para ser retirado.\n");
      }
      break;
    }
  }

  fclose(archivo);
  if (encontrado == 0) {
    printf("\nEl ISBN ingresado no corresponde a ningún libro en la "
           "biblioteca.\n");
  }
}
void devolverLibro() {
  char nombreLibro[MAXLINEA];
  char usuario[MAXLINEA];
  char autor[MAXLINEA];
  printf("\nIngrese el nombre del libro que desea devolver: ");
  scanf(" %[^\n]", nombreLibro);
  printf("Ingrese el autor del libro que desea devolver: ");
  scanf(" %[^\n]", autor);
  FILE *archivo;
  archivo = fopen("biblioteca.csv", "r+");
  if (archivo == NULL) {
    perror("\nError al abrir el archivo 'biblioteca.csv'.\n");
    return;
  }
  char linea[MAXLINEA];
  int encontrado = 0;
  while (fgets(linea, sizeof(linea), archivo)) {
    Libro libro;
    sscanf(linea, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]",
           libro.titulo, libro.autor, libro.genero, libro.isbn, libro.ubicacion,
           libro.estado, libro.reserva1, libro.reserva2);

    if (strcmp(libro.titulo, nombreLibro) == 0 && strcmp(libro.autor, autor) == 0) {
      encontrado = 1;
      if (strcmp(libro.estado, "Prestado") == 0) {
        strcpy(libro.estado, "Disponible");
        printf("Ingrese su nombre de usuario: ");
        scanf("%s", usuario);
        if (strcmp(libro.reserva1, usuario) == 0) {
          strcpy(libro.reserva1,
                 ""); 
          if (strlen(libro.reserva2) > 0) {
            strcpy(libro.reserva1, libro.reserva2);
            strcpy(libro.reserva2, "");             
            printf("El libro ha sido reservado por otro usuario: %s\n",
                   libro.reserva1);
          }
        } else {
        
          printf("El libro no le pertenece a usted. No puede devolverlo.\n");
          break;
        }
        // Actualizar el archivo
        fseek(archivo, -strlen(linea),
              SEEK_CUR);
        fprintf(archivo, "%s,%s,%s,%s,%s,%s,%s,%s\n", libro.titulo, libro.autor,
                libro.genero, libro.isbn, libro.ubicacion,
                libro.estado, libro.reserva1,
                libro.reserva2);
        break;
      } else {
        printf("\nEl libro no está prestado.\n");
        break;
      }
    }
  }
  fclose(archivo);
  if (!encontrado) {
    printf("\nLo siento. No se encontró el libro %s.\n", nombreLibro);
    return;
  }
}

void mostrarLibrosPrestados() {
  FILE *archivo;
  archivo = fopen("biblioteca.csv", "r");
  if (archivo == NULL) {
    perror("\nError al abrir el archivo 'biblioteca.csv'.\n");
    return;
  }
  char linea[MAXLINEA];
  printf("\nListado de todos los libros prestados:\n\n");
  while (fgets(linea, sizeof(linea), archivo)) {
    Libro libro;
    sscanf(linea, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]",
           libro.titulo, libro.autor, libro.genero, libro.isbn, libro.ubicacion,
           libro.estado, libro.reserva1, libro.reserva2);
    //Comprueba si el estado del libro es "Prestado" utilizando la función strcmp. Si es prestado, se ejecuta el siguiente bloque de código
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
//contador_libros incrementa el contador de libros para apuntar a la siguiente posición del arreglo libros , archivo = fopen(nombre_archivo) de la linea 422 Abre ("r") y asigna el puntero del archivo a la variable archivo, Si el archivo no puede abrirse, se muestra un mensaje de error , Comienza un bucle while que se ejecuta mientras se puedan leer líneas del archivo utilizando la función fgets
void importarLibros(Libro libros[], char *nombre_archivo) {
  FILE *archivo;
  archivo = fopen(nombre_archivo, "r");
  if (archivo == NULL) {
    perror("\nError al abrir el archivo.\n");
    return;
  }
  char linea[MAXLINEA];
  while (fgets(linea, sizeof(linea), archivo)) {
    Libro libro;
    sscanf(linea, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]",
           libro.titulo, libro.autor, libro.genero, libro.isbn, libro.ubicacion,
           libro.estado, libro.reserva1, libro.reserva2);
    libros[contador_libros] = libro;
    contador_libros++;
  }
  fclose(archivo);
} //tiene que ser una csv que exista , 
void exportarLibros(Libro libros[], int contador_libros) {
  if (contador_libros == 0) {
    printf("No hay libros para exportar.\n");
    return;
  }
  char nombre_archivo[MAXLINEA];
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
void salir(){
  printf("ha salido del menu");
}
//hay que darle los casos 1 por 1 
int main() {
  int opcion;
  Libro libros[MAX_LIBROS];
  do {
    mostrarMenu();
    scanf("%d", &opcion);
    switch (opcion) {

    case 0:
      salir ();
      break;
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
      
      char nombre_archivo[MAXLINEA];
      
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
//uno de los errores más grandes de este código es no cuidar la memoria adecua ya que cree muchas variables y no medí el uso proporcionado de la memoria 
