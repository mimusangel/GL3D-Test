g++ -c -o src/Core/*.o src/Core/*.cpp -I./build/include
g++ -c -o src/Core/UI/*.o src/Core/UI/*.cpp -I./build/include
g++ -c -o src/Core/Shader/*.o src/Core/Shader/*.cpp -I./build/include
g++ -c -o src/main.o src/main.cpp -I./build/include
g++ -o ColorRunner.out src/Core/UI/*.o src/Core/Shader/*.o src/Core/*.o src/Game/*.o -I./build/include -L./build/lib/ -lglfw3 -lglew32 -lopengl32 -lglu32 -lgdi32 -lm -std=c++11