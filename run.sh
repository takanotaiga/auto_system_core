#!/bin/bash
set -e
docker pull ghcr.io/takanotaiga/buck2_docker:latest
docker run -it --rm \
    -v ./:/root/workspace \
    -w /root/workspace \
    ghcr.io/takanotaiga/buck2_docker:latest
