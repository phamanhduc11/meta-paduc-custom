FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI += " \
    file://smb.conf \
"

FILES:${PN} += " \
    ${sysconfdir}/samba/smb.conf \
"

do_install:append() {
    install -d ${D}${sysconfdir}/samba
    mv ${D}${sysconfdir}/samba/smb.conf ${D}${sysconfdir}/samba/smb.conf.bk
    install -m 0644 ${WORKDIR}/smb.conf ${D}${sysconfdir}/samba
}
