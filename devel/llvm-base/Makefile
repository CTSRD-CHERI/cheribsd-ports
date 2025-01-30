PORTNAME=	llvm
PORTVERSION=	20240315
CATEGORIES=	devel lang
MASTER_SITES=	# not applicable
DISTFILES=	# not applicable
PKGNAMESUFFIX=	-${FLAVOR}

MAINTAINER=	brooks@FreeBSD.org
COMMENT=	Install symlinks for llvm toolchain in ${PREFIX}

FLAVORS=	base localbase
FLAVOR?=	${FLAVORS:[1]}

RUN_DEPENDS=	${LOCALBASE}/bin/clang:devel/llvm

.if ${FLAVOR:Mlocalbase}
CONFLICTS_INSTALL=	binutils
.endif

.if ${FLAVOR:Mbase}
PREFIX=		/usr
.endif

NO_ARCH=	yes
NO_BUILD=	yes

COMMAND_PAIRS= \
	cc clang \
	c++ clang++ \
	cpp clang-cpp \
	ld ld.lld \
	objdump llvm-objdump
.if ${FLAVOR:Mbase}
# Also link in the LLVM names for the base flavor
COMMAND_LINKS=	clang clang++ clang-cpp ld.lld
.endif
COMMANDS=${COMMAND_LINKS}
.for c t in ${COMMAND_PAIRS}
COMMANDS+= ${c}
.endfor

PLIST_FILES=	${COMMANDS:S|^|bin/|}

.include <bsd.port.pre.mk>

do-install:
.for c t in ${COMMAND_PAIRS}
	${LN} -s ${LOCALBASE}/bin/${t} ${STAGEDIR}${PREFIX}/bin/${c}
.endfor
.for c in ${COMMAND_LINKS}
	${LN} -s ${LOCALBASE}/bin/${c} ${STAGEDIR}${PREFIX}/bin/${c}
.endfor

.include <bsd.port.mk>
