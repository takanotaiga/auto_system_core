#!/bin/bash
set -e
docker run -it --rm \
    -v ./:/root/workspace \
    -w /root/workspace \
    ghcr.io/takanotaiga/buck2_docker:latest
