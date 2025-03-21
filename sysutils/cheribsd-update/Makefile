PORTNAME=	cheribsd-update
PORTVERSION=	0.0.d${SNAPDATE}
CATEGORIES=	sysutils

MAINTAINER=	jrtc27@FreeBSD.org
COMMENT=	CheriBSD binary update tool
WWW=		https://github.com/CTSRD-CHERI/cheribsd-update

LICENSE=	BSD2CLAUSE
LICENSE_FILE_BSD2CLAUSE=	${WRKSRC}/LICENSE

USES=		uidfix

USE_GITHUB=	yes
GH_PROJECT=	cheribsd-update
GH_ACCOUNT=	CTSRD-CHERI
GH_TAGNAME=	${SNAPCOMMIT}

.include "Makefile.snapshot"

.include <bsd.port.mk>
