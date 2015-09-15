#pragma once

class Renderer {
public:
    Renderer();
    virtual ~Renderer();

    virtual void init() = 0;
    virtual void render() = 0;
};
