PORTNAME=	dbus-glib
PORTVERSION=	0.112
CATEGORIES=	devel gnome
MASTER_SITES=	http://dbus.freedesktop.org/releases/dbus-glib/

MAINTAINER=	desktop@FreeBSD.org
COMMENT=	GLib bindings for the D-BUS messaging system
WWW=		https://www.freedesktop.org/wiki/Software/DBusBindings/

LICENSE=	GPLv2+
LICENSE_FILE=	${WRKSRC}/COPYING

LIB_DEPENDS=	libdbus-1.so:devel/dbus \
		libexpat.so:textproc/expat2

USES=		cpe gettext gmake gnome libtool localbase pathfix pkgconfig
USE_GNOME=	glib20
USE_LDCONFIG=	yes

CPE_VENDOR=	freedesktop
GNU_CONFIGURE=	yes
CONFIGURE_ARGS=	--with-test-socket-dir=${WRKDIR} \
		--disable-gtk-doc \
		--with-html-dir=${PREFIX}/share/doc
INSTALL_TARGET=	install-strip

PLIST_SUB=	VERSION="1.0"

DOCSDIR=	${PREFIX}/share/doc/${PORTNAME}${PKGNAMESUFFIX}

OPTIONS_DEFINE=	DOCS

# execve() under the user mode returns an incorrect errno that causes GLib not
# to search PATH for glib-genmarshal. Use an absolute path until we fix the user
# mode.
post-patch:
	${REINPLACE_CMD} -e "s|%%LOCALBASE%%|${LOCALBASE}|g" ${WRKSRC}/dbus/dbus-binding-tool-glib.c

.include <bsd.port.mk>
