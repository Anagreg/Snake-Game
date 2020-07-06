#pragma once

#include <vector>
#include "SDL.h"
#include "global_consts.h"

template<class T>
struct Point_2D
{
    T x;
    T y;
};


enum class Block { head, body, food, empty };
enum class Direction { up, down, left, right };


struct Field
{
    std::size_t width;
    std::size_t height;
    std::vector<Block> grid;


    Field(std::size_t width, std::size_t height);    
};

struct Apple
{
    Point_2D<std::size_t> position{0, 0};
};

struct Snake
{
    int size = 1;
    float speed = 0.2f;
    int growing = 0;
    bool isAlive = true;
    
    Direction last_dir = Direction::up;
    Direction dir = Direction::up;
   
    Point_2D<float> pos{ GRID_WIDTH / 2, GRID_HEIGHT / 2 };
    Point_2D<std::size_t> head{ static_cast<std::size_t>(pos.x), static_cast<std::size_t>(pos.y) };
    std::vector<Point_2D<std::size_t>> body; 


    const int& GetSize() const;
    void GrowBody();
    void Slyther(Field& field);    
};

class Game
{
private:
    Field field;
    Apple apple;
    Snake snake;

    int score = 0;
public:
    bool running = true;  


private:
    void HeadCollision();
    void SpawnApple();
public:
    Game(std::size_t gridWidth, std::size_t gridHeight);
    const int& GetScore() const;
    const Snake& GetSnake() const;
    Snake& GetSnake();
    const Apple& GetApple() const;
    const Field& GetField() const;
    void Update();
};