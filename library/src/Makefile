CC := em++
CXX := emcc
CPPFLAGS := 
CXX_FLAGS := -sSIDE_MODULE=1
OPT_DEBUG := -O0
OPT_RELEASE := -O3
LIB_DEBUG := ../godot-cpp/bin/libgodot-cpp.javascript.debug.wasm.a
LIB_RELEASE := ../godot-cpp/bin/libgodot-cpp.javascript.release.wasm.a
INCLUDE := -I../godot-cpp/include -I../godot-cpp/include/core -I../godot-cpp/include/gen -I../godot-cpp/godot-headers -Iinclude

SRCS := $(wildcard *.cpp)

debug : $(SRCS)
	$(CXX) -o ../bin/libgame-debug.wasm $(CXX_FLAGS) $(OPT_DEBUG) $^ $(LIB_DEBUG) $(INCLUDE)
	cp ../bin/libgame-debug.wasm ../../godot-project-src/lib

release : %.o
	$(CXX) -o ../bin/libgame-release.wasm $(CXX_FLAGS) $(OPT_RELEASE) $< $(LIB_RELEASE) $(INCLUDE)
	cp ../bin/libgame-release.wasm ../../godot-project-src/lib