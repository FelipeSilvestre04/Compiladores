import os
import shutil
from pathlib import Path

def update_rom():
    repo_root = Path(__file__).resolve().parents[1]
    src = repo_root / "entregavel_final" / "programa.txt"
    dst = repo_root / "src" / "processor" / "cpu" / "programa.txt"

    if not os.path.exists(src):
        print("Error: entregavel_final/programa.txt not found!")
        return

    shutil.copy(src, dst)
    print(f"Successfully copied {src} to {dst}.")

if __name__ == "__main__":
    update_rom()
