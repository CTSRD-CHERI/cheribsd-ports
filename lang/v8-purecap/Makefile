PORTNAME=	v8-purecap
PORTVERSION=	bea11f0	
CATEGORIES=	lang
MASTER_SITES=	http://chromium.googlesource.com/chromium/src/tools/clang/+archive/:clang \
		https://chromium.googlesource.com/chromium/src/base/trace_event/common/+archive/:common \
		https://chromium.googlesource.com/external/github.com/google/googletest/+archive/:googletest \
		https://chromium.googlesource.com/chromium/deps/icu/+archive/:icu
DISTFILES=	${CLANG_REV}.tar.gz:clang \
		${COMMON_REV}.tar.gz:common \
		${GOOGLETEST_REV}.tar.gz:googletest \
		${ICU_REV}.tar.gz:icu
DIST_SUBDIR=	${PORTNAME}/${PORTVERSION:R:R}
EXTRACT_ONLY=	${DISTNAME}.tar.gz

MAINTAINER=	graeme@capabilitieslimited.co.uk
COMMENT=	Prototype port Open source JavaScript engine by Google to CheriABI
WWW=		https://v8.dev/

LICENSE=	BSD3CLAUSE
LICENSE_FILE=	${WRKSRC}/LICENSE

ONLY_FOR_ARCHS=	aarch64c

BUILD_DEPENDS=	gn:devel/gn \
		${PYTHON_PKGNAMEPREFIX}Jinja2>=0:devel/py-Jinja2@${PY_FLAVOR}
LIB_DEPENDS=	libicudata.so:devel/icu

USES=		compiler:c++17-lang cpe gnome ninja pkgconfig python:build tar:xz
USE_GNOME=	glib20

BINARY_ALIAS=	python3=${PYTHON_CMD}
MAKE_ARGS=	-C out/uncompressed
USE_LDCONFIG=	yes

SUB_FILES=	v8.pc v8_libbase.pc v8_libplatform.pc

USE_GITHUB=	yes
GH_ACCOUNT=	chromium-cheri
GH_PROJECT=	build:build buildtools:buildtools v8 zlib:zlib
GH_TAGNAME=     488dc76:build 8b16338:buildtools 05ca39b:zlib

CPE_VENDOR=	google

CLANG_REV=	4ee099ac1c0d6e86e53cedfdcfd7cd2d45e126ca
COMMON_REV=	147f65333c38ddd1ebf554e89965c243c8ce50b3
GOOGLETEST_REV=	af29db7ec28d6df1c7f0f745186884091e602e07
ICU_REV=	a2961dc659b4ae847a9c6120718cc2517ee57d9e

# Run "gn args --list out/uncompressed" for all variables.
# Some parts don't have use_system_* flag, and can be turned on/off by using
# replace_gn_files.py script, some parts just turned on/off for target host
# OS "target_os == is_bsd", like libusb, libpci.
GN_ARGS+=	arm_control_flow_integrity="none" \
		clang_base_path="${LOCALBASE64}" \
		clang_use_chrome_plugins=false \
		custom_toolchain="//tools/toolchain:morello-buildroot" \
		extra_cxxflags="${CXXFLAGS}" \
		extra_ldflags="${LDFLAGS}" \
		is_cheri=true \
		is_clang=true \
		is_component_build=true\
		target_cpu="arm64" \
		target_os="freebsd" \
		treat_warnings_as_errors=false \
		use_aura=true \
		use_lld=true \
		use_custom_libcxx=false \
		v8_enable_pointer_compression=false \
		v8_enable_external_code_space=false \
		v8_enable_sandbox=false \
		v8_enable_webassembly=false \
		v8_target_cpu="arm64" \
		v8_use_external_startup_data=false \
		chrome_pgo_phase=0 \
		use_thin_lto=false

DEBUG_VARS=		GN_ARGS+=is_debug=true \
			GN_ARGS+=v8_optimized_debug=true \
			GN_ARGS+=v8_enable_slow_dchecks=true

DEBUG_VARS_OFF=		GN_ARGS+=is_debug=false \
			GN_ARGS+=is_official_build=true

OPTIONS_DEFINE=		DEBUG EXAMPLES
OPTIONS_DEFAULT=	DEBUG EXAMPLES

post-extract:
	@${MKDIR} ${WRKSRC}/base/trace_event/common ${WRKSRC}/build ${WRKSRC}/buildtools ${WRKSRC}/third_party/googletest/src ${WRKSRC}/third_party/icu ${WRKSRC}/third_party/zlib ${WRKSRC}/tools/clang
	@${TAR} --strip-components=1 -xf ${DISTDIR}/${DIST_SUBDIR}/${DISTFILE_build} -C ${WRKSRC}/build
	@${TAR} --strip-components=1 -xf ${DISTDIR}/${DIST_SUBDIR}/${DISTFILE_buildtools} -C ${WRKSRC}/buildtools
	@${TAR} -xf ${DISTDIR}/${DIST_SUBDIR}/${CLANG_REV}.tar.gz -C ${WRKSRC}/tools/clang
	@${TAR} -xf ${DISTDIR}/${DIST_SUBDIR}/${COMMON_REV}.tar.gz -C ${WRKSRC}/base/trace_event/common
	@${TAR} -xf ${DISTDIR}/${DIST_SUBDIR}/${GOOGLETEST_REV}.tar.gz -C ${WRKSRC}/third_party/googletest/src
	@${TAR} -xf ${DISTDIR}/${DIST_SUBDIR}/${ICU_REV}.tar.gz -C ${WRKSRC}/third_party/icu
	@${TAR} --strip-components=1 -xf ${DISTDIR}/${DIST_SUBDIR}/${DISTFILE_zlib} -C ${WRKSRC}/third_party/zlib

post-patch:
	@${REINPLACE_CMD} -i '' 's|%%LOCALBASE%%|${LOCALBASE}|' ${WRKSRC}/build/toolchain/gcc_toolchain.gni ${WRKSRC}/buildtools/third_party/libc++/BUILD.gn
	# https://github.com/klzgrad/naiveproxy/blob/master/src/build/config/gclient_args.gni
	@${ECHO_CMD} 'checkout_google_benchmark = false' > ${WRKSRC}/build/config/gclient_args.gni

# Use ICU from ports and create needed directory
pre-configure:
	@cd ${WRKSRC} && ${SETENV} ${CONFIGURE_ENV} ${PYTHON_CMD} ./build/linux/unbundle/replace_gn_files.py --system-libraries icu # || ${FALSE}
	@${MKDIR} ${WRKSRC}/out/uncompressed/gen/shim_headers/icui18n_shim/third_party/icu/source/i18n/unicode ${WRKSRC}/out/uncompressed/gen/shim_headers/icuuc_shim/third_party/icu/source/common/unicode
	@${MKDIR} ${WRKSRC}/out/uncompressed/gen/include
	@${CP} -R ${LOCALBASE}/include/unicode ${WRKSRC}/out/uncompressed/gen/include/unicode

do-configure:
	@cd ${WRKSRC} && ${SETENV} ${CONFIGURE_ENV} gn gen out/uncompressed --args='${GN_ARGS}'

do-install:
	${MKDIR} ${STAGEDIR}${PREFIX}/include/cppgc ${STAGEDIR}${PREFIX}/include/libplatform
	${INSTALL_PROGRAM} ${WRKSRC}/out/uncompressed/d8 ${STAGEDIR}${PREFIX}/bin/d8
	${INSTALL_PROGRAM} ${WRKSRC}/out/uncompressed/mkgrokdump ${STAGEDIR}${PREFIX}/bin/mkgrokdump
	${INSTALL_PROGRAM} ${WRKSRC}/out/uncompressed/mksnapshot ${STAGEDIR}${PREFIX}/bin/mksnapshot
	${INSTALL_PROGRAM} ${WRKSRC}/out/uncompressed/v8_shell ${STAGEDIR}${PREFIX}/bin/v8_shell
	${INSTALL_LIB} ${WRKSRC}/out/uncompressed/libchrome_zlib.so ${STAGEDIR}${PREFIX}/lib/libchrome_zlib.so
	${INSTALL_LIB} ${WRKSRC}/out/uncompressed/libcppgc.so ${STAGEDIR}${PREFIX}/lib/libcppgc.so
	${INSTALL_LIB} ${WRKSRC}/out/uncompressed/libv8.so ${STAGEDIR}${PREFIX}/lib/libv8.so
	${INSTALL_LIB} ${WRKSRC}/out/uncompressed/libv8_libbase.so ${STAGEDIR}${PREFIX}/lib/libv8_libbase.so
	${INSTALL_LIB} ${WRKSRC}/out/uncompressed/libv8_libplatform.so ${STAGEDIR}${PREFIX}/lib/libv8_libplatform.so
	${INSTALL_DATA} ${WRKSRC}/include/*.h ${STAGEDIR}${PREFIX}/include/
	cd ${WRKSRC}/include/cppgc && ${COPYTREE_SHARE} . ${STAGEDIR}${PREFIX}/include/cppgc '-name *\.h'
	${INSTALL_DATA} ${WRKSRC}/include/libplatform/*.h ${STAGEDIR}${PREFIX}/include/libplatform/
	${INSTALL_DATA} ${WRKDIR}/v8*.pc ${STAGEDIR}${PREFIX}/libdata/pkgconfig/

do-install-EXAMPLES-on:
	${MKDIR} ${STAGEDIR}${EXAMPLESDIR}
	${INSTALL_PROGRAM} ${WRKSRC}/out/uncompressed/v8_simple_* ${STAGEDIR}${EXAMPLESDIR}

.include <bsd.port.mk>
