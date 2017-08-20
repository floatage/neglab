#ifndef RAWDATAHANDLEMANAGER_H
#define RAWDATAHANDLEMANAGER_H

#include <QVariant>
#include <QList>
#include <QMultiMap>
#include <QThread>

class DataHandler
{
public:
    virtual void init(const QVariant& param) = 0;
    virtual void handle(QVariant& data) = 0;
    virtual void clear() = 0;
    virtual int priority() = 0;
    virtual int identifier() = 0;
    virtual ~DataHandler(){}
};

class DataExtracter: public DataHandler
{
public:
    void init(const QVariant&){}
    void handle(QVariant& data) = 0;
    void clear(){}
    int priority(){ return 1000;}
    int identifier() = 0;
    ~DataExtracter(){}
};

class DataSampler: public DataHandler
{
public:
    void init(const QVariant&){}
    void handle(QVariant& data) = 0;
    void clear(){}
    int priority(){ return 4000;}
    int identifier() = 0;
    ~DataSampler(){}
};

class DataFilter: public DataHandler
{
public:
    void init(const QVariant&){}
    void handle(QVariant& data) = 0;
    void clear(){}
    int priority(){ return 7000;}
    int identifier() = 0;
    ~DataFilter(){}
};

class DataCutter: public DataHandler
{
public:
    void init(const QVariant&){}
    void handle(QVariant& data) = 0;
    void clear(){}
    int priority(){ return 10000;}
    int identifier() = 0;
    ~DataCutter(){}
};

class ExecuteObject: public QThread
{
public:
    virtual void execute(QVariant params) = 0;
    virtual int identifier() = 0;
    virtual ~ExecuteObject(){}
};

class RawDataHandleManager
{
public:
    ~RawDataHandleManager();

    void handle(QVariant& data);
    bool addHandler(DataHandler* handler);
    bool deleteHandler(int priority, int identifier);

    bool addIntermediateResultHook(int priority, int identifier, ExecuteObject* executor);
    bool deleteIntermediateResultHook(int priority, int identifier, int hookIdentifier);

private:
    typedef QList<DataHandler*> HandlerList;
    typedef QMultiMap<int, ExecuteObject*> ExecutorMap;

    RawDataHandleManager();
    RawDataHandleManager(const RawDataHandleManager&);
    RawDataHandleManager& operator =(const RawDataHandleManager&);

    HandlerList dataHandlerChain;
    ExecutorMap intermediateResultHook;
};

#endif // RAWDATAHANDLEMANAGER_H