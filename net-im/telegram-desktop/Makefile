PORTNAME=	telegram-desktop
DISTVERSION=	4.8.4
PORTREVISION=	2
CATEGORIES=	net-im
MASTER_SITES=	https://github.com/${GH_ACCOUNT}/${GH_PROJECT}/releases/download/v${DISTVERSION}/
DISTNAME=	tdesktop-${DISTVERSION}-full
DISTFILES=	${DISTNAME}${EXTRACT_SUFX}

MAINTAINER=	ports@FreeBSD.org
COMMENT=	Telegram Desktop messaging app
WWW=		https://desktop.telegram.org/

LICENSE=	GPLv3
LICENSE_FILE=	${WRKSRC}/LICENSE

BROKEN_i386=	does not build, webrtc related
BROKEN_SSL=	openssl30 openssl31
BROKEN_SSL_REASON=	undefined symbol: ERR_load_BIO_strings
NOT_FOR_ARCHS=		powerpc powerpc64 powerpcspe
NOT_FOR_ARCHS_REASON=	Only little endian is supported

BUILD_DEPENDS=	boost-libs>0:devel/boost-libs \
		microsoft-gsl>0:devel/microsoft-gsl \
		range-v3>0:devel/range-v3 \
		tl-expected>0:devel/tl-expected \
		v4l_compat>0:multimedia/v4l_compat \
		yasm:devel/yasm \
		${LOCALBASE}/lib/libtg_owt.a:net-im/tg_owt
LIB_DEPENDS=	libabsl_base.so:devel/abseil \
		libavformat.so:multimedia/ffmpeg \
		libdbus-1.so:devel/dbus \
		libdispatch.so:devel/libdispatch \
		libfmt.so:devel/libfmt \
		libhunspell-1.7.so:textproc/hunspell \
		liblz4.so:archivers/liblz4 \
		libopenh264.so:multimedia/openh264 \
		libopus.so:audio/opus \
		libpipewire-0.3.so:multimedia/pipewire \
		libprotobuf.so:devel/protobuf \
		libqrcodegencpp.so:graphics/qr-code-generator \
		librnnoise.so:audio/rnnoise \
		libxcb-keysyms.so:x11/xcb-util-keysyms \
		libxkbcommon.so:x11/libxkbcommon \
		libxxhash.so:devel/xxhash \
		libvpx.so:multimedia/libvpx

FLAVORS=	qt5 qt6
FLAVOR?=	${FLAVORS:[1]}
qt5_PKGNAMESUFFIX=
qt6_PKGNAMESUFFIX=	-qt6
qt5_CONFLICTS_INSTALL=	${PORTNAME}-qt6
qt6_CONFLICTS_INSTALL=	${PORTNAME}

USES=		cmake desktop-file-utils gl gnome jpeg localbase \
		minizip openal pkgconfig python:build ssl xorg

USE_CXXSTD=	c++17
USE_GITHUB=	nodefault
GH_ACCOUNT=	telegramdesktop
GH_PROJECT=	tdesktop

.if ${FLAVOR} == qt5
USES+=		kde:5 qt:5
USE_QT=		buildtools:build core dbus gui imageformats network qmake:build \
		svg wayland widgets
USE_KDE=	coreaddons kimageformats
.else
USES+=		qt:6
USE_QT=		5compat base imageformats lottie shadertools svg tools:build wayland
.endif

USE_GL=		gl
USE_GNOME=	glib20 glibmm26 introspection
USE_XORG=	x11 xcb xcomposite xdamage xext xfixes xrandr xrender xtst

CMAKE_ARGS=	-DTDESKTOP_API_ID=${TELEGRAM_API_ID} -DTDESKTOP_API_HASH=${TELEGRAM_API_HASH}
CMAKE_ON=	DESKTOP_APP_USE_PACKAGED DESKTOP_APP_DISABLE_CRASH_REPORTS \
		DESKTOP_APP_DISABLE_WAYLAND_INTEGRATION

# Since cmake 3.25.0, BSDs are no longer recognised as Linux (in this port).
CMAKE_ARGS+=	-DLINUX=true

# libdispatch components
LDFLAGS+=	-lBlocksRuntime

# Telegram uses OpenAL for its audio, but libtgvoip (for voice calls) can use PulseAudio or ALSA.
# It dynamically loads PulseAudio, and if this fails, it loads ALSA.
# If both of them are not installed, then voice calls do not work, but other functionalities still work.
OPTIONS_DEFINE=		SYSTEM_FONTS
OPTIONS_DEFAULT=	ALSA
OPTIONS_GROUP=	AUDIO
OPTIONS_GROUP_AUDIO=	ALSA PULSEAUDIO

AUDIO_DESC=		Audio backend for voice calls
SYSTEM_FONTS_DESC=	Use system fonts instead of bundled patched ones

ALSA_LIB_DEPENDS=	libasound.so:audio/alsa-lib
PULSEAUDIO_LIB_DEPENDS=	libpulse.so:audio/pulseaudio
ALSA_CMAKE_BOOL_OFF=	LIBTGVOIP_DISABLE_ALSA
PULSEAUDIO_CMAKE_BOOL_OFF=	LIBTGVOIP_DISABLE_PULSEAUDIO
SYSTEM_FONTS_CMAKE_BOOL_OFF=	DESKTOP_APP_USE_PACKAGED_FONTS

# Telegram asks each custom build to have its own API ID and hash.
TELEGRAM_API_HASH=	20a3432aab43f24bb4460fceac5ba38d
TELEGRAM_API_ID=	601761

.include <bsd.port.options.mk>

.if ${OSVERSION} > 1400000
USES+=	llvm:build
CC=	${_LLVM_MK_PREFIX}/bin/clang
CPP=	${_LLVM_MK_PREFIX}/bin/clang-cpp
CXX=	${_LLVM_MK_PREFIX}/bin/clang++
#LD?=	${_LLVM_MK_PREFIX}/bin/ld
.else
USES+=	compiler:c++17-lang
.endif

post-patch:
	# XXX fix the following on every source file
	# warning: unknown warning option '-Wno-maybe-uninitialized'
	# warning: argument unused during compilation: '-fstack-clash-protection'
	${REINPLACE_CMD} -e /-Wno-maybe-uninitialized/d -e /-fstack-clash-protection/d \
	    ${WRKSRC}/cmake/options_linux.cmake

.include <bsd.port.mk>
