#pragma once

#include <iostream>
#include <iomanip>
#include <string>

#ifdef _WIN32
#include <direct.h>
#else
#include <syscall.h>
#endif

#include "ZipLib/ZipFile.h"
#include "GUI.hpp"
#include "World.h"
#include "nlohmann/json.hpp"

class UZipPack {
public:
    UZipPack();

    ~UZipPack();

    static void setTexturePack(const char *file, World *world, Ucraft::GUI *, const char *path);

private:

};