PORTNAME=		sane-airscan
DISTVERSION=		0.99.26
PORTREVISION=	3
CATEGORIES=		graphics

MAINTAINER=		henry.hu.sh@gmail.com
COMMENT=		SANE backend for AirScan (eSCL) and WSD document scanners
WWW=		https://github.com/alexpevzner/sane-airscan

LICENSE=		GPLv2
LICENSE_FILE=		${WRKSRC}/LICENSE

LIB_DEPENDS=		libavahi-client.so:net/avahi-app \
			libpng.so:graphics/png \
			libgnutls.so:security/gnutls
BUILD_DEPENDS=		sane-backends>0:graphics/sane-backends

USES=			gmake gnome jpeg pkgconfig
USE_GNOME=		libxml2
USE_GITHUB=		yes
GH_ACCOUNT=		alexpevzner

MAKE_ARGS=		CC="${CC}" PKG_CONFIG=pkgconf

post-install:
	@${MV} ${STAGEDIR}${PREFIX}/etc/sane.d/airscan.conf \
		${STAGEDIR}${PREFIX}/etc/sane.d/airscan.conf.sample
	${RLN} ${STAGEDIR}${PREFIX}/lib/sane/libsane-airscan.so.1 \
		${STAGEDIR}${PREFIX}/lib/sane/libsane-airscan.so

.include <bsd.port.mk>
