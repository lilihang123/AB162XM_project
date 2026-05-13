#!/usr/bin/env python3
"""
安全复制项目，避免生成 Zone.Identifier 文件。
用法: python new_project.py <源目录路径> <新目录名>
示例: python new_project.py airoha/mcu/applications/hid_device_ref_design_mouse my_new_mouse
"""

import sys
import os
import shutil
from pathlib import Path

def should_ignore(directory, files):
    """忽略所有以 ':Zone.Identifier' 结尾的文件（不区分大小写）"""
    ignored = []
    for f in files:
        if f.lower().endswith(':zone.identifier'):
            ignored.append(f)
    return ignored

def main():
    if len(sys.argv) != 3:
        print("错误：请提供源目录路径和新目录名两个参数。")
        print(f"用法: {sys.argv[0]} <源目录路径> <新目录名>")
        sys.exit(1)

    # 获取参数
    raw_source = sys.argv[1]
    new_dir_name = sys.argv[2].strip()
    if not new_dir_name:
        print("错误：新目录名不能为空。")
        sys.exit(1)

    # 规范化源路径（支持反斜杠）
    source = Path(raw_source.replace('\\', '/')).resolve()

    if not source.exists():
        print(f"错误：源目录不存在 -> {source}")
        sys.exit(1)

    if not source.is_dir():
        print(f"错误：指定路径不是目录 -> {source}")
        sys.exit(1)

    # 目标路径：源目录的父目录 / 新目录名
    target = source.parent / new_dir_name

    # 检查目标是否已存在
    if target.exists():
        print(f"错误：目标目录已存在 -> {target}")
        print("请删除现有目录或更换一个新的目录名。")
        sys.exit(1)

    print(f"源目录: {source}")
    print(f"目标目录: {target}")

    try:
        # 复制整个目录，忽略 Zone.Identifier 文件
        shutil.copytree(source, target, ignore=should_ignore, symlinks=False)
        print(f"✅ 复制成功！新项目位置: {target}")
    except Exception as e:
        print(f"❌ 复制失败: {e}")
        sys.exit(1)

if __name__ == "__main__":
    main()