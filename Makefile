NAME = ColorRunner
SRC = main.cpp

ifeq ($(OS),Windows_NT)
INCS = 
LIBS = -lglfw3 -lglew32
else
INCS = -I ~/.brew/include
LIBS = -lm -framework OPENGL \
	`~/.brew/bin/pkg-config --static --libs glfw3` \
	`~/.brew/bin/pkg-config --static --libs glew`
endif
#------------------------------------------------------------------------------#

CXX = g++
ifeq ($(OS),Windows_NT)
RM = 
MAKE = make --no-print-directory
else
RM = /bin/rm -f
MAKE = mingw32-make --no-print-directory
endif

#------------------------------------------------------------------------------#

O_FILE = $(addprefix src/, $(SRC:.cpp=.o))

.PHONY: all clean fclean re makedir

all: $(NAME)

src/%.o: src/%.cpp
	$(CXX) -o $@ -c $< $(INCS)

$(NAME): $(O_FILE)
	$(CXX) $(LIBS) -o $(NAME) $(O_FILE) $(INCS)

clean:
	$(RM) $(O_FILE)

fclean: clean
	$(RM) $(NAME)

re: fclean all
