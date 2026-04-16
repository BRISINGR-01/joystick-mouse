scriptDir=$(dirname -- "$(readlink -f -- "$BASH_SOURCE")")
rootDir=$scriptDir/..


cmake -S $rootDir -B $rootDir/build
cmake --build $rootDir/build

ctest --test-dir build