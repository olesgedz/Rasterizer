# NAME = rt
# CC = clang++
# SRCS = main.cpp
# OBJS = $(patsubst %.cpp, %.o, $(SRCS))

# all: $(NAME)

# $(NAME):$(OBJS)
# 	$(CC) $(OBJS) -o $(NAME)

# %.o:%.cpp
# 	$(CC) $< -c  -o $@ 

SYSCONF_LINK = g++
CPPFLAGS     = 
LDFLAGS      =  
LIBS         = -lm
DESTDIR = ./
TARGET  = main

OBJECTS := $(patsubst %.cpp,%.o,$(wildcard *.cpp))

all: $(DESTDIR)$(TARGET)

$(DESTDIR)$(TARGET): $(OBJECTS)
	$(SYSCONF_LINK) -Wall $(LDFLAGS) -o $(DESTDIR)$(TARGET) $(OBJECTS) $(LIBS)

$(OBJECTS): %.o: %.cpp
	$(SYSCONF_LINK) -Wall $(CPPFLAGS) -c $(CFLAGS) $< -o $@

clean:
	-rm -f $(OBJECTS)
	-rm -f $(TARGET)
	-rm -f *.tga
