PORTNAME=	chrome-deps
PORTVERSION=	20251007
PORTREVISION=	0
CATEGORIES=	www

MAINTAINER=	konrad.witaszczyk@cl.cam.ac.uk
COMMENT=	Meta-port with dependencies of the pure-capability Chromium.

ONLY_FOR_ARCHS=	aarch64c

LIB_DEPENDS=	libatk-bridge-2.0.so:accessibility/at-spi2-core \
		libatspi.so:accessibility/at-spi2-core \
		libFLAC.so:audio/flac \
		libopus.so:audio/opus \
		libdbus-1.so:devel/dbus \
		libepoll-shim.so:devel/libepoll-shim \
		libevent.so:devel/libevent \
		libffi.so:devel/libffi \
		libicuuc.so:devel/icu \
		libjsoncpp.so:devel/jsoncpp \
		libpci.so:devel/libpci \
		libnspr4.so:devel/nspr \
		libcairo.so:graphics/cairo \
		libdrm.so:graphics/libdrm \
		libpng.so:graphics/png \
		libwebp.so:graphics/webp \
		libdav1d.so:multimedia/dav1d \
		libopenh264.so:multimedia/openh264 \
		libfreetype.so:print/freetype2 \
		libharfbuzz.so:print/harfbuzz \
		libnss3.so:security/nss \
		libexpat.so:textproc/expat2 \
		libfontconfig.so:x11-fonts/fontconfig \
		libwayland-client.so:graphics/wayland \
		libxkbcommon.so:x11/libxkbcommon \
		libxshmfence.so:x11/libxshmfence \
		libpango-1.0.so:x11-toolkits/pango \
		libcups.so:print/cups \
		libxslt.so:textproc/libxslt

RUN_DEPENDS=	noto-basic>0:x11-fonts/noto-basic \
		${LOCALBASE}/bin/bssl:security/boringssl

USE_GNOME=	atkmm gtk30

USES=		metaport

.include <bsd.port.mk>
