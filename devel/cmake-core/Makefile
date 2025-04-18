PORTNAME=	cmake
# Remember to update devel/cmake-doc and devel/cmake-gui as well.
DISTVERSION=	${_CMAKE_VERSION}
PORTREVISION=	1
CATEGORIES=	devel
PKGNAMESUFFIX=	-core

.ifdef QEMU_EMULATING
BROKEN_purecap=	concurrent tags implementation in the user mode is broken
USE_PKG64=	1
.endif

MAINTAINER=	kde@FreeBSD.org
COMMENT=	Cross-platform Makefile generator
WWW=		https://www.cmake.org/

LICENSE=	BSD3CLAUSE
LICENSE_FILE=	${WRKSRC}/Copyright.txt

LIB_DEPENDS=	libexpat.so:textproc/expat2 \
		libuv.so:devel/libuv \
		librhash.so:security/rhash

USES=		cmake:_internal compiler:c++11-lang cpe localbase ncurses ssl

CPE_VENDOR=	cmake_project
HAS_CONFIGURE=	yes
CONFIGURE_ENV=	MAKE=make
CONFIGURE_ARGS=	--prefix=${PREFIX} \
		--datadir="/${DATADIR_REL}" \
		--docdir="/${DOCSDIR_REL}" \
		--system-expat \
		--system-zlib \
		--system-zstd \
		--system-bzip2 \
		--system-liblzma \
		--system-libarchive \
		--system-librhash \
		--system-libuv \
		--no-system-curl \
		--no-system-nghttp2 \
		--parallel=${MAKE_JOBS_NUMBER} \
		--init="${WRKSRC}/InitialCache.cmake"

OPTIONS_DEFINE=	DOCS CPACK
OPTIONS_DEFAULT=	CPACK
OPTIONS_SUB=	yes

CPACK_DESC=		Enable FreeBSD generator in CPack (experimental)
CPACK_LIB_DEPENDS=	libpkg.so:${PKG_ORIGIN}

CXXFLAGS+=	-D__BSD_VISIBLE

.include <bsd.port.pre.mk>

# jsoncpp needs meson when built as a package
.if ${ABI:Mpurecap}
CONFIGURE_ARGS+=	--no-system-jsoncpp
.else
CONFIGURE_ARGS+=	--system-jsoncpp
LIB_DEPENDS+=		libjsoncpp.so:devel/jsoncpp
.endif

.if defined(STRIP) && ${STRIP} != "" && !defined(WITH_DEBUG)
INSTALL_TARGET=	install/strip
.endif

# Before running configure, substitute in the values of options
# for the build. CMake's configure doesn't accept --with-foo
# or similar options: it expects them to be set in CMake-style
# syntax in the initial cache.
pre-configure:
	@${CP} "${FILESDIR}/InitialCache.cmake" "${WRKSRC}/InitialCache.cmake"

pre-configure-CPACK-on:
	@${REINPLACE_CMD} \
		-e 's/@@CPACK_OPTION_VALUE@@/ON/' \
		-e 's/@@CPACK_OPTION_COMMENT@@//' \
		"${WRKSRC}/InitialCache.cmake"

pre-configure-CPACK-off:
	@${REINPLACE_CMD} \
		-e 's/@@CPACK_OPTION_VALUE@@/OFF/' \
		-e 's/@@CPACK_OPTION_COMMENT@@/# /' \
		"${WRKSRC}/InitialCache.cmake"

post-patch:
	@(${FIND} ${WRKSRC}/Modules -name "*.cmake" -print0; \
		${FIND} ${WRKSRC}/Tests -name "CMakeLists.txt" -print0 ) | \
		${XARGS} -0 -n 100 ${REINPLACE_CMD} -e 's,/usr/local,${LOCALBASE},g; \
			s,/usr/X11R6,${LOCALBASE},g'
	@${REINPLACE_CMD} -e 's,/usr/local,${LOCALBASE},g' \
		${WRKSRC}/Source/cmLocalGenerator.cxx \
		${WRKSRC}/Source/CPack/cmCPackGenerator.cxx \
		${WRKSRC}/bootstrap
	@${REINPLACE_CMD} -e 's,/opt/kde4,${PREFIX},g' \
		${WRKSRC}/Modules/FindKDE4.cmake
	@${REINPLACE_CMD} -e 's,/usr/include,${LOCALBASE}/include,' \
		${WRKSRC}/Modules/FindDCMTK.cmake
	@${REINPLACE_CMD} -e 's|%%LOCALBASE%%|${LOCALBASE}|g' \
		${WRKSRC}/Modules/FindFLEX.cmake
	@${FIND} ${WRKSRC} -name "*.bak" -delete -o -name "*.orig" -delete

# cmake-gui(1) is installed by devel/cmake-gui. Remove the man page's source to
# prevent it from being built/installed by devel/cmake.
	${RM} ${WRKSRC}/Help/manual/cmake-gui.1.rst

post-install:
	${INSTALL_DATA} ${WRKSRC}/Auxiliary/cmake-mode.el ${STAGEDIR}${PREFIX}/share/emacs/site-lisp
	# The .NoDartCoverage is supposed to suppress testing in the
	# source directories, but gets accidentally installed.
	@${FIND} ${STAGEDIR}${PREFIX} -name ".NoDartCoverage" -delete

.include <bsd.port.post.mk>
