param(
    [Parameter(Mandatory=$true)] [string]$AppExe,
    [Parameter(Mandatory=$true)] [string]$OutDir,
    [Parameter(Mandatory=$true)] [string]$OutputExe
)

Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

# Requirements:
# - 7-Zip installed and 7z.exe available in PATH
# - 7z SFX module (7z.sfx). If not found in PATH, set $SfxPath below

function Resolve-7z {
    $candidates = @('7z.exe','"C:\\Program Files\\7-Zip\\7z.exe"','"C:\\Program Files (x86)\\7-Zip\\7z.exe"')
    foreach($c in $candidates){
        try { $ver = & $ExecutionContext.InvokeCommand.ExpandString($c) -b | Out-Null; return $ExecutionContext.InvokeCommand.ExpandString($c) } catch {}
    }
    throw '7z.exe not found. Please install 7-Zip and ensure it is in PATH.'
}

function Resolve-Sfx {
    $candidates = @('7z.sfx','"C:\\Program Files\\7-Zip\\7z.sfx"','"C:\\Program Files (x86)\\7-Zip\\7z.sfx"')
    foreach($c in $candidates){ if(Test-Path $ExecutionContext.InvokeCommand.ExpandString($c)){ return $ExecutionContext.InvokeCommand.ExpandString($c) } }
    throw '7z.sfx not found. Please locate 7z.sfx and add it to PATH.'
}

$AppExe = Resolve-Path $AppExe | Select-Object -ExpandProperty Path
$OutDir = Resolve-Path $OutDir | Select-Object -ExpandProperty Path
$OutputExe = [System.IO.Path]::GetFullPath($OutputExe)

if(!(Test-Path $AppExe)){ throw "App exe not found: $AppExe" }
if(!(Test-Path $OutDir)){ throw "Output dir not found: $OutDir" }

$sevenZip = Resolve-7z
$sfxPath = Resolve-Sfx

# Create a staging directory that includes everything next to the app exe
$staging = Join-Path $OutDir 'singlefile_staging'
if(Test-Path $staging){ Remove-Item -Recurse -Force $staging }
New-Item -ItemType Directory -Path $staging | Out-Null

# Copy all runtime artifacts next to the exe into staging
Get-ChildItem -Path $OutDir -Force | ForEach-Object {
    if($_.Name -ne 'singlefile_staging'){
        $dest = Join-Path $staging $_.Name
        if($_.PSIsContainer){ Copy-Item -Recurse -Force $_.FullName $dest }
        else { Copy-Item -Force $_.FullName $dest }
    }
}

# Create config to auto-extract and run the app
$configTxt = @"
;!@Install@!UTF-8!
Title="LabRecorder Single-File"
RunProgram="LabRecorder.exe"
; Extract to %LOCALAPPDATA% subfolder to avoid requiring write access
InstallPath="%LOCALAPPDATA%\\LabRecorder_SFX"
GUIMode="2"
;!@InstallEnd@!
"@

$configFile = Join-Path $staging 'config.txt'
Set-Content -Path $configFile -Value $configTxt -Encoding UTF8

# Build an archive of the staging folder
$archive = Join-Path $OutDir 'LabRecorder.7z'
if(Test-Path $archive){ Remove-Item -Force $archive }
Push-Location $staging
& $sevenZip a -t7z -m0=LZMA2 -mx=5 -mmt=on $archive * | Out-Null
Pop-Location

# Concatenate SFX + config + archive into a self-extracting EXE
if(Test-Path $OutputExe){ Remove-Item -Force $OutputExe }
Get-Content -Path $sfxPath -Encoding Byte | Set-Content -Path $OutputExe -Encoding Byte
Get-Content -Path $configFile -Encoding Byte | Add-Content -Path $OutputExe -Encoding Byte
Get-Content -Path $archive -Encoding Byte | Add-Content -Path $OutputExe -Encoding Byte

Write-Host "Created single-file executable: $OutputExe"


