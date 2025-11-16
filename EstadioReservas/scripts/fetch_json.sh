#!/usr/bin/env bash
set -e
mkdir -p include/nlohmann
URL="https://raw.githubusercontent.com/nlohmann/json/develop/single_include/nlohmann/json.hpp"
OUT="include/nlohmann/json.hpp"
echo "Descargando json.hpp desde: $URL"
if command -v curl >/dev/null 2>&1; then
  curl -L "$URL" -o "$OUT"
elif command -v wget >/dev/null 2>&1; then
  wget -O "$OUT" "$URL"
else
  echo "Necesitas curl o wget para descargar."
  exit 1
fi
echo "Listo: $OUT"
