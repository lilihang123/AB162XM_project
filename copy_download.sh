#!/bin/bash
# 将 download 文件夹复制到 D:\临时文件，存在则替换
# 从工程根目录运行（WSL 或 Docker 容器内均可）

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
SRC="$SCRIPT_DIR/out/ab1623m_evk/keychron_mouse_LM7/download"
DEST="/mnt/d/临时文件/download"

if [ ! -d "$SRC" ]; then
    echo "错误: 源目录不存在: $SRC"
    exit 1
fi

# 如果目标已存在，先删除
if [ -d "$DEST" ]; then
    echo "目标已存在，正在删除: $DEST"
    rm -rf "$DEST"
fi

# 确保目标父目录存在
DEST_PARENT="$(dirname "$DEST")"
if [ ! -d "$DEST_PARENT" ]; then
    echo "错误: 目标父目录不存在: $DEST_PARENT"
    echo "提示: 如果在 Docker 容器内运行，请用 -v 挂载 D 盘"
    exit 1
fi

echo "正在复制: $SRC -> $DEST"
cp -r "$SRC" "$DEST"

if [ $? -eq 0 ]; then
    echo "复制完成!"
else
    echo "复制失败!"
    exit 1
fi
