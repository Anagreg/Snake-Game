#include <iostream>
#include <random>

#include "SDL.h"
#include "Game.h"

int generateRandomNumber(int lowerBound, int upperBound) {
    std::random_device generator;
    std::mt19937 randomNumberEngine(generator());
    std::uniform_int_distribution<std::mt19937::result_type> distribution(lowerBound, upperBound);

    return distribution(randomNumberEngine);
}


Field::Field(std::size_t width, std::size_t height):width(width), height(height), grid(width* height, Block::empty) {}


Game::Game(std::size_t gridWidth, std::size_t gridHeight): field(gridWidth, gridHeight)
{
    SpawnApple();
}

const int& Game::GetScore() const
{
    return score;
}

const Snake& Game::GetSnake() const
{
    return snake;
}

Snake& Game::GetSnake()
{
    return snake;
}

const Apple& Game::GetApple() const
{
    return apple;
}

const Field& Game::GetField() const
{
    return field;
}

const int& Snake::GetSize() const
{
    return size;
}


void Game::SpawnApple()
{
    int lowerBound = 0;
    int upperBound = GRID_WIDTH * GRID_HEIGHT - 1;
    int randomPosition = generateRandomNumber(lowerBound, upperBound);

    while (field.grid[randomPosition] != Block::empty)
    {
        randomPosition = generateRandomNumber(lowerBound, upperBound);     
    }

    field.grid[randomPosition] = Block::food;
    apple.position.x = randomPosition / GRID_WIDTH;
    apple.position.y = randomPosition % GRID_WIDTH;
}


void Snake::GrowBody()
{
    growing ++;
}

void Snake::Slyther(Field& field) {
    if (!isAlive)
        return;

    switch (dir)
    {
    case Direction::up:
        pos.y -= speed;
        pos.x = floorf(pos.x);
        break;

    case Direction::down:
        pos.y += speed;
        pos.x = floorf(pos.x);
        break;

    case Direction::left:
        pos.x -= speed;
        pos.y = floorf(pos.y);
        break;

    case Direction::right:
        pos.x += speed;
        pos.y = floorf(pos.y);
        break;
    }

    //Check for out of bounds
    if (pos.x < 0 || pos.x > GRID_WIDTH
        || pos.y < 0 || pos.y > GRID_HEIGHT)
    {
        isAlive = false;
        return;
    }

    int new_x = static_cast<int>(pos.x);
    int new_y = static_cast<int>(pos.y);

    // Check if position of head has changed
    if (new_x != head.x || new_y != head.y)
    {
        last_dir = dir;

        // If snake is growing, make a new neck
        if (growing > 0)
        {
            size++;
            body.push_back(head);
            growing--;
            field.grid[head.x * GRID_WIDTH + head.y] = Block::body;
        }
        else
        {
            // Move the body
            Point_2D<std::size_t> free = head; 
            for (auto rit = body.rbegin(); rit != body.rend(); ++rit)
            {
                field.grid[free.x * GRID_WIDTH + free.y] = Block::body;
                std::swap(*rit, free);
            }

            field.grid[free.x * GRID_WIDTH + free.y] = Block::empty;
        }

    }

    head.x = new_x;
    head.y = new_y;
}

void Game::HeadCollision() {
    Block& next = field.grid[snake.head.x * GRID_WIDTH + snake.head.y];
    // Check for food
    if (next == Block::food)
    {
        score++;
        if (snake.speed < 0.5f) snake.speed += snake.speed * 0.1f;
        SpawnApple();
        snake.GrowBody();
    }
    // Check for collisions
    else if (next == Block::body)
    {
        snake.isAlive = false;
    }

    next = Block::head;
}

void Game::Update()
{
    snake.Slyther(field);
    HeadCollision();   
}




