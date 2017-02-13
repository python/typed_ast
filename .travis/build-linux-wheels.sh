#!/bin/bash -eux

# Compile wheels
for PYBIN in /opt/python/*/bin; do
  if [ $(echo "${PYBIN}" | grep -o '[[:digit:]][[:digit:]]' | head -n 1) -ge 33 ]; then
    # typed_ast only builds on Python 3.3 and newer
    "${PYBIN}/pip" wheel /io/ -w wheelhouse/
  fi
done

# Bundle external shared libraries into the wheels
for whl in wheelhouse/*.whl; do
    auditwheel repair "$whl" -w /io/wheelhouse/
done
