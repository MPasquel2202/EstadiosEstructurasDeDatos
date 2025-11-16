
# Estadio Reservas C++ (C++17, consola, MVC+Utils, JSON, listas circulares)

## Requisitos
- g++ (C++17)
- curl o wget (solo para descargar `json.hpp` automáticamente)

## Compilación
```bash
make
./estadio
```

> El `Makefile` intentará descargar `include/nlohmann/json.hpp` si no existe (Linux/macOS).  
> En Windows, ejecuta:
```powershell
powershell -ExecutionPolicy Bypass -File scripts/fetch_json.ps1
```
y luego:
```powershell
make
.\estadio.exe
```

## Estructura
- `include/` headers (MVC + Utils + Estructuras de datos propias)
- `src/` fuentes
- `data/` JSON semilla (`eventos.json`, `boletos.json`, `usuarios.json`)
- `scripts/fetch_json.*` descarga la cabecera de nlohmann/json
- `Makefile`

## Notas
- Login por cédula ecuatoriana + nombre (case-sensitive). Si no existe, se registra.
- Límite por usuario **por evento**, acumulable.
- Reservas por **cupos** (GENERAL, TRIBUNA, PALCO), no hay butacas numeradas.
- Se puede reservar hasta el **día anterior** a la fecha del evento.
