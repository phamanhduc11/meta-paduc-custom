DESCRIPTION = "Simple static library"
LICENSE =  "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://print.c \
           file://add.c \
           file://mydynamic.h \
"

S = "${WORKDIR}"

do_compile() {
    ${CC} -c  -fPIC print.c add.c
    ${CC} ${LDFLAGS} -shared -Wl,-soname,libmydynamic.so.1 -o libmydynamic.so.1.0 *.o
}

do_install() {
    install -d ${D}${libdir}
    install -m 0755 libmydynamic.so.1.0 ${D}${libdir}
    ln -s libmydynamic.so.1.0 ${D}${libdir}/libmydynamic.so.1 
    ln -s libmydynamic.so.1 ${D}${libdir}/libmydynamic.so
    install -d ${D}${includedir}
    install -m 0644 mydynamic.h ${D}${includedir}
}

# Unversion will not be included in main package by default
# SOLIBS and SOLIBSDV are defined in bitbake.conf
#SOLIBS = ".so"
#FILES_SOLIBSDEV = ""