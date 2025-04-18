PORTNAME=	signal-desktop
DISTVERSIONPREFIX=	v
DISTVERSION=	6.26.0
PORTREVISION=	1
CATEGORIES=	net-im
MASTER_SITES=	LOCAL/mikael/signal-desktop/:npm \
		LOCAL/mikael/signal-desktop/:sqlite \
		LOCAL/mikael/signal-desktop/:yarn \
		https://build-artifacts.signal.org/desktop/:sqlcipher
DISTFILES=	signal-desktop-${DISTVERSION}-yarn-cache.tar.gz:yarn \
		signal-desktop-6.4.1-npm-cache.tar.gz:npm \
		${SQLCIPHER}.tar.gz:sqlcipher

MAINTAINER=	mikael@FreeBSD.org
COMMENT=	Cross-platform centralized encrypted messaging service
WWW=		https://signal.org/

LICENSE=	AGPLv3
LICENSE_FILE=	${WRKSRC}/LICENSE

ONLY_FOR_ARCHS=	aarch64 amd64

EXTRACT_DEPENDS=jq:textproc/jq \
		yarn-node16>0:www/yarn-node16
BUILD_DEPENDS=	${LOCALBASE}/lib/libcrypto.a:security/openssl30 \
		${LOCALBASE}/lib/libringrtc.so:multimedia/ringrtc \
		${LOCALBASE}/lib/libsignal_node.so:net-im/libsignal-node \
		${LOCALBASE}/lib/libsignal_tokenizer.a:devel/signal-fts5-extension \
		app-builder>0:devel/app-builder \
		electron${ELECTRON_VER_MAJOR}:devel/electron${ELECTRON_VER_MAJOR} \
		jq:textproc/jq \
		npm:www/npm-node16 \
		vips>0:graphics/vips \
		yarn:www/yarn-node16
LIB_DEPENDS=	libasound.so:audio/alsa-lib \
		libatk-bridge-2.0.so:accessibility/at-spi2-core \
		libatspi.so:accessibility/at-spi2-core \
		libcups.so:print/cups \
		libdbus-1.so:devel/dbus \
		libdrm.so:graphics/libdrm \
		libevent.so:devel/libevent \
		libexpat.so:textproc/expat2 \
		libFLAC.so:audio/flac \
		libfontconfig.so:x11-fonts/fontconfig \
		libfreetype.so:print/freetype2 \
		libharfbuzz.so:print/harfbuzz \
		libicuuc.so:devel/icu \
		libnspr4.so:devel/nspr \
		libnss3.so:security/nss \
		libopenh264.so:multimedia/openh264 \
		libopus.so:audio/opus \
		libpci.so:devel/libpci \
		libpng16.so:graphics/png \
		libsnappy.so:archivers/snappy \
		libwayland-client.so:graphics/wayland \
		libwebp.so:graphics/webp \
		libxkbcommon.so:x11/libxkbcommon \
		libxshmfence.so:x11/libxshmfence

USES=		desktop-file-utils gettext-runtime gl gnome jpeg xorg
USE_GITHUB=	yes
GH_ACCOUNT=	signalapp
GH_PROJECT=	Signal-Desktop

USE_GL=		gbm gl
USE_GNOME=	atk cairo gdkpixbuf2 glib20 gtk30 libxml2 libxslt pango
USE_XORG=	x11 xcb xcomposite xdamage xext xfixes xi xrandr xrender xtst

PACKAGE_ENV=	SIGNAL_ENV=production
MAKE_ENV+=	ELECTRON_OVERRIDE_DIST_PATH=${LOCALBASE}/share/electron${ELECTRON_VER_MAJOR} \
		HOME=${WRKDIR} \
		USE_SYSTEM_APP_BUILDER=true \
		SOURCE_DATE_EPOCH=${_BUILD_DATE} \
		PATH=${WRKSRC}/node_modules/.bin:${LOCALBASE}/bin:${PATH}

# Don't download electron binary distribution on electron node_modules installation
MAKE_ENV+=	ELECTRON_SKIP_BINARY_DOWNLOAD=1

# Don't create __pycache__ directory when executing node-gyp
# This is a workaround to avoid filesystem violations during poudriere build
MAKE_ENV+=	PYTHONDONTWRITEBYTECODE=1

MAKE_ENV+=	ESBUILD_BINARY_PATH=${WRKDIR}/esbuild-freebsd-64/package/bin/esbuild

_BUILD_DATE=	$$(date +'%s')

ELECTRON_VER_MAJOR=	25

# sh get_deps.sh
NPM_SIGNAL_DIR=		npm-@signalapp-libsignal-client-0.22.0-d57441612df46f90df68fc5d9ad45b857b9d2c44-integrity
NPM_RINGRTC_DIR=	npm-@signalapp-ringrtc-2.28.1-15785854f986c9a7a52b4dec2cc9145b8c5fbf00-integrity
NPM_SQLITE3_DIR=	npm-@signalapp-better-sqlite3-8.4.3-7ffa8d03d2a12543247936bfb7b9f74cdbc6fe9b-integrity
NPM_ESBUILD_VERS=	0.17.11
SQLCIPHER=		sqlcipher-4.5.3-fts--3.0.7--0.2.1-b633825cf7e0fdd39a6cdf128f2bd76552a88d325f2b9cd07bb87a457cefb986

ESBUILD_ARCH=	${ARCH:S/aarch64/arm64/:S/amd64/x64/}
NODE_ARCH=	${ARCH:S/aarch64/arm64/:S/amd64/x64/}
APP_OUT_DIR=	linux-${ARCH:S/aarch64/arm64-/:S/amd64//}unpacked

PLIST_SUB=	NODE_ARCH=${NODE_ARCH} \
		SHARP_ARCH=${ARCH:S/aarch64/arm64v8/:S/amd64/x64/}

YARN_TIMESTAMP=	1661146515

fetch-yarn:
	if [ ! -f ${DISTDIR}/signal-desktop-${DISTVERSION}-yarn-cache.tar.gz ]; then \
		${MKDIR} /tmp/signal-desktop; \
		${FETCH_CMD} -o - https://raw.githubusercontent.com/signalapp/Signal-Desktop/v${DISTVERSION}/package.json | \
			${PREFIX}/bin/jq '.engines.node = "${NODE_VERSION}"' > /tmp/signal-desktop/package.json; \
		${FETCH_CMD} -o /tmp/signal-desktop/yarn.lock https://raw.githubusercontent.com/signalapp/Signal-Desktop/v${DISTVERSION}/yarn.lock; \
		${ECHO_CMD} 'yarn-offline-mirror "./yarn-offline-cache"' >> \
			/tmp/signal-desktop/.yarnrc; \
		${PREFIX}/bin/jq 'del(.devDependencies."@signalapp/mock-server")' /tmp/signal-desktop/package.json > /tmp/signal-desktop/package.json.tmp; \
		${MV} /tmp/signal-desktop/package.json.tmp /tmp/signal-desktop/package.json; \
		cd /tmp/signal-desktop && ${SETENV} HOME=/tmp/signal-desktop XDG_CACHE_HOME=/tmp/signal-desktop/.cache \
			yarn --frozen-lockfile --ignore-scripts; \
		${MTREE_CMD} -cbnSp yarn-offline-cache | ${MTREE_CMD} -C | ${SED} \
			-e 's:time=[0-9.]*:time=${YARN_TIMESTAMP}.000000000:' \
			-e 's:\([gu]id\)=[0-9]*:\1=0:g' \
			-e 's:flags=.*:flags=none:' \
			-e 's:^\.:./yarn-offline-cache:' > yarn-offline-cache.mtree; \
		${TAR} cJf ${DISTDIR}/signal-desktop-${DISTVERSION}-yarn-cache.tar.gz  \
			@yarn-offline-cache.mtree; \
		${RM} -r ${WRKDIR}; \
	fi

post-patch:
	${REINPLACE_CMD} "s#%%EPOCH%%#${_BUILD_DATE}#" \
		${WRKSRC}/ts/scripts/get-expire-time.ts

post-extract:
	# install yarn modules and fail silently
	${ECHO_CMD} 'yarn-offline-mirror "../yarn-offline-cache"' > ${WRKSRC}/.yarnrc
	${ECHO_CMD} 'nodedir "${LOCALBASE}"' >> ${WRKSRC}/.yarnrc
	# Update node engine
	${PREFIX}/bin/jq '.engines.node = "${NODE_VERSION}"' ${WRKSRC}/package.json > ${WRKSRC}/package.json.tmp
	${MV} ${WRKSRC}/package.json.tmp ${WRKSRC}/package.json
	# remove mock-server as it doesn't build and is useless
	${PREFIX}/bin/jq 'del(.devDependencies."@signalapp/mock-server")' ${WRKSRC}/package.json > ${WRKSRC}/package.json.tmp
	${MV} ${WRKSRC}/package.json.tmp ${WRKSRC}/package.json
	cd ${WRKSRC} && \
		${SETENV} ${MAKE_ENV} yarn install --frozen-lockfile --ignore-optional --offline || ${TRUE}

do-build:
	${ECHO_CMD} 'yarn-offline-mirror "../yarn-offline-cache"' > ${WRKSRC}/.yarnrc
	${ECHO_CMD} 'nodedir "${LOCALBASE}/share/electron${ELECTRON_VER_MAJOR}/node_headers"' >> ${WRKSRC}/.yarnrc

# electron-builder is stupid and tries to open ${LOCALBASE}/share/electron25/electron with WRITE priv
# copy ${LOCALBASE}/share/electron25 in WRKDIR
# it's needed for the do-install phase, it's here because of this issue
# https://github.com/MikaelUrankar/signal-desktop/issues/6 (I don't know why it fails though)
	@${RM} -r ${WRKDIR}/electron${ELECTRON_VER_MAJOR}
	@${CP} -pR ${LOCALBASE}/share/electron${ELECTRON_VER_MAJOR} ${WRKDIR}/electron${ELECTRON_VER_MAJOR}
	${CHMOD} -R a+w ${WRKDIR}/electron${ELECTRON_VER_MAJOR}

	# Install libsignal_node.so and libringrtc.so binaries in the yarn cache
	${MKDIR} ${WRKDIR}/.cache/yarn/v6/${NPM_SIGNAL_DIR}/node_modules/@signalapp/libsignal-client/prebuilds/freebsd-${NODE_ARCH} \
		 ${WRKDIR}/.cache/yarn/v6/${NPM_RINGRTC_DIR}/node_modules/@signalapp/ringrtc/build/freebsd
	${CP} ${LOCALBASE}/lib/libsignal_node.so \
		${WRKDIR}/.cache/yarn/v6/${NPM_SIGNAL_DIR}/node_modules/@signalapp/libsignal-client/prebuilds/freebsd-${NODE_ARCH}/node.napi.node
	${CP} ${LOCALBASE}/lib/libringrtc.so \
		${WRKDIR}/.cache/yarn/v6/${NPM_RINGRTC_DIR}/node_modules/@signalapp/ringrtc/build/freebsd/libringrtc-${NODE_ARCH}.node

	${MKDIR} ${WRKDIR}/.cache/yarn/v6/${NPM_SQLITE3_DIR}/node_modules/@signalapp/better-sqlite3/deps
	${CP} ${DISTDIR}/${SQLCIPHER}.tar.gz \
		${WRKDIR}/.cache/yarn/v6/${NPM_SQLITE3_DIR}/node_modules/@signalapp/better-sqlite3/deps/sqlcipher.tar.gz

	${CP} ${FILESDIR}/fetch-prebuild.js \
		${WRKDIR}/.cache/yarn/v6/${NPM_RINGRTC_DIR}/node_modules/@signalapp/ringrtc/scripts/fetch-prebuild.js
	${CP} ${FILESDIR}/download.js \
		${WRKDIR}/.cache/yarn/v6/${NPM_SQLITE3_DIR}/node_modules/@signalapp/better-sqlite3/deps/download.js

	# patch-package can't patch sqlite3 on aarch64, patch the yarn cache instead
	cd ${WRKDIR}/.cache/yarn/v6 && ${PATCH} -s -N -i ${FILESDIR}/sqlite3.gyp.diff

	${MKDIR} ${WRKDIR}/esbuild-freebsd-64
	${TAR} -xf ${WRKDIR}/yarn-offline-cache/@esbuild-freebsd-${ESBUILD_ARCH}-${NPM_ESBUILD_VERS}.tgz -C ${WRKDIR}/esbuild-freebsd-64

# 	# For online build
#	${RM} ${WRKDIR}/.npmrc
#	cd ${WRKSRC} && \
#		${SETENV} ${MAKE_ENV} yarn install --frozen-lockfile --ignore-optional
#	cd ${WRKSRC} && \
#		${SETENV} ${MAKE_ENV} yarn generate
#	cd ${WRKSRC} && \
#		${SETENV} ${MAKE_ENV} yarn build:esbuild:prod

	# For offline build
	${ECHO_CMD} offline=true > ${WRKDIR}/.npmrc
	cd ${WRKSRC} && \
		${SETENV} ${MAKE_ENV} yarn install --frozen-lockfile --ignore-optional --offline
	cd ${WRKSRC} && \
		${SETENV} ${MAKE_ENV} yarn --offline generate
	cd ${WRKSRC} && \
		${SETENV} ${MAKE_ENV} yarn --offline build:esbuild:prod

do-install:
# taken from https://github.com/tagattie/FreeBSD-Electron/blob/master/Mk/Uses/electron.mk#L387
# and editors/vscode
	cd ${WRKSRC} && \
		${SETENV} ${MAKE_ENV} ${PACKAGE_ENV} yarn run electron-builder \
			--linux --dir --config.npmRebuild=false \
			--config.electronVersion=${ELECTRON_VER_MAJOR} \
			--config.electronDist=${WRKDIR}/electron${ELECTRON_VER_MAJOR}

	${MKDIR} ${STAGEDIR}${DATADIR}
	cd ${BUILD_WRKSRC}/dist/${APP_OUT_DIR} && \
		${COPYTREE_SHARE} . ${STAGEDIR}${DATADIR}

	${MKDIR} ${STAGEDIR}${PREFIX}/share/pixmaps
	${INSTALL_DATA} ${WRKSRC}/images/signal-logo-desktop-linux.png \
		${STAGEDIR}${PREFIX}/share/pixmaps/signal-desktop.png
	${INSTALL_DATA} ${FILESDIR}/${PORTNAME}.desktop \
		${STAGEDIR}${PREFIX}/share/applications

.for f in chromedriver mksnapshot v8_context_snapshot_generator
	${RM} ${STAGEDIR}${DATADIR}/${f}
.endfor
	${RM} -r ${STAGEDIR}${DATADIR}/gen
	${RM} -r ${STAGEDIR}${DATADIR}/node_headers
	${RM} -r ${STAGEDIR}${DATADIR}/resources/completions
	${RLN} ${STAGEDIR}${DATADIR}/signal-desktop ${STAGEDIR}${PREFIX}/bin

create-caches-tarball:
	# do some cleanup first
	${RM} -r  ${WRKDIR}/.npm/_logs ${WRKDIR}/.npm/_update-notifier-last-checked ${WRKDIR}/.cache/yarn/v6/.tmp
	${FIND} ${WRKDIR}/.cache -type f -perm 755 -exec file {} \; | ${EGREP} "ELF|PE32+|Mach-O" | ${AWK} -F ':' '{print $$1}' | ${XARGS} ${RM}

	cd ${WRKDIR} && \
		${TAR} czf signal-desktop-${DISTVERSION}-yarn-cache.tar.gz .cache yarn-cache
	cd ${WRKDIR} && \
		${TAR} czf signal-desktop-${DISTVERSION}-electron-gyp-cache.tar.gz .electron-gyp
	cd ${WRKDIR} && \
		${TAR} czf signal-desktop-${DISTVERSION}-npm-cache.tar.gz .npm

.include <bsd.port.mk>
