#!/bin/bash

if [ -z "$CC" ]; then
  if [ -z "$TRAVIS_OS_NAME" ]; then
  	TRAVIS_OS_NAME="`uname -s`"
  fi
  
  case "$TRAVIS_OS_NAME" in
    osx|Darwin) CC=clang ;;
    linux|Linux) CC=gcc ;;
  	MSYS_NT-*|MINGW??_NT-*) CC=cl ;;
  	*) CC=cc ;;
  esac
fi

ROOT="`cd $(dirname ${BASH_SOURCE}) && pwd -P`"
pushd $ROOT

CC=$CC ./configure                              \
  --has-algo                                    \
	--has-ds                                      \
	--has-hi                                      \
	--has-io                                      \
	--has-lang                                    \
	--has-memory                                  \
	--has-unicode                                 \
	--has-x86
make clean test

popd
