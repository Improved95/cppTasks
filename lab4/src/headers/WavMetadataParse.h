#ifndef WAV_METADATA_PARSE
#define WAV_METADATA_PARSE

#include <unordered_map>
#include "Streams.h"
using std::unordered_map;

class WavMetadataParser {
public:
    WavMetadataParser() {}

    virtual int parse() = 0;
};

class ParserRIFF : public WavMetadataParser {
public:
    virtual int parse() override;
};

class ParserFmt : public WavMetadataParser {
public:
    virtual int parse() override;
};

class ParserLIST : public WavMetadataParser {
public:
    virtual int parse() override;
};

class WavParserCreatorI {
public:
    virtual WavMetadataParser * createParser() const = 0;
};

template <class T>
class WavParserCreator : public WavParserCreatorI {
public:
    virtual WavMetadataParser * createParser() const override {
        return new T();
    }
};

class WavMetadataParsersFactory {
    WavMetadataParsersFactory() {
        add<ParserRIFF>("RIFF");
        add<ParserFmt>("fmt ");
        add<ParserLIST>("LIST");
    }

    template <class T>
    void add(const string &parserName) {
        auto it = this->WavMetadataParsersRegistry.find(parserName);
        if (it == this->WavMetadataParsersRegistry.end()) {
            this->WavMetadataParsersRegistry[parserName] = new WavParserCreator<T>();
        }
    }

    WavMetadataParser * create(const string &parserName) {
        auto it = this->WavMetadataParsersRegistry.find(parserName);
        if (it != this->WavMetadataParsersRegistry.end()) {
            return it->second->createParser();
        }
        return nullptr;
    }

private:
    unordered_map<string, WavParserCreatorI*> WavMetadataParsersRegistry;
};

#endif
