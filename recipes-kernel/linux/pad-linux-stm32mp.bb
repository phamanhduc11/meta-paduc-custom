DESCRIPTION = "PAD linux kernel recipe"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

inherit kernel

### Below just for testing kernel recipe, build error
### Please refer to official recipe linux-stm32mp_%.bb

LINUX_VERSION = "6.4"
LINUX_SUBVERSION = "10"
LINUX_TARNAME = "linux-${LINUX_VERSION}.${LINUX_SUBVERSION}"

SRC_URI = "https://cdn.kernel.org/pub/linux/kernel/v6.x/${LINUX_TARNAME}.tar.xz;name=kernel \
           file://defconfig"

#SRC_URI = "https://cdn.kernel.org/pub/linux/kernel/v6.x/linux-6.4.10.tar.xz;name=kernel \
#            file://defconfig"

S = "${WORKDIR}/linux-${LINUX_VERSION}.${LINUX_SUBVERSION}"

SRC_URI[kernel.sha256sum] = "980b3fb2a97788fd885cbd85ba4520980f76c7ae1d62bfc2e7477ee04df5f239"

#wrong place, this should be placed in conf/machine.conf
#PREFERRED_PROVIDER_virtual/kernel = "pad-linux-stm32mp157" 

