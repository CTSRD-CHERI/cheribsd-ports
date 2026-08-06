PORTNAME=	cheri-demos
PORTVERSION=	0.1
CATEGORIES=	cheri-demos
MASTER_SITES=	# none

MAINTAINER=	brooks@FreeBSD.org
COMMENT=	Meta-port for CHERI demos
WWW=		https://cheribsd.org/

LICENSE=	NONE

USES=		metaport

# XXX: we probably want hybrid and purecap versions of default
FLAVORS=	default vulnerable
FLAVOR?=	${FLAVORS:[1]}
default_RUN_DEPENDS=	git:devel/git
vulnerable_RUN_DEPENDS=

.if ${FLAVOR} == "vulnerable"
USES+=	vulnerable
.endif

.include <bsd.port.mk>
