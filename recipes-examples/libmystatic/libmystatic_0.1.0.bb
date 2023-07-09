DESCRIPTION = "Simple static library"
LICENSE =  "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://print.c \
           file://add.c \
           file://mystatic.h \
"

S = "${WORKDIR}"

do_compile() {
    ${CC} -c print.c add.c
    ${AR} rcs libmystatic.a print.o add.o
}

do_install() {
    install -d ${D}${libdir}
    install -m 0755 libmystatic.a ${D}${libdir}
    install -d ${D}${includedir}
    install -m 0644 mystatic.h ${D}${includedir}
}

# ALLOW_EMPTY_${PN} not work
ALLOW_EMPTY:${PN} = "1"