#!/bin/bash

# Exit on any error
set -e

# Change to the project root directory
cd "$(dirname "$0")"/..

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

# Build libraries
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
./build/test/test_my_lib
./build/test/test_net_lib
./build/test/test_core

echo "
Build and test complete."
