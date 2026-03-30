scriptDir=$(dirname -- "$(readlink -f -- "$BASH_SOURCE")")

rm -rf $scriptDir/../build