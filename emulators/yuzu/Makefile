PORTNAME=	yuzu
PORTVERSION=	s20230731
CATEGORIES=	emulators wayland
.if make(makesum)
MASTER_SITES=	https://api.yuzu-emu.org/gamedb/?dummy=/:gamedb
.else
MASTER_SITES=	LOCAL/jbeich:gamedb
.endif
DISTFILES=	${PORTNAME}-s20230424/compatibility_list.json:gamedb
EXTRACT_ONLY=	${DISTFILES:N*\:gamedb:C/\:.*//}

PATCH_SITES=	https://github.com/${GH_ACCOUNT}/${GH_PROJECT}/commit/
PATCHFILES+=	9bca45aa15.patch:-p1 # https://github.com/yuzu-emu/yuzu/pull/11195 mainline-merge

MAINTAINER=	jbeich@FreeBSD.org
COMMENT=	Nintendo Switch emulator/debugger
WWW=		https://yuzu-emu.org/

LICENSE=	APACHE20 BSD3CLAUSE GPLv3+ ISCL MIT UNLICENSE
LICENSE_COMB=	multi
LICENSE_FILE_BSD3CLAUSE=${WRKSRC}/externals/sirit/LICENSE.txt
LICENSE_FILE_GPLv3+ =	${WRKSRC}/LICENSE.txt
LICENSE_FILE_ISCL=	${WRKSRC}/externals/cubeb/LICENSE
LICENSE_FILE_MIT=	${WRKSRC}/externals/sirit/externals/SPIRV-Headers/LICENSE

ONLY_FOR_ARCHS=	aarch64 amd64
ONLY_FOR_ARCHS_REASON=	requires int128 and dynarmic backend

BUILD_DEPENDS=	boost-libs>0:devel/boost-libs \
		nlohmann-json>0:devel/nlohmann-json \
		xbyak>0:devel/xbyak \
		glslangValidator:graphics/glslang \
		vulkan-headers>0:graphics/vulkan-headers
LIB_DEPENDS=	liblz4.so:archivers/liblz4 \
		libzstd.so:archivers/zstd \
		libopus.so:audio/opus \
		libinih.so:devel/inih \
		libfmt.so:devel/libfmt \
		libavcodec.so:multimedia/ffmpeg \
		libenet.so:net/enet
TEST_DEPENDS=	catch2>0:devel/catch2

FLAVORS=	qt5 qt6
qt5_CONFLICTS_INSTALL=	${PORTNAME}-qt6
qt6_PKGNAMESUFFIX=	-qt6
qt6_CONFLICTS_INSTALL=	${PORTNAME}
qt6_OPTIONS_SLAVE=	QT6
qt6_OPTIONS_EXCLUDE=	QT5

USE_GITHUB=	yes
GH_ACCOUNT=	yuzu-emu
GH_TAGNAME=	2a9eab5e1b
GH_TUPLE=	yuzu-emu:mbedtls:v2.16.9-115-g8c88150ca:mbedtls/externals/mbedtls \
		yuzu-emu:sirit:ab75463:sirit/externals/sirit \
		GPUOpen-LibrariesAndSDKs:VulkanMemoryAllocator:v3.0.1-94-g9b0fc3e:VulkanMemoryAllocator/externals/VulkanMemoryAllocator \
		KhronosGroup:SPIRV-Headers:1.5.4.raytracing.fixed-201-gc214f6f:SPIRV_Headers/externals/sirit/externals/SPIRV-Headers \
		MerryMage:dynarmic:6.4.7-2-g7da37803:dynarmic/externals/dynarmic \
		arun11299:cpp-jwt:v1.4-14-ge12ef06:cpp_jwt/externals/cpp-jwt \
		arsenm:sanitizers-cmake:aab6948:sanitizers_cmake/externals/cubeb/cmake/sanitizers-cmake \
		benhoyt:inih:r52:inih/externals/inih/inih \
		eggert:tz:2022c:tz/externals/nx_tzdb/tzdb_to_nx/externals/tz/tz \
		kinetiknz:cubeb:cubeb-0.2-1452-g48689ae:cubeb/externals/cubeb \
		lat9nq:tzdb_to_nx:220816-27-g212afa2:tzdb_to_nx/externals/nx_tzdb/tzdb_to_nx \
		yhirose:cpp-httplib:v0.12.0-3-g6d963fb:cpp_httplib/externals/cpp-httplib

USES=		cmake:testing elfctl localbase:ldflags pkgconfig sdl ssl
USE_SDL=	sdl2
CMAKE_ON=	Boost_USE_STATIC_LIBS
CMAKE_ON+=	BUNDLE_SPEEX # only used by cubeb tests
CMAKE_ON+=	CMAKE_DISABLE_FIND_PACKAGE_LLVM # only need Demangle but llvm* is huge
CMAKE_OFF=	YUZU_CHECK_SUBMODULES YUZU_USE_EXTERNAL_SDL2 YUZU_USE_EXTERNAL_VULKAN_HEADERS
CMAKE_OFF+=	HTTPLIB_USE_BROTLI_IF_AVAILABLE # unused by ENABLE_WEB_SERVICE
CMAKE_OFF+=	${ARCH:Maarch64:C/.+/YUZU_USE_PRECOMPILED_HEADERS DYNARMIC_USE_PRECOMPILED_HEADERS/}
CMAKE_OFF+=	${CMAKE_TESTING_ON}
CMAKE_TESTING_ON=	YUZU_TESTS
LDFLAGS+=	-Wl,--as-needed # Qt5Network
ELF_FEATURES=	${PLIST_FILES:Mbin/*:S/^/+wxneeded:/}
PLIST_FILES=	bin/${PORTNAME}-cmd \
		bin/${PORTNAME}-room

OPTIONS_DEFINE=	ALSA GUI PULSEAUDIO JACK LTO NLS SNDIO VAAPI VULKAN WEBENGINE
OPTIONS_DEFAULT=PULSEAUDIO JACK LTO QT5 SNDIO VAAPI VULKAN WEBENGINE
OPTIONS_SINGLE=	GUI
OPTIONS_SINGLE_GUI=	QT5 QT6
OPTIONS_SLAVE=		${${FLAVOR}_OPTIONS_SLAVE}
OPTIONS_EXCLUDE=	${${FLAVOR}_OPTIONS_EXCLUDE}

ALSA_BUILD_DEPENDS=	alsa-lib>0:audio/alsa-lib
ALSA_CMAKE_BOOL=	USE_ALSA

GUI_USES=		desktop-file-utils shared-mime-info
GUI_CMAKE_BOOL=		ENABLE_QT
GUI_PLIST_FILES=	bin/${PORTNAME} \
			share/applications/org.yuzu_emu.yuzu.desktop \
			share/icons/hicolor/scalable/apps/org.yuzu_emu.yuzu.svg \
			share/metainfo/org.yuzu_emu.yuzu.metainfo.xml \
			share/mime/packages/org.yuzu_emu.yuzu.xml

JACK_BUILD_DEPENDS=	jackit>0:audio/jack
JACK_CMAKE_BOOL=	USE_JACK

LTO_CMAKE_BOOL=		YUZU_ENABLE_LTO

NLS_DESC=		UI translations (implies ${NLS_IMPLIES})
NLS_USE=		QT=${"${PORT_OPTIONS:MQT5}":?linguist:}tools:build
NLS_CMAKE_BOOL=		ENABLE_QT_TRANSLATION
NLS_IMPLIES=		GUI

PULSEAUDIO_BUILD_DEPENDS=pulseaudio>0:audio/pulseaudio
PULSEAUDIO_CMAKE_BOOL=	USE_PULSE

QT5_USES=		qt:5
QT5_USE=		QT=qmake:build,buildtools:build,concurrent:build,core,dbus,gui,multimedia,widgets
QT5_IMPLIES=		GUI

QT6_USES=		qt:6
QT6_USE=		QT=base
QT6_CMAKE_BOOL=		ENABLE_QT6
QT6_IMPLIES=		GUI

SNDIO_BUILD_DEPENDS=	sndio>0:audio/sndio
SNDIO_CMAKE_BOOL=	USE_SNDIO

VAAPI_LIB_DEPENDS=	libva.so:multimedia/libva

VULKAN_DESC=		Vulkan renderer
VULKAN_RUN_DEPENDS=	${LOCALBASE}/lib/libvulkan.so:graphics/vulkan-loader

WEBENGINE_DESC=		Web applet support (implies ${WEBENGINE_IMPLIES})
WEBENGINE_USE=		QT=webengine
WEBENGINE_CMAKE_BOOL=	YUZU_USE_QT_WEB_ENGINE
WEBENGINE_IMPLIES=	GUI

post-extract:
	@${CP} ${DISTFILES:M*\:gamedb:C/\:.*//:S,^,${_DISTDIR},} \
		${WRKSRC}/dist/compatibility_list/

post-patch:
	@${REINPLACE_CMD} -e 's/@GIT_BRANCH@/master/' \
		-e 's/@GIT_DESC@/${GH_TAGNAME}/' \
		${WRKSRC}/src/common/scm_rev.cpp.in
# Temporarily use ConsoleKit2 like sysutils/gnome-settings-daemon
	@${REINPLACE_CMD} -e 's,/login1,/ConsoleKit/Manager,' \
		-e 's,login1,ConsoleKit,' \
		${WRKSRC}/src/${PORTNAME}/main.cpp

post-patch-VAAPI-off:
	@${REINPLACE_CMD} -i .nova '/pkg_check.*libva/d' \
		${WRKSRC}/CMakeLists.txt

# XXX Drop after FreeBSD 13.2 EOL around 2024-05-01 (don't forget distinfo)
.if !exists(/usr/include/c++/v1/__ranges/as_rvalue_view.h) || make(makesum) || make(fetch)
. if !exists(/usr/include/c++/v1/__memory/concepts.h)
USES+=		llvm:min=14,build
PATH:=		${LLVM_PREFIX}/bin:${PATH} # XXX _CMAKE_TOOLCHAIN_SUFFIX vs. devel/llvm*
CC=		clang${LLVM_VERSION}
CXX=		clang++${LLVM_VERSION}
CPP=		clang-cpp${LLVM_VERSION}
CONFIGURE_ENV+=	CC="${CC}" CXX="${CXX}" CPP="${CPP}"
. endif

# XXX Move into separate port and standardize via USES
GH_TUPLE+=	llvm:llvm-project:llvmorg-16.0.1:libcxx
CXXFLAGS+=	-nostdinc++ -isystem${WRKDIR}/libcxx_prefix/include/c++/v1
# Don't link against new libc++ to avoid ABI mismatch in Qt
#LDFLAGS+=	-nostdlib++ -L${WRKDIR}/libcxx_prefix/lib -l:libc++.a -lcxxrt

pre-configure:	bundled-libcxx
bundled-libcxx:
	@${SETENV} ${CONFIGURE_ENV} ${CMAKE_BIN} ${CMAKE_ARGS:M*Ninja*} \
		-DLIBCXX_INCLUDE_BENCHMARKS:BOOL=OFF \
		-DCMAKE_INSTALL_PREFIX:PATH=${WRKDIR}/libcxx_prefix \
		-B ${WRKDIR}/libcxx_build -S ${WRKSRC_libcxx}/libcxx
	@${DO_MAKE_BUILD:NDESTDIR*} install -C ${WRKDIR}/libcxx_build
.endif

.include <bsd.port.mk>
