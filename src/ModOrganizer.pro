TEMPLATE = subdirs
CONFIG += ordered


SUBDIRS = bsatk \
					shared \
					uibase \
					organizer \
					hookdll \
					archive \
					helper \
          plugins \
					proxydll

hookdll.depends = shared
organizer.depends = shared, uibase

CONFIG(debug, debug|release) {
    DESTDIR = outputd
} else {
    DESTDIR = output
}