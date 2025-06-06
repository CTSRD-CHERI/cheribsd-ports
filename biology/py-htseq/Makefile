PORTNAME=	HTSeq
DISTVERSION=	2.0.3
CATEGORIES=	biology python
MASTER_SITES=	PYPI
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	jwb@FreeBSD.org
COMMENT=	Python library to facilitate programmatic analysis of sequence data
WWW=		https://pypi.python.org/project/htseq/

LICENSE=	GPLv3
LICENSE_FILE=	${WRKSRC}/LICENSE

BUILD_DEPENDS=	${PYNUMPY} \
		${PYTHON_PKGNAMEPREFIX}pysam>0:biology/py-pysam@${PY_FLAVOR}
RUN_DEPENDS=	${PYNUMPY} \
		${PYTHON_PKGNAMEPREFIX}pysam>0:biology/py-pysam@${PY_FLAVOR} \
		${PKGNAMEPREFIX}matplotlib>=1.4.3:math/py-matplotlib@${PY_FLAVOR}
TEST_DEPENDS=	${PYTHON_PKGNAMEPREFIX}scipy>1.5.0:science/py-scipy@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}pandas>=1.1.0:math/py-pandas@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}matplotlib>=1.4:math/py-matplotlib@${PY_FLAVOR}

USES=		python
USE_PYTHON=	autoplist cython distutils pytest

post-stage:
	${STRIP_CMD} ${STAGEDIR}${PYTHON_SITELIBDIR}/HTSeq/_StepVector.cpython-39.so
	${STRIP_CMD} ${STAGEDIR}${PYTHON_SITELIBDIR}/HTSeq/_HTSeq.cpython-39.so

.include <bsd.port.mk>
