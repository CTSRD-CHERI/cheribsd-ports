PORTNAME=	genie
PORTVERSION=	g2020082801
CATEGORIES=	devel

MAINTAINER=	bofh@FreeBSD.org
COMMENT=	GENie Project generator tool
WWW=		https://github.com/bkaradzic/GENie

USES=		gmake
USE_GITHUB=	yes
GH_ACCOUNT=	bkaradzic
GH_PROJECT=	GENie
GH_TAGNAME=	a503d6e

MAKE_ARGS=	-C build/gmake.freebsd config=release CC="${CC}" CXX="${CXX}"
MAKE_JOBS_UNSAFE=	yes
PLIST_FILES=	bin/${PORTNAME}

LICENSE=	BSD3CLAUSE
LICENSE_FILE=	${WRKSRC}/LICENSE

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/bin/bsd/genie ${STAGEDIR}${PREFIX}/bin

.include <bsd.port.mk>
