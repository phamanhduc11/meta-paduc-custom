SUMMARY = "Example of how to build an external Linux kernel module"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=44ac4678311254db62edf8fd39cb8124"

inherit module

SRC_URI = "file://Makefile \
           file://hello.c  \
           file://COPYING  \
           "

S = "${WORKDIR}"

RPROVIDES_${PN} += "kernel-module-hello"

# Auto load module on boot
KERNEL_MODULE_AUTOLOAD += "kernel-module-hello"