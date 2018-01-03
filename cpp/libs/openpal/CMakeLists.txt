cmake_minimum_required (VERSION 3.8)

set(openpal_public_headers
    ./include/openpal/container/Buffer.h
    ./include/openpal/container/HasLength.h    
    ./include/openpal/container/RSeq.h
    ./include/openpal/container/SequenceTypes.h
    ./include/openpal/container/StaticBuffer.h
    ./include/openpal/container/WSeq.h

    ./include/openpal/executor/IExecutor.h
    ./include/openpal/executor/ISteadyTimeSource.h
    ./include/openpal/executor/ITimer.h	
    ./include/openpal/executor/Timer.h
    ./include/openpal/executor/Typedefs.h
	
	./include/openpal/mock/HexConversions.h
	./include/openpal/mock/MockExecutor.h	

    ./include/openpal/serialization/BigEndian.h
    ./include/openpal/serialization/DoubleFloat.h
    ./include/openpal/serialization/EndianHelpers.h
    ./include/openpal/serialization/FloatByteOrder.h
    ./include/openpal/serialization/LittleEndian.h
    ./include/openpal/serialization/SerializationTemplates.h    
    ./include/openpal/serialization/SingleFloat.h
    ./include/openpal/serialization/UInt48Type.h

    ./include/openpal/util/Comparisons.h           
    ./include/openpal/util/Uncopyable.h
)

set(openpal_src    		
	./src/openpal/mock/HexConversions.cpp	

    ./src/openpal/serialization/DoubleFloat.cpp
    ./src/openpal/serialization/FloatByteOrder.cpp
    ./src/openpal/serialization/SingleFloat.cpp       
)

# append asio components in case we want to make this optional in the future
set(openpal_public_headers
    ${openpal_public_headers}
	./include/openpal/executor/asio/StrandExecutor.h
	./include/openpal/executor/asio/ThreadPool.h
)

set(openpal_src 
    ${openpal_src}
	./src/openpal/executor/asio/ASIOTimer.h
    ./src/openpal/executor/asio/StrandExecutor.cpp
	./src/openpal/executor/asio/ThreadPool.cpp
)

add_library(openpal ${openpal_public_headers} ${openpal_src})
target_compile_features(openpal PUBLIC cxx_std_14)
target_include_directories(openpal PUBLIC ./include)

# this could be optional too
target_include_directories(openpal PUBLIC ${CMAKE_SOURCE_DIR}/deps/asio/asio/include)
target_compile_definitions(openpal PUBLIC -DASIO_STANDALONE -DASIO_HAS_STD_SYSTEM_ERROR)
if(WIN32)
    target_compile_definitions(openpal PUBLIC -D_WIN32_WINNT=0x0501)
endif()