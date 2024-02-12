PORTNAME=	libgudev
PORTVERSION=	234
CATEGORIES=	devel
MASTER_SITES=	GNOME

MAINTAINER=	x11@FreeBSD.org
COMMENT=	GObject bindings for libudev
WWW=		https://wiki.gnome.org/Projects/libgudev

LICENSE=	LGPL21
LICENSE_FILE=	${WRKSRC}/COPYING

LIB_DEPENDS=	libudev.so:devel/libudev-devd

USES=		gettext-runtime gmake gnome libtool pathfix pkgconfig tar:xz
USE_GNOME=	glib20 introspection:build
GNU_CONFIGURE=	yes
USE_LDCONFIG=	yes
INSTALL_TARGET=	install-strip
CONFIGURE_ARGS=	--disable-umockdev

.include <bsd.port.options.mk>

.if ${ABI:Mpurecap}
# Purecap libffi does not currently support ffi closures required by
# gobject-introspection.
USE_GNOME:=	${USE_GNOME:Nintrospection\:build}
.endif

.include <bsd.port.mk>
