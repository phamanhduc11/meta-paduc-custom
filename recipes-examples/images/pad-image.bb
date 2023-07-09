inherit core-image
IMAGE_INSTALL += "usbutils"

IMAGE_FEATURES = "ssh-server-dropbear debug-tweaks splash"

IMAGE_NAME = "anhduc"

IMAGE_INSTALL:append = " hello-world"
IMAGE_INSTALL:append = " samba"
IMAGE_INSTALL:append = " vim"
IMAGE_INSTALL:append = " dpkg"
#IMAGE_INSTALL:append = " libmystatic-staticdev"
#IMAGE_INSTALL:append = " libmydynamic"

