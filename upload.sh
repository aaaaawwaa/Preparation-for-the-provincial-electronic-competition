#!/bin/bash
# ========================================
#  电赛备赛 - 工程自动上传脚本
#  修改下面四行，保存后在终端运行：bash upload.sh
# ========================================

# ---------- 手动替换区域 ----------
TEAM="张锐涛组"                              # 你的组别文件夹名
PROJECT_PATH="C:/Users/张书清/Desktop/电赛资料/省赛/2021年省赛练习/STM32控制方案/STM32_plan"  # 要上传的工程路径
COMMIT_MSG="上传STM32_plan工程"               # 提交说明
REPO_DIR="C:/Users/张书清/Desktop/电赛资料/省赛/Preparation-for-the-provincial-electronic-competition"  # 仓库本地路径
# ----------------------------------

cd "$REPO_DIR" || { echo "错误：仓库路径不存在 - $REPO_DIR"; exit 1; }

PROJECT_NAME=$(basename "$PROJECT_PATH")

echo "=========================================="
echo "  电赛备赛 - 工程自动上传"
echo "=========================================="
echo "  组别: $TEAM"
echo "  工程: $PROJECT_NAME"
echo "=========================================="

# 第1步：同步远程仓库
echo "[1/3] 同步远程仓库..."
if git pull origin main 2>/dev/null; then
    echo "  >> 同步成功"
else
    echo "  >> 代理问题，切换直连..."
    git -c http.proxy= -c https.proxy= pull origin main || { echo "  >> 同步失败，请检查网络"; exit 1; }
fi

# 第2步：复制工程文件
echo "[2/3] 复制工程文件到 $TEAM/ ..."
if [ ! -d "$PROJECT_PATH" ]; then
    echo "  >> 错误：工程路径不存在 - $PROJECT_PATH"
    exit 1
fi

mkdir -p "$TEAM"
DEST="$TEAM/$PROJECT_NAME"

# 先删除旧目录再复制，避免权限问题
if [ -d "$DEST" ]; then
    echo "  >> 检测到已有旧版本，正在覆盖..."
    rm -rf "$DEST"
fi

cp -r "$PROJECT_PATH" "$DEST" || { echo "  >> 复制失败"; exit 1; }
echo "  >> 复制完成"

# 第3步：提交并推送
echo "[3/3] 提交并推送..."
git add "$TEAM/"
git commit -m "$TEAM - $COMMIT_MSG" || echo "  >> (无新改动，跳过提交)"

if git push origin main 2>/dev/null; then
    echo "  >> 推送成功"
else
    echo "  >> 代理问题，切换直连..."
    git -c http.proxy= -c https.proxy= push origin main || { echo "  >> 推送失败，请检查网络"; exit 1; }
fi

echo "=========================================="
echo "  上传完成！"
echo "=========================================="
