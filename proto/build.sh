scriptDir=$(dirname -- "$(readlink -f -- "$BASH_SOURCE")")
mkdir -p $scriptDir/../generated

protoc -I=$scriptDir $scriptDir/packet.proto --cpp_out=$scriptDir/../generated