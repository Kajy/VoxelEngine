#include "UZipPack.h"

UZipPack::UZipPack() {
}

UZipPack::~UZipPack() {
}

void createDirectory(std::string pathCache) {
#ifdef _WIN32
    mkdir(pathCache.c_str());
#endif
#ifdef __linux__
    pathCache = "mkdir " + pathCache;
    system(pathCache.c_str());
#endif
#ifdef __APPLE__
    pathCache = "mkdir " + pathCache;
    system(pathCache.c_str());
#endif
}

bool exists_file(const std::string &name) {

    bool toReturn = false;
    std::ifstream f(name.c_str());
    toReturn = f.good();
    if (toReturn) {
        f.close();
    }
    return toReturn;
}

std::string
exportTexture(std::istream *decompressTexture, std::string textureName, std::string pluginName, std::string path) {


    std::string pathTextureExport = path + "/Ressources/cacheTexture/" + pluginName + "/" + textureName + ".png";
    //std::cout << "Exporting in : " << pathTextureExport << std::endl;

    std::ofstream textureFile;

    if (!(exists_file(pathTextureExport))) {
        textureFile.exceptions(std::ios::failbit | std::ios::badbit);
        try {
            textureFile.open(pathTextureExport.c_str(), std::ios::out | std::ios::binary | std::ios::trunc);
            while ((textureFile << decompressTexture->rdbuf()))
                textureFile.close();
        }
        catch (std::ios::failure err) {
            //std::cout << "Error opening file" << std::endl;
        }
        //std::cout << "Export done !" << std::endl;
    }
    return (pathTextureExport);
}

ZipArchiveEntry::Ptr getTextureEntry(nlohmann::json jsonMaterial, ZipArchive::Ptr archive, std::string pluginName,
                                     std::string *fileTextureName, const char *side) {

    std::string pathTexture;

    try {
        std::string tmp = jsonMaterial["states"][0]["elements"][0]["faces"][side]["texture"];
        pathTexture = "textures/" + pluginName + "/" + tmp + ".png";
        ZipArchiveEntry::Ptr entryTexture = archive->GetEntry(pathTexture);

        *fileTextureName = tmp.substr(tmp.find('/') + 1, tmp.size());

        if (entryTexture != nullptr) {
            //std::cout << "FOUND [" << side << "] Texture" << std::endl;
            return entryTexture;
        }
    }
    catch (nlohmann::json::exception const &err) {
        return nullptr;
    }


}

void UZipPack::setTexturePack(const char *filePath, World *world, Ucraft::GUI *gui, const char *path) {

    createDirectory(std::string(path) + "/Ressources/cacheTexture");
    std::string pathTexturePack = path;

    pathTexturePack += filePath;

    ZipArchive::Ptr archive = ZipFile::Open(pathTexturePack);

    size_t test = archive->GetEntriesCount();

    ZipArchiveEntry::Ptr entry = archive->GetEntry("materials.json");

    std::istream *decompressStream = entry->GetDecompressionStream();

    nlohmann::json jsonFile;

    jsonFile << *decompressStream;

    for (int i = 0; i < jsonFile["materials"].size(); ++i) {
        //nlohmann::json jsonMaterial;
        std::string pluginName, pathTexture, pathMaterial;
        std::istream *decompressMaterial, *decompressTexture;

        std::string pathFormated = jsonFile["materials"][i]["stringId"];
        pluginName = pathFormated.substr(0, pathFormated.find(':'));

        createDirectory(std::string(path) + "/Ressources/cacheTexture/" + pluginName);
        gui->addPlugin(pluginName);

        pathFormated.replace(pathFormated.find(':'), 1, "/blocks/");
        pathMaterial = "models/" + pathFormated + ".json";

        //std::cout << "MATERIAL : " << pathMaterial << std::endl;
        ZipArchiveEntry::Ptr entryMaterial = archive->GetEntry(pathMaterial);

        if (entryMaterial != NULL) {// && entryTexture != NULL) {
            decompressMaterial = entryMaterial->GetDecompressionStream();

            int shortId = jsonFile["materials"][i]["shortId"];
            world->getCubeFactory()->addCube(shortId);

            std::string fileTextureName, pathExportedTexture;
            pathExportedTexture = path + std::string("/Ressources/Textures/fallback.png");
            world->getCubeFactory()->getCubeContainer()->at(shortId)->addTexture(pathExportedTexture);

            nlohmann::json jsonMaterial;
            jsonMaterial << *decompressMaterial;

            ZipArchiveEntry::Ptr all = getTextureEntry(jsonMaterial, archive, pluginName, &fileTextureName, "all");
            if (all != nullptr) {
                std::cout << "Texture name : " << fileTextureName << ".png" << std::endl;
                pathExportedTexture = exportTexture(all->GetDecompressionStream(), fileTextureName, pluginName, path);
                int idx = world->getCubeFactory()->getCubeContainer()->at(shortId)->addTexture(pathExportedTexture);
                world->getCubeFactory()->getCubeContainer()->at(shortId)->setDownIdx(idx);
                world->getCubeFactory()->getCubeContainer()->at(shortId)->setUpIdx(idx);
                world->getCubeFactory()->getCubeContainer()->at(shortId)->setLeftIdx(idx);
                world->getCubeFactory()->getCubeContainer()->at(shortId)->setRightIdx(idx);
                world->getCubeFactory()->getCubeContainer()->at(shortId)->setRearIdx(idx);
                world->getCubeFactory()->getCubeContainer()->at(shortId)->setFrontIdx(idx);
                gui->addBlock(pluginName, world->getCubeFactory()->getCubeContainer()->at(
                        shortId)->getTextures()[idx].getPathTexture(), shortId);
            }
            ZipArchiveEntry::Ptr side = getTextureEntry(jsonMaterial, archive, pluginName, &fileTextureName, "side");
            if (side != nullptr) {
                //std::cout << "Texture name : " << fileTextureName <<  ".png" << std::endl;
                pathExportedTexture = exportTexture(side->GetDecompressionStream(), fileTextureName, pluginName, path);
                int idx = world->getCubeFactory()->getCubeContainer()->at(shortId)->addTexture(pathExportedTexture);
                world->getCubeFactory()->getCubeContainer()->at(shortId)->setLeftIdx(idx);
                world->getCubeFactory()->getCubeContainer()->at(shortId)->setRightIdx(idx);
                world->getCubeFactory()->getCubeContainer()->at(shortId)->setRearIdx(idx);
                world->getCubeFactory()->getCubeContainer()->at(shortId)->setFrontIdx(idx);
                //world->getCubeFactory()->getCubeContainer()->at(shortId)->getTextures()[idx].getPathTexture()
                if (all == nullptr)
                    gui->addBlock(pluginName, world->getCubeFactory()->getCubeContainer()->at(
                            shortId)->getTextures()[idx].getPathTexture(), shortId);
            }
            ZipArchiveEntry::Ptr end = getTextureEntry(jsonMaterial, archive, pluginName, &fileTextureName, "end");
            if (end != nullptr) {
                //std::cout << "Texture name : " << fileTextureName <<  ".png" << std::endl;
                pathExportedTexture = exportTexture(end->GetDecompressionStream(), fileTextureName, pluginName, path);
                int idx = world->getCubeFactory()->getCubeContainer()->at(shortId)->addTexture(pathExportedTexture);
                world->getCubeFactory()->getCubeContainer()->at(shortId)->setDownIdx(idx);
                world->getCubeFactory()->getCubeContainer()->at(shortId)->setUpIdx(idx);
                if (all == nullptr && side == nullptr)
                    gui->addBlock(pluginName, world->getCubeFactory()->getCubeContainer()->at(
                            shortId)->getTextures()[idx].getPathTexture(), shortId);
            }
            ZipArchiveEntry::Ptr up = getTextureEntry(jsonMaterial, archive, pluginName, &fileTextureName, "up");
            if (up != nullptr) {
                //std::cout << "Texture name : " << fileTextureName <<  ".png" << std::endl;
                pathExportedTexture = exportTexture(up->GetDecompressionStream(), fileTextureName, pluginName, path);
                int idx = world->getCubeFactory()->getCubeContainer()->at(shortId)->addTexture(pathExportedTexture);
                world->getCubeFactory()->getCubeContainer()->at(shortId)->setUpIdx(idx);
                if (all == nullptr && side == nullptr && end == nullptr)
                    gui->addBlock(pluginName, world->getCubeFactory()->getCubeContainer()->at(
                            shortId)->getTextures()[idx].getPathTexture(), shortId);
            }
            ZipArchiveEntry::Ptr down = getTextureEntry(jsonMaterial, archive, pluginName, &fileTextureName, "down");
            if (down != nullptr) {
                //std::cout << "Texture name : " << fileTextureName <<  ".png" << std::endl;
                pathExportedTexture = exportTexture(down->GetDecompressionStream(), fileTextureName, pluginName, path);
                int idx = world->getCubeFactory()->getCubeContainer()->at(shortId)->addTexture(pathExportedTexture);
                world->getCubeFactory()->getCubeContainer()->at(shortId)->setDownIdx(idx);
                if (all == nullptr && side == nullptr && end == nullptr)
                    gui->addBlock(pluginName, world->getCubeFactory()->getCubeContainer()->at(
                            shortId)->getTextures()[idx].getPathTexture(), shortId);
            }
        }
    }

}