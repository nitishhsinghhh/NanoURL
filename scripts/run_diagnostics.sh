#!/bin/bash
#*********************************************************************/
#  Utility Script - NanoURL Build and Diagnostic Runner              */
#                                                                    */
#  Purpose   : Automates CPP compilation and runs native CLI tests.  */
#  Location  : scripts/run_diagnostics.sh                            */
#  Target    : Apple M2 (macOS)                                      */
#                                                                    */
#  Revision History:                                                 */
#  ------------------------------------------------------------------ */
#  Version    Date        Author          Description                */
#  ------------------------------------------------------------------ */
#  1.0        2026-04-26  Nitish Singh    Initial Build and Run Script */
#*********************************************************************/

set -e

# Resolve the absolute path to the project root
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"

cd "$PROJECT_ROOT"

# Safety check for CMakeLists
if [ ! -f "CMakeLists.txt" ]; then
    echo "Error: CMakeLists.txt not found in $PROJECT_ROOT"
    exit 1
fi

BUILD_DIR="$PROJECT_ROOT/build"
BIN_DIR="$BUILD_DIR/bin"

echo "------------------------------------------------"
echo "NanoURL: Initializing Build Sequence"
echo "Project Root: $PROJECT_ROOT"
echo "Version     : 1.0"
echo "------------------------------------------------"

# 1. Prepare Build Environment
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

# 2. Configure and Build
echo "Generating Build Files (M2 Optimized)..."
cmake .. -DCMAKE_BUILD_TYPE=Release > /dev/null

echo "Compiling Native Engine..."
# Optimized for M2 P-Cores leveraging parallel jobs
make -j$(sysctl -n hw.ncpu)

# 3. Execution Phase
echo "Launching Native Diagnostics..."
echo ""

if [ -f "$BIN_DIR/NanoURL_CLI" ]; then
    "$BIN_DIR/NanoURL_CLI"
else
    echo "Error: NanoURL_CLI binary not found in $BIN_DIR"
    exit 1
fi

echo ""
echo "------------------------------------------------"
echo "Diagnostic Run Complete"
echo "------------------------------------------------"