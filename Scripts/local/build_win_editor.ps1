param(
  [string]$UE = "$env:ProgramFiles\Epic Games\UE_5.6",
  [string]$Proj = "C:\Users\Robin Lifshitz\Documents\Unreal Projects\ProjectHaven\ProjectHaven.uproject"
)

$buildBat = Join-Path $UE "Engine\Build\BatchFiles\Build.bat"

if (!(Test-Path $buildBat)) {
  Write-Error "Build.bat not found at: $buildBat"
  exit 1
}
if (!(Test-Path $Proj)) {
  Write-Error "uproject not found at: $Proj"
  exit 1
}

& $buildBat `
  ProjectHavenEditor `
  Win64 `
  Development `
  -project="$Proj" `
  -NoHotReload
