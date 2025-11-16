$ErrorActionPreference = "Stop"
$Url = "https://raw.githubusercontent.com/nlohmann/json/develop/single_include/nlohmann/json.hpp"
$Out = "include/nlohmann/json.hpp"
New-Item -ItemType Directory -Force -Path "include\nlohmann" | Out-Null
Write-Host "Descargando json.hpp desde: $Url"
Invoke-WebRequest -Uri $Url -OutFile $Out
Write-Host "Listo: $Out"
