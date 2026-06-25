from __future__ import annotations

import math
from pathlib import Path
from textwrap import wrap

from PIL import Image, ImageDraw, ImageFont


OUT = Path(__file__).resolve().parent / "png_16x9"
OUT.mkdir(parents=True, exist_ok=True)

W, H = 1920, 1080
BG = "#FFFFFF"
BOX = "#F7F7F7"
PANEL = "#FBFBFB"
LINE = "#303030"
TEXT = "#111111"


def font(size: int, bold: bool = False) -> ImageFont.FreeTypeFont:
    candidates = [
        r"C:\Windows\Fonts\arialbd.ttf" if bold else r"C:\Windows\Fonts\arial.ttf",
        r"C:\Windows\Fonts\calibrib.ttf" if bold else r"C:\Windows\Fonts\calibri.ttf",
    ]
    for candidate in candidates:
        p = Path(candidate)
        if p.exists():
            return ImageFont.truetype(str(p), size)
    return ImageFont.load_default()


TITLE = font(34, True)
HEAD = font(25, True)
BODY = font(22)
SMALL = font(19)
MONO = font(19)


def canvas(title: str) -> tuple[Image.Image, ImageDraw.ImageDraw]:
    img = Image.new("RGB", (W, H), BG)
    d = ImageDraw.Draw(img)
    d.text((W // 2, 34), title, fill=TEXT, font=TITLE, anchor="mm")
    return img, d


def text_size(d: ImageDraw.ImageDraw, s: str, f: ImageFont.ImageFont) -> tuple[int, int]:
    bbox = d.multiline_textbbox((0, 0), s, font=f, spacing=5)
    return bbox[2] - bbox[0], bbox[3] - bbox[1]


def fit_lines(d: ImageDraw.ImageDraw, text: str, f: ImageFont.ImageFont, max_width: int) -> str:
    lines: list[str] = []
    for raw in text.split("\n"):
        if not raw:
            lines.append("")
            continue
        words = raw.split()
        current = ""
        for word in words:
            test = word if not current else f"{current} {word}"
            if text_size(d, test, f)[0] <= max_width:
                current = test
            else:
                if current:
                    lines.append(current)
                current = word
        if current:
            lines.append(current)
    return "\n".join(lines)


def box(
    d: ImageDraw.ImageDraw,
    xy: tuple[int, int, int, int],
    text: str,
    *,
    fill: str = BOX,
    outline: str = LINE,
    f: ImageFont.ImageFont = BODY,
    radius: int = 12,
    heading: bool = False,
) -> None:
    x1, y1, x2, y2 = xy
    d.rounded_rectangle(xy, radius=radius, fill=fill, outline=outline, width=2)
    rendered = fit_lines(d, text, f, (x2 - x1) - 28)
    tw, th = text_size(d, rendered, f)
    d.multiline_text(
        ((x1 + x2) // 2, (y1 + y2) // 2 - th // 2),
        rendered,
        fill=TEXT,
        font=f,
        anchor="ma",
        align="center",
        spacing=5,
    )
    if heading:
        d.line((x1, y1 + 40, x2, y1 + 40), fill=outline, width=2)


def panel(d: ImageDraw.ImageDraw, xy: tuple[int, int, int, int], title: str) -> None:
    x1, y1, x2, y2 = xy
    d.rounded_rectangle(xy, radius=15, fill=PANEL, outline=LINE, width=2)
    d.text(((x1 + x2) // 2, y1 + 28), title, fill=TEXT, font=HEAD, anchor="mm")
    d.line((x1, y1 + 55, x2, y1 + 55), fill=LINE, width=2)


def center(xy: tuple[int, int, int, int]) -> tuple[int, int]:
    x1, y1, x2, y2 = xy
    return (x1 + x2) // 2, (y1 + y2) // 2


def side(xy: tuple[int, int, int, int], where: str) -> tuple[int, int]:
    x1, y1, x2, y2 = xy
    if where == "left":
        return x1, (y1 + y2) // 2
    if where == "right":
        return x2, (y1 + y2) // 2
    if where == "top":
        return (x1 + x2) // 2, y1
    if where == "bottom":
        return (x1 + x2) // 2, y2
    raise ValueError(where)


def arrow(
    d: ImageDraw.ImageDraw,
    start: tuple[int, int],
    end: tuple[int, int],
    *,
    label: str | None = None,
    width: int = 3,
    elbow: tuple[int, int] | None = None,
) -> None:
    points = [start, end] if elbow is None else [start, elbow, end]
    d.line(points, fill=LINE, width=width)
    x1, y1 = points[-2]
    x2, y2 = points[-1]
    angle = math.atan2(y2 - y1, x2 - x1)
    length = 14
    spread = 0.45
    p1 = (x2 - length * math.cos(angle - spread), y2 - length * math.sin(angle - spread))
    p2 = (x2 - length * math.cos(angle + spread), y2 - length * math.sin(angle + spread))
    d.polygon([end, p1, p2], fill=LINE)
    if label:
        lx = sum(p[0] for p in points) // len(points)
        ly = sum(p[1] for p in points) // len(points)
        d.rectangle((lx - 6, ly - 14, lx + text_size(d, label, SMALL)[0] + 6, ly + 10), fill=BG)
        d.text((lx, ly), label, fill=TEXT, font=SMALL, anchor="lm")


def start_node(d: ImageDraw.ImageDraw, x: int, y: int) -> None:
    d.ellipse((x - 17, y - 17, x + 17, y + 17), fill=LINE, outline=LINE)


def end_node(d: ImageDraw.ImageDraw, x: int, y: int) -> None:
    d.ellipse((x - 21, y - 21, x + 21, y + 21), fill=BG, outline=LINE, width=3)
    d.ellipse((x - 12, y - 12, x + 12, y + 12), fill=LINE, outline=LINE)


def diamond(d: ImageDraw.ImageDraw, xy: tuple[int, int, int, int], text: str) -> None:
    x1, y1, x2, y2 = xy
    pts = [((x1 + x2) // 2, y1), (x2, (y1 + y2) // 2), ((x1 + x2) // 2, y2), (x1, (y1 + y2) // 2)]
    d.polygon(pts, fill=BG, outline=LINE)
    rendered = fit_lines(d, text, SMALL, (x2 - x1) - 20)
    d.multiline_text(center(xy), rendered, fill=TEXT, font=SMALL, anchor="mm", align="center", spacing=4)


def save(img: Image.Image, name: str) -> None:
    img.save(OUT / name, quality=95)


def processador_blocos() -> None:
    img, d = canvas("Diagrama de Blocos - Processador")
    panel(d, (70, 110, 520, 520), "Busca e Decodificacao")
    panel(d, (610, 110, 1030, 520), "Controle")
    panel(d, (1120, 110, 1850, 900), "Caminho de Dados")

    pc = (185, 185, 405, 255)
    rom = (175, 315, 415, 385)
    dec = (175, 445, 415, 500)
    uc = (705, 235, 930, 315)
    ctrl = (700, 395, 940, 475)
    reg = (1375, 325, 1605, 405)
    ula = (1200, 185, 1390, 255)
    ram = (1640, 185, 1815, 255)
    stack = (1190, 600, 1415, 680)
    io = (1585, 600, 1815, 680)

    for xy, text in [
        (pc, "PC\nContador de Programa"),
        (rom, "ROM de Instrucoes\nprograma.txt"),
        (dec, "Decodificador\nde Instrucao"),
        (uc, "Unidade de Controle"),
        (ctrl, "Controle de Desvio\nbranch / jump / jal / jr"),
        (reg, "Banco de Registradores"),
        (ula, "ULA"),
        (ram, "Memoria de Dados\nRAM"),
        (stack, "Unidade de Pilha\nSP interno"),
        (io, "Entrada e Saida\nIN / OUT"),
    ]:
        box(d, xy, text)

    arrow(d, side(pc, "bottom"), side(rom, "top"))
    d.text((300, 285), "endereco", fill=TEXT, font=SMALL, anchor="mm")
    arrow(d, side(rom, "bottom"), side(dec, "top"))
    d.text((300, 418), "instrucao", fill=TEXT, font=SMALL, anchor="mm")
    arrow(d, side(dec, "right"), side(uc, "left"))
    d.text((555, 470), "opcode / funct", fill=TEXT, font=SMALL, anchor="mm")
    arrow(d, side(uc, "bottom"), side(ctrl, "top"))
    d.text((820, 360), "fluxo", fill=TEXT, font=SMALL, anchor="mm")
    d.text((625, 390), "o controle de desvio\natualiza o proximo PC", fill=TEXT, font=SMALL, anchor="mm", align="center")
    arrow(d, side(uc, "right"), side(reg, "left"))
    d.text((1190, 315), "controle", fill=TEXT, font=SMALL, anchor="mm")
    arrow(d, side(reg, "left"), side(ula, "right"))
    d.text((1320, 280), "operandos", fill=TEXT, font=SMALL, anchor="mm")
    arrow(d, side(ula, "right"), side(reg, "top"))
    d.text((1440, 250), "resultado", fill=TEXT, font=SMALL, anchor="mm")
    arrow(d, side(reg, "right"), side(ram, "left"))
    d.text((1618, 318), "load/store", fill=TEXT, font=SMALL, anchor="mm")
    arrow(d, side(reg, "bottom"), side(stack, "top"))
    d.text((1390, 535), "pilha", fill=TEXT, font=SMALL, anchor="mm")
    arrow(d, side(reg, "bottom"), side(io, "top"))
    d.text((1605, 535), "entrada/saida", fill=TEXT, font=SMALL, anchor="mm")

    save(img, "01_processador_blocos.png")


def processador_atividades() -> None:
    img, d = canvas("Diagrama de Atividades - Ciclo de Execucao do Processador")
    start_node(d, 100, 135)
    fetch = (165, 95, 405, 175)
    decode = (470, 95, 735, 175)
    control = (800, 95, 1045, 175)
    halt = (1110, 95, 1330, 175)
    box(d, fetch, "Buscar instrucao\nna ROM")
    box(d, decode, "Decodificar opcode,\nfunct e operandos")
    box(d, control, "Gerar sinais\nde controle")
    diamond(d, halt, "HALT?")
    arrow(d, (117, 135), side(fetch, "left"))
    arrow(d, side(fetch, "right"), side(decode, "left"))
    arrow(d, side(decode, "right"), side(control, "left"))
    arrow(d, side(control, "right"), side(halt, "left"))

    end_node(d, 1740, 135)
    arrow(d, side(halt, "right"), (1718, 135))
    d.text((1545, 135), "sim", fill=TEXT, font=BODY, anchor="mm")

    tipo = (800, 230, 1045, 310)
    box(d, tipo, "Identificar tipo\nda instrucao")
    arrow(d, side(halt, "bottom"), side(tipo, "top"))
    d.text((1010, 205), "nao", fill=TEXT, font=BODY, anchor="mm")

    cols = [
        ("Tipo R", "Ler rs1 e rs2\nExecutar ULA\nEscrever em rd", 90),
        ("Tipo I", "Acessar memoria\nou imediato\nAtualizar rd/RAM", 405),
        ("Tipo B", "Comparar rs1 e rs2\nAtualizar PC\nconforme condicao", 720),
        ("Tipo J", "Executar salto,\nretorno ou chamada\nAtualizar PC", 1035),
        ("Tipo IO", "Executar entrada,\nsaida ou pilha\nAtualizar registrador/SP", 1350),
        ("Tipo N", "Executar NOP\nAtualizar PC", 1645),
    ]
    y_panel = 300
    for title, body, x in cols:
        panel(d, (x, y_panel, x + 240, 750), title)
        action = (x + 25, y_panel + 95, x + 215, y_panel + 255)
        pcbox = (x + 25, y_panel + 305, x + 215, y_panel + 385)
        box(d, action, body, f=SMALL)
        box(d, pcbox, "Definir proximo PC", f=SMALL)
        arrow(d, side(action, "bottom"), side(pcbox, "top"))

    box(
        d,
        (555, 875, 1365, 975),
        "Para instrucoes diferentes de HALT, o processador executa a operacao,\n"
        "define o proximo PC e retorna ao ciclo de busca.",
        fill="#FFFFFF",
        f=BODY,
    )

    save(img, "02_processador_atividades.png")


def analise_blocos() -> None:
    img, d = canvas("Diagrama de Blocos - Fase de Analise do Compilador")
    nodes = [
        ((70, 290, 245, 380), "Codigo-fonte\nC-"),
        ((310, 280, 545, 390), "Analisador Lexico\nlexer.l"),
        ((615, 310, 760, 360), "Tokens"),
        ((835, 280, 1085, 390), "Analisador Sintatico\nparser.y"),
        ((1160, 280, 1395, 390), "Construcao\nda AST"),
        ((1470, 280, 1645, 390), "AST"),
        ((1470, 555, 1670, 660), "Analisador\nSemantico"),
        ((1160, 720, 1420, 810), "Tabela de\nSimbolos"),
        ((1730, 555, 1860, 660), "AST\nvalidada"),
        ((780, 720, 1055, 810), "Mensagens\nde Erro"),
    ]
    for xy, text in nodes:
        box(d, xy, text)
    for a, b in [
        (nodes[0][0], nodes[1][0]),
        (nodes[1][0], nodes[2][0]),
        (nodes[2][0], nodes[3][0]),
        (nodes[3][0], nodes[4][0]),
        (nodes[4][0], nodes[5][0]),
    ]:
        arrow(d, side(a, "right"), side(b, "left"))
    arrow(d, side(nodes[5][0], "bottom"), side(nodes[6][0], "top"))
    arrow(d, side(nodes[6][0], "right"), side(nodes[8][0], "left"))
    arrow(d, side(nodes[6][0], "bottom"), side(nodes[7][0], "top"))
    arrow(d, side(nodes[1][0], "bottom"), side(nodes[9][0], "left"), elbow=(425, 765))
    arrow(d, side(nodes[3][0], "bottom"), side(nodes[9][0], "top"))
    arrow(d, side(nodes[6][0], "left"), side(nodes[9][0], "right"))
    d.text((425, 665), "erros lexicos", fill=TEXT, font=SMALL, anchor="mm")
    d.text((955, 650), "erros sintaticos", fill=TEXT, font=SMALL, anchor="mm")
    save(img, "03_analise_blocos.png")


def analise_atividades() -> None:
    img, d = canvas("Diagrama de Atividades - Fase de Analise do Compilador")
    start_node(d, 90, 150)
    box(d, (150, 110, 360, 190), "Receber\narquivo-fonte")
    arrow(d, (107, 150), (150, 150))

    panels = [
        ((430, 110, 845, 860), "Analise Lexica"),
        ((895, 110, 1310, 860), "Analise Sintatica"),
        ((1360, 110, 1810, 860), "Analise Semantica"),
    ]
    for xy, title in panels:
        panel(d, xy, title)

    lex1 = (485, 220, 790, 300)
    lex2 = (485, 390, 790, 470)
    lexd = (520, 560, 755, 640)
    syn1 = (950, 220, 1255, 300)
    syn2 = (950, 390, 1255, 470)
    synd = (985, 560, 1220, 640)
    sem1 = (1415, 220, 1755, 300)
    sem2 = (1415, 390, 1755, 470)
    semd = (1450, 560, 1720, 640)
    err = (770, 925, 1110, 1000)
    ok = (1450, 925, 1760, 1000)

    box(d, lex1, "Ler caracteres\ne formar lexemas")
    box(d, lex2, "Gerar tokens\ne descartar espacos/comentarios")
    diamond(d, lexd, "erro lexico?")
    box(d, syn1, "Receber fluxo\nde tokens")
    box(d, syn2, "Aplicar gramatica\ne construir AST")
    diamond(d, synd, "erro sintatico?")
    box(d, sem1, "Percorrer AST\ne tabela de simbolos")
    box(d, sem2, "Verificar declaracoes,\ntipos, parametros,\nretornos e main")
    diamond(d, semd, "erro semantico?")
    box(d, err, "Emitir mensagens\nde erro")
    box(d, ok, "Liberar AST validada\npara sintese")
    end_node(d, 1835, 962)

    arrow(d, side((150, 110, 360, 190), "right"), side(lex1, "left"))
    arrow(d, side(lex1, "bottom"), side(lex2, "top"))
    arrow(d, side(lex2, "bottom"), side(lexd, "top"))
    arrow(d, side(lexd, "right"), side(syn1, "left"), label="nao")
    arrow(d, side(lexd, "bottom"), side(err, "left"), elbow=(637, 965), label="sim")
    arrow(d, side(syn1, "bottom"), side(syn2, "top"))
    arrow(d, side(syn2, "bottom"), side(synd, "top"))
    arrow(d, side(synd, "right"), side(sem1, "left"), label="nao")
    arrow(d, side(synd, "bottom"), side(err, "top"), label="sim")
    arrow(d, side(sem1, "bottom"), side(sem2, "top"))
    arrow(d, side(sem2, "bottom"), side(semd, "top"))
    arrow(d, side(semd, "bottom"), side(ok, "top"), label="nao")
    arrow(d, side(semd, "left"), side(err, "right"), elbow=(1330, 965), label="sim")
    arrow(d, side(ok, "right"), (1814, 962))

    save(img, "04_analise_atividades.png")


def sintese_blocos() -> None:
    img, d = canvas("Diagrama de Blocos - Fase de Sintese do Compilador")
    nodes = [
        ((60, 330, 230, 410), "AST\nvalidada"),
        ((295, 310, 520, 430), "Gerador de\nQuadruplas"),
        ((585, 330, 750, 410), "saida.quad"),
        ((815, 310, 1040, 430), "Gerador de\nAssembly"),
        ((1105, 330, 1270, 410), "saida.asm"),
        ((1335, 310, 1560, 430), "Gerador de\nCodigo Binario"),
        ((1625, 330, 1790, 410), "programa.txt"),
        ((1515, 650, 1810, 735), "ROM do\nProcessador"),
        ((655, 650, 1135, 755), "Mapa de Variaveis,\nRegistradores e Rotulos"),
    ]
    for xy, text in nodes:
        box(d, xy, text)
    for i in range(7):
        arrow(d, side(nodes[i][0], "right"), side(nodes[i + 1][0], "left"))
    arrow(d, side(nodes[7][0], "left"), side(nodes[8][0], "right"), label="carga do programa")
    arrow(d, side(nodes[1][0], "bottom"), side(nodes[8][0], "left"), elbow=(410, 700), label="temporarios,\nenderecos e labels")
    arrow(d, side(nodes[3][0], "bottom"), side(nodes[8][0], "top"), label="simbolos e rotulos")
    save(img, "05_sintese_blocos.png")


def sintese_atividades() -> None:
    img, d = canvas("Diagrama de Atividades - Fase de Sintese do Compilador")
    start_node(d, 80, 150)
    box(d, (140, 110, 335, 190), "Receber\nAST validada")
    arrow(d, (97, 150), (140, 150))

    panels = [
        ((400, 110, 820, 860), "Geracao de Quadruplas"),
        ((890, 110, 1310, 860), "Geracao de Assembly"),
        ((1380, 110, 1800, 860), "Geracao de Binario"),
    ]
    for xy, title in panels:
        panel(d, xy, title)

    q1 = (460, 220, 760, 305)
    q2 = (460, 385, 760, 500)
    q3 = (460, 580, 760, 665)
    a1 = (950, 220, 1250, 305)
    a2 = (950, 385, 1250, 500)
    a3 = (950, 580, 1250, 665)
    b1 = (1440, 220, 1740, 305)
    b2 = (1440, 385, 1740, 500)
    b3 = (1440, 580, 1740, 665)
    out = (1450, 925, 1765, 1000)

    box(d, q1, "Inicializar tabelas\ne registradores")
    box(d, q2, "Percorrer AST\ne classificar nos")
    box(d, q3, "Salvar saida.quad")
    box(d, a1, "Ler quadruplas")
    box(d, a2, "Aplicar regra de traducao\nou expandir operacao")
    box(d, a3, "Resolver rotulos\ne salvar saida.asm")
    box(d, b1, "Ler instrucoes\nassembly")
    box(d, b2, "Identificar formato\nR, I, J, B, N ou IO")
    box(d, b3, "Gerar palavra binaria\nde 32 bits")
    box(d, out, "Salvar programa.txt")
    end_node(d, 1835, 962)

    arrow(d, side((140, 110, 335, 190), "right"), side(q1, "left"))
    for first, second in [(q1, q2), (q2, q3), (a1, a2), (a2, a3), (b1, b2), (b2, b3)]:
        arrow(d, side(first, "bottom"), side(second, "top"))
    arrow(d, side(q3, "right"), side(a1, "left"), label="quadruplas")
    arrow(d, side(a3, "right"), side(b1, "left"), label="assembly")
    arrow(d, side(b3, "bottom"), side(out, "top"))
    arrow(d, side(out, "right"), (1814, 962))
    save(img, "06_sintese_atividades.png")


def main() -> None:
    processador_blocos()
    processador_atividades()
    analise_blocos()
    analise_atividades()
    sintese_blocos()
    sintese_atividades()


if __name__ == "__main__":
    main()
