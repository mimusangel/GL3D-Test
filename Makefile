NAME = ColorRunner
SRC = main.cpp\
	Core/Core.cpp\
	Core/Timer.cpp\
	Core/Mesh.cpp\
	Core/Shader.cpp\
	Core/Vec2f.cpp\
	Core/AWidget.cpp\
	\
	Game/Loader.cpp\
	Game/Renderer.cpp\
	Game/SceneMain.cpp


ifeq ($(OS),Windows_NT)
INCS := -I.\win\include
LIBS := -L.\win\lib -lglfw3 -lglew32 -lopengl32 -lglu32 -lgdi32 
else
INCS := -I ~/.brew/include
LIBS := -lm -framework OPENGL \
	`~/.brew/bin/pkg-config --static --libs glfw3` \
	`~/.brew/bin/pkg-config --static --libs glew` 
endif
#------------------------------------------------------------------------------#

CXX = g++
ifeq ($(OS),Windows_NT)
RM = del
MAKE = make --no-print-directory
else
RM = /bin/rm -f
MAKE = mingw32-make --no-print-directory
endif

ifeq ($(OS),Windows_NT)
NAME := $(addsuffix .exe, $(NAME))
endif

#------------------------------------------------------------------------------#

ifeq ($(OS),Windows_NT)
O_FILE = $(addprefix src\, $(SRC:.cpp=.o))
else
O_FILE = $(addprefix src/, $(SRC:.cpp=.o))
endif
.PHONY: all clean fclean re makedir

all: $(NAME)

src/%.o: src/%.cpp
	$(CXX) -c -o $@ $< $(INCS)

$(NAME): $(O_FILE)
	$(CXX) $(LIBS) -o $(NAME) $(O_FILE) $(INCS)

clean:
	$(RM) $(O_FILE)

fclean: clean
	$(RM) $(NAME)

re: fclean all

test:
	@echo $(NAME)
	@echo $(INCS)
	@echo $(LIBS)

os:
	@echo $(OS)