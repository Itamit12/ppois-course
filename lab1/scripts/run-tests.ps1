<#
.SYNOPSIS
    Builds lab1, runs the tests and prints the coverage table to the console.

.DESCRIPTION
    Sets up the MSVC environment (vcvars64), configures the build with Ninja
    if needed, builds everything and invokes the 'coverage' CMake target.
    OpenCppCoverage runs the test binary, so the tests are executed once and
    their output is followed by the per-file coverage table.

.PARAMETER Config
    Build configuration: Debug (default) or Release.

.PARAMETER NoCoverage
    Run plain ctest without measuring coverage.

.PARAMETER BuildDir
    Build directory, defaults to <repo>/lab1/build.

.EXAMPLE
    .\run-tests.ps1

.EXAMPLE
    .\run-tests.ps1 -Config Release -NoCoverage
#>
[CmdletBinding()]
param(
    [ValidateSet('Debug', 'Release')]
    [string]$Config = 'Debug',

    [switch]$NoCoverage,

    [string]$BuildDir
)

$ErrorActionPreference = 'Stop'

function Import-VisualStudioEnvironment {
    $vswhere = Join-Path ${env:ProgramFiles(x86)} 'Microsoft Visual Studio\Installer\vswhere.exe'
    if (-not (Test-Path $vswhere)) {
        throw "vswhere.exe not found. Install Visual Studio with the C++ toolset."
    }

    $vsPath = & $vswhere -all -products * -property installationPath |
        Where-Object { $_ } | Select-Object -First 1
    if (-not $vsPath) {
        throw "Visual Studio with the C++ toolset not found."
    }

    $vcvars = Join-Path $vsPath 'VC\Auxiliary\Build\vcvars64.bat'
    if (-not (Test-Path $vcvars)) {
        throw "vcvars64.bat not found: $vcvars"
    }

    # Pull the environment prepared by vcvars64.bat into the current session.
    cmd /c "`"$vcvars`" >nul && set" | ForEach-Object {
        if ($_ -match '^([^=]+)=(.*)$') {
            Set-Item -Path "env:$($matches[1])" -Value $matches[2]
        }
    }

    $ninjaDir = Join-Path $vsPath 'Common7\IDE\CommonExtensions\Microsoft\CMake\Ninja'
    if (Test-Path (Join-Path $ninjaDir 'ninja.exe')) {
        $env:PATH = "$ninjaDir;$env:PATH"
    }
}

$sourceDir = (Resolve-Path (Join-Path $PSScriptRoot '..')).Path
if (-not $BuildDir) {
    $BuildDir = Join-Path $sourceDir 'build'
}
$BuildDir = [System.IO.Path]::GetFullPath($BuildDir)

Import-VisualStudioEnvironment

if (-not (Test-Path (Join-Path $BuildDir 'CMakeCache.txt'))) {
    Write-Host "[configure] $BuildDir" -ForegroundColor Cyan
    cmake -S $sourceDir -B $BuildDir -G Ninja -DCMAKE_BUILD_TYPE=$Config
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
}

Write-Host "[build] $Config" -ForegroundColor Cyan
cmake --build $BuildDir --parallel
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

if ($NoCoverage) {
    Write-Host "[test]" -ForegroundColor Cyan
    ctest --test-dir $BuildDir --output-on-failure
} else {
    Write-Host "[test + coverage]" -ForegroundColor Cyan
    cmake --build $BuildDir --target coverage
}

exit $LASTEXITCODE
