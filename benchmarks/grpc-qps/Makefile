PORTNAME=	grpc-qps
PORTVERSION=	1.54.2
DISTVERSIONPREFIX=	v
PORTEPOCH=	2
CATEGORIES=	benchmarks

MAINTAINER=	alfredo.mazzinghi@cl.cam.ac.uk
COMMENT=	HTTP/2-based RPC framework
WWW=		https://grpc.io/ \
		https://github.com/grpc/grpc

LICENSE=	BSD3CLAUSE
LICENSE_FILE=	${WRKSRC}/LICENSE

BUILD_DEPENDS=	${LOCALBASE}/include/xxhash.h:devel/xxhash
LIB_DEPENDS=	libabsl_base.so:devel/abseil \
		libbenchmark.so:devel/benchmark \
		libcares.so:dns/c-ares \
		libprotobuf.so:devel/protobuf \
		libre2.so:devel/re2 \
		libgrpc.so:devel/grpc

USES=		cmake compiler:c++17-lang cpe localbase:ldflags pkgconfig ssl python

USE_GITHUB=	yes
GH_ACCOUNT=grpc
GH_PROJECT=grpc
GH_TUPLE=	census-instrumentation:opencensus-proto:v0.4.1:census_instrumentation_opencensus_proto/third_party/opencensus-proto/src \
		cncf:xds:32f1caf:cncf_xds/third_party/xds \
		google:googletest:release-1.8.0-2911-g0e402173:grpc/third_party/googletest

CMAKE_ARGS=	-DCMAKE_CXX_STANDARD=17 \
		-DgRPC_ABSL_PROVIDER=package \
		-DgRPC_BENCHMARK_PROVIDER=package \
		-DgRPC_CARES_PROVIDER=package \
		-DgRPC_PROTOBUF_PROVIDER=package \
		-DgRPC_RE2_PROVIDER=package \
		-DgRPC_SSL_PROVIDER=package \
		-DgRPC_ZLIB_PROVIDER=package
CMAKE_OFF=	gRPC_BACKWARDS_COMPATIBILITY_MODE
CMAKE_ON=	BUILD_SHARED_LIBS gRPC_BUILD_CODEGEN gRPC_BUILD_GRPC_CPP_PLUGIN gRPC_BUILD_TESTS
USE_CSTD=	c11
USE_CXXSTD=	c++17
USE_LDCONFIG=	yes

PLIST_SUB=	SHLIB_MAJOR=${PORTVERSION:R} \
		SHLIB_MINOR=${PORTVERSION:E}

CONFLICTS_INSTALL=	grpc-qps[0-9][0-9][0-9]

EXTRA_PATCHES+=${.CURDIR}/../../devel/grpc/files/cheribsd.patch
EXTRA_PATCHES+=${.CURDIR}/../../devel/grpc/files/extra-patch-openssl

.include <bsd.port.pre.mk>

# Skip openssl.pc while using OpenSSL from base system on older FreeBSD versions which does not skip this file
.if ${SSL_DEFAULT} == base && !exists(/usr/libdata/pkgconfig/openssl.pc)
EXTRA_PATCHES+=	${PATCHDIR}/extra-patch-openssl
.endif

ALL_TARGET=	qps_worker qps_json_driver

post-patch:
# Clean up bundled libraries
	@${RM} -r ${WRKSRC}/third_party/abseil-cpp/
	@${RM} -r ${WRKSRC}/third_party/benchmark/
	@${RM} -r ${WRKSRC}/third_party/boringssl-with-bazel/
	@${RM} -r ${WRKSRC}/third_party/cares/
	@${RM} -r ${WRKSRC}/third_party/protobuf/
	@${RM} -r ${WRKSRC}/third_party/re2/
	@${RM} -r ${WRKSRC}/third_party/xxhash/
	@${RM} -r ${WRKSRC}/third_party/zlib/

post-build:
	${MKDIR} -p ${BUILD_WRKSRC}/qps_scenarios
	cd ${BUILD_WRKSRC}/qps_scenarios && \
		${PYTHON_CMD} ${WRKSRC}/tools/run_tests/performance/scenario_config_exporter.py \
			--export_scenarios -l c++ --category=all

QPSBIN=${STAGEDIR}${PREFIX}/bin
QPSSHARE=${STAGEDIR}${PREFIX}/share/${PORTNAME}
GRPC_CORE_SOVERSION=31.0.0
do-install:
	${MKDIR} -p ${QPSBIN}

	${INSTALL_PROGRAM} ${BUILD_WRKSRC}/qps_worker ${QPSBIN}/grpc_qps_worker
	${INSTALL_PROGRAM} ${BUILD_WRKSRC}/qps_json_driver ${QPSBIN}/grpc_qps_json_driver
	${INSTALL_SCRIPT} ${.CURDIR}/files/qps_port_server.sh ${QPSBIN}/grpc_qps_port_server

	${INSTALL_LIB} ${BUILD_WRKSRC}/libgrpc++_test_config.so.${PORTVERSION} ${STAGEDIR}${PREFIX}/lib
	${LN} -f -s libgrpc++_test_config.so.${PORTVERSION} ${STAGEDIR}${PREFIX}/lib/libgrpc++_test_config.so.${PORTVERSION:R}
	${LN} -f -s libgrpc++_test_config.so.${PORTVERSION} ${STAGEDIR}${PREFIX}/lib/libgrpc++_test_config.so

	${INSTALL_LIB} ${BUILD_WRKSRC}/libgrpc++_test_util.so.${PORTVERSION} ${STAGEDIR}${PREFIX}/lib
	${LN} -f -s libgrpc++_test_util.so.${PORTVERSION} ${STAGEDIR}${PREFIX}/lib/libgrpc++_test_util.so.${PORTVERSION:R}
	${LN} -f -s libgrpc++_test_util.so.${PORTVERSION} ${STAGEDIR}${PREFIX}/lib/libgrpc++_test_util.so

	${INSTALL_LIB} ${BUILD_WRKSRC}/libgrpc_test_util.so.${GRPC_CORE_SOVERSION} ${STAGEDIR}${PREFIX}/lib
	${LN} -f -s libgrpc_test_util.so.${GRPC_CORE_SOVERSION} ${STAGEDIR}${PREFIX}/lib/libgrpc_test_util.so.31
	${LN} -f -s libgrpc_test_util.so.${GRPC_CORE_SOVERSION} ${STAGEDIR}${PREFIX}/lib/libgrpc_test_util.so

	${MKDIR} -p ${QPSSHARE}/scenarios
	cd ${BUILD_WRKSRC}/qps_scenarios && ${COPYTREE_SHARE} . ${QPSSHARE}/scenarios

.include <bsd.port.post.mk>
