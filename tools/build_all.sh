#!/bin/bash

# Exit on error
set -e

BUILD_DIR="build"
BIN_DIR="${BUILD_DIR}/bin"
TEST_DIR="${BUILD_DIR}/test"

# Clean previous builds
echo "Cleaning previous builds..."
make -C core clean
make -C libs/math_lib clean
make -C libs/net_lib clean
make -C apps/calculator clean
make -C apps/file-analyzer clean
make -C apps/contact-book clean
make -C apps/tiny-server clean
make -C tests/core clean
make -C tests/libs clean

# Create build directories
mkdir -p ${BIN_DIR} ${TEST_DIR}

# Build all libraries
echo "Building libraries..."
make -C libs/math_lib
make -C libs/net_lib
make -C core

# Build all applications
echo "Building applications..."
make -C apps/calculator
make -C apps/file-analyzer
make -C apps/contact-book
make -C apps/tiny-server

# Build all tests
echo "Building tests..."
make -C tests/libs
make -C tests/core

# Run tests
echo "Running tests..."
${TEST_DIR}/test_my_lib
${TEST_DIR}/test_core

echo "Build and test complete."