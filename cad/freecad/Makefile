PORTNAME=	FreeCAD
DISTVERSION=	0.20.2
PORTREVISION=	5
# use these for bugfixes/snapshots
# DISTVERSION=	0.18-16093 # git rev-list --count
# DISTVERSIONSUFFIX=	-g690774c0e
CATEGORIES=	cad

MAINTAINER=	cmt@FreeBSD.org
COMMENT=	General purpose 3D CAD modeller
WWW=		https://www.freecadweb.org/

LICENSE=	LGPL20+
LICENSE_FILE=	${WRKSRC}/LICENSE

BUILD_DEPENDS=	pyside_tool.py:devel/pyside2-tools@${PY_FLAVOR} \
		${PYTHON_SITELIBDIR}/matplotlib/__init__.py:math/py-matplotlib@${PY_FLAVOR} \
		swig:devel/swig
LIB_DEPENDS=	libexpat.so:textproc/expat2 \
		libfreetype.so:print/freetype2 \
		${PY_BOOST} \
		libpyside2.cpython-${PYTHON_SUFFIX}${PYTHON_ABIVER}.so:devel/pyside2@${PY_FLAVOR} \
		libCoin.so:graphics/Coin \
		libpng.so:graphics/png \
		libtiff.so:graphics/tiff \
		libvtksys-${VTK_VER}.so:math/vtk${VTK_VER:R} \
		libTKernel.so:cad/opencascade \
		libxerces-c.so:textproc/xerces-c3 \
		libboost_thread.so:devel/boost-libs \
		libarea.so:devel/libarea \
		libmed.so:french/med \
		libshiboken2.cpython-${PYTHON_SUFFIX}${PYTHON_ABIVER}.so:devel/shiboken2@${PY_FLAVOR} \
		libhdf5-110.so:science/hdf5-110

RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}pivy>0:graphics/py-pivy@${PY_FLAVOR} \
		${PYTHON_SITELIBDIR}/matplotlib/__init__.py:math/py-matplotlib@${PY_FLAVOR}

USES=		dos2unix compiler:c++17-lang cmake cpe gl eigen:3 fortran jpeg \
		localbase:ldflags mpi:openmpi pkgconfig python localbase qt:5 xorg \
		desktop-file-utils shared-mime-info shebangfix
USE_GITHUB=	yes
USE_XORG=	ice sm x11 xext xt
USE_GL=		gl glu
USE_QT=		buildtools concurrent core declarative gui location network \
		opengl printsupport qmake:build svg webchannel widgets xml \
		xmlpatterns
USE_LDCONFIG=	yes

CPE_VENDOR=	freecad_project

VTK_VER=	9.2

DOS2UNIX_GLOB=	*.txt *.h *.cpp *.py *.qss *.csv *.pov *.stp *.ui *.wrl *.WRL
SHEBANG_FILES=	src/Tools/freecad-thumbnailer

CMAKE_ARGS+=	-DOCC_INCLUDE_DIR="${LOCALBASE}/include/OpenCASCADE" \
		-DOPENMPI_INCLUDE_DIRS="${LOCALBASE}/mpi/openmpi/include" \
		-DBUILD_QT5="ON" \
		-DPYTHON_LIBRARY="${PYTHONBASE}/lib/libpython${PYTHON_VER}${PYTHON_ABIVER}.so" \
		-DPYTHON_INCLUDE_DIR="${PYTHON_INCLUDEDIR}" \
		-DPYTHON_PACKAGES_PATH="${PYTHON_SITELIBDIR}" \
		-DPYTHON_EXECUTABLE="${PYTHON_CMD}" \
		-DBUILD_ASSEMBLY="OFF" -DBUILD_FLAT_MESH="ON" \
		-DHDF5_CFLAGS="-I${LOCALBASE}/include/hdf5-110" \
		-DHDF5_FOUND=TRUE \
		-DHDF5_INCLUDE_DIRS="${LOCALBASE}/include/hdf5-110" \
		-DHDF5_LIBRARIES="-L${LOCALBASE}/lib -lhdf5-110" \
		-DHDF5_LIBRARY_DIRS="${LOCALBASE}/lib" \
		-DPYSIDE2RCCBINARY="${RCC}" \
		-DPYSIDE2UICBINARY="${UIC}" \
		-DBUILD_ENABLE_CXX_STD=C++17

CMAKE_INSTALL_PREFIX=	${PREFIX}/${PORTNAME}
# Install XDG icons and files to the standard path
CMAKE_ARGS+=	-DXDG_DATADIR="${PREFIX}/share"

OPTIONS_DEFINE=	COLLADA

COLLADA_DESC=		Install pycollada for Collada files import
COLLADA_RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}pycollada>0:graphics/py-pycollada@${PY_FLAVOR}

.include <bsd.port.options.mk>

.if ${ARCH} == aarch64 || ${ARCH} == amd64 || ${ARCH} == i386
USE_QT+=	webengine
.else
USE_QT+=	webkit
.endif

post-patch:
	@${REINPLACE_CMD} -e '/self\.rev/s/Unknown/${DISTVERSION:C/.*-//}/' \
		${WRKSRC}/src/Tools/SubWCRev.py
# Install XDG icons and files to the standard path
	@${REINPLACE_CMD} -e 's/CMAKE_INSTALL_DATAROOTDIR/XDG_DATADIR/g' \
		${WRKSRC}/src/XDGData/CMakeLists.txt \
		${WRKSRC}/src/Gui/CMakeLists.txt

post-install:
	${LN} -s ../${PORTNAME}/bin/FreeCAD ${STAGEDIR}${LOCALBASE}/bin/FreeCAD
	${LN} -s ../${PORTNAME}/bin/FreeCADCmd ${STAGEDIR}${LOCALBASE}/bin/FreeCADCmd
	${INSTALL_SCRIPT} ${WRKSRC}/src/Tools/freecad-thumbnailer \
		${STAGEDIR}${PREFIX}/bin/freecad-thumbnailer

.include <bsd.port.mk>
