PORTNAME=	hidapi
DISTVERSIONPREFIX=	${PORTNAME}-
DISTVERSION=	0.14.0
CATEGORIES=	comms

MAINTAINER=	sstallion@gmail.com
COMMENT=	Library to access USB HID-class devices
WWW=		https://github.com/libusb/hidapi

LICENSE=	BSD3CLAUSE GPLv3
LICENSE_COMB=	dual

USES=		autoreconf gettext-tools iconv:wchar_t libtool localbase \
		pkgconfig

USE_GITHUB=	yes
GH_ACCOUNT=	libusb
USE_LDCONFIG=	yes

GNU_CONFIGURE=	yes
INSTALL_TARGET=	install-strip

OPTIONS_DEFINE=	DOCS

.include <bsd.port.pre.mk>

.if ${ARCH} == "aarch64c"
GETTEXT_LOCALBASE=	${LOCALBASE64}
.else
GETTEXT_LOCALBASE=	${LOCALBASE}
.endif

pre-configure:
	@${CP} ${GETTEXT_LOCALBASE}/share/gettext/config.rpath ${WRKSRC}

.include <bsd.port.mk>
