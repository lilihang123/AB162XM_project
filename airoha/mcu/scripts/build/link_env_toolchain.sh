#!/bin/bash

# Determine the codebase root directory
# Assuming the script is in airoha/mcu/scripts/build
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
CODEBASE_ROOT="$(cd "$SCRIPT_DIR/../../../.." && pwd)"

echo "Using codebase root: $CODEBASE_ROOT"

# Define source and target paths
SRC_ENV="/mtkoss/git/airoha/btd/.environment"
SRC_TOOLCHAIN="/mtkoss/git/airoha/btd/xpack-riscv-none-elf-gcc-13.2.0-2"

TARGET_ENV="modules/lib/matter/.environment"
TARGET_TOOLCHAIN="airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2"

# Function to create symbolic link if target doesn't exist
create_link_if_not_exists() {
    local src="$1"
    local target="$2"
    
    if [ ! -e "$target" ]; then
        echo "Creating symbolic link: $target -> $src"
        # Create parent directory if it doesn't exist
        mkdir -p "$(dirname "$target")"
        ln -s "$src" "$target"
    else
        echo "Target already exists: $target"
    fi
}

# Main execution
echo "Checking and creating symbolic links if needed..."

# Check if modules/lib/matter exists before creating the .environment link
MATTER_DIR="$CODEBASE_ROOT/modules/lib/matter"
if [ -d "$MATTER_DIR" ]; then
    create_link_if_not_exists "$SRC_ENV" "$CODEBASE_ROOT/$TARGET_ENV"
else
    echo "Directory $MATTER_DIR does not exist. Skipping .environment link creation."
fi

# Create toolchain link
mkdir -p airoha/risc-v/tools/toolchain;
create_link_if_not_exists "$SRC_TOOLCHAIN" "$CODEBASE_ROOT/$TARGET_TOOLCHAIN"

echo "Done."
