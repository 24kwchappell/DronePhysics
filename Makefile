CXX = clang++
CXXFLAGS = -std=c++26 -Werror -Wall -Wextra -g

TARGET = myprogram

SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	@clear
	@./$(TARGET)

clean:
	@clear
	@rm -f $(OBJS) $(TARGET)
