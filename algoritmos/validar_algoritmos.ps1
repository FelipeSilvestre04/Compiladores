$ErrorActionPreference = "Stop"

$repo = Split-Path -Parent $PSScriptRoot
$simulador = Join-Path $repo "tools\interactive_sim.py"

$casos = @(
    @{ Nome = "01_fatorial"; Entradas = "5"; Esperado = "120" },
    @{ Nome = "01_fatorial"; Entradas = "0"; Esperado = "1" },
    @{ Nome = "02_mdc"; Entradas = "48,18"; Esperado = "6" },
    @{ Nome = "02_mdc"; Entradas = "7,0"; Esperado = "7" },
    @{ Nome = "03_ordenacao_selecao"; Entradas = "9,2,7,1,8,3,5,0,4,6"; Esperado = "0,1,2,3,4,5,6,7,8,9" },
    @{ Nome = "03_ordenacao_selecao"; Entradas = "5,1,5,3,2,0,9,8,7,6"; Esperado = "0,1,2,3,5,5,6,7,8,9" },
    @{ Nome = "04_fibonacci"; Entradas = "10"; Esperado = "55" },
    @{ Nome = "04_fibonacci"; Entradas = "0"; Esperado = "0" },
    @{ Nome = "04_fibonacci"; Entradas = "1"; Esperado = "1" },
    @{ Nome = "05_potenciacao"; Entradas = "3,4"; Esperado = "81" },
    @{ Nome = "05_potenciacao"; Entradas = "7,0"; Esperado = "1" },
    @{ Nome = "06_numero_primo"; Entradas = "29"; Esperado = "1" },
    @{ Nome = "06_numero_primo"; Entradas = "21"; Esperado = "0" },
    @{ Nome = "06_numero_primo"; Entradas = "1"; Esperado = "0" },
    @{ Nome = "07_busca_linear"; Entradas = "4,9,2,7,5,7"; Esperado = "3" },
    @{ Nome = "07_busca_linear"; Entradas = "4,9,2,7,5,6"; Esperado = "5" },
    @{ Nome = "08_soma_media"; Entradas = "4,8,6,2"; Esperado = "20,5" },
    @{ Nome = "08_soma_media"; Entradas = "0,0,0,0"; Esperado = "0,0" },
    @{ Nome = "09_produto_escalar"; Entradas = "1,2,3,4,5,6"; Esperado = "32" },
    @{ Nome = "09_produto_escalar"; Entradas = "1,0,2,0,3,0"; Esperado = "0" },
    @{ Nome = "10_matrizes_2x2"; Entradas = "1,2,3,4,5,6,7,8"; Esperado = "19,22,43,50" },
    @{ Nome = "10_matrizes_2x2"; Entradas = "2,3,4,5,1,0,0,1"; Esperado = "2,3,4,5" }
)

$falhas = 0
foreach ($caso in $casos) {
    $programa = Join-Path $PSScriptRoot "$($caso.Nome)\program.txt"
    & python $simulador $programa --inputs $caso.Entradas --expect $caso.Esperado --quiet
    if ($LASTEXITCODE -ne 0) {
        $falhas++
        Write-Host "FALHA: $($caso.Nome), entradas $($caso.Entradas)" -ForegroundColor Red
    }
}

if ($falhas -ne 0) {
    throw "$falhas caso(s) de teste falharam."
}

Write-Host "Todos os $($casos.Count) casos foram aprovados." -ForegroundColor Green
