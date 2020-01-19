
aux_source_directory(../Common/src COMMON_LIB)
aux_source_directory(src CRF_LIB)
aux_source_directory(zhajinhua/src ZJH_LIB)
aux_source_directory(holdem HOLDEM_LIB)

add_library(cfr_kuhn_deps ${COMMON_LIB} ${CRF_LIB})
add_library(zjh_deps ${COMMON_LIB} ${ZJH_LIB})
add_library(holdem_deps ${COMMON_LIB} ${HOLDEM_LIB})

