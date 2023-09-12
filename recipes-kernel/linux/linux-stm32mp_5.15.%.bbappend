FILESEXTRAPATHS:prepend := "${THISDIR}/files:"
SRC_URI += "file://0001-add-my-print.patch"
SRC_URI += "file://0002-add-ssd1309-device-modify-reset-delay.patch"
SRC_URI += "file://kernelconfig.cfg"


KERNEL_CONFIG_FRAGMENTS += "${WORKDIR}/kernelconfig.cfg"