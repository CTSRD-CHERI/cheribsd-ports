PORTNAME=	giflib
PORTVERSION=	5.2.1
PORTREVISION=	0
CATEGORIES=	graphics
MASTER_SITES=	SF/${PORTNAME}

MAINTAINER=	desktop@FreeBSD.org
COMMENT=	Tools and library routines for working with GIF images
WWW=		https://sourceforge.net/projects/giflib/

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/COPYING

TEST_DEPENDS=	ghead:sysutils/coreutils

USES=		cpe gmake
USE_LDCONFIG=	yes
CFLAGS+=	-DHAVE_REALLOCARRAY
MAKE_ARGS=	CC="${CC}" LDFLAGS="${LDFLAGS}" MANDIR="${MANPREFIX}/man" OFLAGS="${CFLAGS}" PREFIX="${PREFIX}"
CPE_VENDOR=	giflib_project

CONFLICTS_INSTALL=	giftool

OPTIONS_DEFINE=	DOCS
TEST_TARGET=	check

do-install-DOCS-on:
	${MKDIR} ${STAGEDIR}${DOCSDIR}
	cd ${WRKSRC}/doc && ${COPYTREE_SHARE} . ${STAGEDIR}${DOCSDIR} "! ( -name Makefile -o -name *\.1 -o -name *\.in -o -name *\.xml )"

post-install:
	${STRIP_CMD} ${STAGEDIR}${PREFIX}/bin/*
	${STRIP_CMD} --strip-unneeded ${STAGEDIR}${PREFIX}/lib/libgif.so.7.2.0

.include <bsd.port.mk>
