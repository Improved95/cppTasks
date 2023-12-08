#ifndef WAV_METADATA_PARSE
#define WAV_METADATA_PARSE

#include <iostream>
#include <unordered_map>
using std::unordered_map;
using std::fstream;
using std::string;

class BinaryStreamIn;

class WavMetadataParser {
public:
    WavMetadataParser() {}

    virtual int parse(fstream &input, BinaryStreamIn &streamInObj) = 0;
};

class ParserRIFF : public WavMetadataParser {
public:
    virtual int parse(fstream &input, BinaryStreamIn &streamInObj) override;
};

class ParserFmt : public WavMetadataParser {
public:
    virtual int parse(fstream &input, BinaryStreamIn &streamInObj) override;
};

class ParserLIST : public WavMetadataParser {
public:
    virtual int parse(fstream &input, BinaryStreamIn &streamInObj) override;
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
public:
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
