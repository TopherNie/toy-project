
aux_source_directory(../Common/src COMMON_LIB)
aux_source_directory(src CRF_LIB)
aux_source_directory(zhajinhua/src ZJH_LIB)

add_library(cfr_kuhn_deps ${COMMON_LIB} ${CRF_LIB} zhajinhua/include/tree.h zhajinhua/include/round.h)
add_library(zjh_deps ${COMMON_LIB} ${ZJH_LIB} zhajinhua/src/player.cpp)

