PORTNAME=	diffoscope
PORTVERSION=	245
CATEGORIES=	sysutils python
MASTER_SITES=	PYPI
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	ygy@FreeBSD.org
COMMENT=	In-depth comparison of files, archives, and directories
WWW=		https://diffoscope.org/

LICENSE=	GPLv3+
LICENSE_FILE=	${WRKSRC}/COPYING

RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}libarchive-c>=0:archivers/py-libarchive-c@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}python-magic>=0:devel/py-python-magic@${PY_FLAVOR} \
		gdiff:textproc/diffutils
TEST_DEPENDS=	${PYTHON_PKGNAMEPREFIX}pytest>=0:devel/py-pytest@${PY_FLAVOR} \
		zipinfo:archivers/unzip \
		isoinfo:sysutils/cdrkit \
		rpm2cpio:archivers/rpm2cpio

USES=		cpe python
CPE_VENDOR=	reproducible_builds
USE_PYTHON=	autoplist concurrent distutils

NO_ARCH=	yes

do-test:
	@cd ${WRKSRC} && ${PYTHON_CMD} -m pytest -v -rs -o addopts=

.include <bsd.port.mk>
