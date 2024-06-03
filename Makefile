# Makefile

# 컴파일러
CXX = g++
# 컴파일 옵션
CXXFLAGS = -g -Wall
# 링크 옵션
LDFLAGS = -lncurses
# 소스 파일들
SRC = main.cpp Game.cpp Display.cpp Input.cpp Snake.cpp Item.cpp Gate.cpp
# 오브젝트 파일들
OBJ = $(SRC:.cpp=.o)
# 실행 파일 이름
TARGET = snake_game

# 기본 규칙: 실행 파일 생성
all: $(TARGET)

# 실행 파일 규칙: 오브젝트 파일들을 링크
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# 오브젝트 파일 규칙: 소스 파일들을 컴파일
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 청소 규칙: 생성된 파일들 삭제
clean:
	rm -f $(OBJ) $(TARGET)

# 청소 후 재빌드 규칙
rebuild: clean all

