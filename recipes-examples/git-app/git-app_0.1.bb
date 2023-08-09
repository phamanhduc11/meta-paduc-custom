DESCRIPTION = "Simple app build from git"
LICENSE =  "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

# SRC_URI = "git://github.com/phamanhduc11/yocto_learning.git;protocol=https;branch=main"
SRC_URI = "git://github.com/phamanhduc11/yocto_learning.git;protocol=https;branch=main"

# SRCREV is git revision
# AUTOREV = latest revision
SRCREV = "${AUTOREV}"
# SRCREV  = "81d482b0e9bfcc069ae7affd42e8577aeb5af142"

# Alternative packagename
PROVIDERS += "mygitapp"

S = "${WORKDIR}/git"
