PORTNAME=	crispy-doom
PORTVERSION=	6.0
DISTVERSIONPREFIX=	${PORTNAME}-
PORTREVISION=	1
CATEGORIES=	games

MAINTAINER=	danilo@FreeBSD.org
COMMENT=	Enhanced-resolution Doom source port based on Chocolate Doom
WWW=		https://github.com/fabiangreffrath/crispy-doom

LICENSE=	GPLv2

LIB_DEPENDS=	libsamplerate.so:audio/libsamplerate \
		libpng.so:graphics/png

USES=		autoreconf pkgconfig python:build sdl shebangfix

CONFLICTS_INSTALL=	chocolate-doom

USE_CSTD=	c99
USE_SDL=	mixer2 net2 sdl2
GNU_CONFIGURE=	yes
INSTALL_TARGET=	install-strip
SHEBANG_FILES=	man/docgen man/simplecpp

OPTIONS_DEFINE=	DOCS

USE_GITHUB=	yes
GH_ACCOUNT=	fabiangreffrath

.include <bsd.port.options.mk>

.if !${ABI:Mpurecap}
USES+=		desktop-file-utils
# fluidsynth needs glib
LIB_DEPENDS+=	libfluidsynth.so:audio/fluidsynth
.endif

post-patch:
	${REINPLACE_CMD} "s|python3|${PYTHON_VERSION}|" ${WRKSRC}/configure.ac

post-stage:
	${STRIP_CMD} ${STAGEDIR}${PREFIX}/bin/crispy-*-setup

.include <bsd.port.mk>
