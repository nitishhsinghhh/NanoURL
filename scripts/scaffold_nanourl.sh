#!/bin/bash
#*********************************************************************/
#  Utility Script - Project Scaffolding (In-Place Edition)           */
#                                                                    */
# Purpose   : Generates the hierarchy within the current NanoURL dir.*/
# Location  : ./scripts/scaffold_here.sh                             */
#                                                                    */
# Revision History:                                                  */
# ------------------------------------------------------------------ */
# Version    Date        Author          Description                 */
# ------------------------------------------------------------------ */
# 1.0        2026-04-25  Nitish Singh    Initial Scaffolding         */
# 1.1        2026-04-25  Nitish Singh    Removed root folder prefix  */
#*********************************************************************/

set -e

echo "===== Building Project Structure in Current Directory ====="

# -----------------------------
# 1. Native Core (C++17)
# -----------------------------
echo "Setting up Native Engine (M2-Optimized)..."
mkdir -p src/NativeEngine/include
mkdir -p src/NativeEngine/src
mkdir -p src/NativeEngine/tests

# -----------------------------
# 2. API Layer (.NET 8)
# -----------------------------
echo "Setting up .NET API Gateway..."
mkdir -p src/NanoURL.API/Controllers
mkdir -p src/NanoURL.API/Services
mkdir -p src/NanoURL.API/Interop

# Files for .NET
touch src/NanoURL.API/Program.cs
touch src/NanoURL.API/NanoURL.API.csproj
touch src/NanoURL.API/Controllers/ShortenController.cs
touch src/NanoURL.API/Interop/NativeMethods.cs

# -----------------------------
# 3. Web Frontend
# -----------------------------
echo "Setting up Frontend UI..."
mkdir -p src/NanoURL.UI/wwwroot
touch src/NanoURL.UI/wwwroot/index.html
touch src/NanoURL.UI/wwwroot/app.js
touch src/NanoURL.UI/wwwroot/style.css

# -----------------------------
# 4. DevOps & Tooling
# -----------------------------
echo "Setting up DevOps and Build Config..."
mkdir -p scripts
mkdir -p .github/workflows
mkdir -p docker
mkdir -p lib # Binary output folder for .dylib/.so

# Core Config Files
touch README.md
touch CMakeLists.txt
touch .gitignore
touch docker/Dockerfile
touch NanoURL.sln

echo "Scaffolding Complete in $(pwd)"