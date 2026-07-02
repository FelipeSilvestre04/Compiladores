from __future__ import annotations

import math
from pathlib import Path
from typing import Sequence
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
    label_pos: tuple[int, int] | None = None,
    width: int = 3,
    elbow: tuple[int, int] | Sequence[tuple[int, int]] | None = None,
) -> None:
    if elbow is None:
        points = [start, end]
    elif isinstance(elbow, tuple):
        points = [start, elbow, end]
    else:
        points = [start, *elbow, end]
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
        if label_pos is None:
            lx = sum(p[0] for p in points) // len(points)
            ly = sum(p[1] for p in points) // len(points)
        else:
            lx, ly = label_pos
        rendered = fit_lines(d, label, SMALL, 220)
        tw, th = text_size(d, rendered, SMALL)
        d.rounded_rectangle(
            (lx - tw // 2 - 8, ly - th // 2 - 5, lx + tw // 2 + 8, ly + th // 2 + 5),
            radius=6,
            fill=BG,
        )
        d.multiline_text((lx, ly), rendered, fill=TEXT, font=SMALL, anchor="mm", align="center", spacing=4)


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
    panel(d, (70, 110, 520, 540), "Busca e Decodificacao")
    panel(d, (600, 110, 1040, 540), "Controle")
    panel(d, (1115, 110, 1850, 900), "Caminho de Dados")

    pc = (185, 175, 405, 245)
    rom = (160, 305, 430, 385)
    dec = (160, 445, 430, 515)
    uc = (690, 175, 950, 265)
    ctrl = (685, 385, 955, 475)
    reg = (1190, 190, 1455, 280)
    muxula = (1190, 390, 1405, 470)
    ula = (1480, 390, 1665, 470)
    muxmem = (1605, 190, 1830, 280)
    ram = (1435, 585, 1670, 675)
    io = (1170, 735, 1405, 815)
    stack = (1525, 735, 1815, 815)

    for xy, text in [
        (pc, "PC\nPC.v"),
        (rom, "ROM de Instrucoes\nrom.v / programa.txt"),
        (dec, "Decodificador\ndecoder_instrucao.v"),
        (uc, "Unidade de Controle\nUnidade_Controle.v"),
        (ctrl, "Controle de PC\nbranch / jump / jr / jal"),
        (reg, "Banco de Registradores\nbanco.v"),
        (muxula, "MUX da ULA\nmux_ula.v"),
        (ula, "ULA\nula.v"),
        (muxmem, "MUX de Escrita\nmux_memoria.v"),
        (ram, "Memoria de Dados\nram.v"),
        (stack, "Pilha / SP\ncpu.v + ram.v"),
        (io, "Entrada e Saida\nControleSinal.v\nControleSaida.v"),
    ]:
        box(d, xy, text)

    arrow(d, side(pc, "bottom"), side(rom, "top"), label="endereco", label_pos=(300, 275))
    arrow(d, side(rom, "bottom"), side(dec, "top"), label="instrucao", label_pos=(300, 418))
    arrow(d, side(dec, "right"), side(uc, "left"), label="opcode / funct", label_pos=(555, 475))
    arrow(d, side(uc, "bottom"), side(ctrl, "top"), label="sinais de fluxo", label_pos=(820, 335))
    arrow(d, side(ctrl, "left"), side(pc, "top"), elbow=[(560, 430), (560, 80), (295, 80)], label="proximo PC", label_pos=(560, 80))

    arrow(d, side(uc, "right"), side(reg, "left"), label="controle", label_pos=(1090, 180))
    arrow(d, side(uc, "right"), side(muxula, "left"), elbow=(1080, 430), label="ALUSrc / ALUop", label_pos=(1060, 430))

    arrow(d, side(reg, "bottom"), side(muxula, "top"), label="rs2", label_pos=(1305, 335))
    arrow(d, side(reg, "right"), side(ula, "top"), elbow=(1575, 330), label="rs1", label_pos=(1590, 335))
    arrow(d, side(muxula, "right"), side(ula, "left"), label="operando 2", label_pos=(1440, 430))
    arrow(d, side(ula, "top"), side(muxmem, "bottom"), label="resultado", label_pos=(1605, 340))
    arrow(d, side(muxmem, "left"), side(reg, "right"), label="rd_data", label_pos=(1530, 235))

    arrow(d, side(ula, "bottom"), side(ram, "top"), label="endereco\nLOAD/STORE", label_pos=(1550, 535))
    arrow(d, side(ram, "right"), side(muxmem, "bottom"), elbow=[(1780, 630), (1780, 285)], label="dado lido", label_pos=(1770, 555))
    arrow(d, side(reg, "left"), side(io, "left"), elbow=[(1145, 235), (1145, 775)], label="IN / OUT", label_pos=(1145, 690))
    arrow(d, side(ram, "bottom"), side(stack, "top"), label="push / pop", label_pos=(1605, 705))

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
    arrow(d, side(halt, "right"), (1718, 135), label="sim", label_pos=(1545, 135))

    tipo = (800, 230, 1045, 310)
    box(d, tipo, "Identificar formato\nR, I, B, J, N ou IO")
    arrow(d, side(halt, "bottom"), side(tipo, "top"), label="nao", label_pos=(1035, 215))

    cols = [
        ("Tipo R", "Ler rs1 e rs2\nExecutar ULA\nEscrever em rd", 90),
        ("Tipo I", "Acessar memoria,\nimediato, LA ou MOV\nAtualizar rd/RAM", 405),
        ("Tipo B", "Comparar rs1 e rs2\nAplicar condicao\nCalcular desvio", 720),
        ("Tipo J", "Executar salto,\nJR ou JAL\nAtualizar destino", 1035),
        ("Tipo IO", "Executar IN, OUT\nou pilha\nAtualizar rd/SP", 1350),
        ("Tipo N", "Executar NOP\nAtualizar PC", 1645),
    ]
    y_panel = 350
    bus_y = 335
    arrow(d, side(tipo, "bottom"), (922, bus_y))
    d.line((210, bus_y, 1765, bus_y), fill=LINE, width=3)

    for title, body, x in cols:
        panel(d, (x, y_panel, x + 240, 760), title)
        action = (x + 25, y_panel + 95, x + 215, y_panel + 255)
        box(d, action, body, f=SMALL)
        arrow(d, (x + 120, bus_y), side(action, "top"))

    note = (535, 850, 1385, 950)
    box(
        d,
        note,
        "Cada caminho define o proximo PC: PC + 1, desvio, salto,\nretorno, parada para I/O ou HALT.",
        fill="#FFFFFF",
        f=BODY,
    )

    save(img, "02_processador_atividades.png")


def analise_blocos() -> None:
    img, d = canvas("Diagrama de Blocos - Fase de Analise do Compilador")
    nodes = [
        ((60, 285, 230, 375), "Codigo-fonte\nC-"),
        ((285, 260, 535, 395), "Analisador Lexico\nlexer.l"),
        ((595, 305, 745, 355), "Tokens"),
        ((805, 260, 1065, 395), "Analisador Sintatico\nyyparse()\nparser.y"),
        ((1125, 260, 1410, 395), "Construcao da AST\nparser.y + ast.h"),
        ((1500, 260, 1700, 395), "AST\nast.h"),
        ((1195, 555, 1515, 680), "Analise Semantica\nsemantic_analysis()\nparser.y"),
        ((1200, 745, 1520, 840), "Tabela de Simbolos\nstruct Symbol\nparser.y"),
        ((1600, 555, 1845, 680), "AST validada\npara sintese"),
        ((835, 745, 1160, 840), "Mensagens de Erro\nlexico / sintatico\nsemantico"),
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
    arrow(d, side(nodes[6][0], "bottom"), side(nodes[7][0], "top"), label="consulta / insere", label_pos=(1360, 715))
    arrow(d, side(nodes[1][0], "bottom"), side(nodes[9][0], "left"), elbow=(410, 792), label="erro lexico", label_pos=(410, 650))
    arrow(d, side(nodes[3][0], "bottom"), side(nodes[9][0], "top"), label="erro sintatico", label_pos=(955, 650))
    arrow(d, side(nodes[6][0], "left"), side(nodes[9][0], "right"), elbow=[(1135, 620), (1135, 792)], label="erro semantico", label_pos=(1100, 620))
    save(img, "03_analise_blocos.png")


def analise_atividades() -> None:
    img, d = canvas("Diagrama de Atividades - Fase de Analise do Compilador")
    start_node(d, 90, 150)
    box(d, (150, 110, 360, 190), "Receber\narquivo-fonte")
    arrow(d, (107, 150), (150, 150))

    panels = [
        ((430, 110, 845, 860), "Analise Lexica - lexer.l"),
        ((895, 110, 1310, 860), "Analise Sintatica - parser.y"),
        ((1360, 110, 1810, 860), "Analise Semantica - parser.y"),
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
    box(d, syn1, "Receber tokens\npor yylex()")
    box(d, syn2, "Aplicar gramatica\ne construir AST\ncom ast.h")
    diamond(d, synd, "erro sintatico?")
    box(d, sem1, "Percorrer AST\nsemantic_analysis()")
    box(d, sem2, "Verificar declaracoes,\ntipos, parametros,\nretornos e main")
    diamond(d, semd, "erro semantico?")
    box(d, err, "Emitir mensagens\nde erro")
    box(d, ok, "Liberar AST validada\npara sintese")
    end_node(d, 1835, 962)

    arrow(d, side((150, 110, 360, 190), "right"), side(lex1, "left"))
    arrow(d, side(lex1, "bottom"), side(lex2, "top"))
    arrow(d, side(lex2, "bottom"), side(lexd, "top"))
    arrow(d, side(lexd, "right"), side(syn1, "left"), label="nao", label_pos=(870, 600))
    arrow(d, side(lexd, "bottom"), side(err, "left"), elbow=(637, 965), label="sim", label_pos=(655, 810))
    arrow(d, side(syn1, "bottom"), side(syn2, "top"))
    arrow(d, side(syn2, "bottom"), side(synd, "top"))
    arrow(d, side(synd, "right"), side(sem1, "left"), label="nao", label_pos=(1335, 600))
    arrow(d, side(synd, "bottom"), side(err, "top"), label="sim", label_pos=(1090, 800))
    arrow(d, side(sem1, "bottom"), side(sem2, "top"))
    arrow(d, side(sem2, "bottom"), side(semd, "top"))
    arrow(d, side(semd, "bottom"), side(ok, "top"), label="nao", label_pos=(1625, 800))
    arrow(d, side(semd, "left"), side(err, "right"), elbow=(1330, 965), label="sim", label_pos=(1330, 805))
    arrow(d, side(ok, "right"), (1814, 962))

    save(img, "04_analise_atividades.png")


def sintese_blocos() -> None:
    img, d = canvas("Diagrama de Blocos - Fase de Sintese do Compilador")
    nodes = [
        ((55, 330, 225, 420), "AST validada\nast.h"),
        ((285, 295, 555, 455), "Geracao de Quadruplas\nprocessa_arvore()\ngerador_quaduplas.c"),
        ((620, 330, 780, 420), "saida.quad"),
        ((845, 295, 1115, 455), "Traducao para Assembly\nsalvar_asm_line()\ngerador_quaduplas.c"),
        ((1180, 330, 1340, 420), "saida.asm"),
        ((1405, 295, 1675, 455), "Codificacao Binaria\nwrite_binary_instruction()\ngerador_quaduplas.c"),
        ((1735, 330, 1880, 420), "programa.txt"),
        ((1510, 695, 1830, 790), "ROM do Processador\nrom.v"),
        ((560, 665, 1285, 800), "Estruturas internas\nprogram[], labels[], variables[]\nregistradores, escopos, enderecos e rotulos"),
    ]
    for xy, text in nodes:
        box(d, xy, text)
    for i in range(6):
        arrow(d, side(nodes[i][0], "right"), side(nodes[i + 1][0], "left"))
    arrow(d, side(nodes[6][0], "bottom"), side(nodes[7][0], "top"), label="carga do programa", label_pos=(1810, 565))
    arrow(d, side(nodes[1][0], "bottom"), side(nodes[8][0], "left"), elbow=(420, 735), label="temporarios e\nenderecos", label_pos=(420, 610))
    arrow(d, side(nodes[3][0], "bottom"), side(nodes[8][0], "top"), label="instrucoes e\nrotulos", label_pos=(980, 590))
    arrow(d, side(nodes[5][0], "bottom"), (1150, 665), elbow=[(1540, 610), (1150, 610)], label="labels e PCs", label_pos=(1540, 600))
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

    q1 = (455, 205, 765, 290)
    q2 = (455, 365, 765, 470)
    q3 = (455, 545, 765, 650)
    a1 = (945, 205, 1255, 290)
    a2 = (945, 365, 1255, 470)
    a3 = (945, 545, 1255, 650)
    b1 = (1435, 205, 1745, 290)
    b2 = (1435, 365, 1745, 470)
    b3 = (1435, 545, 1745, 650)
    out = (1450, 925, 1765, 1000)

    box(d, q1, "Inicializar variaveis,\nlabels e registradores")
    box(d, q2, "Percorrer AST\nswitch NodeType")
    box(d, q3, "Emitir quadruplas\ne salvar saida.quad")
    box(d, a1, "Ler program[]\ngerado pelas quadruplas")
    box(d, a2, "Selecionar traducao\npela operacao")
    box(d, a3, "Resolver labels/PC\ne salvar saida.asm")
    box(d, b1, "Ler instrucoes\nassembly")
    box(d, b2, "Selecionar formato\nR, I, J, B, N ou IO")
    box(d, b3, "Preencher opcode, funct,\nregistradores e imediato")
    box(d, out, "Salvar programa.txt")
    end_node(d, 1835, 962)

    arrow(d, side((140, 110, 335, 190), "right"), side(q1, "left"))
    for first, second in [(q1, q2), (q2, q3), (a1, a2), (a2, a3), (b1, b2), (b2, b3)]:
        arrow(d, side(first, "bottom"), side(second, "top"))
    arrow(d, side(q3, "right"), side(a1, "left"), label="quadruplas", label_pos=(855, 600))
    arrow(d, side(a3, "right"), side(b1, "left"), label="assembly", label_pos=(1345, 600))
    arrow(d, side(b3, "bottom"), side(out, "top"), label="palavras de 32 bits", label_pos=(1625, 795))
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
