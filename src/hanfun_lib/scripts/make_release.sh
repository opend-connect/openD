#!/usr/bin/env bash
# =============================================================================
#
#   @file scripts/make_release.sh
#
#   This helper script is used to create the release tarballs for the HAN-FUN
#   library.
#
#   @version    1.3.0
#
#   @copyright  Copyright (c) 2014  ULE Alliance
#
#   For licensing information, please see the file 'LICENSE' in the root folder.
#
#   Initial development by Bithium S.A. [http://www.bithium.com]
#
# =============================================================================

PATH=$PATH:$(git --exec-path)
source git-sh-setup

require_work_tree

XZ_EXECUTABLE=$(which xz)

# Make sure we have the configuration for the compression used correct.
git config --local --replace-all tar.tar.xz.command "${XZ_EXECUTABLE} -c"

# Get release version string
RELEASE=$(git describe --tags HEAD)
RELEASE=${RELEASE//-/_}
RELEASE=${RELEASE/v/hanfun-}

# Create the release.

PROJECT_DIR="$(git rev-parse --show-toplevel)"

pushd $PROJECT_DIR > release.log

# Create source tarball
echo -n "Creating source tarball (${RELEASE}.tar.xz) ... "
git archive --prefix "${RELEASE}/" --output "${RELEASE}.tar.xz" HEAD
echo "done !"

# Create documentation tarball.
RELEASE=${RELEASE/-/_api-}
echo -n "Creating documentation tarball (${RELEASE}.tar.xz) ... "
pushd doc/ > release.log
cp -R html "${RELEASE}" && tar cf - "${RELEASE}" | xz > "../${RELEASE}.tar.xz" && rm -rf "${RELEASE}"
popd > release.log
echo "done !"

popd > release.log

