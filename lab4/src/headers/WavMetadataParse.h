#ifndef WAV_METADATA_PARSE
#define WAV_METADATA_PARSE

#include <iostream>
#include <unordered_map>
using std::unordered_map;
using std::fstream;
using std::string;
#define SIZE_OF_CHUNK_NAME 4 // в байтах

class BinaryStreamIn;

class CompareString {
public:
    bool compareString(const string &s1, const string &s2);
};

class WavMetadataParser : public CompareString {
public:
    WavMetadataParser() {}

    virtual int parse(BinaryStreamIn &streamInObj) = 0;
};

class ParserRIFF : public WavMetadataParser {
public:
    virtual int parse(BinaryStreamIn &streamInObj) override;
};

class ParserFmt : public WavMetadataParser {
public:
    virtual int parse(BinaryStreamIn &streamInObj) override;
};

class ParserLIST : public WavMetadataParser {
public:
    virtual int parse(BinaryStreamIn &streamInObj) override;
};

class ParserData : public WavMetadataParser {
public:
    virtual int parse(BinaryStreamIn &streamInObj) override;
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
        add<ParserData>("data");
    }

    template <class T>
    void add(const string &parserName) {
        auto it = this->WavMetadataParsersRegistry.find(parserName);
        if (it == this->WavMetadataParsersRegistry.end()) {
            this->WavMetadataParsersRegistry[parserName] = new WavParserCreator<T>();
        }
    }

    WavMetadataParser * create(const char parserName[SIZE_OF_CHUNK_NAME]) {
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
