DESCRIPTION = "Simple hello world"
LICENSE =  "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://hello.c"

S = "${WORKDIR}"

DEPENDS = "libmystatic"
DEPENDS += "libmydynamic"

do_compile() {
    ${CC} ${LDFLAGS} hello.c -o hello.x -lmystatic -lmydynamic
}

do_install() {
    install -d ${D}${bindir}
    install -m 0755 hello.x ${D}${bindir}
    echo "install -d ${D}${bindir}" > ~/paduc.log
    echo "install -m 0755 hello.x ${D}${bindir}" >> ~/paduc.log
}