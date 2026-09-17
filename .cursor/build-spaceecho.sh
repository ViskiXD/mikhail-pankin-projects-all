#!/usr/bin/env bash
#
# Idempotent Cloud Agent install for this repository.
#
# The repo is a creative audio-visual portfolio (Unity / Max / Ableton).
# The one component that is buildable and runnable in a headless Linux VM is
# the RNBO "Space Echo" C++ export, which is compiled into a Unity native
# audio plugin (.so) and exercised by a standalone DSP smoke test.
#
# This script:
#   1. Ensures a C++ toolchain (cmake + g++) is available.
#   2. Builds the Space Echo Unity native audio plugin via CMake.
#   3. Compiles and runs a standalone DSP verification harness.
#
# It is safe to re-run: build directories are reused and the steps converge.

set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
TINYSOUP="${REPO_ROOT}/TinySoup_MikhailPankin"
EXPORT_DIR="${TINYSOUP}/C++export"
PLUGIN_SRC="${TINYSOUP}/rnbo.unity.audioplugin-main"
BUILD_DIR="${PLUGIN_SRC}/build"

# The default `c++`/`cc` alternatives on this image resolve to clang, which
# targets the gcc-14 toolchain whose libstdc++ dev files are not installed.
# g++-13 links cleanly, so pin the compiler deterministically.
CXX_BIN="g++-13"
CC_BIN="gcc-13"

echo "==> Ensuring C++ toolchain (cmake, ${CXX_BIN})"
need_pkgs=()
command -v cmake  >/dev/null 2>&1 || need_pkgs+=(cmake)
command -v "${CXX_BIN}" >/dev/null 2>&1 || need_pkgs+=(g++-13)
if [ "${#need_pkgs[@]}" -gt 0 ]; then
    echo "    installing: ${need_pkgs[*]}"
    sudo apt-get update -y
    sudo DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends "${need_pkgs[@]}"
fi
cmake --version | head -1
"${CXX_BIN}" --version | head -1

echo "==> Building Space Echo Unity native audio plugin (CMake)"
cmake -S "${PLUGIN_SRC}" -B "${BUILD_DIR}" \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER="${CC_BIN}" \
    -DCMAKE_CXX_COMPILER="${CXX_BIN}" \
    -DRNBO_EXPORT_DIR="${EXPORT_DIR}" \
    -DRNBO_CPP_DIR="${EXPORT_DIR}/rnbo" \
    -DRNBO_CLASS_FILE_NAME="Space Echo.cpp" \
    -DPLUGIN_NAME="Space Echo"
cmake --build "${BUILD_DIR}" -j"$(nproc)"

PLUGIN_SO="${BUILD_DIR}/SpaceEcho/Assets/Plugins/Linux/libSpaceEcho.so"
if [ ! -f "${PLUGIN_SO}" ]; then
    echo "ERROR: expected plugin artifact not found: ${PLUGIN_SO}" >&2
    exit 1
fi
echo "    built: ${PLUGIN_SO}"

echo "==> Building and running Space Echo DSP verification harness"
VERIFY_BIN="${BUILD_DIR}/verify_spaceecho"
"${CXX_BIN}" -std=c++17 -O2 -w \
    -I "${EXPORT_DIR}/rnbo" \
    -I "${EXPORT_DIR}/rnbo/common" \
    -I "${EXPORT_DIR}/rnbo/src" \
    -I "${EXPORT_DIR}/rnbo/src/3rdparty" \
    "${EXPORT_DIR}/verify_spaceecho.cpp" \
    "${EXPORT_DIR}/Space Echo.cpp" \
    "${EXPORT_DIR}/rnbo/RNBO.cpp" \
    -lpthread -o "${VERIFY_BIN}"
"${VERIFY_BIN}"

echo "==> Install complete: Space Echo plugin + DSP verification both succeeded."
