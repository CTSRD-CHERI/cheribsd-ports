PORTNAME=	yaml-cpp
PORTVERSION=	0.7.0
DISTVERSIONPREFIX=	${PORTNAME}-
CATEGORIES=	devel

MAINTAINER=	madpilot@FreeBSD.org
COMMENT=	YAML parser and emitter in C++ matching the YAML 1.2 spec
WWW=		https://github.com/jbeder/yaml-cpp

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/LICENSE

USES=		cmake compiler:c++11-lang
USE_LDCONFIG=	yes
CMAKE_ARGS+=	-DYAML_BUILD_SHARED_LIBS:BOOL=ON \
		-DYAML_CPP_BUILD_TOOLS=OFF \
		-DYAML_CPP_BUILD_TESTS=OFF

USE_GITHUB=	yes
GH_ACCOUNT=	jbeder

post-patch:
	@${REINPLACE_CMD} "s|%%PREFIX%%|${PREFIX}|" \
		${WRKSRC}/yaml-cpp-config.cmake.in

.include <bsd.port.pre.mk>

.if ${CMAKE_BUILD_TYPE} == "Debug"
# yaml-cpp sets CMAKE_DEBUG_POSTFIX="d" that results in the "d" suffix added to
# shared library file names.
PLIST_SUB+=	CMAKE_DEBUG_POSTFIX="d"
.else
PLIST_SUB+=	CMAKE_DEBUG_POSTFIX=""
.endif

.include <bsd.port.post.mk>
