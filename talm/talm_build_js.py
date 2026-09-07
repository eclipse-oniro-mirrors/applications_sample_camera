#!/usr/bin/env python3
"""Build talm JS bundle via ace-loader webpack.

Usage: talm_build_js.py <source_root> <output_dir>
"""
import glob
import os
import shutil
import subprocess
import sys
import tempfile

_NODE = os.path.join(
    os.path.dirname(__file__), os.pardir, os.pardir, os.pardir, os.pardir,
    "prebuilts", "build-tools", "common", "nodejs", "current", "bin", "node")


def find_ace_loader():
    if os.environ.get("OHOS_BUILD_HOME"):
        root = os.environ["OHOS_BUILD_HOME"]
    else:
        cur = os.path.dirname(os.path.abspath(__file__))
        for _ in range(10):
            if os.path.isfile(os.path.join(cur, "build.py")):
                root = cur
                break
            cur = os.path.dirname(cur)
        else:
            raise RuntimeError("could not locate source root (no build.py found upward)")
    return os.path.join(root, "developtools", "ace_js2bundle", "ace-loader")


def _find_prebuilt_lib(source_root):
    """Find any complete ace-loader lib/ directory in the build output."""
    out_dir = os.path.join(source_root, "out")
    if not os.path.isdir(out_dir):
        return None
    for path in glob.glob(os.path.join(
            out_dir, "*", "obj", "developtools", "ace_js2bundle",
            "ace_loader*", "lib", "loader.js")):
        candidate = os.path.dirname(path)
        if os.path.isfile(os.path.join(candidate, "util.js")):
            return candidate
    return None


def _ensure_ace_loader_lib(ace_loader):
    """Ensure ace-loader/lib/ has the files webpack needs.

    The source tree's src/ is incomplete (missing util.js, loader.js, etc.),
    so babel alone cannot produce a working lib/.  If lib/ already looks
    complete we do nothing; otherwise we try to copy a pre-built lib/ from
    a previous build output, falling back to babel for whatever src/ can
    provide.
    """
    lib_loader = os.path.join(ace_loader, "lib", "loader.js")
    if os.path.isfile(lib_loader):
        return

    lib_lite = os.path.join(ace_loader, "lib", "lite")

    source_root = os.path.abspath(os.path.join(ace_loader, os.pardir,
                                                 os.pardir, os.pardir))
    prebuilt = _find_prebuilt_lib(source_root)
    if prebuilt:
        lib_dir = os.path.join(ace_loader, "lib")
        if os.path.isdir(lib_dir):
            shutil.rmtree(lib_dir)
        shutil.copytree(prebuilt, lib_dir)
        return

    if not os.path.isdir(lib_lite):
        src_dir = os.path.join(ace_loader, "src")
        out_dir = os.path.join(ace_loader, "lib")
        node = os.path.abspath(_NODE)
        babel_js = os.path.join(ace_loader, "node_modules", "@babel", "cli",
                                "bin", "babel.js")
        babel_cfg = os.path.join(ace_loader, "babel.config.js")
        module_src = os.path.join(ace_loader, "module-source.js")
        uglify_src = os.path.join(ace_loader, "uglify-source.js")

        for cmd in [
            [node, babel_js, src_dir, "--out-dir", out_dir,
             "--config-file", babel_cfg],
            [node, module_src, out_dir],
            [node, uglify_src, out_dir],
        ]:
            subprocess.run(cmd, check=True, cwd=ace_loader)


def _copy_build_output(tmp_build, out_dir):
    """Copy webpack build output to out_dir, dropping sourcemaps and logs."""
    skip_filenames = {"image_convert_result.txt"}
    for root, _dirs, files in os.walk(tmp_build):
        rel = os.path.relpath(root, tmp_build)
        for name in files:
            if name.endswith(".map") or name in skip_filenames:
                continue
            src = os.path.join(root, name)
            dst_dir = os.path.join(out_dir, rel) if rel != "." else out_dir
            os.makedirs(dst_dir, exist_ok=True)
            shutil.copy2(src, os.path.join(dst_dir, name))


def main():
    if len(sys.argv) != 3:
        print("Usage: talm_build_js.py <source_root> <output_dir>",
              file=sys.stderr)
        return 1

    src_root = sys.argv[1]
    out_dir = sys.argv[2]
    ace_loader = find_ace_loader()

    if not os.path.isdir(src_root):
        print(f"source root not found: {src_root}", file=sys.stderr)
        return 1

    _ensure_ace_loader_lib(ace_loader)

    tmp_build = tempfile.mkdtemp(prefix="talm_webpack_")
    try:
        subprocess.run(
            [
                "./node_modules/.bin/webpack",
                "--config", "./webpack.lite.config.js",
                "--env", f"aceModuleRoot={src_root}",
                "--env", f"aceModuleBuild={tmp_build}",
            ],
            cwd=ace_loader,
            check=True,
            stdout=subprocess.DEVNULL,
            stderr=subprocess.STDOUT,
        )
        os.makedirs(out_dir, exist_ok=True)
        _copy_build_output(tmp_build, out_dir)
    finally:
        shutil.rmtree(tmp_build, ignore_errors=True)

    return 0


if __name__ == "__main__":
    sys.exit(main())
