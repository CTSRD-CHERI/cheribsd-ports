PORTNAME=	pango
PORTVERSION=	1.50.14
PORTREVISION=	1
CATEGORIES=	x11-toolkits
MASTER_SITES=	GNOME
DIST_SUBDIR=	gnome2

MAINTAINER=	desktop@FreeBSD.org
COMMENT=	Open-source framework for the layout and rendering of i18n text
WWW=		https://www.pango.org/

LICENSE=	LGPL20
LICENSE_FILE=	${WRKSRC}/COPYING

LIB_DEPENDS=	libfreetype.so:print/freetype2 \
		libharfbuzz.so:print/harfbuzz \
		libfontconfig.so:x11-fonts/fontconfig \
		libfribidi.so:converters/fribidi
RUN_DEPENDS=	xorg-fonts-truetype>0:x11-fonts/xorg-fonts-truetype \
		${FONTENCOD}:x11-fonts/encodings

PORTSCOUT=	limitw:1,even

USES=		compiler:c11 cpe gettext gnome localbase meson pkgconfig python:env tar:xz
USE_LDCONFIG=	yes
USE_GNOME=	cairo glib20 introspection:build

CPE_VENDOR=	gnome

VERSION=	1.8.0
LIBVERSION=	0.5000.14
PLIST_SUB+=     VERSION=${VERSION} LIBVERSION=${LIBVERSION}

FONTSCALE=	${LOCALBASE}/share/fonts/TTF/luximb.ttf
FONTENCOD=	${LOCALBASE}/share/fonts/encodings/encodings.dir

OPTIONS_SUB=	yes
OPTIONS_DEFINE=	X11 DOCS MANPAGES THAI
OPTIONS_DEFAULT=X11 MANPAGES THAI

DOCS_BUILD_DEPENDS=	gi-docgen:textproc/py-gi-docgen
DOCS_MESON_TRUE=	gtk_doc

MANPAGES_BUILD_DEPENDS=	help2man:misc/help2man

THAI_DESC=		Thai language support via libThai
THAI_LIB_DEPENDS=	libthai.so:devel/libthai
THAI_MESON_ENABLED=	libthai

X11_MESON_ENABLED=	xft
X11_USES=	xorg
X11_USE=	XORG=x11,xft,xrender

.include <bsd.port.options.mk>

.if ${ABI:Mpurecap}
# -Dintrospection should be set to "disabled" when disabling introspection.
introspection_MESON_ARG=	disabled
.endif

pre-configure:
# .if !exists() evaluates too early before cairo has a chance to be installed
	@if ! pkg-config --exists cairo-gobject; then \
		${ECHO_MSG} "${PKGNAME}: Needs cairo with GLIB (GObject) support enabled."; \
		${FALSE}; \
	fi

.include <bsd.port.mk>
