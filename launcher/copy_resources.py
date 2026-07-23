#!/usr/bin/env python3
# Copyright (c) 2020 Huawei Device Co., Ltd.
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

"""把 resources 目录复制到构建目录,可选排除指定相对路径的文件。

用法:
    copy_resources.py --src <src_dir> --dst <dst_dir> \
        [--exclude <posix_rel_path>] ...

排除路径是相对 --src 的 posix 风格路径,例如:
    base/media/background_1920x1080.png
"""

import argparse
import os
import shutil


def _norm_posix(path):
    """归一化为相对 src 的 posix 路径,用于和 --exclude 比对。"""
    return path.replace("\\", "/").lstrip("./")


def copy_tree(src, dst, excludes):
    """递归复制 src 到 dst,跳过 excludes 中的相对路径文件。"""
    excl_set = {_norm_posix(p) for p in excludes}
    for root, _dirs, files in os.walk(src):
        rel_root = os.path.relpath(root, src).replace("\\", "/")
        if rel_root == ".":
            rel_root = ""
        for name in files:
            rel = name if not rel_root else f"{rel_root}/{name}"
            rel_norm = _norm_posix(rel)
            if rel_norm in excl_set:
                continue
            src_file = os.path.join(root, name)
            dst_file = os.path.join(dst, rel_norm)
            os.makedirs(os.path.dirname(dst_file), exist_ok=True)
            shutil.copy2(src_file, dst_file)


def main():
    ap = argparse.ArgumentParser(description="Copy resources tree.")
    ap.add_argument("--src", required=True, help="source resources dir")
    ap.add_argument("--dst", required=True, help="destination dir")
    ap.add_argument(
        "--exclude",
        action="append",
        default=[],
        help="posix rel path to exclude (repeatable)",
    )
    args = ap.parse_args()

    if not os.path.isdir(args.src):
        raise FileNotFoundError(f"source dir not found: {args.src}")

    # 每次构建重新生成副本,保证排除策略生效。
    if os.path.exists(args.dst):
        shutil.rmtree(args.dst)
    os.makedirs(args.dst, exist_ok=True)

    copy_tree(args.src, args.dst, args.exclude)

    # 写一个 stamp 文件作为 GN action 的 outputs 占位。
    with open(os.path.join(args.dst, ".stamp"), "w", encoding="utf-8") as f:
        f.write("done\n")


if __name__ == "__main__":
    main()
