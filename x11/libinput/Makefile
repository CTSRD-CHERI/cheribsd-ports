PORTNAME=	libinput
DISTVERSION=	1.23.0
CATEGORIES=	x11

MAINTAINER=	x11@FreeBSD.org
COMMENT=	Generic input library
WWW=		https://www.freedesktop.org/wiki/Software/libinput/

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/COPYING

LIB_DEPENDS=	libevdev.so:devel/libevdev \
		libepoll-shim.so:devel/libepoll-shim \
		libudev.so:devel/libudev-devd \
		libmtdev.so:devel/libmtdev

USES=		cpe localbase meson pkgconfig shebangfix tar:bz2
USE_LDCONFIG=	yes

USE_GITLAB=	yes
GL_SITE=	https://gitlab.freedesktop.org
GL_TAGNAME=	0b005eb64b12603e65a620a77c67ec62fd03f413

CPE_VENDOR=	freedesktop

MESON_ARGS=	-Ddocumentation=false -Dtests=false

SHEBANG_FILES=	tools/libinput-analyze-per-slot-delta.py \
		tools/libinput-analyze-recording.py \
		tools/libinput-analyze-touch-down-state.py \
		tools/libinput-measure-fuzz.py \
		tools/libinput-measure-touch-size.py \
		tools/libinput-measure-touchpad-pressure.py \
		tools/libinput-measure-touchpad-size.py \
		tools/libinput-measure-touchpad-tap.py \
		tools/libinput-list-kernel-devices.py \
		tools/libinput-replay.py
# The following files are not installed, but might be
# run as part of the test suite.
SHEBANG_FILES+=	tools/test_tool_option_parsing.py \
		tools/libinput-record-verify-yaml.py

OPTIONS_DEFINE=	DEBUG_GUI LIBWACOM
OPTIONS_DEFAULT=LIBWACOM
OPTIONS_SUB=	yes
OPTIONS_EXCLUDE_purecap=	LIBWACOM

DEBUG_GUI_DESC=	Build the GUI event viewer
LIBWACOM_DESC=	Libwacom support

DEBUG_GUI_USES=		gnome xorg
DEBUG_GUI_USE=		GNOME=gtk30,glib20,cairo xorg=x11
DEBUG_GUI_LIB_DEPENDS=	libwayland-client.so:graphics/wayland
DEBUG_GUI_MESON_TRUE=	debug-gui
LIBWACOM_LIB_DEPENDS=	libwacom.so:x11/libwacom
LIBWACOM_MESON_TRUE=	libwacom

.include <bsd.port.options.mk>

.if !${ABI:Mpurecap}
RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}evdev>0:devel/py-evdev@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}pyudev>0:devel/py-pyudev@${PY_FLAVOR}
USES+=	python:run
.endif

.include <bsd.port.mk>
