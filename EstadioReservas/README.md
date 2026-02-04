
# Estadio Reservas C++ (C++17, consola, MVC+Utils, MongoDB, listas circulares)

## Requisitos
- g++ (C++17)
- MongoDB (servidor accesible)
- MongoDB C++ Driver (`mongocxx` / `bsoncxx`)

## Compilación
```bash
make
./estadio
```

> El `Makefile` usa `pkg-config` para detectar las banderas de `libmongocxx`.

## Configuración de conexión
La conexión se parametriza con variables de entorno:
- `MONGO_URI` (por defecto: `mongodb://localhost:27017`)
- `MONGO_DB_USUARIOS` (por defecto: `usuarios`)
- `MONGO_DB_EVENTOS` (por defecto: `eventos`)
- `MONGO_DB_BOLETOS` (por defecto: `boletos`)
- `MONGO_COLLECTION` (por defecto: `EstadioReservas`)

Ejemplo:
```bash
export MONGO_URI="mongodb+srv://usuario:clave@mi-cluster.mongodb.net"
export MONGO_DB_USUARIOS="usuarios"
export MONGO_DB_EVENTOS="eventos"
export MONGO_DB_BOLETOS="boletos"
export MONGO_COLLECTION="EstadioReservas"
./estadio
```

## Estructura
- `include/` headers (MVC + Utils + Estructuras de datos propias)
- `src/` fuentes
- `Makefile`

## Notas
- Login por cédula ecuatoriana + nombre (case-sensitive). Si no existe, se registra.
- Límite por usuario **por evento**, acumulable.
- Reservas por **cupos** (GENERAL, TRIBUNA, PALCO), no hay butacas numeradas.
- Se puede reservar hasta el **día anterior** a la fecha del evento.
