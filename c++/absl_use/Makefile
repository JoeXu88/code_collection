TARGET=absl_test
INCLUDE=-I./ -I/mnt/e/Code/thirdparty/abseil-cpp/install_dir_lts_2020_02_25/include \
	-I/usr/local/include/boost_1_61_0/

LIBS=/mnt/e/Code/thirdparty/abseil-cpp/install_dir_lts_2020_02_25/lib64/libabsl_strings.a \
	/mnt/e/Code/thirdparty/abseil-cpp/install_dir_lts_2020_02_25/lib64/libabsl_raw_logging_internal.a \
	/mnt/e/Code/thirdparty/abseil-cpp/install_dir_lts_2020_02_25/lib64/libabsl_base.a \
	/mnt/e/Code/thirdparty/abseil-cpp/install_dir_lts_2020_02_25/lib64/libabsl_throw_delegate.a \
	/mnt/e/Code/thirdparty/abseil-cpp/install_dir_lts_2020_02_25/lib64/libabsl_int128.a \
	/mnt/e/Code/thirdparty/abseil-cpp/install_dir_lts_2020_02_25/lib64/libabsl_str_format_internal.a 

LIBS+=/mnt/e/Code/thirdparty/boost_1_61_0/stage/lib/libboost_thread.a

$TARGET:
	g++ $(INCLUDE) -o ${TARGET} main.cpp -std=c++11 $(LIBS)