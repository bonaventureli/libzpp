TARGET = libzpp
SOURCES = $(wildcard *.cpp)
DEPS = $(addsuffix .d, $(basename $(SOURCES)))
OBJECTS = $(addsuffix .o, $(basename $(SOURCES)))

# Set to 1 for debug build
DEBUG = 1

CXX = g++
CPPFLAGS = -MMD -MP
CXXFLAGS = -Wall -fPIC
LIBS = -lz

ifeq ($(DEBUG), 1)
	CPPFLAGS += -DDEBUG
	CXXFLAGS += -g
else
	CXXFLAGS += -O3
endif

$(TARGET).so: $(OBJECTS)
	$(CXX) -shared -Wl,--no-undefined $(CXXFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	@echo " Building file: $<"
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -rf $(DEPS) $(OBJECTS) $(addprefix $(TARGET), .so)

# Include automatically generated dependencies
-include $(DEPS)
