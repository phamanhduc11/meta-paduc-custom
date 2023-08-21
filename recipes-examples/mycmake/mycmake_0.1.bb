DESCRIPTION = "Example CMake app"
LICENSE =  "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "git://github.com/phamanhduc11/yocto_learning.git;protocol=https;branch=main \
"
#           file://0001-mypatch.patch"

SRCREV = "${AUTOREV}"

S = "${WORKDIR}/git/cmake_learning"

inherit cmake
# Extra CMAKE
EXTRA_OECMAKE += "-DCMAKE_INSTALL_PREFIX:PATH=/usr" 
#OECMAKE_BUILDPATH += "${WORKDIR}/build"

# Override do_install for not using cmake_do_install
#do_install() {
#    install -d ${D}${bindir}
#    install -m 0755 cameracapture ${D}${bindir}
#}