#!/bin/bash

# Build script for Heap Scheduler Project

echo "╔════════════════════════════════════════╗"
echo "║  Heap Scheduler - Build Script         ║"
echo "╚════════════════════════════════════════╝"
echo ""

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Check if build directory exists
if [ -d "build" ]; then
    echo -e "${YELLOW}Build directory exists. Cleaning...${NC}"
    rm -rf build
fi

# Create build directory
echo -e "${GREEN}Creating build directory...${NC}"
mkdir build
cd build

# Run CMake
echo -e "${GREEN}Running CMake...${NC}"
if cmake .. ; then
    echo -e "${GREEN}✓ CMake configuration successful${NC}"
else
    echo -e "${RED}✗ CMake configuration failed${NC}"
    exit 1
fi

# Build the project
echo -e "${GREEN}Building project...${NC}"
if cmake --build . ; then
    echo -e "${GREEN}✓ Build successful${NC}"
else
    echo -e "${RED}✗ Build failed${NC}"
    exit 1
fi

echo ""
echo "╔════════════════════════════════════════╗"
echo "║  Build Complete!                       ║"
echo "╚════════════════════════════════════════╝"
echo ""
echo "To run the program:"
echo "  cd build"
echo "  ./heap_scheduler"
echo ""
