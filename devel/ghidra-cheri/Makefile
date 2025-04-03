PORTNAME=	ghidra-cheri
PORTVERSION=	${GHIDRA_VERSION}.d${SNAPDATE}
PORTREVISION=	0
CATEGORIES=	devel security java
MASTER_SITES=	SF/pydev/pydev/PyDev%206.3.1/:pydev \
		SF/yajsw/yajsw/yajsw-stable-13.09/:yajsw \
		https://archive.eclipse.org/tools/cdt/releases/8.6/:eclipse \
		https://ftp.postgresql.org/pub/source/v15.3/:postgresql \
		https://github.com/NationalSecurityAgency/ghidra-data/raw/Ghidra_11.1/:ghidra \
		https://github.com/pxb1988/dex2jar/releases/download/v2.1/:dex2jar \
		https://storage.googleapis.com/google-code-archive-downloads/v2/code.google.com/android4me/:axml2printer \
		https://files.pythonhosted.org/packages/8d/14/619e24a4c70df2901e1f4dbc50a6291eb63a759172558df326347dce1f0d/:py_protobuf \
		https://files.pythonhosted.org/packages/90/c7/6dc0a455d111f68ee43f27793971cf03fe29b6ef972042549db29eec39a2/:py_psutil \
		https://files.pythonhosted.org/packages/c7/42/be1c7bbdd83e1bfb160c94b9cafd8e25efc7400346cf7ccdbdb452c467fa/:py_setuptools \
		https://files.pythonhosted.org/packages/27/d6/003e593296a85fd6ed616ed962795b2f87709c3eee2bca4f6d0fe55c6d00/:py_wheel \
		https://files.pythonhosted.org/packages/2d/e0/f877c91e036fcaed2a827f80d6cbdf1d26cffc3333c9ebda31c55c45f050/:py_pybag \
		https://files.pythonhosted.org/packages/d0/dd/b28df50316ca193dd1275a4c47115a720796d9e1501c1888c4bfa5dc2260/:py_capstone \
		https://files.pythonhosted.org/packages/50/8f/518a37381e55a8857a638afa86143efa5508434613541402d20611a1b322/:py_comtypes \
		https://files.pythonhosted.org/packages/83/1c/25b79fc3ec99b19b0a0730cc47356f7e2959863bf9f3cd314332bddb4f68/:py_pywin32

DISTFILES=	AXMLPrinter2.jar:axml2printer \
		FunctionID/vs2012_x64.fidb:ghidra \
		FunctionID/vs2012_x86.fidb:ghidra \
		FunctionID/vs2015_x64.fidb:ghidra \
		FunctionID/vs2015_x86.fidb:ghidra \
		FunctionID/vs2017_x64.fidb:ghidra \
		FunctionID/vs2017_x86.fidb:ghidra \
		FunctionID/vs2019_x64.fidb:ghidra \
		FunctionID/vs2019_x86.fidb:ghidra \
		FunctionID/vsOlder_x64.fidb:ghidra \
		FunctionID/vsOlder_x86.fidb:ghidra \
		PyDev%206.3.1.zip:pydev \
		cdt-8.6.0.zip:eclipse \
		dex2jar-2.1.zip:dex2jar \
		lib/java-sarif-2.1-modified.jar:ghidra \
		postgresql-15.3.tar.gz:postgresql \
		yajsw-stable-13.09.zip:yajsw \
		protobuf-3.20.3-py2.py3-none-any.whl:py_protobuf \
		psutil-5.9.8.tar.gz:py_psutil \
		setuptools-68.0.0-py3-none-any.whl:py_setuptools \
		wheel-0.37.1-py2.py3-none-any.whl:py_wheel \
		Pybag-2.2.10-py3-none-any.whl:py_pybag \
		capstone-5.0.1-py3-none-win_amd64.whl:py_capstone \
		comtypes-1.4.1-py3-none-any.whl:py_comtypes \
		pywin32-306-cp312-cp312-win_amd64.whl:py_pywin32
DIST_SUBDIR=	${PORTNAME}
EXTRACT_ONLY=	${DISTNAME}${EXTRACT_SUFX}

USE_GITHUB=	yes
GH_ACCOUNT=	CTSRD-CHERI
GH_PROJECT=	ghidra
GH_TAGNAME=	${GHIDRA_COMMIT}

MAINTAINER=	zyj20@cl.cam.ac.uk
COMMENT=	Software reverse engineering (SRE) framework
WWW=		https://github.com/CTSRD-CHERI/ghidra

LICENSE=	APACHE20
LICENSE_FILE=	${WRKSRC}/LICENSE

ONLY_FOR_ARCHS= aarch64	amd64

NOT_FOR_ABIS=	purecap
NOT_FOR_ABIS_REASON_purecap=is not adapted for CheriABI yet

EXTRACT_DEPENDS=	${UNZIP_CMD}:archivers/unzip
BUILD_DEPENDS=		bash:shells/bash \
			gradle>=7.3:devel/gradle \
			protoc:devel/protobuf
RUN_DEPENDS=		bash:shells/bash \
			protoc:devel/protobuf

USES=		bison cpe shebangfix
CPE_VENDOR=	nsa

USE_JAVA=	yes
JAVA_VERSION=	17+
JAVA_BUILD=	yes
JAVA_RUN=	yes

SHEBANG_FILES=	Ghidra/RuntimeScripts/Common/server/jaas_external_program.example.sh \
		Ghidra/RuntimeScripts/Linux/* \
		Ghidra/RuntimeScripts/Linux/server/* \
		Ghidra/RuntimeScripts/Linux/support/* \
		Ghidra/Features/BSim/make-postgres.sh \
		Ghidra/Debug/Debugger-agent-frida/src/main/sh/execjar.sh \
		Ghidra/Debug/Debugger-agent-lldb/src/main/sh/execjar.sh \
		Ghidra/Debug/Debugger-agent-gdb/data/debugger-launchers/local-gdb.sh \
		Ghidra/Debug/Debugger-agent-gdb/src/main/sh/execjar.sh \
		Ghidra/Debug/Debugger-swig-lldb/macos_debugger_lldb_build_from_brew.sh


# Gradle cache path must be absolute (see https://github.com/gradle/gradle/issues/1338)
GRADLE_HOME_BASE=	/tmp
GRADLE_RUN=		${SETENV} ${MAKE_ENV} gradle --gradle-user-home \
			${GRADLE_HOME_BASE}/gradle-${PORTNAME} --no-daemon

# to rebuild the deps archive:
#   1. set DEV_UPDATE_MODE=yes
#   2. make makesum build
#   3. upload the *-deps archive
#   4. set DEV_UPDATE_MODE=no
#   5. make clean makesum

DEV_UPDATE_MODE?=	no

.if (${DEV_UPDATE_MODE} == "no")
MASTER_SITES+=	LOCAL_CHERIBSD/ghidra-cheri/:gradle
DISTFILES+=	${PORTNAME}-${DISTVERSION}-deps${EXTRACT_SUFX}:gradle
EXTRACT_ONLY+=	${PORTNAME}-${DISTVERSION}-deps${EXTRACT_SUFX}
GRADLE_RUN+=	--offline
.endif

.include "${.CURDIR}/Makefile.snapshot"

.include <bsd.port.pre.mk>

post-extract:
	@${MKDIR} ${WRKSRC}/dependencies/flatRepo
	@${UNZIP_CMD} -j -d ${WRKSRC}/dependencies/flatRepo ${DISTDIR}/${DIST_SUBDIR}/dex2jar-2.1.zip "dex-tools-2.1/lib/dex-*.jar"
	@${CP} ${DISTDIR}/${DIST_SUBDIR}/AXMLPrinter2.jar ${WRKSRC}/dependencies/flatRepo
	@${CP} ${DISTDIR}/${DIST_SUBDIR}/lib/java-sarif-2.1-modified.jar ${WRKSRC}/dependencies/flatRepo
	@${MKDIR} ${WRKSRC}/dependencies/GhidraServer
	@${CP} ${DISTDIR}/${DIST_SUBDIR}/yajsw-stable-13.09.zip ${WRKSRC}/dependencies/GhidraServer
	@${MKDIR} ${WRKSRC}/dependencies/BSim
	@${CP} ${DISTDIR}/${DIST_SUBDIR}/postgresql-15.3.tar.gz ${WRKSRC}/dependencies/BSim
	@${MKDIR} ${WRKSRC}/dependencies/GhidraDev
	@${CP} ${DISTDIR}/${DIST_SUBDIR}/PyDev%206.3.1.zip ${WRKSRC}/dependencies/GhidraDev
	@${CP} ${DISTDIR}/${DIST_SUBDIR}/cdt-8.6.0.zip ${WRKSRC}/dependencies/GhidraDev
	${MKDIR} ${WRKSRC}/dependencies/fidb
	@${CP} ${DISTDIR}/${DIST_SUBDIR}/FunctionID/*fidb ${WRKSRC}/dependencies/fidb
	${MKDIR} ${WRKSRC}/dependencies/Debugger-rmi-trace
	@${CP} ${DISTDIR}/${DIST_SUBDIR}/protobuf-3.20.3-py2.py3-none-any.whl ${WRKSRC}/dependencies/Debugger-rmi-trace
	@${CP} ${DISTDIR}/${DIST_SUBDIR}/psutil-5.9.8.tar.gz ${WRKSRC}/dependencies/Debugger-rmi-trace
	@${CP} ${DISTDIR}/${DIST_SUBDIR}/setuptools-68.0.0-py3-none-any.whl ${WRKSRC}/dependencies/Debugger-rmi-trace
	@${CP} ${DISTDIR}/${DIST_SUBDIR}/wheel-0.37.1-py2.py3-none-any.whl ${WRKSRC}/dependencies/Debugger-rmi-trace
	${MKDIR} ${WRKSRC}/dependencies/Debugger-agent-dbgeng
	@${CP} ${DISTDIR}/${DIST_SUBDIR}/Pybag-2.2.10-py3-none-any.whl ${WRKSRC}/dependencies/Debugger-agent-dbgeng
	@${CP} ${DISTDIR}/${DIST_SUBDIR}/capstone-5.0.1-py3-none-win_amd64.whl ${WRKSRC}/dependencies/Debugger-agent-dbgeng
	@${CP} ${DISTDIR}/${DIST_SUBDIR}/comtypes-1.4.1-py3-none-any.whl ${WRKSRC}/dependencies/Debugger-agent-dbgeng
	@${CP} ${DISTDIR}/${DIST_SUBDIR}/pywin32-306-cp312-cp312-win_amd64.whl ${WRKSRC}/dependencies/Debugger-agent-dbgeng
	@${RM} -r ${GRADLE_HOME_BASE}/gradle-${PORTNAME}
.if (${DEV_UPDATE_MODE} == "no")
	@${LN} -sf ${WRKDIR}/gradle-${PORTNAME} ${GRADLE_HOME_BASE}
.endif

post-patch:
	@${REINPLACE_CMD} -e "s|JAVA_HOME_PLACEHOLDER|${JAVA_HOME}|" \
		${WRKSRC}/Ghidra/RuntimeScripts/Linux/support/launch.sh
	@${ECHO_CMD} "org.gradle.java.home=${JAVA_HOME}" > ${WRKSRC}/gradle.properties

do-build:
	@cd ${WRKSRC} && ${GRADLE_RUN} buildGhidra

.if (${DEV_UPDATE_MODE} == "yes")
post-build:
	cd ${GRADLE_HOME_BASE} && ${TAR} czf ${DISTDIR}/${DIST_SUBDIR}/${PORTNAME}-${DISTVERSION}-deps${EXTRACT_SUFX} gradle-${PORTNAME}
	@${ECHO} "(!!!) Please upload the Gradle deps archive: ${DISTDIR}/${DIST_SUBDIR}/${PORTNAME}-${DISTVERSION}-deps${EXTRACT_SUFX}"
	@${RM} -r ${GRADLE_HOME_BASE}/gradle-${PORTNAME}
.endif

do-install:
	@${UNZIP_CMD} -d ${STAGEDIR} ${WRKSRC}/build/dist/*.zip
	@${MV} ${STAGEDIR}/ghidra* ${STAGEDIR}${DATADIR}
	@${RLN} ${STAGEDIR}/${DATADIR}/ghidraRun ${STAGEDIR}${PREFIX}/bin/ghidra-cheri
	@${RLN} ${STAGEDIR}/${DATADIR}/server/ghidraSvr ${STAGEDIR}${PREFIX}/bin/ghidra-server-cheri
	@${RLN} ${STAGEDIR}/${DATADIR}/support/analyzeHeadless ${STAGEDIR}${PREFIX}/bin/ghidra-headless-cheri
	@${STRIP_CMD} ${STAGEDIR}/${DATADIR}/GPL/DemanglerGnu/os/freebsd_arm_64/demangler_gnu*
	@${STRIP_CMD} ${STAGEDIR}/${DATADIR}/Ghidra/Features/Decompiler/os/freebsd_arm_64/decompile
	@${STRIP_CMD} ${STAGEDIR}/${DATADIR}/Ghidra/Features/Decompiler/os/freebsd_arm_64/sleigh

post-install:
	@${FIND} ${STAGEDIR} ! -type d | \
		${SED} 's,${STAGEDIR}${PREFIX}/,,' >> ${TMPPLIST}
	@${FIND} -ds ${STAGEDIR}${DATADIR} -type d -empty | \
		${SED} 's,${STAGEDIR}${PREFIX}/,, ; s,^,@dir ,' >> ${TMPPLIST}

.include <bsd.port.post.mk>
