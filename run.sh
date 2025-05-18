#!/bin/bash
set -e

docker build -t buck2:latest .
docker run -it --rm -v ./:/root/workspace buck2:latest
