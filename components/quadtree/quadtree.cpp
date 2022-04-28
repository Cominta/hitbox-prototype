#include "quadtree.h"

Quadtree::Quadtree(sf::RenderWindow* window, int size, float x, float y, float width, float height)
    : window(window), size(size), x(x), y(y), width(width), height(height)
{
    this->boundary = new sf::RectangleShape(sf::Vector2f(this->width, this->height));
    this->boundary->setPosition(this->x, this->y);
    this->boundary->setOrigin(this->width / 2, this->height / 2);
    this->boundary->setFillColor(sf::Color::Transparent);
    this->boundary->setOutlineColor(sf::Color::White);
    this->boundary->setOutlineThickness(1.0f);

    this->divided = false;
}

Quadtree::~Quadtree()
{

}

void Quadtree::insert(Point* point)
{
    if (!((*point).x >= this->x - this->width / 2 && (*point).x <= this->x + this->width / 2 &&
        (*point).y >= this->y - this->height / 2 && (*point).y <= this->y + this->height / 2)) // AABB
    {
        return;
    }

    if (this->points.size() < this->size)
    {
        this->points.emplace_back(point);
    }

    else
    {
        if (!divided)
        {
            this->subdivide();
            this->divided = true;
        }

        this->lt->insert(point);
        this->rt->insert(point);
        this->rb->insert(point);
        this->lb->insert(point);
    }
}

void Quadtree::subdivide()
{
    int newWidth = this->width / 2;
    int newHeight = this->height / 2;

    this->lt = new Quadtree(this->window, 4, this->x - this->width / 4, this->height / 4, newWidth, newHeight);
    this->rt = new Quadtree(this->window, 4, this->x + this->width / 4, this->y - this->height / 4, newWidth, newHeight);
    this->rb = new Quadtree(this->window, 4, this->x + this->width / 4, this->y + this->height / 4, newWidth, newHeight);
    this->lb = new Quadtree(this->window, 4, this->x - this->width / 4, this->y + this->height / 4, newWidth, newHeight);
}

void Quadtree::update()
{

}

void Quadtree::render()
{
    this->window->draw(*this->boundary);

    for (auto &point : this->points)
    {
        point->render();
    }

    if (divided)
    {
        this->lt->render();
        this->rt->render();
        this->rb->render();
        this->lb->render();
    }
}