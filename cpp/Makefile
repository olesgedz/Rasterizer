# NAME = rt
# CC = clang++
# SRCS = main.cpp
# OBJS = $(patsubst %.cpp, %.o, $(SRCS))

# all: $(NAME)

# $(NAME):$(OBJS)
# 	$(CC) $(OBJS) -o $(NAME)

# %.o:%.cpp
# 	$(CC) $< -c  -o $@ 

SYSCONF_LINK = clang++
CPPFLAGS     = 
LDFLAGS      =  
LIBS         = -lm
DESTDIR = ./
TARGET  = renderer

OBJECTS := $(patsubst %.cpp,%.o,$(wildcard *.cpp))

all: $(DESTDIR)$(TARGET)

$(DESTDIR)$(TARGET): $(OBJECTS)
	$(SYSCONF_LINK) -g -Wall $(LDFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)

$(OBJECTS): %.o: %.cpp
	$(SYSCONF_LINK) -g -Wall $(CPPFLAGS) -c $(CFLAGS) $< -o $@

clean:
	-rm -f $(OBJECTS)
	-rm -f $(TARGET)
	-rm -f *.tga
