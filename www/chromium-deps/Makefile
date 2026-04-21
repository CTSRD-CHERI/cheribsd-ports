PORTNAME=	chromium-deps
PORTVERSION=	20260421
PORTREVISION=	0
CATEGORIES=	www

MAINTAINER=	konrad.witaszczyk@cl.cam.ac.uk
COMMENT=	Meta-port with run-time and build-time dependencies of the pure-capability Chromium.

ONLY_FOR_ARCHS=	aarch64c

USES=		metaport

#
# {LIB,RUN}_DEPENDS, USES and USE_* lists include dependencies as listed in
# www/chromium except for dependencies of features currently not supported in
# the pure-capability Chromium.
#
# Build-time dependencies of www/chromium are run-time dependencies of this
# meta-port because chromium-deps provides both run-time and build-time
# dependencies for the pure-capability Chromium.
#

LIB_DEPENDS=	libatk-bridge-2.0.so:accessibility/at-spi2-core \
		libatspi.so:accessibility/at-spi2-core \
		libFLAC.so:audio/flac \
		libopus.so:audio/opus \
		libdbus-1.so:devel/dbus \
		libdbus-glib-1.so:devel/dbus-glib \
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
		libgcrypt.so:security/libgcrypt \
		libnss3.so:security/nss \
		libexpat.so:textproc/expat2 \
		libfontconfig.so:x11-fonts/fontconfig \
		libwayland-client.so:graphics/wayland \
		libxkbcommon.so:x11/libxkbcommon \
		libxshmfence.so:x11/libxshmfence
# Listed under CUPS in www/chromium:
LIB_DEPENDS+=	libcups.so:print/cups

RUN_DEPENDS=	xdg-open:devel/xdg-utils \
		noto-basic>0:x11-fonts/noto-basic
# Build-time dependencies:
RUN_DEPENDS+=	bash:shells/bash

USES+=		iconv:wchar_t gl gnome jpeg xorg

USE_GL=		gl
USE_GNOME=	atk gdkpixbuf2 glib20 gtk30 libxml2 libxslt
USE_XORG=	x11 xcb xcomposite xcursor xext xdamage xfixes xi \
		xrandr xrender xscrnsaver xtst

.include <bsd.port.mk>
