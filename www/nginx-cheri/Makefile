PORTNAME=	nginx
PORTREVISION=	3

FLAVORS=	default subobject
FLAVOR?=${FLAVORS:[1]}
subobject_PKGNAMESUFFIX=	-cheri-subobject
default_PKGNAMESUFFIX=		-cheri

MAINTAINER=	alfredo.mazzinghi@cl.cam.ac.uk
COMMENT=	CHERI port of the nginx WWW server

MASTERDIR=	${.CURDIR}/../nginx

CONFLICTS=	nginx-1.* \
		nginx-devel-1.* \
		nginx-lite-1.* \
		nginx-naxsi-1.*

EXTRA_PATCHES+=	${.CURDIR}/files/cheribsd.patch
.if ${FLAVOR:U} == subobject
CFLAGS+=	-cheri-bounds=subobject-safe -DWITH_SUBOBJECT_SAFE
.endif

.include "${MASTERDIR}/Makefile"
