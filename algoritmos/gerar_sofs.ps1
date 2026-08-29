param(
    [ValidateSet("Todos", "Local", "Remoto")]
    [string] $Modo = "Todos"
)

$ErrorActionPreference = "Stop"

$repo = Split-Path -Parent $PSScriptRoot
$projetoBase = Join-Path $repo "src\processor\cpu"
$quartusBin = "C:\intelFPGA_lite\21.1\quartus\bin64"
$quartusSh = Join-Path $quartusBin "quartus_sh.exe"
$quartusCdb = Join-Path $quartusBin "quartus_cdb.exe"
$quartusAsm = Join-Path $quartusBin "quartus_asm.exe"

foreach ($executavel in @($quartusSh, $quartusCdb, $quartusAsm)) {
    if (-not (Test-Path -LiteralPath $executavel)) {
        throw "Executavel do Quartus nao encontrado: $executavel"
    }
}

$algoritmos = Get-ChildItem -LiteralPath $PSScriptRoot -Directory |
    Where-Object { $_.Name -match '^\d{2}_' } |
    Sort-Object Name

if ($algoritmos.Count -ne 10) {
    throw "Esperadas 10 pastas de algoritmos; encontradas $($algoritmos.Count)."
}

$buildRoot = Join-Path ([IO.Path]::GetTempPath()) ("compiladores_pc1_quartus_" + [guid]::NewGuid().ToString("N"))
$localBuild = Join-Path $buildRoot "local"
$remoteBuild = Join-Path $buildRoot "remoto"

function Copy-ProjectFiles([string] $destination) {
    New-Item -ItemType Directory -Force -Path $destination | Out-Null
    Get-ChildItem -LiteralPath $projetoBase -File | ForEach-Object {
        Copy-Item -LiteralPath $_.FullName -Destination $destination
    }
}

function Set-RemotePinning([string] $qsfPath) {
    $localAssignments = @(
        "set_location_assignment PIN_M23 -to btn_in",
        "set_location_assignment PIN_R24 -to rst",
        "set_location_assignment PIN_F19 -to btn_out",
        "set_location_assignment PIN_AB28 -to switches[0]",
        "set_location_assignment PIN_AC28 -to switches[1]",
        "set_location_assignment PIN_AC27 -to switches[2]",
        "set_location_assignment PIN_AD27 -to switches[3]",
        "set_location_assignment PIN_AB27 -to switches[4]",
        "set_location_assignment PIN_AC26 -to switches[5]",
        "set_location_assignment PIN_AD26 -to switches[6]",
        "set_location_assignment PIN_AB26 -to switches[7]",
        "set_location_assignment PIN_AC25 -to switches[8]",
        "set_location_assignment PIN_AB25 -to switches[9]",
        "set_location_assignment PIN_AC24 -to switches[10]",
        "set_location_assignment PIN_AB24 -to switches[11]",
        "set_location_assignment PIN_AB23 -to switches[12]",
        "set_location_assignment PIN_AA24 -to switches[13]",
        "set_location_assignment PIN_AA23 -to switches[14]",
        "set_location_assignment PIN_AA22 -to switches[15]",
        "set_location_assignment PIN_Y24 -to switches[16]",
        "set_location_assignment PIN_Y23 -to switches[17]",
        "set_location_assignment PIN_Y2 -to clk_50"
    )

    $remoteAssignments = @(
        "set_location_assignment PIN_AB22 -to btn_in",
        "set_location_assignment PIN_Y17 -to rst",
        "set_location_assignment PIN_M23 -to btn_out",
        "set_location_assignment PIN_Y16 -to switches[0]",
        "set_location_assignment PIN_AD21 -to switches[1]",
        "set_location_assignment PIN_AE16 -to switches[2]",
        "set_location_assignment PIN_AD15 -to switches[3]",
        "set_location_assignment PIN_AE15 -to switches[4]",
        "set_location_assignment PIN_AC19 -to switches[5]",
        "set_location_assignment PIN_AF16 -to switches[6]",
        "set_location_assignment PIN_AD19 -to switches[7]",
        "set_location_assignment PIN_AF15 -to switches[8]",
        "set_location_assignment PIN_AF24 -to switches[9]",
        "set_location_assignment PIN_AE21 -to switches[10]",
        "set_location_assignment PIN_AF25 -to switches[11]",
        "set_location_assignment PIN_AC22 -to switches[12]",
        "set_location_assignment PIN_AE22 -to switches[13]",
        "set_location_assignment PIN_AF21 -to switches[14]",
        "set_location_assignment PIN_AF22 -to switches[15]",
        "set_location_assignment PIN_AD22 -to switches[16]",
        "set_location_assignment PIN_AG25 -to switches[17]",
        "set_location_assignment PIN_AG14 -to clk_50"
    )

    $content = Get-Content -LiteralPath $qsfPath -Raw
    foreach ($assignment in $localAssignments) {
        $content = $content.Replace($assignment, "# $assignment")
    }
    foreach ($assignment in $remoteAssignments) {
        $content = $content.Replace("# $assignment", $assignment)
    }
    Set-Content -LiteralPath $qsfPath -Value $content -Encoding UTF8
}

function Convert-ProgramToMif(
    [string] $programPath,
    [string] $mifPath
) {
    $instructions = @(Get-Content -LiteralPath $programPath)
    if ($instructions.Count -gt 256) {
        throw "Programa excede as 256 palavras da ROM: $programPath"
    }

    foreach ($instruction in $instructions) {
        if ($instruction -notmatch '^[01]{32}$') {
            throw "Instrucao binaria invalida em ${programPath}: $instruction"
        }
    }

    $lines = [Collections.Generic.List[string]]::new()
    $lines.Add("WIDTH=32;")
    $lines.Add("DEPTH=256;")
    $lines.Add("")
    $lines.Add("ADDRESS_RADIX=UNS;")
    $lines.Add("DATA_RADIX=BIN;")
    $lines.Add("")
    $lines.Add("CONTENT BEGIN")
    for ($address = 0; $address -lt 256; $address++) {
        if ($address -lt $instructions.Count) {
            $value = $instructions[$address]
        }
        else {
            $value = "00000000000000000000000000000000"
        }
        $lines.Add("    $address : $value;")
    }
    $lines.Add("END;")
    Set-Content -LiteralPath $mifPath -Value $lines -Encoding ASCII
}

function Invoke-Quartus(
    [string] $executable,
    [string[]] $arguments,
    [string] $workingDirectory,
    [string] $logPath
) {
    Push-Location $workingDirectory
    try {
        & $executable @arguments 2>&1 | Tee-Object -FilePath $logPath -Append
        if ($LASTEXITCODE -ne 0) {
            throw "Quartus terminou com codigo ${LASTEXITCODE}: $executable $arguments"
        }
    }
    finally {
        Pop-Location
    }
}

function Build-Mode(
    [string] $buildDirectory,
    [string] $sofName,
    [bool] $remote
) {
    Copy-ProjectFiles $buildDirectory
    if ($remote) {
        Set-RemotePinning (Join-Path $buildDirectory "cpu.qsf")
    }

    for ($index = 0; $index -lt $algoritmos.Count; $index++) {
        $algoritmo = $algoritmos[$index]
        $programa = Join-Path $algoritmo.FullName "program.txt"
        if ($remote) {
            $logName = "quartus_remoto.log"
        }
        else {
            $logName = "quartus_local.log"
        }
        $log = Join-Path $algoritmo.FullName $logName
        Set-Content -LiteralPath $log -Value "Algoritmo: $($algoritmo.Name)" -Encoding UTF8
        Copy-Item -LiteralPath $programa -Destination (Join-Path $buildDirectory "programa.txt") -Force
        Convert-ProgramToMif $programa (Join-Path $buildDirectory "programa.mif")

        if ($index -eq 0) {
            Invoke-Quartus $quartusSh @("--flow", "compile", "cpu") $buildDirectory $log
        }
        else {
            $romMifs = @(Get-ChildItem -LiteralPath (Join-Path $buildDirectory "db") -Filter "*rom*.hdl.mif" -File)
            if ($romMifs.Count -ne 1) {
                throw "Esperado um MIF gerado para a ROM; encontrados $($romMifs.Count)."
            }
            Convert-ProgramToMif $programa $romMifs[0].FullName
            Invoke-Quartus $quartusCdb @("--update_mif", "cpu") $buildDirectory $log
            Invoke-Quartus $quartusAsm @("cpu") $buildDirectory $log
        }

        $generatedSof = Join-Path $buildDirectory "output_files\cpu.sof"
        if (-not (Test-Path -LiteralPath $generatedSof)) {
            throw "SOF nao foi gerado para $($algoritmo.Name)."
        }
        Copy-Item -LiteralPath $generatedSof -Destination (Join-Path $algoritmo.FullName $sofName) -Force
        Write-Host "$sofName gerado para $($algoritmo.Name)"
    }
}

try {
    if ($Modo -in @("Todos", "Local")) {
        Build-Mode $localBuild "cpu.sof" $false
    }
    if ($Modo -in @("Todos", "Remoto")) {
        Build-Mode $remoteBuild "cpu_remoto.sof" $true
    }
}
finally {
    $tempRoot = [IO.Path]::GetFullPath([IO.Path]::GetTempPath())
    $resolvedBuild = [IO.Path]::GetFullPath($buildRoot)
    if ($resolvedBuild.StartsWith($tempRoot, [StringComparison]::OrdinalIgnoreCase) -and
        (Test-Path -LiteralPath $resolvedBuild)) {
        Remove-Item -LiteralPath $resolvedBuild -Recurse -Force
    }
}

Write-Host "Geracao de SOFs concluida no modo: $Modo." -ForegroundColor Green
