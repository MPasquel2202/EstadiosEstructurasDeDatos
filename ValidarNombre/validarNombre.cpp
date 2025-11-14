#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Función para validar y capturar un nombre (solo letras)
void ingresoNombre(char msj[50], char resultado[50]) {
    char c;
    int i = 0;
    
    printf("\n!!!%s", msj);
    
    // Captura caracteres hasta presionar Enter (ASCII 13)
    while((c = getch()) != 13) {
        // Acepta letras (mayúsculas y minúsculas) y espacio
        if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == ' ') {
            resultado[i++] = c;
            printf("%c", c);
        }
        // Opcionalmente puedes permitir backspace para corregir
        else if(c == 8 && i > 0) { // 8 es el código ASCII para Backspace
            i--;
            printf("\b \b"); // Borra el carácter anterior en pantalla
        }
        // Ignora cualquier otro carácter (números, símbolos)
    }
    
    resultado[i] = '\0'; // Termina la cadena
}

// Función para convertir primera letra de cada palabra a mayúscula
void formatearNombre(char nombre[50]) {
    int i;
    bool nuevaPalabra = true;
    
    for(i = 0; nombre[i] != '\0'; i++) {
        // Si es el inicio de una palabra, convertir a mayúscula
        if(nuevaPalabra && isalpha(nombre[i])) {
            nombre[i] = toupper(nombre[i]);
            nuevaPalabra = false;
        }
        // Si no es letra, es un separador (nuevo inicio de palabra)
        else if(nombre[i] == ' ') {
            nuevaPalabra = true;
        }
        // El resto de letras se convierten a minúsculas
        else if(isalpha(nombre[i])) {
            nombre[i] = tolower(nombre[i]);
        }
    }
}

int main(int argc, char** argv) {
    char nombreIngresado[50] = {0};
    
    ingresoNombre("Ingrese un nombre (solo letras)", nombreIngresado);
    
    // Muestra el nombre exactamente como fue ingresado
    printf("\n...Nombre ingresado: %s", nombreIngresado);
    
    // Formatea el nombre (primera letra de cada palabra en mayúscula)
    formatearNombre(nombreIngresado);
    printf("\n...Nombre formateado: %s", nombreIngresado);
    
    return 0;
}