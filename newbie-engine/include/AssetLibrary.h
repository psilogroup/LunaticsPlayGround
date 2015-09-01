#ifndef __ASSETLIBRARY__
#define __ASSETLIBRARY__

#include "Texture.h"
#include "BZK_List.h"
class AssetTexture
{
    public:
        std::string assetName;
        Texture *asset;
};

class AssetLibrary
{
    public:
        BZK_List<AssetTexture> Textures;
        Texture *AddTexture(std::string textureName)
        {
            int i = 0;

            for(i = 0; i < Textures.TotalItems();i++)
            {
                if (Textures[i].assetName == textureName)
                    return Textures[i].asset;
            }

            std::string _name = "storage/textures/"+textureName;
            Texture *tex = new Texture(_name.c_str());
            AssetTexture asset;
            asset.asset = tex;
            asset.assetName = textureName;
            Textures.Add(asset);
            return tex;
        };

        AssetLibrary()
        {


        };
};


#endif
