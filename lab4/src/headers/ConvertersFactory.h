#ifndef FACTORY
#define FACTORY

#include "Converter.h"

class NsuConverterCreatorI {
public:
    virtual NsuConverterI * createConverter(const string &parameters, const size_t createNumber) const = 0;
};

template <class T>
class NsuConverterCreator : public NsuConverterCreatorI {
public:
    virtual NsuConverterI * createConverter(const string &parameters, const size_t createNumber) const override {
        return new T(parameters, createNumber);
    }
};

class NsuConvertersFactory {
public:
    NsuConvertersFactory() {
        add<NsuMute>(NsuConvertersInfo::getConvertersName()[0]);
        add<NsuMix>(NsuConvertersInfo::getConvertersName()[1]);
    }

    template<class T>
    void add(const string &converterName) {
        auto it = convetersRegistry.find(converterName);
        if (it == convetersRegistry.end()) {
            convetersRegistry[converterName] = new NsuConverterCreator<T>();
        }
    }

    NsuConverterI * create(const string &converterName, const string &parameters, const size_t createNumber) {
        auto it = convetersRegistry.find(converterName);
        if (it != convetersRegistry.end()) {
            return it->second->createConverter(parameters, createNumber);
        }
        return nullptr;
    }

private:
    unordered_map<string, NsuConverterCreatorI*> convetersRegistry;
};

#endif
