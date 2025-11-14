#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

// Función para validar y capturar números decimales como texto
void ingresoNumeroExacto(char msj[50], char resultado[30]) {
    char c;
    int i = 0;
    bool puntoDecimal = false; // Control de punto decimal
    
    printf("\n!!!%s", msj);
    
    // Captura caracteres hasta presionar Enter (ASCII 13)
    while((c = getch()) != 13) {
        // Acepta dígitos (0-9)
        if(c >= '0' && c <= '9') {
            resultado[i++] = c;
            printf("%c", c);
        }
        // Acepta un único punto decimal
        else if(c == '.' && !puntoDecimal) {
            resultado[i++] = c;
            printf("%c", c);
            puntoDecimal = true;
        }
        // Ignora cualquier otro carácter
    }
    
    resultado[i] = '\0'; // Termina la cadena
}

int main(int argc, char** argv) {
    char numeroIngresado[30] = {0};
    
    ingresoNumeroExacto("Ingrese un valor decimal (con punto decimal)", numeroIngresado);
    
    // Muestra el número exactamente como fue ingresado
    printf("\n...%s", numeroIngresado);
    
    // Si necesitas hacer cálculos con el número, puedes convertirlo
    // pero solo para uso interno, no para mostrar
    double valorDouble = atof(numeroIngresado);
    
    return 0;
}