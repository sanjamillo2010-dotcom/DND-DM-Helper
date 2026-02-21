#!/bin/bash
# ─────────────────────────────────────────────────
#  GM_Helper — Dependency installer & first build
#  Run once: bash setup.sh
# ─────────────────────────────────────────────────

set -e

echo "╔══════════════════════════════════════════╗"
echo "║  GM_Helper — Setup Script                ║"
echo "╚══════════════════════════════════════════╝"
echo ""

# 1. Update apt
echo "▶ Updating package list..."
sudo apt update

# 2. Install build tools + yaml-cpp
echo "▶ Installing build tools and yaml-cpp..."
sudo apt install -y \
    build-essential \
    cmake \
    git \
    gdb \
    libyaml-cpp-dev \
    pkg-config

# 3. Try Qt6 first (Ubuntu 22.04+), fall back to Qt5
echo ""
echo "▶ Detecting Qt version..."

if apt-cache show qt6-base-dev &>/dev/null; then
    echo "  → Qt6 found, installing..."
    sudo apt install -y \
        qt6-base-dev \
        libgl-dev
else
    echo "  → Qt6 not available, installing Qt5..."
    sudo apt install -y \
        qtbase5-dev \
        qtbase5-dev-tools \
        libqt5widgets5
fi

echo ""
echo "▶ Creating build directory..."
mkdir -p build

echo ""
echo "▶ Running CMake configure..."
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug

echo ""
echo "▶ Building..."
cmake --build build --parallel

echo ""
echo "╔═══════════════════════════════════════════════╗"
echo "║  Build complete!                              ║"
echo "║  Run:  ./build/GM_Helper                     ║"
echo "╚═══════════════════════════════════════════════╝"
