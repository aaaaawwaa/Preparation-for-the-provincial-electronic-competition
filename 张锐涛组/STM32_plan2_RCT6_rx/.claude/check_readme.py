"""检查代码改动后README是否需要更新"""
import os, sys

PROJECT_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
README = os.path.join(PROJECT_DIR, "readme.txt")
MARKER = os.path.join(PROJECT_DIR, ".claude", ".code_changed_marker")

def on_edit_write():
    """Edit/Write工具触发时，写入标记文件"""
    with open(MARKER, "w") as f:
        f.write(str(os.path.getmtime(README) if os.path.exists(README) else 0))

def on_stop():
    """对话结束时，检查是否需要在README中记录"""
    if not os.path.exists(MARKER):
        return
    try:
        with open(MARKER) as f:
            old_readme_mtime = float(f.read().strip())
    except:
        os.remove(MARKER)
        return
    os.remove(MARKER)
    if not os.path.exists(README):
        return
    if os.path.getmtime(README) == old_readme_mtime:
        print("[HOOK提醒] 本轮有代码改动但readme.txt未更新，请确认关键变更已记录到README", file=sys.stderr)

if __name__ == "__main__":
    cmd = sys.argv[1] if len(sys.argv) > 1 else ""
    if cmd == "mark":
        on_edit_write()
    elif cmd == "check":
        on_stop()
