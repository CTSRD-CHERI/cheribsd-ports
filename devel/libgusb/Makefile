PORTNAME=	libgusb
PORTVERSION=	0.3.10
PORTREVISION=	1
CATEGORIES=	devel

MAINTAINER=	gnome@FreeBSD.org
COMMENT=	GUsb is a GObject wrapper for libusb1
WWW=		https://github.com/hughsie/libgusb

LICENSE=	LGPL21
LICENSE_FILE=	${WRKSRC}/COPYING

BUILD_DEPENDS=	${PY_SETUPTOOLS}

USES=		gnome meson pkgconfig python:build

USE_GITHUB=	yes
GH_ACCOUNT=	hughsie

OPTIONS_DEFINE=		DOCS VAPI
OPTIONS_DEFAULT=	DOCS VAPI
OPTIONS_SUB=		yes

DOCS_BUILD_DEPENDS=	gtk-doc>0:textproc/gtk-doc
DOCS_MESON_TRUE=	docs

VAPI_MESON_TRUE=	vapi
VAPI_USES=		vala:build

.include <bsd.port.options.mk>

.if ${ABI:Mpurecap}
USE_GNOME=	glib20
MESON_ARGS+=	-Dintrospection=false
PLIST_SUB+=	GIR="@comment "
.else
USE_GNOME=	glib20 introspection:build
PLIST_SUB+=	GIR=""
.endif

.include <bsd.port.mk>
