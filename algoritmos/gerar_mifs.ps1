$ErrorActionPreference = "Stop"

$algoritmos = Get-ChildItem -LiteralPath $PSScriptRoot -Directory |
    Where-Object { $_.Name -match '^\d{2}_' } |
    Sort-Object Name

foreach ($algoritmo in $algoritmos) {
    $programa = Join-Path $algoritmo.FullName "program.txt"
    $mif = Join-Path $algoritmo.FullName "programa.mif"
    $instrucoes = @(Get-Content -LiteralPath $programa)

    if ($instrucoes.Count -gt 256) {
        throw "$($algoritmo.Name) excede as 256 palavras da ROM."
    }

    foreach ($instrucao in $instrucoes) {
        if ($instrucao -notmatch '^[01]{32}$') {
            throw "Instrucao binaria invalida em ${programa}: $instrucao"
        }
    }

    $linhas = [Collections.Generic.List[string]]::new()
    $linhas.Add("WIDTH=32;")
    $linhas.Add("DEPTH=256;")
    $linhas.Add("")
    $linhas.Add("ADDRESS_RADIX=UNS;")
    $linhas.Add("DATA_RADIX=BIN;")
    $linhas.Add("")
    $linhas.Add("CONTENT BEGIN")

    for ($endereco = 0; $endereco -lt 256; $endereco++) {
        if ($endereco -lt $instrucoes.Count) {
            $valor = $instrucoes[$endereco]
        }
        else {
            $valor = "00000000000000000000000000000000"
        }
        $linhas.Add("    $endereco : $valor;")
    }

    $linhas.Add("END;")
    Set-Content -LiteralPath $mif -Value $linhas -Encoding ASCII
    Write-Host "MIF gerado: $($algoritmo.Name)"
}

Write-Host "MIFs gerados para os $($algoritmos.Count) algoritmos." -ForegroundColor Green
