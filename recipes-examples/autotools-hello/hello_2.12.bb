SUMMARY = "GNU Helloworld"
LICENSE = "GPLv3+"
LIC_FILES_CHKSUM = "file://COPYING;md5=1ebbd3e34237af26da5dc08a4e440464"
# md5sum COPYING file in tarball extracted folder

SRC_URI = "${GNU_MIRROR}/hello/hello-${PV}.tar.gz;name=tarball \
"
SRC_URI[tarball.md5sum] = "048d95d41f9c0bd3424bf0917f53782d"

FILESEXTRAPATHS:prepend := "${THISDIR}/hello-${PV}:"

inherit autotools gettext
# Incase of out of tree build ${B} != ${S}
inherit autotools-brokensep
