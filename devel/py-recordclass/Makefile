PORTNAME=	recordclass
PORTVERSION=	0.19.2
CATEGORIES=	devel python
MASTER_SITES=	PYPI
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	thierry@FreeBSD.org
COMMENT=	Mutable variants of tuple and collections.namedtuple
WWW=		https://pypi.org/project/recordclass/

LICENSE=	MIT

USES=		python:3.9+
USE_PYTHON=	distutils

.if ! defined(WITH_DEBUG)
LDFLAGS+=	-s
.endif

do-test: install
	(cd ${WRKSRC} && ${PYTHON_CMD} ./test_all.py)

.include <bsd.port.mk>
