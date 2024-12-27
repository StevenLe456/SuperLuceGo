CXX := emcc
CXX_FLAGS := -sSIDE_MODULE=1
OPT_DEBUG := -O0 -g
OPT_RELEASE := -O3
LIB_DEBUG := ../godot-cpp/bin/web/libgodot-cpp.javascript.debug.wasm.a
LIB_RELEASE := ../godot-cpp/bin/web/libgodot-cpp.javascript.release.wasm.a
INCLUDE := -I../godot-cpp/include -I../godot-cpp/include/core -I../godot-cpp/include/gen -I../godot-cpp/godot-headers -Iinclude

SRCS := $(wildcard *.cpp)

debug-web : $(SRCS)
	$(CXX) -o ../bin/libgame-debug.wasm $(CXX_FLAGS) $(OPT_DEBUG) $^ $(LIB_DEBUG) $(INCLUDE)
	cp ../bin/libgame-debug.wasm ../../godot-project-src/lib

release-web : $(SRCS)
	$(CXX) -o ../bin/libgame-release.wasm $(CXX_FLAGS) $(OPT_RELEASE) $^ $(LIB_RELEASE) $(INCLUDE)
	cp ../bin/libgame-release.wasm ../../godot-project-src/lib

debug-linux : $(SRCS)
	clang++ -shared -fpic $(OPT_DEBUG) $^ ../godot-cpp/bin/linux/libgodot-cpp.linux.debug.64.a $(INCLUDE) -o ../bin/linux/libgame-debug.so
	cp ../bin/linux/libgame-debug.so ../../godot-project-src/lib/linux