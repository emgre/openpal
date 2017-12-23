cmake_minimum_required (VERSION 3.8)

set(openpal_public_headers
    ./include/openpal/container/Array.h
    ./include/openpal/container/ArrayView.h
    ./include/openpal/container/Buffer.h
    ./include/openpal/container/HasLength.h
    ./include/openpal/container/LinkedList.h
    ./include/openpal/container/Option.h
    ./include/openpal/container/Pair.h
    ./include/openpal/container/Queue.h
    ./include/openpal/container/RingBuffer.h
    ./include/openpal/container/RSeq.h
    ./include/openpal/container/SequenceTypes.h
    ./include/openpal/container/StaticBuffer.h
    ./include/openpal/container/WSeq.h

    ./include/openpal/executor/IExecutor.h
    ./include/openpal/executor/IMonotonicTimeSource.h
    ./include/openpal/executor/ITimer.h
    ./include/openpal/executor/IUTCTimeSource.h
    ./include/openpal/executor/TimeDuration.h
    ./include/openpal/executor/TimerRef.h
    ./include/openpal/executor/Timestamp.h
    ./include/openpal/executor/UTCTimestamp.h

    ./include/openpal/logging/HexLogging.h
    ./include/openpal/logging/ILogHandler.h
    ./include/openpal/logging/Location.h
    ./include/openpal/logging/Logger.h
    ./include/openpal/logging/LogLevels.h
    ./include/openpal/logging/LogMacros.h
    ./include/openpal/logging/Strings.h

    ./include/openpal/serialization/BigEndian.h
    ./include/openpal/serialization/DoubleFloat.h
    ./include/openpal/serialization/EndianHelpers.h
    ./include/openpal/serialization/FloatByteOrder.h
    ./include/openpal/serialization/LittleEndian.h
    ./include/openpal/serialization/SerializationTemplates.h
    ./include/openpal/serialization/Serializer.h
    ./include/openpal/serialization/SingleFloat.h
    ./include/openpal/serialization/UInt48Type.h

    ./include/openpal/util/Comparisons.h
    ./include/openpal/util/Limits.h
    ./include/openpal/util/SequenceNum.h
    ./include/openpal/util/ToHex.h
    ./include/openpal/util/Uncopyable.h
)

set(openpal_src
    ./src/openpal/container/Buffer.cpp

    ./src/openpal/executor/TimeDuration.cpp
    ./src/openpal/executor/TimerRef.cpp
    ./src/openpal/executor/Timestamp.cpp

    ./src/openpal/logging/HexLogging.cpp

    ./src/openpal/serialization/DoubleFloat.cpp
    ./src/openpal/serialization/FloatByteOrder.cpp
    ./src/openpal/serialization/SingleFloat.cpp

    ./src/openpal/util/Limits.cpp
    ./src/openpal/util/ToHex.cpp
)

add_library(openpal ${openpal_public_headers} ${openpal_src})
target_compile_features(openpal PUBLIC cxx_std_11)
target_include_directories(openpal
    PUBLIC ./include
)