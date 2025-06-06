PORTNAME=	veloren
PORTVERSION=	s20230802
CATEGORIES=	games wayland
PKGNAMESUFFIX=	-weekly

MAINTAINER=	jbeich@FreeBSD.org
COMMENT=	Multiplayer voxel RPG written in Rust (weekly snapshot)
WWW=		https://veloren.net/

LICENSE=	GPLv3
LICENSE_FILE=	${WRKSRC}/LICENSE

BROKEN_aarch64=	https://github.com/rust-lang/libc/issues/3217
ONLY_FOR_ARCHS=	aarch64 amd64 i386
# https://gitlab.com/veloren/veloren/-/issues/1006
ONLY_FOR_ARCHS_REASON=	unsupported platform by https://github.com/wasmerio/wasmer

LIB_DEPENDS=	libasound.so:audio/alsa-lib \
		libudev.so:devel/libudev-devd \
		libshaderc_shared.so:graphics/shaderc
RUN_DEPENDS=	${LOCALBASE}/lib/alsa-lib/libasound_module_pcm_oss.so:audio/alsa-plugins \
		${LOCALBASE}/lib/libvulkan.so:graphics/vulkan-loader

USES=		cargo xorg
USE_XORG=	xcb
USE_GITLAB=	yes
GL_TAGNAME=	8abb93040ca49f9873a657c6a4b7f7aaf49bae78
CARGO_ENV=	VELOREN_USERDATA_STRATEGY=system SHADERC_LIB_DIR="${LOCALBASE}/lib"
PLIST_FILES=	bin/${PORTNAME}-server-cli \
		bin/${PORTNAME}-voxygen \
		share/applications/net.veloren.veloren.desktop \
		share/metainfo/net.veloren.veloren.metainfo.xml \
		share/pixmaps/net.veloren.veloren.png
PORTDATA=	*

CONFLICTS_INSTALL=	${PORTNAME}

.if ${MACHINE_ARCH} == i386
# Fixes error "Rust cannot catch foreign exceptions"
CARGO_ENV+=	CARGO_PROFILE_RELEASE_LTO=false
.endif
# Fixes error "Instruction does not dominate all uses!"
LTO_UNSAFE=	yes

# https://gitlab.com/veloren/veloren/issues/264
CARGO_ENV+=		RUSTC_BOOTSTRAP=1
# XXX https://github.com/rust-lang/cargo/issues/4101
CARGO_INSTALL_PATH=	server-cli voxygen

post-patch:
# .git/ directory is missing, so don't abort if git binary is also missing
	@${REINPLACE_CMD} -e 's/"git"/"${TRUE}"/' \
		${WRKSRC}/common/build.rs
# Extract (snapshot) version from the port instead of empty file
	@${REINPLACE_CMD} -e '/GIT_HASH/s/=.*/= "${GL_TAGNAME:C/(.{8}).*/\1/}";/' \
		-e "/GIT_DATE.*static/s/=.*/= \"$$(date -ur $$(${AWK} '/TIMESTAMP/ { print $$3 }' \
			${DISTINFO_FILE}) +'%Y-%m-%d-%H:%M')\";/" \
		${WRKSRC}/common/src/util/mod.rs
# Respect PREFIX != /usr/local for system assets
	@${REINPLACE_CMD} -e 's,/usr/share,${DATADIR:H},' \
		${WRKSRC}/common/assets/src/lib.rs

do-install:
# XXX [workspace.dependencies] breaks rebuild in subdirs
.for f in ${CARGO_INSTALL_PATH}
	${INSTALL_PROGRAM} ${CARGO_TARGET_DIR}/*/*/${PORTNAME}-$f \
		${STAGEDIR}${PREFIX}/bin
.endfor

post-install:
	${STRIP_CMD} ${STAGEDIR}${PREFIX}/bin/*
	(cd ${WRKSRC} && ${COPYTREE_SHARE} assets ${STAGEDIR}${DATADIR})
	${RLN} ${STAGEDIR}${DATADIR}/assets/voxygen/*.desktop \
		${STAGEDIR}${PREFIX}/share/applications
	${RLN} ${STAGEDIR}${DATADIR}/assets/voxygen/*.png \
		${STAGEDIR}${PREFIX}/share/pixmaps
	${MKDIR} ${STAGEDIR}${PREFIX}/share/metainfo
	${RLN} ${STAGEDIR}${DATADIR}/assets/voxygen/*.metainfo.xml \
		${STAGEDIR}${PREFIX}/share/metainfo

.include <bsd.port.mk>
