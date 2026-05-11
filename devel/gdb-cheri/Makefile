PORTNAME?=	gdb-cheri
PORTVERSION?=	${GDB_RELEASE}.d${SNAPDATE}
PORTREVISION?=	1
CATEGORIES=	devel

USE_GITHUB=	yes
GH_ACCOUNT=	CTSRD-CHERI
GH_PROJECT=	gdb
GH_TAGNAME=	${GDB_COMMIT}

MAINTAINER=	konrad.witaszczyk@cl.cam.ac.uk
COMMENT?=	GNU Project Debugger with support for the Arm Morello and CHERI-RISC-V architectures
WWW=		https://github.com/CTSRD-CHERI/gdb

.ifndef SLAVE_PORT
NOT_FOR_ABIS=	purecap
NOT_FOR_ABIS_REASON_purecap=is not adapted for CheriABI yet

# Configure the Poudriere toolchain wrapper to build the port for hybrid.
CONFIGURE_ENV+=	MACHINE_ARCH_HYBRID=yes
MAKE_ENV+=	MACHINE_ARCH_HYBRID=yes
.endif

DATADIR?=	${PREFIX}/share/gdb

# devel/readline defines rl_completer_word_break_characters as const char *.
OPTIONS_DEFAULT+=BUNDLED_READLINE
OPTIONS_EXCLUDE+=PORT_READLINE

# There is no pure-capability Python yet. We must disable Python support for
# purecap because GDB links with Python libraries.
OPTIONS_EXCLUDE_purecap+=	PYTHON

SLAVE_PORT?=	${PORTNAME}
GDBDIR=		${.CURDIR}/../gdb
GDBCHERIDIR=	${.CURDIR}/../gdb-cheri
DESCR=		${GDBDIR}/pkg-descr
PLIST=		${GDBDIR}/pkg-plist
DISTINFO_FILE=	${GDBCHERIDIR}/distinfo
FILESDIR=	${GDBCHERIDIR}/files
PLIST_SUB+=	PYDISASSEMBLER="@comment "

# CTSRD-CHERI/gdb does not include gdb.1.
GDB1_SRC=	${FILESDIR}/gdb.1
# CTSRD-CHERI/gdb does include kgdb.1.
KGDB1_SRC=	${WRKSRC}/gdb/doc/kgdb.1

.include "${GDBCHERIDIR}/Makefile.snapshot"
.include "${GDBDIR}/Makefile"
