#include "msdf-atlas-gen.h"
#include <locale>
#include <codecvt>
#include <string>
#include "SDFLoader.h"

//std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
//std::string narrow = converter.to_bytes(wide_utf16_source_string);
//std::wstring wide = converter.from_bytes(narrow_utf8_source_string);

//extern int outlineStrength;

static lua_State* _state_;

#define THREAD_COUNT 4

template<typename ... Args>
std::string string_format(const std::string& format, Args ... args)
{
    size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
    if (size <= 0) { throw std::runtime_error("Error during formatting."); }
    std::unique_ptr<char[]> buf(new char[size]);
    snprintf(buf.get(), size, format.c_str(), args ...);
    return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

using namespace msdf_atlas;

static std::string escapeJsonString(const char* str) {
    char uval[7] = "\\u0000";
    std::string outStr;
    while (*str) {
        switch (*str) {
        case '\\':
            outStr += "\\\\";
            break;
        case '"':
            outStr += "\\\"";
            break;
        case '\n':
            outStr += "\\n";
            break;
        case '\r':
            outStr += "\\r";
            break;
        case '\t':
            outStr += "\\t";
            break;
        case 0x00: case 0x01: case 0x02: case 0x03: case 0x04: case 0x05: case 0x06: case 0x07: case 0x08: /* \\t */  /* \\n */  case 0x0b: case 0x0c: /* \\r */  case 0x0e: case 0x0f:
        case 0x10: case 0x11: case 0x12: case 0x13: case 0x14: case 0x15: case 0x16: case 0x17: case 0x18: case 0x19: case 0x1a: case 0x1b: case 0x1c: case 0x1d: case 0x1e: case 0x1f:
            uval[4] = '0' + (*str >= 0x10);
            uval[5] = "0123456789abcdef"[*str & 0x0f];
            outStr += uval;
            break;
        default:
            outStr.push_back(*str);
        }
        ++str;
    }
    return outStr;
}

static const char* imageTypeString(ImageType type) {
    switch (type) {
    case ImageType::HARD_MASK:
        return "hardmask";
    case ImageType::SOFT_MASK:
        return "softmask";
    case ImageType::SDF:
        return "sdf";
    case ImageType::PSDF:
        return "psdf";
    case ImageType::MSDF:
        return "msdf";
    case ImageType::MTSDF:
        return "mtsdf";
    }
    return nullptr;
}

std::string generateJSON(const FontGeometry* fonts, int fontCount, double fontSize, double pxRange, int atlasWidth, int atlasHeight, ImageType imageType, bool kerning) {
    YDirection yDirection = YDirection::BOTTOM_UP;
    
    std::string s = "";
    s += "{";
    
    // Atlas properties
    s += "\"atlas\":{"; {
        s += string_format("\"type\":\"%s\",", imageTypeString(imageType));
        if (imageType == ImageType::SDF || imageType == ImageType::PSDF || imageType == ImageType::MSDF || imageType == ImageType::MTSDF)
            s += string_format("\"distanceRange\":%.17g,", pxRange);
        s += string_format("\"size\":%.17g,", fontSize);
        s += string_format("\"width\":%d,", atlasWidth);
        s += string_format("\"height\":%d,", atlasHeight);
        s += string_format("\"yOrigin\":\"%s\"", yDirection == YDirection::TOP_DOWN ? "top" : "bottom");
    } s += "},";

    if (fontCount > 1)
        s += "\"variants\":[";
    for (int i = 0; i < fontCount; ++i) {
        const FontGeometry& font = fonts[i];
        if (fontCount > 1)
           s += i == 0 ? "{" : ",{";

        // Font name
        const char* name = font.getName();
        if (name)
            s += string_format("\"name\":\"%s\",", escapeJsonString(name).c_str());

        // Font metrics
        s += "\"metrics\":{"; {
            double yFactor = yDirection == YDirection::TOP_DOWN ? -1 : 1;
            const msdfgen::FontMetrics& metrics = font.getMetrics();
            s += string_format("\"emSize\":%.17g,", metrics.emSize);
            s += string_format("\"lineHeight\":%.17g,", metrics.lineHeight);
            s += string_format("\"ascender\":%.17g,", yFactor * metrics.ascenderY);
            s += string_format("\"descender\":%.17g,", yFactor * metrics.descenderY);
            s += string_format("\"underlineY\":%.17g,", yFactor * metrics.underlineY);
            s += string_format("\"underlineThickness\":%.17g", metrics.underlineThickness);
        } s += "},";

        // Glyph mapping
        s += "\"glyphs\":[";
        bool firstGlyph = true;
        for (const GlyphGeometry& glyph : font.getGlyphs()) {
            s += firstGlyph ? "{" : ",{";
            switch (font.getPreferredIdentifierType()) {
            case GlyphIdentifierType::GLYPH_INDEX:
                s += string_format("\"index\":%d,", glyph.getIndex());
                break;
            case GlyphIdentifierType::UNICODE_CODEPOINT:
                s += string_format("\"unicode\":%u,", glyph.getCodepoint());
                break;
            }
            s += string_format("\"advance\":%.17g", glyph.getAdvance());
            double l, b, r, t;
            glyph.getQuadPlaneBounds(l, b, r, t);
            if (l || b || r || t) {
                switch (yDirection) {
                case YDirection::BOTTOM_UP:
                    s += string_format(",\"planeBounds\":{\"left\":%.17g,\"bottom\":%.17g,\"right\":%.17g,\"top\":%.17g}", l, b, r, t);
                    break;
                case YDirection::TOP_DOWN:
                    s += string_format(",\"planeBounds\":{\"left\":%.17g,\"top\":%.17g,\"right\":%.17g,\"bottom\":%.17g}", l, -t, r, -b);
                    break;
                }
            }
            glyph.getQuadAtlasBounds(l, b, r, t);
            if (l || b || r || t) {
                switch (yDirection) {
                case YDirection::BOTTOM_UP:
                    s += string_format(",\"atlasBounds\":{\"left\":%.17g,\"bottom\":%.17g,\"right\":%.17g,\"top\":%.17g}", l, b, r, t);
                    break;
                case YDirection::TOP_DOWN:
                    s += string_format(",\"atlasBounds\":{\"left\":%.17g,\"top\":%.17g,\"right\":%.17g,\"bottom\":%.17g}", l, atlasHeight - t, r, atlasHeight - b);
                    break;
                }
            }
            s += "}";
            firstGlyph = false;
        } s += "]";

        // Kerning pairs
        if (kerning) {
            s += ",\"kerning\":[";
            bool firstPair = true;
            switch (font.getPreferredIdentifierType()) {
            case GlyphIdentifierType::GLYPH_INDEX:
                for (const std::pair<std::pair<int, int>, double>& kernPair : font.getKerning()) {
                    s += firstPair ? "{" : ",{";
                    s += string_format("\"index1\":%d,", kernPair.first.first);
                    s += string_format("\"index2\":%d,", kernPair.first.second);
                    s += string_format("\"advance\":%.17g", kernPair.second);
                    s += "}";
                    firstPair = false;
                }
                break;
            case GlyphIdentifierType::UNICODE_CODEPOINT:
                for (const std::pair<std::pair<int, int>, double>& kernPair : font.getKerning()) {
                    const GlyphGeometry* glyph1 = font.getGlyph(msdfgen::GlyphIndex(kernPair.first.first));
                    const GlyphGeometry* glyph2 = font.getGlyph(msdfgen::GlyphIndex(kernPair.first.second));
                    if (glyph1 && glyph2 && glyph1->getCodepoint() && glyph2->getCodepoint()) {
                        s += firstPair ? "{" : ",{";
                        s += string_format("\"unicode1\":%u,", glyph1->getCodepoint());
                        s += string_format("\"unicode2\":%u,", glyph2->getCodepoint());
                        s += string_format("\"advance\":%.17g", kernPair.second);
                        s += "}";
                        firstPair = false;
                    }
                }
                break;
            } s += "]";
        }

        if (fontCount > 1)
            s += "}";
    }
    if (fontCount > 1)
        s += "]";

    s += "}\n";
    
    return s;
}

LuaIntf::LuaRef  generateSDF(lua_State* L, const char* fontFilename, const std::string charsetStr, double fontSize, double pxRange, int atlasWidth, int atlasHeight, TightAtlasPacker::DimensionsConstraint dimensionConstraint, ImageType imageType, bool kerning)
{
    bool success = false;
    // Initialize instance of FreeType library
    if (msdfgen::FreetypeHandle* ft = msdfgen::initializeFreetype()) {
        // Load font file
        if (msdfgen::FontHandle* font = msdfgen::loadFont(ft, fontFilename)) {
            // Storage for glyph geometry and their coordinates in the atlas
            std::vector<GlyphGeometry> glyphs;
            // FontGeometry is a helper class that loads a set of glyphs from a single font.
            // It can also be used to get additional font metrics, kerning information, etc.
            FontGeometry fontGeometry(&glyphs);
            // Load a set of character glyphs:
            // The second argument can be ignored unless you mix different font sizes in one atlas.
            // In the last argument, you can specify a charset other than ASCII.
            // To load specific glyph indices, use loadGlyphs instead.
            
            Charset charset;

            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
            std::wstring wide = converter.from_bytes(charsetStr);

            for (std::wstring::const_iterator i = wide.begin(); i != wide.end(); i++)
            {
                wchar_t code = *i;
                charset.add(code);
            }

            //const char* ASCII = "abcdefghi";
            //std::wstring Unicode(ASCII, ASCII + strlen(ASCII));
            fontGeometry.loadCharset(font, 1.0, charset);

            std::vector<FontGeometry> fontGeometryList;
            fontGeometryList.push_back(fontGeometry);

            // Apply MSDF edge coloring. See edge-coloring.h for other coloring strategies.
            const double maxCornerAngle = 3.0;
            for (GlyphGeometry& glyph : glyphs)
                glyph.edgeColoring(&msdfgen::edgeColoringInkTrap, maxCornerAngle, 0);
            // TightAtlasPacker class computes the layout of the atlas.
            TightAtlasPacker packer;
            // Set atlas parameters:
            // setDimensions or setDimensionsConstraint to find the best value
            if ((int)dimensionConstraint == -1)
            {
                packer.setDimensions(atlasWidth, atlasHeight);
            }
            else
            {
                packer.setDimensionsConstraint(dimensionConstraint);
            }
           
            // setScale for a fixed size or setMinimumScale to use the largest that fits
            //packer.setMinimumScale(24.0);
            packer.setScale(fontSize);
            // setPixelRange or setUnitRange
            packer.setPixelRange(pxRange);
            packer.setMiterLimit(1.0);
            // Compute atlas layout - pack glyphs
            packer.pack(glyphs.data(), glyphs.size());
            // Get final atlas dimensions
            int width = atlasWidth, height = atlasHeight;
            packer.getDimensions(width, height);

            std::string sdfJson = generateJSON(fontGeometryList.data(), fontGeometryList.size(), fontSize, pxRange, width, height, imageType, kerning);

            if (imageType == ImageType::SDF)
            {
                // The ImmediateAtlasGenerator class facilitates the generation of the atlas bitmap.
                ImmediateAtlasGenerator<
                    float, // pixel type of buffer for individual glyphs depends on generator function
                    1, // number of atlas color channels
                    &sdfGenerator, // function to generate bitmaps for individual glyphs
                    BitmapAtlasStorage<byte, 1> // class that stores the atlas bitmap
                    // For example, a custom atlas storage class that stores it in VRAM can be used.
                > generator(width, height);
                // GeneratorAttributes can be modified to change the generator's default settings.
                GeneratorAttributes attributes;
                generator.setAttributes(attributes);
                generator.setThreadCount(4);
                // Generate atlas bitmap
                generator.generate(glyphs.data(), glyphs.size());

                msdfgen::BitmapConstRef<byte, 1> buffer;
                buffer = generator.atlasStorage();

                // The atlas bitmap can now be retrieved via atlasStorage as a BitmapConstRef.
                // The glyphs array (or fontGeometry) contains positioning data for typesetting text.
                // success = myProject::submitAtlasBitmapAndLayout(generator.atlasStorage(), glyphs);
              
                std::string pixels(reinterpret_cast<const char*>(buffer.pixels), buffer.width * buffer.height);

                auto t = LuaIntf::LuaRef::createTable(L);
                t.set<int, std::string>(1, sdfJson);
                t.set<int, std::string>(2, pixels);
                t.set<int, int>(3, (int)imageType);
                t.set<int, int>(4, buffer.width);
                t.set<int, int>(5, buffer.height);

                // Cleanup
                msdfgen::destroyFont(font);
                msdfgen::deinitializeFreetype(ft);

                return t;
            }
            else if(imageType == ImageType::PSDF)
            {
                // The ImmediateAtlasGenerator class facilitates the generation of the atlas bitmap.
                ImmediateAtlasGenerator<
                    float, // pixel type of buffer for individual glyphs depends on generator function
                    1, // number of atlas color channels
                    &psdfGenerator, // function to generate bitmaps for individual glyphs
                    BitmapAtlasStorage<byte, 1> // class that stores the atlas bitmap
                    // For example, a custom atlas storage class that stores it in VRAM can be used.
                > generator(width, height);
                // GeneratorAttributes can be modified to change the generator's default settings.
                GeneratorAttributes attributes;
                generator.setAttributes(attributes);
                generator.setThreadCount(4);
                // Generate atlas bitmap
                generator.generate(glyphs.data(), glyphs.size());

                msdfgen::BitmapConstRef<byte, 1> buffer;
                buffer = generator.atlasStorage();

                //The atlas bitmap can now be retrieved via atlasStorage as a BitmapConstRef.
                //The glyphs array (or fontGeometry) contains positioning data for typesetting text.
                //success = myProject::submitAtlasBitmapAndLayout(generator.atlasStorage(), glyphs);
                
                std::string pixels(reinterpret_cast<const char*>(buffer.pixels), buffer.width * buffer.height);

                auto t = LuaIntf::LuaRef::createTable(L);
                t.set<int, std::string>(1, sdfJson);
                t.set<int, std::string>(2, pixels);
                t.set<int, int>(3, (int)imageType);
                t.set<int, int>(4, buffer.width);
                t.set<int, int>(5, buffer.height);

                 // Cleanup
                msdfgen::destroyFont(font);

                msdfgen::deinitializeFreetype(ft);

                return t;
            }
            else if (imageType == ImageType::MSDF)
            {
                // The ImmediateAtlasGenerator class facilitates the generation of the atlas bitmap.
                ImmediateAtlasGenerator<
                    float, // pixel type of buffer for individual glyphs depends on generator function
                    3, // number of atlas color channels
                    &msdfGenerator, // function to generate bitmaps for individual glyphs
                    BitmapAtlasStorage<byte, 3> // class that stores the atlas bitmap
                    // For example, a custom atlas storage class that stores it in VRAM can be used.
                > generator(width, height);
                // GeneratorAttributes can be modified to change the generator's default settings.
                GeneratorAttributes attributes;
                generator.setAttributes(attributes);
                generator.setThreadCount(4);
                // Generate atlas bitmap
                generator.generate(glyphs.data(), glyphs.size());

                msdfgen::BitmapConstRef<byte, 3> buffer;
                buffer = generator.atlasStorage();

                // The atlas bitmap can now be retrieved via atlasStorage as a BitmapConstRef.
                // The glyphs array (or fontGeometry) contains positioning data for typesetting text.
                // success = myProject::submitAtlasBitmapAndLayout(generator.atlasStorage(), glyphs);
                std::string pixels(reinterpret_cast<const char*>(buffer.pixels), buffer.width* buffer.height);

                auto t = LuaIntf::LuaRef::createTable(L);
                t.set<int, std::string>(1, sdfJson);
                t.set<int, std::string>(2, pixels);
                t.set<int, int>(3, (int)imageType);
                t.set<int, int>(4, buffer.width);
                t.set<int, int>(5, buffer.height);

                 // Cleanup
                msdfgen::destroyFont(font);

                msdfgen::deinitializeFreetype(ft);

                return t;
            }
            else if (imageType == ImageType::MTSDF)
            {
                // The ImmediateAtlasGenerator class facilitates the generation of the atlas bitmap.
                ImmediateAtlasGenerator<
                    float, // pixel type of buffer for individual glyphs depends on generator function
                    4, // number of atlas color channels
                    &mtsdfGenerator, // function to generate bitmaps for individual glyphs
                    BitmapAtlasStorage<byte, 4> // class that stores the atlas bitmap
                    // For example, a custom atlas storage class that stores it in VRAM can be used.
                > generator(width, height);
                // GeneratorAttributes can be modified to change the generator's default settings.
                GeneratorAttributes attributes;
                generator.setAttributes(attributes);
                generator.setThreadCount(4);
                // Generate atlas bitmap
                generator.generate(glyphs.data(), glyphs.size());

                msdfgen::BitmapConstRef<byte, 4> buffer;
                buffer = generator.atlasStorage();
                
                // The atlas bitmap can now be retrieved via atlasStorage as a BitmapConstRef.
                // The glyphs array (or fontGeometry) contains positioning data for typesetting text.
                //success = myProject::submitAtlasBitmapAndLayout(generator.atlasStorage(), glyphs);
                std::string pixels(reinterpret_cast<const char*>(buffer.pixels), buffer.width* buffer.height);

                auto t = LuaIntf::LuaRef::createTable(L);
                t.set<int, std::string>(1, sdfJson);
                t.set<int, std::string>(2, pixels);
                t.set<int, int>(3, (int)imageType);
                t.set<int, int>(4, buffer.width);
                t.set<int, int>(5, buffer.height);

                 // Cleanup
                msdfgen::destroyFont(font);

                msdfgen::deinitializeFreetype(ft);

                return t;
            }
        }
    }
}

LuaIntf::LuaRef  generateSDFBuffer(lua_State* L, const std::string fontBuffer, const std::string charsetStr, double fontSize, double pxRange, int atlasWidth, int atlasHeight, TightAtlasPacker::DimensionsConstraint dimensionConstraint, ImageType imageType, bool kerning)
{
    bool success = false;
    // Initialize instance of FreeType library
    if (msdfgen::FreetypeHandle* ft = msdfgen::initializeFreetype()) {
        // Load font file

        if (msdfgen::FontHandle* font = msdfgen::loadFontData(ft, reinterpret_cast<const msdfgen::byte*>(fontBuffer.data()), fontBuffer.length())) {
            // Storage for glyph geometry and their coordinates in the atlas
            std::vector<GlyphGeometry> glyphs;
            // FontGeometry is a helper class that loads a set of glyphs from a single font.
            // It can also be used to get additional font metrics, kerning information, etc.
            FontGeometry fontGeometry(&glyphs);
            // Load a set of character glyphs:
            // The second argument can be ignored unless you mix different font sizes in one atlas.
            // In the last argument, you can specify a charset other than ASCII.
            // To load specific glyph indices, use loadGlyphs instead.

            Charset charset;

            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
            std::wstring wide = converter.from_bytes(charsetStr);

            for (std::wstring::const_iterator i = wide.begin(); i != wide.end(); i++)
            {
                wchar_t code = *i;
                charset.add(code);
            }

            //const char* ASCII = "abcdefghi";
            //std::wstring Unicode(ASCII, ASCII + strlen(ASCII));
            fontGeometry.loadCharset(font, 1.0, charset);

            std::vector<FontGeometry> fontGeometryList;
            fontGeometryList.push_back(fontGeometry);

            // Apply MSDF edge coloring. See edge-coloring.h for other coloring strategies.
            const double maxCornerAngle = 3.0;
            for (GlyphGeometry& glyph : glyphs)
                glyph.edgeColoring(&msdfgen::edgeColoringInkTrap, maxCornerAngle, 0);
            // TightAtlasPacker class computes the layout of the atlas.
            TightAtlasPacker packer;
            // Set atlas parameters:
            // setDimensions or setDimensionsConstraint to find the best value
            if ((int)dimensionConstraint == -1)
            {
                packer.setDimensions(atlasWidth, atlasHeight);
            }
            else
            {
                packer.setDimensionsConstraint(dimensionConstraint);
            }

            // setScale for a fixed size or setMinimumScale to use the largest that fits
            //packer.setMinimumScale(24.0);
            packer.setScale(fontSize);
            // setPixelRange or setUnitRange
            packer.setPixelRange(pxRange);
            packer.setMiterLimit(1.0);
            // Compute atlas layout - pack glyphs
            packer.pack(glyphs.data(), glyphs.size());
            // Get final atlas dimensions
            int width = atlasWidth, height = atlasHeight;
            packer.getDimensions(width, height);

            std::string sdfJson = generateJSON(fontGeometryList.data(), fontGeometryList.size(), fontSize, pxRange, width, height, imageType, kerning);

            if (imageType == ImageType::SDF)
            {
                // The ImmediateAtlasGenerator class facilitates the generation of the atlas bitmap.
                ImmediateAtlasGenerator<
                    float, // pixel type of buffer for individual glyphs depends on generator function
                    1, // number of atlas color channels
                    &sdfGenerator, // function to generate bitmaps for individual glyphs
                    BitmapAtlasStorage<byte, 1> // class that stores the atlas bitmap
                    // For example, a custom atlas storage class that stores it in VRAM can be used.
                > generator(width, height);
                // GeneratorAttributes can be modified to change the generator's default settings.
                GeneratorAttributes attributes;
                generator.setAttributes(attributes);
                generator.setThreadCount(4);
                // Generate atlas bitmap
                generator.generate(glyphs.data(), glyphs.size());

                msdfgen::BitmapConstRef<byte, 1> buffer;
                buffer = generator.atlasStorage();

                // The atlas bitmap can now be retrieved via atlasStorage as a BitmapConstRef.
                // The glyphs array (or fontGeometry) contains positioning data for typesetting text.
                // success = myProject::submitAtlasBitmapAndLayout(generator.atlasStorage(), glyphs);

                std::string pixels(reinterpret_cast<const char*>(buffer.pixels), buffer.width * buffer.height);

                auto t = LuaIntf::LuaRef::createTable(L);
                t.set<int, std::string>(1, sdfJson);
                t.set<int, std::string>(2, pixels);
                t.set<int, int>(3, (int)imageType);
                t.set<int, int>(4, buffer.width);
                t.set<int, int>(5, buffer.height);

                // Cleanup
                msdfgen::destroyFont(font);
                msdfgen::deinitializeFreetype(ft);

                return t;
            }
            else if (imageType == ImageType::PSDF)
            {
                // The ImmediateAtlasGenerator class facilitates the generation of the atlas bitmap.
                ImmediateAtlasGenerator<
                    float, // pixel type of buffer for individual glyphs depends on generator function
                    1, // number of atlas color channels
                    &psdfGenerator, // function to generate bitmaps for individual glyphs
                    BitmapAtlasStorage<byte, 1> // class that stores the atlas bitmap
                    // For example, a custom atlas storage class that stores it in VRAM can be used.
                > generator(width, height);
                // GeneratorAttributes can be modified to change the generator's default settings.
                GeneratorAttributes attributes;
                generator.setAttributes(attributes);
                generator.setThreadCount(4);
                // Generate atlas bitmap
                generator.generate(glyphs.data(), glyphs.size());

                msdfgen::BitmapConstRef<byte, 1> buffer;
                buffer = generator.atlasStorage();

                //The atlas bitmap can now be retrieved via atlasStorage as a BitmapConstRef.
                //The glyphs array (or fontGeometry) contains positioning data for typesetting text.
                //success = myProject::submitAtlasBitmapAndLayout(generator.atlasStorage(), glyphs);

                std::string pixels(reinterpret_cast<const char*>(buffer.pixels), buffer.width * buffer.height);

                auto t = LuaIntf::LuaRef::createTable(L);
                t.set<int, std::string>(1, sdfJson);
                t.set<int, std::string>(2, pixels);
                t.set<int, int>(3, (int)imageType);
                t.set<int, int>(4, buffer.width);
                t.set<int, int>(5, buffer.height);

                // Cleanup
                msdfgen::destroyFont(font);

                msdfgen::deinitializeFreetype(ft);

                return t;
            }
            else if (imageType == ImageType::MSDF)
            {
                // The ImmediateAtlasGenerator class facilitates the generation of the atlas bitmap.
                ImmediateAtlasGenerator<
                    float, // pixel type of buffer for individual glyphs depends on generator function
                    3, // number of atlas color channels
                    &msdfGenerator, // function to generate bitmaps for individual glyphs
                    BitmapAtlasStorage<byte, 3> // class that stores the atlas bitmap
                    // For example, a custom atlas storage class that stores it in VRAM can be used.
                > generator(width, height);
                // GeneratorAttributes can be modified to change the generator's default settings.
                GeneratorAttributes attributes;
                generator.setAttributes(attributes);
                generator.setThreadCount(4);
                // Generate atlas bitmap
                generator.generate(glyphs.data(), glyphs.size());

                msdfgen::BitmapConstRef<byte, 3> buffer;
                buffer = generator.atlasStorage();

                // The atlas bitmap can now be retrieved via atlasStorage as a BitmapConstRef.
                // The glyphs array (or fontGeometry) contains positioning data for typesetting text.
                // success = myProject::submitAtlasBitmapAndLayout(generator.atlasStorage(), glyphs);
                std::string pixels(reinterpret_cast<const char*>(buffer.pixels), buffer.width * buffer.height);

                auto t = LuaIntf::LuaRef::createTable(L);
                t.set<int, std::string>(1, sdfJson);
                t.set<int, std::string>(2, pixels);
                t.set<int, int>(3, (int)imageType);
                t.set<int, int>(4, buffer.width);
                t.set<int, int>(5, buffer.height);

                // Cleanup
                msdfgen::destroyFont(font);

                msdfgen::deinitializeFreetype(ft);

                return t;
            }
            else if (imageType == ImageType::MTSDF)
            {
                // The ImmediateAtlasGenerator class facilitates the generation of the atlas bitmap.
                ImmediateAtlasGenerator<
                    float, // pixel type of buffer for individual glyphs depends on generator function
                    4, // number of atlas color channels
                    &mtsdfGenerator, // function to generate bitmaps for individual glyphs
                    BitmapAtlasStorage<byte, 4> // class that stores the atlas bitmap
                    // For example, a custom atlas storage class that stores it in VRAM can be used.
                > generator(width, height);
                // GeneratorAttributes can be modified to change the generator's default settings.
                GeneratorAttributes attributes;
                generator.setAttributes(attributes);
                generator.setThreadCount(4);
                // Generate atlas bitmap
                generator.generate(glyphs.data(), glyphs.size());

                msdfgen::BitmapConstRef<byte, 4> buffer;
                buffer = generator.atlasStorage();

                // The atlas bitmap can now be retrieved via atlasStorage as a BitmapConstRef.
                // The glyphs array (or fontGeometry) contains positioning data for typesetting text.
                //success = myProject::submitAtlasBitmapAndLayout(generator.atlasStorage(), glyphs);
                std::string pixels(reinterpret_cast<const char*>(buffer.pixels), buffer.width * buffer.height);

                auto t = LuaIntf::LuaRef::createTable(L);
                t.set<int, std::string>(1, sdfJson);
                t.set<int, std::string>(2, pixels);
                t.set<int, int>(3, (int)imageType);
                t.set<int, int>(4, buffer.width);
                t.set<int, int>(5, buffer.height);

                // Cleanup
                msdfgen::destroyFont(font);

                msdfgen::deinitializeFreetype(ft);

                return t;
            }
        }
    }
}

bool exportJSON(const FontGeometry* fonts, int fontCount, double fontSize, double pxRange, int atlasWidth, int atlasHeight, ImageType imageType, const char* filename, bool kerning) {
    YDirection yDirection = YDirection::BOTTOM_UP;

    FILE* f = fopen(filename, "w");
    if (!f)
        return false;
    fputs("{", f);

    // Atlas properties
    fputs("\"atlas\":{", f); {
        fprintf(f, "\"type\":\"%s\",", imageTypeString(imageType));
        if (imageType == ImageType::SDF || imageType == ImageType::PSDF || imageType == ImageType::MSDF || imageType == ImageType::MTSDF)
            fprintf(f, "\"distanceRange\":%.17g,", pxRange);
        fprintf(f, "\"size\":%.17g,", fontSize);
        fprintf(f, "\"width\":%d,", atlasWidth);
        fprintf(f, "\"height\":%d,", atlasHeight);
        fprintf(f, "\"yOrigin\":\"%s\"", yDirection == YDirection::TOP_DOWN ? "top" : "bottom");
    } fputs("},", f);

    if (fontCount > 1)
        fputs("\"variants\":[", f);
    for (int i = 0; i < fontCount; ++i) {
        const FontGeometry& font = fonts[i];
        if (fontCount > 1)
            fputs(i == 0 ? "{" : ",{", f);

        // Font name
        const char* name = font.getName();
        if (name)
            fprintf(f, "\"name\":\"%s\",", escapeJsonString(name).c_str());

        // Font metrics
        fputs("\"metrics\":{", f); {
            double yFactor = yDirection == YDirection::TOP_DOWN ? -1 : 1;
            const msdfgen::FontMetrics& metrics = font.getMetrics();
            fprintf(f, "\"emSize\":%.17g,", metrics.emSize);
            fprintf(f, "\"lineHeight\":%.17g,", metrics.lineHeight);
            fprintf(f, "\"ascender\":%.17g,", yFactor * metrics.ascenderY);
            fprintf(f, "\"descender\":%.17g,", yFactor * metrics.descenderY);
            fprintf(f, "\"underlineY\":%.17g,", yFactor * metrics.underlineY);
            fprintf(f, "\"underlineThickness\":%.17g", metrics.underlineThickness);
        } fputs("},", f);

        // Glyph mapping
        fputs("\"glyphs\":[", f);
        bool firstGlyph = true;
        for (const GlyphGeometry& glyph : font.getGlyphs()) {
            fputs(firstGlyph ? "{" : ",{", f);
            switch (font.getPreferredIdentifierType()) {
            case GlyphIdentifierType::GLYPH_INDEX:
                fprintf(f, "\"index\":%d,", glyph.getIndex());
                break;
            case GlyphIdentifierType::UNICODE_CODEPOINT:
                fprintf(f, "\"unicode\":%u,", glyph.getCodepoint());
                break;
            }
            fprintf(f, "\"advance\":%.17g", glyph.getAdvance());
            double l, b, r, t;
            glyph.getQuadPlaneBounds(l, b, r, t);
            if (l || b || r || t) {
                switch (yDirection) {
                case YDirection::BOTTOM_UP:
                    fprintf(f, ",\"planeBounds\":{\"left\":%.17g,\"bottom\":%.17g,\"right\":%.17g,\"top\":%.17g}", l, b, r, t);
                    break;
                case YDirection::TOP_DOWN:
                    fprintf(f, ",\"planeBounds\":{\"left\":%.17g,\"top\":%.17g,\"right\":%.17g,\"bottom\":%.17g}", l, -t, r, -b);
                    break;
                }
            }
            glyph.getQuadAtlasBounds(l, b, r, t);
            if (l || b || r || t) {
                switch (yDirection) {
                case YDirection::BOTTOM_UP:
                    fprintf(f, ",\"atlasBounds\":{\"left\":%.17g,\"bottom\":%.17g,\"right\":%.17g,\"top\":%.17g}", l, b, r, t);
                    break;
                case YDirection::TOP_DOWN:
                    fprintf(f, ",\"atlasBounds\":{\"left\":%.17g,\"top\":%.17g,\"right\":%.17g,\"bottom\":%.17g}", l, atlasHeight - t, r, atlasHeight - b);
                    break;
                }
            }
            fputs("}", f);
            firstGlyph = false;
        } fputs("]", f);

        // Kerning pairs
        if (kerning) {
            fputs(",\"kerning\":[", f);
            bool firstPair = true;
            switch (font.getPreferredIdentifierType()) {
            case GlyphIdentifierType::GLYPH_INDEX:
                for (const std::pair<std::pair<int, int>, double>& kernPair : font.getKerning()) {
                    fputs(firstPair ? "{" : ",{", f);
                    fprintf(f, "\"index1\":%d,", kernPair.first.first);
                    fprintf(f, "\"index2\":%d,", kernPair.first.second);
                    fprintf(f, "\"advance\":%.17g", kernPair.second);
                    fputs("}", f);
                    firstPair = false;
                }
                break;
            case GlyphIdentifierType::UNICODE_CODEPOINT:
                for (const std::pair<std::pair<int, int>, double>& kernPair : font.getKerning()) {
                    const GlyphGeometry* glyph1 = font.getGlyph(msdfgen::GlyphIndex(kernPair.first.first));
                    const GlyphGeometry* glyph2 = font.getGlyph(msdfgen::GlyphIndex(kernPair.first.second));
                    if (glyph1 && glyph2 && glyph1->getCodepoint() && glyph2->getCodepoint()) {
                        fputs(firstPair ? "{" : ",{", f);
                        fprintf(f, "\"unicode1\":%u,", glyph1->getCodepoint());
                        fprintf(f, "\"unicode2\":%u,", glyph2->getCodepoint());
                        fprintf(f, "\"advance\":%.17g", kernPair.second);
                        fputs("}", f);
                        firstPair = false;
                    }
                }
                break;
            } fputs("]", f);
        }

        if (fontCount > 1)
            fputs("}", f);
    }
    if (fontCount > 1)
        fputs("]", f);

    fputs("}\n", f);
    fclose(f);
    return true;
}

// byte float 4
template <typename T, typename S, int N, GeneratorFunction<S, N> GEN_FN>
static bool exportTexture(const std::vector<GlyphGeometry>& glyphs, const std::vector<FontGeometry>& fonts, int atlasWidth, int atlasHeight, GeneratorAttributes &attributes, int threadCount, ImageFormat imageFormat, const char* imageFilename) {
    ImmediateAtlasGenerator<S, N, GEN_FN, BitmapAtlasStorage<T, N> > generator(atlasWidth, atlasHeight);
    generator.setAttributes(attributes);
    generator.setThreadCount(threadCount);
    generator.generate(glyphs.data(), glyphs.size());
    msdfgen::BitmapConstRef<T, N> bitmap = (msdfgen::BitmapConstRef<T, N>) generator.atlasStorage();

    bool success = true;

    if (imageFilename) {
        if (saveImage(bitmap, imageFormat, imageFilename, YDirection::BOTTOM_UP))
            puts("[SDFPlugin]Atlas image file saved.");
        else {
            success = false;
            puts("[SDFPlugin]Failed to save the atlas as an image file.");
        }
    }

    return success;
}

int exportSDF(const char* fontFilename, const std::string charsetStr, double fontSize, double pxRange, int atlasWidth, int atlasHeight, TightAtlasPacker::DimensionsConstraint dimensionConstraint, ImageType imageType, ImageFormat imageFormat, bool kerning, const char* exportFilename)
{
    bool success = false;
    int charSetLength = 0;
    int charLoadedLength = 0;
    // Initialize instance of FreeType library
    if (msdfgen::FreetypeHandle* ft = msdfgen::initializeFreetype()) {
        // Load font file
        if (msdfgen::FontHandle* font = msdfgen::loadFont(ft, fontFilename)) {
            // Storage for glyph geometry and their coordinates in the atlas
            std::vector<GlyphGeometry> glyphs;
            // FontGeometry is a helper class that loads a set of glyphs from a single font.
            // It can also be used to get additional font metrics, kerning information, etc.
            FontGeometry fontGeometry(&glyphs);

            Charset charset;
            
            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
            std::wstring wide = converter.from_bytes(charsetStr);

            for (std::wstring::const_iterator i = wide.begin(); i != wide.end(); i++)
            {  
                wchar_t code = *i;
                charset.add(code);
            }

            charSetLength = charset.size();

            // Load a set of character glyphs:
            // The second argument can be ignored unless you mix different font sizes in one atlas.
            // In the last argument, you can specify a charset other than ASCII.
            // To load specific glyph indices, use loadGlyphs instead.
            charLoadedLength = fontGeometry.loadCharset(font, 1.0, charset, false);

            std::vector<FontGeometry> fontGeometryList;
            fontGeometryList.push_back(fontGeometry);

            // Apply MSDF edge coloring. See edge-coloring.h for other coloring strategies.
            const double maxCornerAngle = 3.0;
            for (GlyphGeometry& glyph : glyphs)
                glyph.edgeColoring(&msdfgen::edgeColoringSimple, maxCornerAngle, 0);
            // TightAtlasPacker class computes the layout of the atlas.
            TightAtlasPacker packer;
            // Set atlas parameters:
            // setDimensions or setDimensionsConstraint to find the best value
            if ((int)dimensionConstraint == -1)
            {
                packer.setDimensions(atlasWidth, atlasHeight);
            }
            else
            {
                packer.setDimensionsConstraint(dimensionConstraint);
            }
            // setScale for a fixed size or setMinimumScale to use the largest that fits
            packer.setMinimumScale(24.0);
            packer.setScale(fontSize);
            // setPixelRange or setUnitRange
            packer.setPixelRange(pxRange);
            packer.setMiterLimit(1.0);
            // Compute atlas layout - pack glyphs
            packer.pack(glyphs.data(), glyphs.size());
            // Get final atlas dimensions
            int width = atlasWidth, height = atlasHeight;
            packer.getDimensions(width, height);

            GeneratorAttributes attributes;

            attributes.config.overlapSupport = true;
            attributes.scanlinePass = true;
            attributes.config.errorCorrection.distanceCheckMode = msdfgen::ErrorCorrectionConfig::DO_NOT_CHECK_DISTANCE;

            char fullTexPath[1000] = {};

            strcat(fullTexPath, exportFilename);
            strcat(fullTexPath, ".");

            switch (imageFormat) {
            case ImageFormat::PNG:
                strcat(fullTexPath, "png");
                break;
            case ImageFormat::BMP:
                strcat(fullTexPath, "bmp");
                break;
            case ImageFormat::TIFF:
                strcat(fullTexPath, "tiff");
                break;
            case ImageFormat::UNSPECIFIED:
                break;
            default:
                break;
            }

            if (imageType == ImageType::SDF)
            {
                exportTexture<byte, float, 1, sdfGenerator>(glyphs, fontGeometryList, width, height, attributes, THREAD_COUNT, imageFormat, fullTexPath);
            }
            else if (imageType == ImageType::PSDF)
            {
                exportTexture<byte, float, 1, psdfGenerator>(glyphs, fontGeometryList, width, height, attributes, THREAD_COUNT, imageFormat, fullTexPath);
            }
            else if (imageType == ImageType::MSDF)
            {
                exportTexture<byte, float, 3, msdfGenerator>(glyphs, fontGeometryList, width, height, attributes, THREAD_COUNT, imageFormat, fullTexPath);
            }
            else if (imageType == ImageType::MTSDF)
            {
                exportTexture<byte, float, 4, mtsdfGenerator>(glyphs, fontGeometryList, width, height, attributes, THREAD_COUNT, imageFormat, fullTexPath);
            }
            else if (imageType == ImageType::HARD_MASK)
            {
                exportTexture<byte, float, 1, scanlineGenerator>(glyphs, fontGeometryList, width, height, attributes, THREAD_COUNT, imageFormat, fullTexPath);
            }

            char fullJsonPath[1000] = {};

            strcat(fullJsonPath, exportFilename);
            strcat(fullJsonPath, ".json");

            if (exportJSON(fontGeometryList.data(), fontGeometryList.size(), fontSize, pxRange, width, height, imageType, fullJsonPath, kerning))
                puts("[SDFPlugin]Glyph layout and metadata written into JSON file.");
            else {
                puts("[SDFPlugin]Failed to write JSON output file.");
            }

            msdfgen::destroyFont(font);
        }

        msdfgen::deinitializeFreetype(ft);
    }

    return charSetLength - charLoadedLength;
}

LuaIntf::LuaRef stringToUnicode(lua_State* L, const std::string str)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wide = converter.from_bytes(str);

    LuaIntf::LuaState LS(L);
    LS.newTable();
    LuaIntf::LuaRef ref(L, -1);
    LS.pop();

    int index = 0;
    for (std::wstring::const_iterator i = wide.begin(); i != wide.end(); i++)
    {
        index++;
        wchar_t code = *i;
        ref.set<int, int>(index, code);
    }

    return ref;
}
//// The ImmediateAtlasGenerator class facilitates the generation of the atlas bitmap.
//ImmediateAtlasGenerator<
//    float, // pixel type of buffer for individual glyphs depends on generator function
//    1, // number of atlas color channels
//    &sdfGenerator, // function to generate bitmaps for individual glyphs
//    BitmapAtlasStorage<byte, 1> // class that stores the atlas bitmap
//    // For example, a custom atlas storage class that stores it in VRAM can be used.
//> generator(width, height);
//// GeneratorAttributes can be modified to change the generator's default settings.
//
//generator.setAttributes(attributes);
//generator.setThreadCount(4);
//// Generate atlas bitmap
//generator.generate(glyphs.data(), glyphs.size());
//
//msdfgen::BitmapConstRef<byte, 1> buffer;
//buffer = generator.atlasStorage();
//
//// The atlas bitmap can now be retrieved via atlasStorage as a BitmapConstRef.
//// The glyphs array (or fontGeometry) contains positioning data for typesetting text.
//// success = myProject::submitAtlasBitmapAndLayout(generator.atlasStorage(), glyphs);
//  // Cleanup
//msdfgen::destroyFont(font);
//
//msdfgen::deinitializeFreetype(ft);
//
///*auto t = LuaIntf::LuaRef::createTable(_state_);
//t.set<int, std::string>(1, sdfJson);
//t.set<int, const byte*>(2, buffer.pixels);
//return t;*/

using namespace LuaIntf;

static void register_example(lua_State* L) {

    auto t = LuaRef::createTable(L);

    LuaBinding(t)
        .beginModule("SDFfont")
        .addFunction("generateSDF", generateSDF)
        .addFunction("generateSDFBuffer", generateSDFBuffer)
        .addFunction("exportSDF", exportSDF)
        .addFunction("stringToUnicode", stringToUnicode)
        .endModule();
	LuaBinding(t)
		.beginClass<SDFLoader>("SDFLoader")
		.addStaticFunction("loadSDFData", &SDFLoader::loadSDFData)
		.addStaticFunction("getCharInfoFromId", &SDFLoader::getCharInfoFromId)
		.addStaticFunction("getUniformDataFromId", &SDFLoader::getUniformDataFromId)
		.addStaticFunction("getStringWidthFromId", &SDFLoader::getStringWidthFromId);
    t.pushToStack();
}

// 插件的主要入口从这里开始(主线程)
static int SDFFont(EPluginMsgType eMsgType, void* param1) {
    
    switch (eMsgType) {
        case ELuaOnReady:{
                auto* state = (lua_State*)param1;
                _state_ = state;
                // 主线程LUA初始化完毕
                register_example(state);
            }
            break;
        case EThreadLuaOnReady:
        {
            auto* state = (lua_State*)param1;
            // 主线程LUA初始化完毕
            register_example(state);
        }
            // 线程池LUA初始化完毕，在线程池线程中调用。
            // register_example((lua_State*)param2);
            break;
        case EFrameUpdate:
            // 每帧回调 此时的 param1 为dt ，业务开发自行转换使用
            break;
        case EOnPause:
            // 暂停
            break;
        case EOnResume:
            // 继续
            break;
        case EOnExit:
            // 退出的时候, 如果业务持有了lua虚拟机，需要在此释放，还有就是类似于全局的东西也要考虑释放
            break;
        default:
            break;
    }

    return 0;
}

// example 既是插件名字也是入口函数名字。
BABE_PLUGIN_ENTRY(SDFFont)
