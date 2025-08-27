PORTNAME=	depot_tools
DISTVERSION=	g20250826
CATEGORIES=	devel	

MAINTAINER=	graeme@capabilitieslimited.co.uk
COMMENT=	Tools for working with Chromium development
WWW=		https://chromium.googlesource.com/chromium/tools/depot_tools.git

LICENSE=	BSD3CLAUSE	
LICENSE_FILE=	${WRKSRC}/LICENSE	

USE_GO=		pkg64
USES=		go:run ninja:run python:run
RUN_DEPENDS=	${PYTHON_SITELIBDIR}/httplib2/__init__.py:www/py-httplib2@${PY_FLAVOR} \
		${PYTHON_SITELIBDIR}/six.py:devel/py-six@${PY_FLAVOR}

NO_ARCH=	yes
NO_BUILD=	yes
NO_TEST=	yes

USE_GITHUB=	yes
GH_ACCOUNT=	CTSRD-CHERI
GH_TAGNAME=	fe59a9c

INSTALLDIR=	${STAGEDIR}${DATADIR}

do-install:
	@(cd ${WRKSRC} && \
		${COPYTREE_BIN} . ${INSTALLDIR} "! -name *\.bat ! -name .gitignore ! -name .gitattributes")
	@${MKDIR} -p ${INSTALLDIR}/.cipd_bin
	# Prevent depot_tools from automatically updating.
	@${PYTHON_CMD} ${INSTALLDIR}/update_depot_tools_toggle.py --disable

.include <bsd.port.mk>
