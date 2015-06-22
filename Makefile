TARGET = libzpp
SOURCES = $(wildcard *.cpp)
DEPS = $(addsuffix .d, $(basename $(SOURCES)))
OBJECTS = $(addsuffix .o, $(basename $(SOURCES)))
PREFIX = /usr/local

# Set to 1 for debug build
DEBUG = 0

CXX = g++
CPPFLAGS = -MMD -MP
CXXFLAGS = -Wall -fPIC
LIBS = -lz

INSTALL_HEADERS = zpp.h zpplib.h zreader.h izstream.h

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

install:
	install -m 0644 $(INSTALL_HEADERS) $(PREFIX)/include
	install $(TARGET).so $(PREFIX)/lib

uninstall: zpp.h
	rm -rf $(addprefix $(PREFIX)/include/, $(INSTALL_HEADERS))
	rm -rf $(PREFIX)/lib/$(TARGET).so

clean:
	rm -rf $(DEPS) $(OBJECTS) $(addprefix $(TARGET), .so)

# Include automatically generated dependencies
-include $(DEPS)
