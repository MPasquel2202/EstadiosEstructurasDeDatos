#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Directorio {
public:
    string nombre;
    vector<string> archivos;
    vector<Directorio*> subdirectorios;
    
    Directorio(string nombre) : nombre(nombre) {}
    
    void agregarArchivo(string archivo) {
        archivos.push_back(archivo);
    }
    
    void agregarSubdirectorio(Directorio* subdir) {
        subdirectorios.push_back(subdir);
    }
};

// 1. RECURSIVIDAD DIRECTA - Función que se llama a sí misma directamente
void mostrarEstructura(Directorio* dir, int nivel = 0) {
    string indentacion(nivel * 2, ' ');
    cout << indentacion << "📁 " << dir->nombre << endl;
    
    // Mostrar archivos
    for (const auto& archivo : dir->archivos) {
        cout << indentacion << "  📄 " << archivo << endl;
    }
    
    // Llamada recursiva para subdirectorios
    for (auto subdir : dir->subdirectorios) {
        mostrarEstructura(subdir, nivel + 1);
    }
}

// 2. RECURSIVIDAD INDIRECTA - Funciones que se llaman mutuamente
void procesarDirectorio(Directorio* dir);
void procesarContenido(Directorio* dir);

void procesarDirectorio(Directorio* dir) {
    cout << "Procesando directorio: " << dir->nombre << endl;
    procesarContenido(dir); // Llamada indirecta
}

void procesarContenido(Directorio* dir) {
    // Procesar archivos
    for (const auto& archivo : dir->archivos) {
        cout << "  - Archivo: " << archivo << endl;
    }
    
    // Llamada indirecta de vuelta
    for (auto subdir : dir->subdirectorios) {
        procesarDirectorio(subdir);
    }
}

// 3. RECURSIVIDAD DE COLA - Última operación es la llamada recursiva
int contarArchivosRecursivo(Directorio* dir, int contador = 0) {
    // Contar archivos del directorio actual
    contador += dir->archivos.size();
    
    // Llamada recursiva de cola para subdirectorios
    for (auto subdir : dir->subdirectorios) {
        contador = contarArchivosRecursivo(subdir, contador);
    }
    
    return contador;
}

// 4. RECURSIVIDAD MÚLTIPLE - Múltiples llamadas recursivas
vector<string> buscarArchivo(Directorio* dir, const string& nombreArchivo) {
    vector<string> rutas;
    
    // Buscar en archivos actuales
    for (const auto& archivo : dir->archivos) {
        if (archivo == nombreArchivo) {
            rutas.push_back(dir->nombre + "/" + archivo);
        }
    }
    
    // Múltiples llamadas recursivas para subdirectorios
    for (auto subdir : dir->subdirectorios) {
        vector<string> resultados = buscarArchivo(subdir, nombreArchivo);
        for (const auto& ruta : resultados) {
            rutas.push_back(dir->nombre + "/" + ruta);
        }
    }
    
    return rutas;
}

// 5. RECURSIVIDAD ANIDADA - Recursión dentro de estructuras anidadas
int calcularProfundidadMaxima(Directorio* dir) {
    if (dir->subdirectorios.empty()) {
        return 1; // Directorio hoja
    }
    
    int maxProfundidad = 0;
    for (auto subdir : dir->subdirectorios) {
        // Llamada recursiva anidada en la lógica de comparación
        maxProfundidad = max(maxProfundidad, calcularProfundidadMaxima(subdir));
    }
    
    return maxProfundidad + 1;
}

// 6. RECURSIVIDAD CON BACKTRACKING - Exploración con vuelta atrás
bool encontrarRutaArchivo(Directorio* dir, const string& archivoBuscado, vector<string>& rutaActual) {
    rutaActual.push_back(dir->nombre);
    
    // Buscar en archivos actuales
    for (const auto& archivo : dir->archivos) {
        if (archivo == archivoBuscado) {
            rutaActual.push_back(archivo);
            return true;
        }
    }
    
    // Backtracking en subdirectorios
    for (auto subdir : dir->subdirectorios) {
        if (encontrarRutaArchivo(subdir, archivoBuscado, rutaActual)) {
            return true;
        }
    }
    
    // Backtrack - eliminar este directorio de la ruta
    rutaActual.pop_back();
    return false;
}

// Función principal para demostrar todos los tipos
int main() {
    cout << "=== SISTEMA DE GESTIÓN DE DIRECTORIOS ===" << endl;
    
    // Crear estructura de directorios
    Directorio* raiz = new Directorio("Raiz");
    Directorio* docs = new Directorio("Documentos");
    Directorio* imagenes = new Directorio("Imagenes");
    Directorio* musica = new Directorio("Musica");
    Directorio* vacaciones = new Directorio("Vacaciones");
    
    // Configurar estructura
    raiz->agregarArchivo("readme.txt");
    raiz->agregarSubdirectorio(docs);
    raiz->agregarSubdirectorio(imagenes);
    raiz->agregarSubdirectorio(musica);
    
    docs->agregarArchivo("trabajo.docx");
    docs->agregarArchivo("presupuesto.xlsx");
    docs->agregarSubdirectorio(vacaciones);
    
    imagenes->agregarArchivo("foto1.jpg");
    imagenes->agregarArchivo("foto2.png");
    
    musica->agregarArchivo("cancion1.mp3");
    
    vacaciones->agregarArchivo("playa.jpg");
    vacaciones->agregarArchivo("montaña.png");
    vacaciones->agregarArchivo("playa.jpg"); // Duplicado para demostrar búsqueda
    
    cout << "\n1. RECURSIVIDAD DIRECTA - Estructura:" << endl;
    mostrarEstructura(raiz);
    
    cout << "\n2. RECURSIVIDAD INDIRECTA - Procesamiento:" << endl;
    procesarDirectorio(raiz);
    
    cout << "\n3. RECURSIVIDAD DE COLA - Total archivos: " 
         << contarArchivosRecursivo(raiz) << endl;
    
    cout << "\n4. RECURSIVIDAD MÚLTIPLE - Buscar 'playa.jpg':" << endl;
    vector<string> resultados = buscarArchivo(raiz, "playa.jpg");
    for (const auto& ruta : resultados) {
        cout << "   Encontrado en: " << ruta << endl;
    }
    
    cout << "\n5. RECURSIVIDAD ANIDADA - Profundidad máxima: " 
         << calcularProfundidadMaxima(raiz) << endl;
    
    cout << "\n6. RECURSIVIDAD CON BACKTRACKING - Ruta a 'montaña.png':" << endl;
    vector<string> ruta;
    if (encontrarRutaArchivo(raiz, "montaña.png", ruta)) {
        cout << "   Ruta: ";
        for (size_t i = 0; i < ruta.size(); ++i) {
            cout << ruta[i];
            if (i < ruta.size() - 1) cout << " → ";
        }
        cout << endl;
    }
    
    // Limpieza de memoria
    delete vacaciones;
    delete musica;
    delete imagenes;
    delete docs;
    delete raiz;
    
    return 0;
}
