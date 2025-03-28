PORTNAME=	nginx-cheri
PORTVERSION=	${NGINX_RELEASE}.d${SNAPDATE}
PORTREVISION=	0
CATEGORIES=	www

USE_GITHUB=	yes
GH_ACCOUNT=	CTSRD-CHERI
GH_PROJECT=	nginx
GH_TAGNAME=	${NGINX_COMMIT}

MAINTAINER=	alfredo.mazzinghi@cl.cam.ac.uk
COMMENT=	CHERI port of the nginx WWW server
WWW=		https://cheribsd.org/

FLAVORS=	default subobject
FLAVOR?=${FLAVORS:[1]}
subobject_PKGNAMESUFFIX=	-subobject

CONFIGURE_SCRIPT=	auto/configure
.if ${FLAVOR:U} == subobject
CFLAGS+=	-cheri-bounds=subobject-safe -DWITH_SUBOBJECT_SAFE
.endif

.include "${.CURDIR}/Makefile.snapshot"

NGINXDIR=	${.CURDIR}/../nginx
FILESDIR=	${NGINXDIR}/files
DESCR=      ${NGINXDIR}/pkg-descr
PLIST=      ${NGINXDIR}/pkg-plist
SLAVE_PORT?=	${PORTNAME}

# The HTTPV3 option must be excluded as it is not supported by the
# CHERI patches yet.
OPTIONS_EXCLUDE=	HTTPV3 HTTPV3_BORING HTTPV3_LSSL HTTPV3_QTLS
# Override MODULESDIR to not depend on PORTNAME
DSO_VARS=		MODULESDIR=${PREFIX}/libexec/nginx

# The nginx package expects the configure, LICENSE and html files to be
# in the top-level WRKSRC directory. This is done in nginx release tarballs.
post-extract:
	cp ${WRKSRC}/docs/text/LICENSE ${WRKSRC}/LICENSE
	cp -r ${WRKSRC}/docs/html ${WRKSRC}/html

.include "${NGINXDIR}/Makefile"
