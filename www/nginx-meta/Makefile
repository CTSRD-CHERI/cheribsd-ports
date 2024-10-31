PORTNAME=	nginx
PORTVERSION=	${NGINX_RELEASE}
PORTREVISION=	0
CATEGORIES=	www

MAINTAINER=	alfredo.mazzinghi@cl.cam.ac.uk
COMMENT=	Meta-port for the default version of the nginx WWW server
WWW=		https://cheribsd.org/
DESCR=		${.CURDIR}/../nginx/pkg-descr

USES=		metaport

RUN_DEPENDS=	${LOCALBASE}/sbin/nginx:www/nginx-cheri

.include "${.CURDIR}/../nginx-cheri/Makefile.snapshot"
.include <bsd.port.mk>
