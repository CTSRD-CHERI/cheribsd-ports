PORTNAME=	libqrencode
PORTVERSION=	4.1.1
DISTVERSIONPREFIX=	v
CATEGORIES=	graphics

MAINTAINER=	vanilla@FreeBSD.org
COMMENT=	C library for encoding data in a QR Code symbol
WWW=		https://github.com/fukuchi/libqrencode

LICENSE=	LGPL21
LICENSE_FILE=	${WRKSRC}/COPYING

LIB_DEPENDS=	libpng.so:graphics/png

USES=		cmake iconv pathfix pkgconfig
USE_GITHUB=	yes
GH_ACCOUNT=	fukuchi
USE_LDCONFIG=	yes
GNU_CONFIGURE=	yes

CMAKE_ARGS=	-DBUILD_SHARED_LIBS=ON
PLIST_FILES=	bin/qrencode \
		include/qrencode.h \
		lib/libqrencode.so \
		lib/libqrencode.so.4 \
		lib/libqrencode.so.${PORTVERSION} \
		libdata/pkgconfig/libqrencode.pc


.include <bsd.port.options.mk>

.if !${ABI:Mpurecap}
PLIST_FILES+=	share/man/man1/qrencode.1.gz
.endif

.include <bsd.port.mk>
