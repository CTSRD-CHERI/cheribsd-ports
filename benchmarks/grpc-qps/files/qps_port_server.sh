#!/bin/sh

BASEDIR=$(dirname "$0")
cd "${BASEDIR}/../libexec/grpc-qps"
python tools/run_tests/start_port_server.py
