PORTNAME=	yapet
DISTVERSION=	2.3
PORTREVISION=	1
CATEGORIES=	security
MASTER_SITES=	https://yapet.guengel.ch/downloads/

MAINTAINER=	rafi@guengel.ch
COMMENT=	Curses based password manager
WWW=		https://yapet.guengel.ch/

LICENSE=	GPLv3
LICENSE_FILE=	${WRKSRC}/COPYING

LIB_DEPENDS+=	libargon2.so:security/libargon2 \
		libcppunit.so:devel/cppunit

USES=		compiler:c++14-lang gmake ncurses ssl pkgconfig
USES+=		localbase
USE_CXXSTD=	c++14

GNU_CONFIGURE=	yes

OPTIONS_DEFINE=		DOCS NLS
OPTIONS_SUB=		yes

NLS_USES=		gettext-runtime
NLS_CONFIGURE_ENABLE=	nls

TEST_TARGET=	check

.include <bsd.port.mk>
