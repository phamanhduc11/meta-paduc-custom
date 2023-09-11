SUMMARY = "SD1309 module with i2c board info"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=44ac4678311254db62edf8fd39cb8124"

inherit module

SRC_URI = "file://Makefile \
           file://ssd1309.c  \
           file://COPYING  \
           "

S = "${WORKDIR}"

MODULE_NAME = "kernel-module-sd1309"

RPROVIDES_${PN} += "${MODULE_NAME}"

# Auto load module on boot
# KERNEL_MODULE_AUTOLOAD += "${MODULE_NAME}"
