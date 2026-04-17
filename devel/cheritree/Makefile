PORTNAME=	cheritree
PORTREVISION=	1
PORTVERSION=	0.0.d${SNAPDATE}
CATEGORIES=	devel

MAINTAINER=	dapeng.gao@cl.cam.ac.uk
COMMENT=	CHERI Capability Derivation Tree
WWW=		https://github.com/rtegrity/cheritree

LICENSE=	BSD3CLAUSE
LICENSE_FILE_BSD2CLAUSE=	${WRKSRC}/LICENSE

USE_GITHUB=	yes
GH_PROJECT=	cheritree
GH_ACCOUNT=	dpgao
GH_TAGNAME=	${CHERITREE_COMMIT}

PLIST=
PLIST_FILES=	include/cheritree.h \
		lib/libcheritree.so \
		lib/libcheritreestub.a \
		share/examples/${PORTNAME}/visualize.py

.include "Makefile.snapshot"

.include <bsd.port.pre.mk>

.if !${ABI:Mpurecap}
IGNORE=		pure capability program
.endif

do-install:
	${INSTALL_DATA} ${WRKSRC}/src/cheritree.h ${STAGEDIR}${PREFIX}/include
	${INSTALL_PROGRAM} ${WRKSRC}/libcheritree.so ${WRKSRC}/libcheritreestub.a \
	    ${STAGEDIR}${PREFIX}/lib/
	${MKDIR} ${STAGEDIR}${EXAMPLESDIR}
	${INSTALL_SCRIPT} ${WRKSRC}/visualizer/visualize.py \
	    ${STAGEDIR}${EXAMPLESDIR}/

.include <bsd.port.post.mk>
