$ErrorActionPreference = "Stop"

$algoritmos = Get-ChildItem -LiteralPath $PSScriptRoot -Directory |
    Where-Object { $_.Name -match '^\d{2}_' } |
    Sort-Object Name

$saida = [Collections.Generic.List[string]]::new()
$saida.Add("PONTO DE CHECAGEM PC1")
$saida.Add("ALGORITMOS EM C- E CODIGOS DE MAQUINA")
$saida.Add("")

foreach ($algoritmo in $algoritmos) {
    $fonte = Join-Path $algoritmo.FullName "codigo_c.txt"
    $maquina = Join-Path $algoritmo.FullName "program.txt"

    $saida.Add("================================================================")
    $saida.Add($algoritmo.Name.ToUpperInvariant())
    $saida.Add("================================================================")
    $saida.Add("")
    $saida.Add("CODIGO DE ALTO NIVEL (C-)")
    $saida.Add("")
    foreach ($linha in Get-Content -LiteralPath $fonte) {
        $saida.Add($linha)
    }
    $saida.Add("")
    $saida.Add("CODIGO DE MAQUINA (32 BITS)")
    $saida.Add("")
    foreach ($linha in Get-Content -LiteralPath $maquina) {
        $saida.Add($linha)
    }
    $saida.Add("")
}

$destino = Join-Path $PSScriptRoot "ENTREGA_PC1.txt"
Set-Content -LiteralPath $destino -Value $saida -Encoding UTF8
Write-Host "Arquivo de entrega gerado: $destino" -ForegroundColor Green
