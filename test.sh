#!/usr/bin/env bash

_ROOT_DIR_="`cd $(dirname ${BASH_SOURCE[0]}); pwd`"
_TEST_="${_TEST_:-basic}"
_OS_NAME_="`uname -s 2>/dev/null`"
_WIN_ENV_=

case "${_OS_NAME_}" in
  MSYS_NT-*|MINGW??_NT-*) _OS_NAME_="WinNT" ;;
esac

CC="${CC}"
if [ -z "$CC" ]; then
  case `uname -s 2>/dev/null` in
    Darwin)  CC="clang" ;;
    Linux)   CC="gcc"   ;;
    WinNT)   CC="cl"    ;;
  esac
fi

cd "${_ROOT_DIR_}"

# check nore
if [ !- "${_ROOT_DIR_%/}/configure" ]; then
  bash <(curl https://raw.githubusercontent.com/junjiemars/nore/master/bootstrap.sh)
fi

# check cc-env for cl
if [ "WinNT" = "${_OS_NAME_}" -a "cl" = "${CC}" ]; then
  if [ ! -f "${HOME}/.nore/cc-env.sh" ]; then
    echo "!panic: ${HOME}/.nore/cc-env.sh no found"
    exit 1
  fi
  ${HOME}/.nore/cc-env.sh
  if [ ! -f "${HOME}/.nore/cc-env.bat" ]; then
    echo "!panic: ${HOME}/.nore/cc-env.bat no found"
    exit 1
  fi
  _WIN_ENV_="${HOME}/.nore/cc-env.bat"
fi

# basic test
if [ "basic" = "${_TEST_}" ]; then
  ${_ROOT_DIR_%/}/configure --has-hi              \
                 --has-algo                       \
                 --has-ds                         \
                 --has-library                    \
                 --has-lang                       \
                 --has-memory
  make -k -C ${_ROOT_DIR_} clean test
fi

# eof
