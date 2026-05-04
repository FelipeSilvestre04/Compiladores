"""
Diagrama de Atividades SysML — Gerador de Código Intermediário
Compilador C- → RISC-V Customizado

Notação padrão SysML/UML:
  ● Nó inicial (círculo preto preenchido)
  ◆ Decisão / Merge (losango)
  ▭ Ação (retângulo arredondado)
  ⊕ Nó final (bullseye)

Uso: python diagrama_atividades.py
Saída: diagrama_atividades.png
"""

import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
from matplotlib.patches import FancyBboxPatch
import matplotlib.patheffects as pe

# ══════════════════════════════════════════════════════════════════
#  PALETA — estilo acadêmico / profissional
# ══════════════════════════════════════════════════════════════════
WHITE      = "#FFFFFF"
BG         = "#FAFBFC"
BLACK      = "#1a1a2e"
DARK_GRAY  = "#2d2d44"
MED_GRAY   = "#6b7280"
LIGHT_GRAY = "#d1d5db"
ACTION_BG  = "#e8f4fd"
ACTION_BD  = "#2563eb"
EMIT_BG    = "#dbeafe"
EMIT_BD    = "#1d4ed8"
EMIT_TX    = "#1e40af"
DECISION_BG = "#fef3c7"
DECISION_BD = "#d97706"
FORK_COLOR  = BLACK
LABEL_COLOR = "#374151"
GUARD_COLOR = "#059669"
GUARD_NO    = "#dc2626"

# ══════════════════════════════════════════════════════════════════
#  PRIMITIVAS DE DESENHO
# ══════════════════════════════════════════════════════════════════

def action_box(ax, cx, cy, w, h, text, is_emit=False, fontsize=8.5):
    """Ação: retângulo com cantos arredondados."""
    bg = EMIT_BG if is_emit else ACTION_BG
    bd = EMIT_BD if is_emit else ACTION_BD
    tx = EMIT_TX if is_emit else BLACK
    box = FancyBboxPatch(
        (cx - w/2, cy - h/2), w, h,
        boxstyle="round,pad=0.06", facecolor=bg, edgecolor=bd,
        linewidth=1.4, zorder=3,
    )
    ax.add_patch(box)
    ax.text(cx, cy, text, ha="center", va="center", fontsize=fontsize,
            color=tx, family="sans-serif", zorder=4, linespacing=1.3,
            fontweight="medium")

def decision(ax, cx, cy, size=0.45):
    """Losango de decisão/merge."""
    s = size / 2
    d = plt.Polygon(
        [(cx, cy+s), (cx+s, cy), (cx, cy-s), (cx-s, cy)],
        closed=True, facecolor=DECISION_BG, edgecolor=DECISION_BD,
        linewidth=1.4, zorder=3,
    )
    ax.add_patch(d)

def initial_node(ax, cx, cy, r=0.13):
    """● Nó inicial (círculo preto preenchido)."""
    c = plt.Circle((cx, cy), r, fc=BLACK, ec=BLACK, lw=1.5, zorder=3)
    ax.add_patch(c)

def final_node(ax, cx, cy, r=0.15):
    """⊕ Nó final (bullseye)."""
    outer = plt.Circle((cx, cy), r, fc=BLACK, ec=BLACK, lw=2, zorder=3)
    inner = plt.Circle((cx, cy), r*0.55, fc=WHITE, ec=BLACK, lw=1.2, zorder=4)
    dot = plt.Circle((cx, cy), r*0.28, fc=BLACK, ec=BLACK, lw=0, zorder=5)
    ax.add_patch(outer)
    ax.add_patch(inner)
    ax.add_patch(dot)

def fork_bar(ax, cx, cy, width=2.5):
    """Barra de fork/join."""
    ax.plot([cx - width/2, cx + width/2], [cy, cy],
            color=FORK_COLOR, lw=4, solid_capstyle="round", zorder=3)

def arr(ax, x1, y1, x2, y2, color=MED_GRAY, lw=1.2):
    """Seta simples."""
    ax.annotate("", xy=(x2, y2), xytext=(x1, y1),
                arrowprops=dict(arrowstyle="-|>", color=color,
                                lw=lw, mutation_scale=12),
                zorder=2)

def guard(ax, x, y, text, color=GUARD_COLOR, fontsize=7.5):
    """Rótulo de guarda [condição]."""
    ax.text(x, y, text, ha="center", va="center", fontsize=fontsize,
            color=color, family="sans-serif", style="italic", zorder=5)

def note(ax, x, y, text, fontsize=7):
    """Nota explicativa."""
    ax.text(x, y, text, ha="center", va="center", fontsize=fontsize,
            color=MED_GRAY, family="sans-serif", style="italic", zorder=5)


# ══════════════════════════════════════════════════════════════════
#  LAYOUT DO DIAGRAMA
# ══════════════════════════════════════════════════════════════════

fig, ax = plt.subplots(figsize=(10, 20))
fig.patch.set_facecolor(BG)
ax.set_facecolor(BG)
ax.set_xlim(-1.5, 13)
ax.set_ylim(-0.5, 24.5)
ax.set_aspect("equal")
ax.axis("off")

# ── Título ──
ax.text(5, 24.0, "Diagrama de Atividades", ha="center", fontsize=16,
        color=BLACK, fontweight="bold", family="sans-serif")
ax.text(5, 23.5, "Gerador de Código Intermediário (Quádruplas)",
        ha="center", fontsize=11, color=MED_GRAY, family="sans-serif")

# ── Borda do diagrama ──
border = FancyBboxPatch(
    (-0.8, -0.3), 13.2, 24.0,
    boxstyle="round,pad=0.1", facecolor="none", edgecolor=LIGHT_GRAY,
    linewidth=1.5, linestyle="-", zorder=0,
)
ax.add_patch(border)
ax.text(-0.2, 23.3, "  «activity» GerarCódigoIntermediário", ha="left",
        fontsize=8, color=MED_GRAY, family="sans-serif")

CX = 5   # Centro X principal
y = 22.5 # Cursor Y (de cima para baixo)

# ══════════════════════════════════════════════════════════════════
#  FLUXO PRINCIPAL
# ══════════════════════════════════════════════════════════════════

# 1. Nó Inicial
initial_node(ax, CX, y)
y_start = y
y -= 0.6

# 2. Receber AST
action_box(ax, CX, y, 3.5, 0.55, "Receber AST (raiz da árvore)")
arr(ax, CX, y_start - 0.13, CX, y + 0.28)
y_prev = y; y -= 0.75

# 3. Obter primeira declaração
action_box(ax, CX, y, 3.8, 0.55, "Obter primeira declaração\np ← root.child1")
arr(ax, CX, y_prev - 0.28, CX, y + 0.28)
y_prev = y; y -= 0.75

# 4. Decisão: p != NULL?
decision(ax, CX, y, 0.5)
guard(ax, CX, y, "?", fontsize=7)
arr(ax, CX, y_prev - 0.28, CX, y + 0.25)

# ── Ramo [p == NULL] → HALT ──
y_dec1 = y
arr(ax, CX + 0.25, y, 10.5, y)
guard(ax, 8.0, y + 0.22, "[p = NULL]", color=GUARD_NO)
action_box(ax, 10.5, y - 0.7, 2.0, 0.5,
           "Emitir\n(HALT, -, -, -)", is_emit=True, fontsize=8)
arr(ax, 10.5, y, 10.5, y - 0.45)
final_node(ax, 10.5, y - 1.35)
arr(ax, 10.5, y - 0.95, 10.5, y - 1.2)

# ── Ramo [p != NULL] → continua ──
y -= 0.75
guard(ax, CX + 0.6, y_dec1 - 0.05, "[p ≠ NULL]", color=GUARD_COLOR)

# 5. Decisão: tipo do nó
decision(ax, CX, y, 0.5)
arr(ax, CX, y_dec1 - 0.25, CX, y + 0.25)
y_dec2 = y

# ══════════════════════════════════════════════════════════════════
#  RAMO ESQUERDO: DECLARAÇÃO DE VARIÁVEL
# ══════════════════════════════════════════════════════════════════

y_var = y - 0.8
var_x = 2.0

arr(ax, CX - 0.25, y, var_x, y)
ax.plot([var_x, var_x], [y, y_var + 0.28], color=MED_GRAY, lw=1.2, zorder=2)
ax.annotate("", xy=(var_x, y_var + 0.28), xytext=(var_x, y_var + 0.55),
            arrowprops=dict(arrowstyle="-|>", color=MED_GRAY, lw=1.2, mutation_scale=12), zorder=2)
guard(ax, var_x, y + 0.22, "[VAR_DECLARACAO]")

action_box(ax, var_x, y_var, 2.8, 0.5,
           "Emitir\n(ALLOC, nome, escopo, -)", is_emit=True, fontsize=8)

# ══════════════════════════════════════════════════════════════════
#  RAMO DIREITO: DECLARAÇÃO DE FUNÇÃO
# ══════════════════════════════════════════════════════════════════

fun_x = 8.0
arr(ax, CX + 0.25, y, fun_x, y)
guard(ax, fun_x, y + 0.22, "[FUN_DECLARACAO]")

y_fun = y - 0.8
ax.plot([fun_x, fun_x], [y, y_fun + 0.28], color=MED_GRAY, lw=1.2, zorder=2)
ax.annotate("", xy=(fun_x, y_fun + 0.28), xytext=(fun_x, y_fun + 0.55),
            arrowprops=dict(arrowstyle="-|>", color=MED_GRAY, lw=1.2, mutation_scale=12), zorder=2)

action_box(ax, fun_x, y_fun, 2.8, 0.5,
           "Emitir\n(FUN, tipo, nome, -)", is_emit=True, fontsize=8)
y_f = y_fun; y_f -= 0.7

action_box(ax, fun_x, y_f, 3.5, 0.55,
           "Processar parâmetros\nda função")
arr(ax, fun_x, y_fun - 0.25, fun_x, y_f + 0.28)
y_f2 = y_f; y_f -= 0.7

action_box(ax, fun_x, y_f, 3.5, 0.55,
           "Processar corpo\n(gera_comando)")
arr(ax, fun_x, y_f2 - 0.28, fun_x, y_f + 0.28)
y_f3 = y_f; y_f -= 0.7

action_box(ax, fun_x, y_f, 2.8, 0.5,
           "Emitir\n(END, nome, -, -)", is_emit=True, fontsize=8)
arr(ax, fun_x, y_f3 - 0.28, fun_x, y_f + 0.25)

# ══════════════════════════════════════════════════════════════════
#  MERGE → Avançar para próxima declaração
# ══════════════════════════════════════════════════════════════════

y_merge = y_f - 0.65
decision(ax, CX, y_merge, 0.4)  # Merge node

# VAR → merge
ax.plot([var_x, var_x], [y_var - 0.25, y_merge], color=MED_GRAY, lw=1.2, zorder=2)
arr(ax, var_x, y_merge, CX - 0.2, y_merge)

# FUN → merge
ax.plot([fun_x, fun_x], [y_f - 0.25, y_merge], color=MED_GRAY, lw=1.2, zorder=2)
arr(ax, fun_x, y_merge, CX + 0.2, y_merge)

y_m = y_merge - 0.65
action_box(ax, CX, y_m, 3.5, 0.5,
           "Avançar para a próxima\ndeclaração (p ← p.sibling)")
arr(ax, CX, y_merge - 0.2, CX, y_m + 0.25)

# ── Loop de volta à decisão p != NULL ──
y_loop = y_m - 0.25
ax.plot([CX, CX], [y_loop, y_loop - 0.3], color=MED_GRAY, lw=1.2)
ax.plot([CX, -0.2], [y_loop - 0.3, y_loop - 0.3], color=MED_GRAY, lw=1.2)
ax.plot([-0.2, -0.2], [y_loop - 0.3, y_dec1], color=MED_GRAY, lw=1.2)
arr(ax, -0.2, y_dec1, CX - 0.25, y_dec1)

# ══════════════════════════════════════════════════════════════════
#  PARTIÇÃO INFERIOR: DETALHAMENTO — Processar Corpo
# ══════════════════════════════════════════════════════════════════

# Linha pontilhada de separação
ax.plot([-0.5, 12.0], [y_loop - 1.0, y_loop - 1.0],
        color=LIGHT_GRAY, lw=1, linestyle="--", zorder=1)
ax.text(5, y_loop - 1.3,
        "Detalhamento: Processar Corpo (gera_comando + gera_expressao)",
        ha="center", fontsize=9, color=DARK_GRAY, fontweight="bold",
        family="sans-serif")

y_sub = y_loop - 2.0

# Nó inicial do subfluxo
initial_node(ax, CX, y_sub, r=0.1)
y_sub -= 0.55

# Decisão: tipo de comando
decision(ax, CX, y_sub, 0.55)
note(ax, CX, y_sub, "?", fontsize=7)
arr(ax, CX, y_sub + 0.55, CX, y_sub + 0.28)

y_d = y_sub

# ── Coluna 1: IF-ELSE ──
c1 = 1.3
y_c = y_d - 1.2
arr(ax, CX - 0.27, y_d, c1, y_d)
ax.plot([c1, c1], [y_d, y_c + 0.35], color=MED_GRAY, lw=1.2)
ax.annotate("", xy=(c1, y_c + 0.35), xytext=(c1, y_c + 0.55),
            arrowprops=dict(arrowstyle="-|>", color=MED_GRAY, lw=1.2, mutation_scale=12), zorder=2)
guard(ax, c1, y_d + 0.22, "[IF]")

action_box(ax, c1, y_c, 2.3, 0.6,
           "Avaliar condição\nEmitir IFF, LAB,\nJUMP", is_emit=True, fontsize=7)

# ── Coluna 2: WHILE ──
c2 = 3.8
y_c2 = y_d - 1.2
arr(ax, CX - 0.15, y_d - 0.15, c2, y_d - 0.15)
ax.plot([c2, c2], [y_d - 0.15, y_c2 + 0.35], color=MED_GRAY, lw=1.2)
ax.annotate("", xy=(c2, y_c2 + 0.35), xytext=(c2, y_c2 + 0.55),
            arrowprops=dict(arrowstyle="-|>", color=MED_GRAY, lw=1.2, mutation_scale=12), zorder=2)
guard(ax, c2, y_d + 0.07, "[WHILE]")

action_box(ax, c2, y_c2, 2.3, 0.6,
           "Avaliar condição\nEmitir LAB, IFF,\nJUMP", is_emit=True, fontsize=7)

# ── Coluna 3: RETURN ──
c3 = 6.3
y_c3 = y_d - 1.2
arr(ax, CX + 0.15, y_d + 0.15, c3, y_d + 0.15)
ax.plot([c3, c3], [y_d + 0.15, y_c3 + 0.35], color=MED_GRAY, lw=1.2)
ax.annotate("", xy=(c3, y_c3 + 0.35), xytext=(c3, y_c3 + 0.55),
            arrowprops=dict(arrowstyle="-|>", color=MED_GRAY, lw=1.2, mutation_scale=12), zorder=2)
guard(ax, c3, y_d + 0.37, "[RETURN]")

action_box(ax, c3, y_c3, 2.3, 0.6,
           "Avaliar expressão\nEmitir\n(RET, $t, -, -)", is_emit=True, fontsize=7)

# ── Coluna 4: EXPRESSÃO ──
c4 = 8.8
y_c4 = y_d - 1.2
arr(ax, CX + 0.27, y_d, c4, y_d)
ax.plot([c4, c4], [y_d, y_c4 + 0.35], color=MED_GRAY, lw=1.2)
ax.annotate("", xy=(c4, y_c4 + 0.35), xytext=(c4, y_c4 + 0.55),
            arrowprops=dict(arrowstyle="-|>", color=MED_GRAY, lw=1.2, mutation_scale=12), zorder=2)
guard(ax, c4, y_d + 0.22, "[EXPR]")

action_box(ax, c4, y_c4, 2.3, 0.6,
           "Gerar quádruplas\nADD, LOAD, STORE,\nCALL, IN, OUT ...", is_emit=True, fontsize=7)

# ── Merge final + processar sibling ──
y_merge2 = y_c - 0.7
decision(ax, CX, y_merge2, 0.4)

for cx_col in [c1, c2, c3, c4]:
    ax.plot([cx_col, cx_col], [y_c - 0.3, y_merge2], color=MED_GRAY, lw=1.0, zorder=2)

arr(ax, c1, y_merge2, CX - 0.2, y_merge2)
arr(ax, c4, y_merge2, CX + 0.2, y_merge2)

y_sib = y_merge2 - 0.65
action_box(ax, CX, y_sib, 3.5, 0.5,
           "Processar próximo statement\n(node.sibling)")
arr(ax, CX, y_merge2 - 0.2, CX, y_sib + 0.25)

# Nó final do subfluxo
final_node(ax, CX, y_sib - 0.6, r=0.12)
arr(ax, CX, y_sib - 0.25, CX, y_sib - 0.48)

# ══════════════════════════════════════════════════════════════════
#  LEGENDA
# ══════════════════════════════════════════════════════════════════

leg_y = y_sib - 1.5
leg_x = 0.5

ax.text(leg_x, leg_y, "Legenda:", fontsize=8, color=DARK_GRAY,
        fontweight="bold", family="sans-serif")

# Nó inicial
initial_node(ax, leg_x + 0.3, leg_y - 0.4, r=0.08)
ax.text(leg_x + 0.7, leg_y - 0.4, "Nó Inicial", fontsize=7,
        color=MED_GRAY, va="center", family="sans-serif")

# Nó final
final_node(ax, leg_x + 2.5, leg_y - 0.4, r=0.09)
ax.text(leg_x + 2.9, leg_y - 0.4, "Nó Final", fontsize=7,
        color=MED_GRAY, va="center", family="sans-serif")

# Ação
action_box(ax, leg_x + 5.5, leg_y - 0.4, 1.2, 0.3, "Ação", fontsize=6.5)

# Emissão
action_box(ax, leg_x + 7.5, leg_y - 0.4, 1.5, 0.3, "Emitir quad.", 
           is_emit=True, fontsize=6.5)

# Decisão
decision(ax, leg_x + 9.2, leg_y - 0.4, 0.25)
ax.text(leg_x + 9.6, leg_y - 0.4, "Decisão", fontsize=7,
        color=MED_GRAY, va="center", family="sans-serif")


# ══════════════════════════════════════════════════════════════════
#  SALVAR
# ══════════════════════════════════════════════════════════════════

plt.tight_layout()
plt.savefig("diagrama_atividades.png", dpi=180, bbox_inches="tight",
            facecolor=fig.get_facecolor(), edgecolor="none")
plt.close()
print("✅ Diagrama salvo em: diagrama_atividades.png")
