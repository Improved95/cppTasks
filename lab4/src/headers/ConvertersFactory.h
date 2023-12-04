#ifndef FACTORY
#define FACTORY

#include "Converter.h"

class NsuConverterCreatorI {
public:
    virtual NsuConverterI * createConverter(const string &parameters) const = 0;
};

template <class T>
class NsuConverterCreator : public NsuConverterCreatorI {
public:
    virtual NsuConverterI * createConverter(const string &parameters) const override {
        return new T(parameters);
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

    NsuConverterI * create(const string &converterName, const string &parameterStr) {
        auto it = convetersRegistry.find(converterName);
        if (it != convetersRegistry.end()) {
            return it->second->createConverter(parameterStr);
        }
        return nullptr;
    }

private:
    unordered_map<string, NsuConverterCreatorI*> convetersRegistry;
};

#endif
